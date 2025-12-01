#!/usr/bin/env python3
"""
Automatic Plotting System for Semi-Streaming Algorithm Results

Discovers CSV files, determines optimal ranges, and generates publication-quality plots.
Handles different structures for VARN, VARM, and VARK experiments.
"""

import os
import re
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path
from collections import defaultdict
import argparse
from typing import List, Dict, Tuple, Optional

# Global plot configuration
PLOT_CONFIG = {
    'figure_size': (10, 7),
    'dpi': 150,
    'font_size': 14,
    'line_width': 2,
    'marker_size': 8,
    'grid': True,
    'grid_alpha': 0.3,
    
    # Inset configuration
    'inset_size': (0.40, 0.35),  # width, height as fraction
    'inset_position': (0.52, 0.55),  # x, y position
    'inset_threshold': 0.35,  # Create inset if > 35% of data points are in lower 25% of x-range
    'inset_lower_threshold': 0.25,  # Consider lower 25% of x-range for inset
    
    # Padding for auto-range (as fraction of data range)
    'range_padding': 0.05,  # Reduced from 0.1 to 0.05
    
    # Number of x-axis ticks
    'num_xticks': 10,
    'num_yticks': 8,
    
    # Variant styling
    'variants': {
        '0': {'color': '#1f77b4', 'marker': 'o', 'linestyle': '-'},
        '1': {'color': '#ff7f0e', 'marker': 's', 'linestyle': '-'},
        '2': {'color': '#2ca02c', 'marker': '^', 'linestyle': '-'},
        'N': {'color': '#d62728', 'marker': 'D', 'linestyle': '-'},
    }
}

class PlotGenerator:
    def __init__(self, base_dir: str, output_dir: str):
        self.base_dir = Path(base_dir)
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(parents=True, exist_ok=True)
        
    def discover_csv_files(self) -> Dict:
        """
        Discover all CSV files and organize by experiment structure
        Structure differs by experiment type:
        - VARN: [exp][graph_type][sparsity][algorithm][k_value]
        - VARM: [exp][graph_type][algorithm][k_value]  (no sparsity)
        - VARK: [exp][graph_type][sparsity][algorithm]  (no k_value)
        """
        varn_structure = defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: defaultdict(list))))
        varm_structure = defaultdict(lambda: defaultdict(lambda: defaultdict(list)))
        vark_structure = defaultdict(lambda: defaultdict(lambda: defaultdict(list)))
        
        for csv_file in self.base_dir.glob("**/*.csv"):
            parts = csv_file.relative_to(self.base_dir).parts
            
            # Skip system files
            if csv_file.name.startswith('.'):
                continue
            
            if len(parts) < 4:
                continue
            
            experiment_type = parts[0]  # VARN, VARM, VARK
            
            # Extract variant from filename (case-insensitive)
            filename = csv_file.stem
            variant_match = re.search(r'(kpath|klev)(\d+|N)', filename, re.IGNORECASE)
            if not variant_match:
                continue
            
            variant = variant_match.group(2)  # 0, 1, 2, or N
            
            file_info = {
                'variant': variant,
                'path': csv_file,
                'filename': filename
            }
            
            if experiment_type == 'VARN':
                # Structure: VARN/UNIFORM/logN/kpath/k2/file.csv
                if len(parts) < 5:
                    continue
                graph_type = parts[1]    # UNIFORM, POWLAW
                sparsity = parts[2]      # logN, sqrtN, N2
                algorithm = parts[3]     # kpath, klev
                k_value = parts[4]       # k2, k5, k10
                varn_structure[graph_type][sparsity][algorithm][k_value].append(file_info)
                
            elif experiment_type == 'VARM':
                # Structure: VARM/UNIFORM/kpath/k2/file.csv (no sparsity level)
                if len(parts) < 4:
                    continue
                graph_type = parts[1]    # UNIFORM, POWLAW
                algorithm = parts[2]     # kpath, klev
                k_value = parts[3]       # k2, k5, k10
                varm_structure[graph_type][algorithm][k_value].append(file_info)
                
            elif experiment_type == 'VARK':
                # Structure: VARK/UNIFORM/logN/kPath/file.csv (no k subfolders)
                if len(parts) < 4:
                    continue
                graph_type = parts[1]    # UNIFORM, POWLAW
                sparsity = parts[2]      # logN, sqrtN, N2
                algorithm = parts[3]     # kPath, kLev
                vark_structure[graph_type][sparsity][algorithm].append(file_info)
        
        return {
            'VARN': varn_structure,
            'VARM': varm_structure,
            'VARK': vark_structure
        }
    
    def determine_ranges(self, dataframes: Dict[str, pd.DataFrame], 
                        metric: str, x_col: str = 'N') -> Tuple[Tuple, Tuple, Optional[Tuple]]:
        """
        Determine optimal x and y ranges, and inset range if needed
        Returns: (x_range, y_range, inset_x_range or None)
        """
        all_x = []
        all_y = []
        
        for df in dataframes.values():
            if x_col in df.columns and metric in df.columns:
                all_x.extend(df[x_col].dropna().values)
                all_y.extend(df[metric].dropna().values)
        
        if not all_x or not all_y:
            return (0, 100), (0, 10), None
        
        x_min, x_max = min(all_x), max(all_x)
        y_min, y_max = min(all_y), max(all_y)
        
        # Smart padding: use smaller padding for data that ends at round numbers
        x_span = x_max - x_min
        y_span = y_max - y_min
        
        # If x_max is close to a round number (like 10000), don't add padding beyond it
        if x_span > 0:
            x_padding = x_span * PLOT_CONFIG['range_padding']
            # Check if x_max is close to a round number
            round_numbers = [100, 500, 1000, 2000, 5000, 10000, 20000, 50000]
            for rn in round_numbers:
                if abs(x_max - rn) / x_max < 0.01:  # Within 1% of round number
                    x_max = rn  # Set to exactly that number
                    x_padding = 0  # No padding on the right
                    break
        else:
            x_padding = 0
        
        if y_span > 0:
            y_padding = y_span * PLOT_CONFIG['range_padding']
        else:
            y_padding = 0
        
        x_range = (max(0, x_min - x_padding), x_max + x_padding)
        y_range = (max(0, y_min - y_padding), y_max + y_padding)
        
        # Determine if inset is needed
        inset_x_range = None
        if x_max > 0 and x_span > 0:
            # Check if there's significant data in the lower portion
            lower_threshold = x_min + x_span * PLOT_CONFIG['inset_lower_threshold']
            lower_x = [x for x in all_x if x <= lower_threshold]
            
            # Only create inset if there's enough data points and variation in lower range
            if len(lower_x) / len(all_x) > PLOT_CONFIG['inset_threshold']:
                # Check if there's actual variation in y-values in lower range
                lower_y = []
                for df in dataframes.values():
                    if x_col in df.columns and metric in df.columns:
                        mask = df[x_col] <= lower_threshold
                        lower_y.extend(df[mask][metric].dropna().values)
                
                if lower_y and (max(lower_y) - min(lower_y)) / y_span > 0.1:  # At least 10% variation
                    inset_x_range = (max(0, x_min - x_padding * 0.5), lower_threshold)
        
        return x_range, y_range, inset_x_range
    
    def compute_smart_ticks(self, range_tuple: Tuple[float, float], 
                           num_ticks: int = 6) -> List[float]:
        """Compute nice tick positions"""
        min_val, max_val = range_tuple
        span = max_val - min_val
        
        if span == 0:
            return [min_val]
        
        # Find a nice step size
        raw_step = span / (num_ticks - 1)
        magnitude = 10 ** np.floor(np.log10(raw_step))
        
        # Round to nice numbers (1, 2, 5) * 10^n
        nice_steps = [1, 2, 5, 10]
        normalized = raw_step / magnitude
        nice_step = min([s for s in nice_steps if s >= normalized], default=10)
        step = nice_step * magnitude
        
        # Generate ticks
        start = np.floor(min_val / step) * step
        ticks = []
        current = start
        while current <= max_val + step/2:
            if current >= min_val - step/2:
                ticks.append(current)
            current += step
        
        return ticks
    
    def create_plot(self, csv_files: List[Dict], experiment_type: str, 
                   params: Dict, metric: str, metric_label: str):
        """Create a single plot for given configuration and metric"""
        
        # Load data for all variants
        dataframes = {}
        
        for file_info in csv_files:
            variant = file_info['variant']
            try:
                df = pd.read_csv(file_info['path'])
                
                # Convert Memory from KB to MB
                if 'Memory (KB)' in df.columns:
                    df['Memory (MB)'] = df['Memory (KB)'] / 1024.0
                
                dataframes[variant] = df
            except Exception as e:
                print(f"Error reading {file_info['path']}: {e}")
                continue
        
        if not dataframes:
            return
        
        # Update metric if it's memory
        if metric == 'Memory (KB)':
            metric = 'Memory (MB)'
            metric_label = 'Memory (MB)'
        
        # Determine x-axis column
        if experiment_type == 'VARN':
            x_col = 'N'
            x_label = 'Number of Vertices (N)'
        elif experiment_type == 'VARM':
            x_col = 'M' if 'M' in list(dataframes.values())[0].columns else 'N'
            x_label = 'Number of Edges (M)'
        elif experiment_type == 'VARK':
            x_col = 'K' if 'K' in list(dataframes.values())[0].columns else 'N'
            x_label = 'Space Parameter (K)'
        else:
            x_col = 'N'
            x_label = 'N'
        
        # Check if metric exists
        metric_exists = any(metric in df.columns for df in dataframes.values())
        if not metric_exists:
            return
        
        # Determine ranges
        x_range, y_range, inset_x_range = self.determine_ranges(dataframes, metric, x_col)
        
        # Create figure
        fig, ax = plt.subplots(figsize=PLOT_CONFIG['figure_size'], dpi=PLOT_CONFIG['dpi'])
        
        # Plot each variant
        plotted_any = False
        for variant in ['0', '1', '2', 'N']:
            if variant not in dataframes:
                continue
            
            df = dataframes[variant]
            if x_col not in df.columns or metric not in df.columns:
                continue
            
            style = PLOT_CONFIG['variants'][variant]
            
            # Determine label
            algo_name = params['algorithm'].lower()
            if 'path' in algo_name:
                label = f"kPath{variant}"
            elif 'lev' in algo_name:
                label = f"kLev{variant}"
            else:
                label = f"{params['algorithm']}{variant}"
            
            ax.plot(df[x_col], df[metric], 
                   label=label,
                   color=style['color'],
                   marker=style['marker'],
                   linestyle=style['linestyle'],
                   linewidth=PLOT_CONFIG['line_width'],
                   markersize=PLOT_CONFIG['marker_size'],
                   markevery=max(1, len(df) // 10))
            plotted_any = True
        
        if not plotted_any:
            plt.close()
            return
        
        # Configure main plot
        ax.set_xlabel(x_label, fontsize=PLOT_CONFIG['font_size'])
        ax.set_ylabel(metric_label, fontsize=PLOT_CONFIG['font_size'])
        ax.set_xlim(x_range)
        ax.set_ylim(y_range)
        
        # Set ticks
        x_ticks = self.compute_smart_ticks(x_range, PLOT_CONFIG['num_xticks'])
        y_ticks = self.compute_smart_ticks(y_range, PLOT_CONFIG['num_yticks'])
        ax.set_xticks(x_ticks)
        ax.set_yticks(y_ticks)
        
        if PLOT_CONFIG['grid']:
            ax.grid(True, alpha=PLOT_CONFIG['grid_alpha'])
        
        ax.legend(loc='upper left', fontsize=PLOT_CONFIG['font_size']-2, 
                 framealpha=0.9, ncol=2 if len(dataframes) > 2 else 1)
        
        # Add inset if needed
        if inset_x_range is not None:
            self.add_inset(fig, ax, dataframes, x_col, metric, inset_x_range)
        
        # Create title based on experiment type
        algo_display = "kPath" if "path" in params['algorithm'].lower() else "kLev"
        
        if experiment_type == 'VARN':
            # VARN: algorithm (k=X) - sparsity - graph_type
            k_display = f"(k={params['k_value'].replace('k', '')})"
            sparsity_display = params['sparsity'].replace('N2', 'n²')
            title = f"{algo_display} {k_display} - {sparsity_display} - {params['graph_type']}"
        elif experiment_type == 'VARM':
            # VARM: algorithm (k=X) - graph_type
            k_display = f"(k={params['k_value'].replace('k', '')})"
            title = f"{algo_display} {k_display} - {params['graph_type']}"
        elif experiment_type == 'VARK':
            # VARK: algorithm - sparsity - graph_type
            sparsity_display = params['sparsity'].replace('N2', 'n²')
            title = f"{algo_display} - {sparsity_display} - {params['graph_type']}"
        else:
            title = f"{algo_display}"
        
        ax.set_title(title, fontsize=PLOT_CONFIG['font_size']+2, pad=20)
        
        plt.tight_layout()
        
        # Create output directory and filename based on experiment type
        if experiment_type == 'VARN':
            output_subdir = self.output_dir / 'VARN' / params['graph_type'] / params['sparsity'] / params['algorithm'] / params['k_value']
            base_name = f"{params['algorithm']}_{params['k_value']}_{params['sparsity']}"
        elif experiment_type == 'VARM':
            output_subdir = self.output_dir / 'VARM' / params['graph_type'] / params['algorithm'] / params['k_value']
            base_name = f"{params['algorithm']}_{params['k_value']}"
        elif experiment_type == 'VARK':
            output_subdir = self.output_dir / 'VARK' / params['graph_type'] / params['sparsity'] / params['algorithm']
            base_name = f"{params['algorithm']}_{params['sparsity']}"
        else:
            return
        
        output_subdir.mkdir(parents=True, exist_ok=True)
        
        metric_safe = metric.replace(' ', '_').replace('(', '').replace(')', '')
        
        # Find next available sequence number
        seq_num = 1
        while True:
            output_file = output_subdir / f"{base_name}_{metric_safe}_v{seq_num:02d}.png"
            if not output_file.exists():
                break
            seq_num += 1
        
        plt.savefig(output_file, dpi=PLOT_CONFIG['dpi'], bbox_inches='tight')
        plt.close()
        
        print(f"✓ {output_file}")
    
    def add_inset(self, fig, main_ax, dataframes: Dict[str, pd.DataFrame], 
                  x_col: str, metric: str, inset_x_range: Tuple[float, float]):
        """Add zoomed-in inset to the plot"""
        inset_ax = fig.add_axes([
            PLOT_CONFIG['inset_position'][0],
            PLOT_CONFIG['inset_position'][1],
            PLOT_CONFIG['inset_size'][0],
            PLOT_CONFIG['inset_size'][1]
        ])
        
        # Determine y-range for inset
        inset_y_values = []
        for df in dataframes.values():
            if x_col in df.columns and metric in df.columns:
                mask = (df[x_col] >= inset_x_range[0]) & (df[x_col] <= inset_x_range[1])
                inset_y_values.extend(df[mask][metric].dropna().values)
        
        if inset_y_values:
            y_min, y_max = min(inset_y_values), max(inset_y_values)
            y_span = y_max - y_min
            y_padding = y_span * 0.05  # Smaller padding for inset
            inset_y_range = (max(0, y_min - y_padding), y_max + y_padding)
        else:
            inset_y_range = (0, 10)
        
        # Plot data in inset
        for variant in ['0', '1', '2', 'N']:
            if variant not in dataframes:
                continue
            
            df = dataframes[variant]
            if x_col not in df.columns or metric not in df.columns:
                continue
            
            mask = (df[x_col] >= inset_x_range[0]) & (df[x_col] <= inset_x_range[1])
            inset_df = df[mask]
            
            if len(inset_df) == 0:
                continue
            
            style = PLOT_CONFIG['variants'][variant]
            
            inset_ax.plot(inset_df[x_col], inset_df[metric],
                         color=style['color'],
                         marker=style['marker'],
                         linestyle=style['linestyle'],
                         linewidth=PLOT_CONFIG['line_width']-0.5,
                         markersize=PLOT_CONFIG['marker_size']-2)
        
        # Configure inset
        inset_ax.set_xlim(inset_x_range)
        inset_ax.set_ylim(inset_y_range)
        
        inset_x_ticks = self.compute_smart_ticks(inset_x_range, num_ticks=4)
        inset_y_ticks = self.compute_smart_ticks(inset_y_range, num_ticks=4)
        inset_ax.set_xticks(inset_x_ticks)
        inset_ax.set_yticks(inset_y_ticks)
        
        inset_ax.tick_params(labelsize=PLOT_CONFIG['font_size']-4)
        
        if PLOT_CONFIG['grid']:
            inset_ax.grid(True, alpha=PLOT_CONFIG['grid_alpha'])
        
        for spine in inset_ax.spines.values():
            spine.set_edgecolor('black')
            spine.set_linewidth(1.5)
    
    def generate_all_plots(self, experiment_filter: Optional[str] = None,
                          graph_filter: Optional[str] = None,
                          sparsity_filter: Optional[str] = None,
                          k_filter: Optional[str] = None,
                          algorithm_filter: Optional[str] = None):
        """Generate all plots based on discovered CSV files"""
        
        structures = self.discover_csv_files()
        
        metrics = [
            ('Time (s)', 'Time (s)'),
            ('Memory (KB)', 'Memory (MB)'),
            ('AvgPasses', 'Average Passes'),
            ('AvgHeight', 'Average Height'),
        ]
        
        total_plots = 0
        
        # Process VARN
        if not experiment_filter or experiment_filter == 'VARN':
            print("\n=== Processing VARN ===")
            for graph_type in structures['VARN']:
                if graph_filter and graph_type != graph_filter:
                    continue
                
                for sparsity in structures['VARN'][graph_type]:
                    if sparsity_filter and sparsity != sparsity_filter:
                        continue
                    
                    for algorithm in structures['VARN'][graph_type][sparsity]:
                        if algorithm_filter and algorithm.lower() != algorithm_filter.lower():
                            continue
                        
                        for k_value in structures['VARN'][graph_type][sparsity][algorithm]:
                            if k_filter and k_value != k_filter:
                                continue
                            
                            csv_files = structures['VARN'][graph_type][sparsity][algorithm][k_value]
                            params = {
                                'graph_type': graph_type,
                                'sparsity': sparsity,
                                'algorithm': algorithm,
                                'k_value': k_value
                            }
                            
                            for metric_col, metric_label in metrics:
                                self.create_plot(csv_files, 'VARN', params, metric_col, metric_label)
                                total_plots += 1
        
        # Process VARM
        if not experiment_filter or experiment_filter == 'VARM':
            print("\n=== Processing VARM ===")
            for graph_type in structures['VARM']:
                if graph_filter and graph_type != graph_filter:
                    continue
                
                for algorithm in structures['VARM'][graph_type]:
                    if algorithm_filter and algorithm.lower() != algorithm_filter.lower():
                        continue
                    
                    for k_value in structures['VARM'][graph_type][algorithm]:
                        if k_filter and k_value != k_filter:
                            continue
                        
                        csv_files = structures['VARM'][graph_type][algorithm][k_value]
                        params = {
                            'graph_type': graph_type,
                            'algorithm': algorithm,
                            'k_value': k_value
                        }
                        
                        for metric_col, metric_label in metrics:
                            self.create_plot(csv_files, 'VARM', params, metric_col, metric_label)
                            total_plots += 1
        
        # Process VARK
        if not experiment_filter or experiment_filter == 'VARK':
            print("\n=== Processing VARK ===")
            for graph_type in structures['VARK']:
                if graph_filter and graph_type != graph_filter:
                    continue
                
                for sparsity in structures['VARK'][graph_type]:
                    if sparsity_filter and sparsity != sparsity_filter:
                        continue
                    
                    for algorithm in structures['VARK'][graph_type][sparsity]:
                        if algorithm_filter and algorithm.lower() != algorithm_filter.lower():
                            continue
                        
                        csv_files = structures['VARK'][graph_type][sparsity][algorithm]
                        params = {
                            'graph_type': graph_type,
                            'sparsity': sparsity,
                            'algorithm': algorithm
                        }
                        
                        for metric_col, metric_label in metrics:
                            self.create_plot(csv_files, 'VARK', params, metric_col, metric_label)
                            total_plots += 1
        
        print(f"\n{'='*60}")
        print(f"Total plots generated: {total_plots}")
        print(f"Output directory: {self.output_dir}")
        print(f"{'='*60}")

def main():
    parser = argparse.ArgumentParser(
        description="Automatic plotting system for semi-streaming algorithm results"
    )
    parser.add_argument("-i", "--input-dir", type=str,
                       default="results/random_v3",
                       help="Input directory containing CSV files")
    parser.add_argument("-o", "--output-dir", type=str,
                       default="plots_v3",
                       help="Output directory for plots")
    parser.add_argument("-e", "--experiment", type=str,
                       choices=['VARN', 'VARM', 'VARK'],
                       help="Filter by experiment type")
    parser.add_argument("-g", "--graph-type", type=str,
                       choices=['UNIFORM', 'POWLAW'],
                       help="Filter by graph type")
    parser.add_argument("-s", "--sparsity", type=str,
                       choices=['logN', 'sqrtN', 'N2'],
                       help="Filter by sparsity")
    parser.add_argument("-k", "--k-value", type=str,
                       help="Filter by k value (e.g., k2, k5, k10)")
    parser.add_argument("-a", "--algorithm", type=str,
                       choices=['kpath', 'klev', 'kPath', 'kLev'],
                       help="Filter by algorithm")
    
    args = parser.parse_args()
    
    generator = PlotGenerator(args.input_dir, args.output_dir)
    generator.generate_all_plots(
        experiment_filter=args.experiment,
        graph_filter=args.graph_type,
        sparsity_filter=args.sparsity,
        k_filter=args.k_value,
        algorithm_filter=args.algorithm
    )

if __name__ == "__main__":
    main()

# source venv/bin/activate
# pip install pandas matplotlib numpy
# deactivate

# Generate all plots (using latest files)
# python plot_system.py -i results/random_v2 -o plots

# Generate only kpath plots with k=2
# python plot_system.py -i results/random_v2 -o plots -a kpath -k k2

# Generate VARN experiments only, with UNIFORM graphs
# python plot_system.py -e VARN -g UNIFORM

# Use oldest files instead of latest (for reproducibility)
# python plot_system.py --use-oldest

# Generate only sqrtN sparsity with k=5
# python plot_system.py -s sqrtN -k k5

# Combine filters: VARN + UNIFORM + logN + k=10 + kLev
# python plot_system.py -e VARN -g UNIFORM -s logN -k k10 -a klev



# plots/
# ├── VARN/
# │   ├── UNIFORM/
# │   │   ├── logN/
# │   │   │   ├── kpath/
# │   │   │   │   ├── k2/
# │   │   │   │   │   ├── kpath_k2_logN_Time_s.png
# │   │   │   │   │   ├── kpath_k2_logN_Memory_MB.png
# │   │   │   │   │   ├── kpath_k2_logN_AvgPasses.png
# │   │   │   │   │   └── kpath_k2_logN_AvgHeight.png
# │   │   │   │   ├── k5/
# │   │   │   │   └── k10/
# │   │   │   └── klev/
# │   │   ├── sqrtN/
# │   │   └── N2/
# │   └── POWLAW/
# ├── VARM/
# │   └── UNIFORM/
# │       ├── kpath/
# │       │   ├── k2/
# │       │   │   ├── kpath_k2_Time_s.png
# │       │   │   └── ...
# │       │   ├── k5/
# │       │   └── k10/
# │       └── klev/
# └── VARK/
#     └── UNIFORM/
#         ├── logN/
#         │   ├── kPath/
#         │   │   ├── kPath_logN_Time_s.png
#         │   │   └── ...
#         │   └── kLev/
#         ├── sqrtN/
#         └── N2/