#!/usr/bin/env python3
"""
Configurable Plot Generator for Paper Figures

Generates individual plots with fine-grained control over all parameters.
Each plot has its own configuration that can be tuned independently.
"""

import pandas as pd
import matplotlib.pyplot as plt
import brokenaxes
from pathlib import Path
from typing import Dict
import numpy as np
import matplotlib.ticker as mticker

# ============================================================================
# GLOBAL STYLING (applies to all plots)
# ============================================================================

GLOBAL_STYLE = {
    # Default figure size (can be overridden per plot)
    'figure_width': 6.0,
    'figure_height': 6.0,
    'dpi': 200,
    
    # Font sizes
    'title_fontsize': 14,
    'label_fontsize': 20,
    'tick_fontsize': 16,
    'legend_fontsize': 12,
    
    # Line properties
    'line_width': 1.5,
    'marker_size': 6,
    
    # Grid
    'grid_alpha': 0.3,
    'grid_linestyle': '--',

    'output_dir': 'plots/paper/',
}

# Color schemes: Blues for kPath (light to dark), Oranges for kLev
KPATH_COLORS = ['#deebf7', '#9ecae1', '#4292c6', '#08519c']  # Light to dark blue
KLEV_COLORS = ['#fee6ce', '#fdae6b', '#f16913', '#d94801']   # Light to dark orange

# Alternative: More visible colors
KPATH_COLORS_ALT = ['#6baed6', '#4292c6', '#2171b5', '#08519c']  # Medium to dark blues
KLEV_COLORS_ALT = ['#fdae6b', '#fd8d3c', '#f16913', '#d94801']   # Medium to dark oranges

# Choose which palette to use
USE_ALT_COLORS = True  # Set to False for lighter palette

KPATH_COLORS = KPATH_COLORS_ALT if USE_ALT_COLORS else KPATH_COLORS
KLEV_COLORS = KLEV_COLORS_ALT if USE_ALT_COLORS else KLEV_COLORS

# Marker styles
MARKERS = ['o', 's', '^', 'D']  # circle, square, triangle, diamond

# ============================================================================
# PLOT CONFIGURATIONS
# ============================================================================

PLOT_CONFIGS = {
    # ========================================================================
    # ROW 1: VARN (Varying N)
    # ========================================================================
    'varn_logn_k2': {
        # 'title': 'VARN: logN density, k=2',
        # 'title': 'logN, k=2',
        'title': '',
        'csv_files': {
            # kPath variants
            'kpath0': 'results/random_v3/VARN/UNIFORM/logN/kpath/k2/kpath0_k2_seed_1729_itr_1000_20250731_164330.csv',
            'kpath1': 'results/random_v3/VARN/UNIFORM/logN/kpath/k2/kpath1_k2_seed_1729_itr_1000_20250731_164330.csv',
            'kpath2': 'results/random_v3/VARN/UNIFORM/logN/kpath/k2/kpath2_k2_seed_1729_itr_1000_20250731_164330.csv',
            'kpathN': 'results/random_v3/VARN/UNIFORM/logN/kpath/k2/kpathN_k2_seed_1729_itr_1000_20250731_164330.csv',
            # kLev variants
            'klev0': 'results/random_v3/VARN/UNIFORM/logN/klev/k2/klev0_k2_seed_1729_itr_1000_20250731_164330.csv',
            'klev1': 'results/random_v3/VARN/UNIFORM/logN/klev/k2/klev1_k2_seed_1729_itr_1000_20250731_164330.csv',
            'klev2': 'results/random_v3/VARN/UNIFORM/logN/klev/k2/klev2_k2_seed_1729_itr_1000_20250731_164330.csv',
            'klevN': 'results/random_v3/VARN/UNIFORM/logN/klev/k2/klevN_k2_seed_1729_itr_1000_20250731_164330.csv',
        },
        'x_column': 'N',
        'y_column': 'AvgPasses',
        'x_label': 'Number of Vertices (N)',
        'y_label': 'Average Passes',
        'x_scale': 'log',  # 'linear' or 'log'
        'y_scale': 'linear',  # 'linear' or 'log'
        'x_log_base': 2,  # 2 or 10
        'y_log_base': 2,
        'x_range': None,  # None for auto, or (min, max)
        'y_range': None,
        'grid': True,
        'broken_y_axis': True,  # Enable broken axis
        'y_breaks': ((0.9, 4.5), (11, 12)),  # Define the ranges to show
        'height_ratios': [1, 5],  # Ratio of heights for the broken sections        
        'legend': False,  # Will use global legend
        # 'figure_size': (6, 6),  # (width, height) in inches
        'output_file': 'plots/paper/varn_logn_k2_passes.png',
    },
    'varn_sqrtn_k2': {
        # 'title': 'VARN: √n density, k=2',
        'title': '',
        'csv_files': {
            'kpath0': 'results/random_v3/VARN/UNIFORM/sqrtN/kpath/k2/kpath0_k2_seed_1729_itr_1000_20250805_103819.csv',
            'kpath1': 'results/random_v3/VARN/UNIFORM/sqrtN/kpath/k2/kpath1_k2_seed_1729_itr_1000_20250805_103819.csv',
            'kpath2': 'results/random_v3/VARN/UNIFORM/sqrtN/kpath/k2/kpath2_k2_seed_1729_itr_1000_20250805_103819.csv',
            'kpathN': 'results/random_v3/VARN/UNIFORM/sqrtN/kpath/k2/kpathN_k2_seed_1729_itr_1000_20250805_103819.csv',
            'klev0': 'results/random_v3/VARN/UNIFORM/sqrtN/klev/k2/klev0_k2_seed_1729_itr_1000_20250805_103819.csv',
            'klev1': 'results/random_v3/VARN/UNIFORM/sqrtN/klev/k2/klev1_k2_seed_1729_itr_1000_20250805_103819.csv',
            'klev2': 'results/random_v3/VARN/UNIFORM/sqrtN/klev/k2/klev2_k2_seed_1729_itr_1000_20250805_103819.csv',
            'klevN': 'results/random_v3/VARN/UNIFORM/sqrtN/klev/k2/klevN_k2_seed_1729_itr_1000_20250805_103819.csv',
        },
        'x_column': 'N',
        'y_column': 'AvgPasses',
        'x_label': 'Number of Vertices (N)',
        'y_label': 'Average Passes',
        'x_scale': 'log',
        'y_scale': 'linear',
        'x_log_base': 2,
        'y_log_base': 2,
        'x_range': None,
        'y_range': None,
        'grid': True,
        'legend': False,
        'broken_y_axis': True,  # Enable broken axis
        'y_breaks': ((0.9, 6.5), (15, 17)),  # Define the ranges to show
        'height_ratios': [1, 3],  # Ratio of heights for the broken sections        
        # 'figure_size': (6, 6),
        'output_file': 'plots/paper/varn_sqrtn_k2_passes.png',
    },
    'varn_sqrtn_k5': {
        # 'title': 'VARN: √n density, k=5',
        'title': '',
        'csv_files': {
            'kpath0': 'results/random_v3/VARN/UNIFORM/sqrtN/kpath/k5/kpath0_k5_seed_1729_itr_1000_20250805_103819.csv',
            'kpath1': 'results/random_v3/VARN/UNIFORM/sqrtN/kpath/k5/kpath1_k5_seed_1729_itr_1000_20250805_103819.csv',
            'kpath2': 'results/random_v3/VARN/UNIFORM/sqrtN/kpath/k5/kpath2_k5_seed_1729_itr_1000_20250805_103819.csv',
            'kpathN': 'results/random_v3/VARN/UNIFORM/sqrtN/kpath/k5/kpathN_k5_seed_1729_itr_1000_20250805_103819.csv',
            'klev0': 'results/random_v3/VARN/UNIFORM/sqrtN/klev/k5/klev0_k5_seed_1729_itr_1000_20250805_103819.csv',
            'klev1': 'results/random_v3/VARN/UNIFORM/sqrtN/klev/k5/klev1_k5_seed_1729_itr_1000_20250805_103819.csv',
            'klev2': 'results/random_v3/VARN/UNIFORM/sqrtN/klev/k5/klev2_k5_seed_1729_itr_1000_20250805_103819.csv',
            'klevN': 'results/random_v3/VARN/UNIFORM/sqrtN/klev/k5/klevN_k5_seed_1729_itr_1000_20250805_103819.csv',
        },
        'x_column': 'N',
        'y_column': 'AvgPasses',
        'x_label': 'Number of Vertices (N)',
        'y_label': 'Average Passes',
        'x_scale': 'log',
        'y_scale': 'linear',
        'x_log_base': 2,
        'y_log_base': 2,
        'x_range': None,
        'y_range': None,
        'grid': True,
        'legend': False,
        # 'figure_size': (6, 6),
        'output_file': 'plots/paper/varn_sqrtn_k5_passes.png',
    },
    
    # ========================================================================
    # ROW 2: VARM (Varying M)
    # ========================================================================
    'varm_k2': {
        # 'title': 'VARM: k=2',
        'title': '',
        'csv_files': {
            'kpath0': 'results/random_v3/VARM/UNIFORM/kpath/k2/kpath0_k2_seed_1729_itr_100_20250929_090633.csv',
            'kpath1': 'results/random_v3/VARM/UNIFORM/kpath/k2/kpath1_k2_seed_1729_itr_100_20250929_090633.csv',
            'kpath2': 'results/random_v3/VARM/UNIFORM/kpath/k2/kpath2_k2_seed_1729_itr_100_20250929_090633.csv',
            'kpathN': 'results/random_v3/VARM/UNIFORM/kpath/k2/kpathN_k2_seed_1729_itr_100_20250929_090633.csv',
            'klev0': 'results/random_v3/VARM/UNIFORM/klev/k2/klev0_k2_seed_1729_itr_100_20250929_090633.csv',
            'klev1': 'results/random_v3/VARM/UNIFORM/klev/k2/klev1_k2_seed_1729_itr_100_20250929_090633.csv',
            'klev2': 'results/random_v3/VARM/UNIFORM/klev/k2/klev2_k2_seed_1729_itr_100_20250929_090633.csv',
            'klevN': 'results/random_v3/VARM/UNIFORM/klev/k2/klevN_k2_seed_1729_itr_100_20250929_090633.csv',
        },
        'x_column': 'M', 
        'y_column': 'AvgPasses',
        'x_label': 'Number of Edges (M)',
        'y_label': 'Average Passes',
        'x_scale': 'log',
        'y_scale': 'linear',
        'x_log_base': 10,
        'y_log_base': 10,
        'x_range': None,
        'y_range': None,
        'grid': True,
        'legend': False,
        'broken_y_axis': True,  # Enable broken axis
        'y_breaks': ((0.75, 9.25), (20, 21.2)),  # Define the ranges to show
        'height_ratios': [1, 7],  # Ratio of heights for the broken sections 
        # 'figure_size': (7, 6),
        'output_file': 'plots/paper/varm_k2_passes.png',
    },
    'varm_k5': {
        # 'title': 'VARM: k=5',
        'title': '',
        'csv_files': {
            'kpath0': 'results/random_v3/VARM/UNIFORM/kpath/k5/kpath0_k5_seed_1729_itr_100_20250929_090633.csv',
            'kpath1': 'results/random_v3/VARM/UNIFORM/kpath/k5/kpath1_k5_seed_1729_itr_100_20250929_090633.csv',
            'kpath2': 'results/random_v3/VARM/UNIFORM/kpath/k5/kpath2_k5_seed_1729_itr_100_20250929_090633.csv',
            'kpathN': 'results/random_v3/VARM/UNIFORM/kpath/k5/kpathN_k5_seed_1729_itr_100_20250929_090633.csv',
            'klev0': 'results/random_v3/VARM/UNIFORM/klev/k5/klev0_k5_seed_1729_itr_100_20250929_090633.csv',
            'klev1': 'results/random_v3/VARM/UNIFORM/klev/k5/klev1_k5_seed_1729_itr_100_20250929_090633.csv',
            'klev2': 'results/random_v3/VARM/UNIFORM/klev/k5/klev2_k5_seed_1729_itr_100_20250929_090633.csv',
            'klevN': 'results/random_v3/VARM/UNIFORM/klev/k5/klevN_k5_seed_1729_itr_100_20250929_090633.csv',
        },
        'x_column': 'M',
        'y_column': 'AvgPasses',
        'x_label': 'Number of Edges (M)',
        'y_label': 'Average Passes',
        'x_scale': 'log',
        'y_scale': 'linear',
        'x_log_base': 10,
        'y_log_base': 10,
        'x_range': None,
        'y_range': None,
        'grid': True,
        'legend': False,
        # 'figure_size': (7, 6),
        'output_file': 'plots/paper/varm_k5_passes.png',
    },
    'varm_k10': {
        # 'title': 'VARM: k=10',
        'title': '',
        'csv_files': {
            'kpath0': 'results/random_v3/VARM/UNIFORM/kpath/k10/kpath0_k10_seed_1729_itr_100_20250929_090633.csv',
            'kpath1': 'results/random_v3/VARM/UNIFORM/kpath/k10/kpath1_k10_seed_1729_itr_100_20250929_090633.csv',
            'kpath2': 'results/random_v3/VARM/UNIFORM/kpath/k10/kpath2_k10_seed_1729_itr_100_20250929_090633.csv',
            'kpathN': 'results/random_v3/VARM/UNIFORM/kpath/k10/kpathN_k10_seed_1729_itr_100_20250929_090633.csv',
            'klev0': 'results/random_v3/VARM/UNIFORM/klev/k10/klev0_k10_seed_1729_itr_100_20250929_090633.csv',
            'klev1': 'results/random_v3/VARM/UNIFORM/klev/k10/klev1_k10_seed_1729_itr_100_20250929_090633.csv',
            'klev2': 'results/random_v3/VARM/UNIFORM/klev/k10/klev2_k10_seed_1729_itr_100_20250929_090633.csv',
            'klevN': 'results/random_v3/VARM/UNIFORM/klev/k10/klevN_k10_seed_1729_itr_100_20250929_090633.csv',
        },
        'x_column': 'M',
        'y_column': 'AvgPasses',
        'x_label': 'Number of Edges (M)',
        'y_label': 'Average Passes',
        'x_scale': 'log',
        'y_scale': 'linear',
        'x_log_base': 10,
        'y_log_base': 10,
        'x_range': None,
        'y_range': None,
        'grid': True,
        'legend': False,
        # 'figure_size': (7, 6),
        'output_file': 'plots/paper/varm_k10_passes.png',
    },
    # ========================================================================
    # ROW 3: VARK (Varying K)
    # ========================================================================
    'vark_logn': {
        # 'title': 'VARK: logN density',
        'title': '',
        'csv_files': {
            'kpath0': 'results/random_v3/VARK/UNIFORM/logN/kPath/kPath0_logN_seed_1729_itr_1000_20250804_102307.csv',
            'kpath1': 'results/random_v3/VARK/UNIFORM/logN/kPath/kPath1_logN_seed_1729_itr_1000_20250804_102307.csv',
            'kpath2': 'results/random_v3/VARK/UNIFORM/logN/kPath/kPath2_logN_seed_1729_itr_1000_20250804_102307.csv',
            'kpathN': 'results/random_v3/VARK/UNIFORM/logN/kPath/kPathN_logN_seed_1729_itr_1000_20250804_102307.csv',
            'klev0': 'results/random_v3/VARK/UNIFORM/logN/kLev/kLev0_logN_seed_1729_itr_1000_20250804_102307.csv',
            'klev1': 'results/random_v3/VARK/UNIFORM/logN/kLev/kLev1_logN_seed_1729_itr_1000_20250804_102307.csv',
            'klev2': 'results/random_v3/VARK/UNIFORM/logN/kLev/kLev2_logN_seed_1729_itr_1000_20250804_102307.csv',
            'klevN': 'results/random_v3/VARK/UNIFORM/logN/kLev/kLevN_logN_seed_1729_itr_1000_20250804_102307.csv',
        },
        'x_column': 'K',
        'y_column': 'AvgPasses',
        'x_label': 'Space Parameter (K)',
        'y_label': 'Average Passes',
        'x_scale': 'log',
        'y_scale': 'log',  # Try log scale for VARK
        'x_log_base': 2,
        'y_log_base': 2,
        'x_range': None,
        'y_range': None,
        'grid': True,
        'legend': False,
        # 'figure_size': (8, 6.5),
        'broken_y_axis': True,
        'y_breaks': ((0.9, 5), (32, 140)),
        'height_ratios': [1, 3],
        'output_file': 'plots/paper/vark_logn_passes.png',
    }, 
    'vark_sqrtn': {
        # 'title': 'VARK: √n density',
        'title': '',
        'csv_files': {
            'kpath0': 'results/random_v3/VARK/UNIFORM/sqrtN/kPath/kPath0_sqrtN_seed_1729_itr_1000_20250812_052344.csv',
            'kpath1': 'results/random_v3/VARK/UNIFORM/sqrtN/kPath/kPath1_sqrtN_seed_1729_itr_1000_20250812_052344.csv',
            'kpath2': 'results/random_v3/VARK/UNIFORM/sqrtN/kPath/kPath2_sqrtN_seed_1729_itr_1000_20250812_052344.csv',
            'kpathN': 'results/random_v3/VARK/UNIFORM/sqrtN/kPath/kPathN_sqrtN_seed_1729_itr_1000_20250812_052344.csv',
            'klev0': 'results/random_v3/VARK/UNIFORM/sqrtN/kLev/kLev0_sqrtN_seed_1729_itr_1000_20250812_052344.csv',
            'klev1': 'results/random_v3/VARK/UNIFORM/sqrtN/kLev/kLev1_sqrtN_seed_1729_itr_1000_20250812_052344.csv',
            'klev2': 'results/random_v3/VARK/UNIFORM/sqrtN/kLev/kLev2_sqrtN_seed_1729_itr_1000_20250812_052344.csv',
            'klevN': 'results/random_v3/VARK/UNIFORM/sqrtN/kLev/kLevN_sqrtN_seed_1729_itr_1000_20250812_052344.csv',
        },
        'x_column': 'K',
        'y_column': 'AvgPasses',
        'x_label': 'Space Parameter (K)',
        'y_label': 'Average Passes',
        'x_scale': 'log',
        'y_scale': 'log',
        'x_log_base': 2,
        'y_log_base': 2,
        'x_range': None,
        'y_range': None,
        'grid': True,
        'legend': False,
        'broken_y_axis': True,
        'y_breaks': ((0.9, 8), (32, 180)),
        'height_ratios': [1, 2.5],
        # 'figure_size': (8, 6.5),
        'output_file': 'plots/paper/vark_sqrtn_passes.png',
    }, 
    'vark_n2': {
        # 'title': 'VARK: n² density',
        'title': '',
        'csv_files': {
            'kpath0': 'results/random_v3/VARK/UNIFORM/N2/kPath/kPath0_N2_seed_1729_itr_100_20251003_084320.csv',
            'kpath1': 'results/random_v3/VARK/UNIFORM/N2/kPath/kPath1_N2_seed_1729_itr_100_20251003_084320.csv',
            'kpath2': 'results/random_v3/VARK/UNIFORM/N2/kPath/kPath2_N2_seed_1729_itr_100_20251003_084320.csv',
            'kpathN': 'results/random_v3/VARK/UNIFORM/N2/kPath/kPathN_N2_seed_1729_itr_100_20251003_084320.csv',
            'klev0': 'results/random_v3/VARK/UNIFORM/N2/kLev/kLev0_N2_seed_1729_itr_100_20251003_084320.csv',
            'klev1': 'results/random_v3/VARK/UNIFORM/N2/kLev/kLev1_N2_seed_1729_itr_100_20251003_084320.csv',
            'klev2': 'results/random_v3/VARK/UNIFORM/N2/kLev/kLev2_N2_seed_1729_itr_100_20251028_155538.csv',
            'klevN': 'results/random_v3/VARK/UNIFORM/N2/kLev/kLevN_N2_seed_1729_itr_100_20251028_155538.csv',
        },
        'x_column': 'K',
        'y_column': 'AvgPasses',
        'x_label': 'Space Parameter (K)',
        'y_label': 'Average Passes',
        'x_scale': 'log',
        'y_scale': 'log',
        'x_log_base': 2,
        'y_log_base': 2,
        'x_range': None,
        'y_range': None,
        'grid': True,
        'broken_y_axis': True,
        'y_breaks': ((0.9, 10), (32, 240)),
        'height_ratios': [1, 3.5],
        'legend': False,
        # 'figure_size': (8, 6.5),
        'output_file': 'plots/paper/vark_n2_passes.png',
    },
}

# ============================================================================
# PLOTTING FUNCTIONS
# ============================================================================

def get_file_path(dir: str, plot_id: str, broken: bool = False) -> Path:
    """Construct full file path"""
    seq_num = 1
    while True:
        output_file = Path(dir) /  f"{plot_id}_{'broken_' if broken else ''}v{seq_num:02d}.png"
        if not output_file.exists():
            break
        seq_num += 1

    return output_file

def is_brokenaxes(ax):
    return hasattr(ax, "axs")

def iter_axes(ax):
    """Return list of real matplotlib Axes objects."""
    return ax.axs if is_brokenaxes(ax) else [ax]

def int_formatter(x, pos=None):
    # avoid -0
    if abs(x) < 1e-12:
        x = 0
    # show as integer without decimals
    return f"{int(round(x))}"

def apply_axis_formatting(ax, config):
    """
    Applies:
    - log/linear scales
    - tick locators (mostly automatic)
    - tick formatters per requirement
    Works for normal ax and brokenaxes.
    """
    x_scale = config.get("x_scale", "linear")
    y_scale = config.get("y_scale", "linear")
    x_base = config.get("x_log_base", 10)
    y_base = config.get("y_log_base", 10)

    for a in iter_axes(ax):
        # ---------------- X AXIS ----------------
        if x_scale == "log":
            a.set_xscale("log", base=x_base)

            # keep automatic tick placement, just format labels
            if x_base == 10:
                a.xaxis.set_major_formatter(mticker.LogFormatterMathtext(base=10))
            else:
                # integer labels for bases like 2
                a.xaxis.set_major_formatter(mticker.FuncFormatter(int_formatter))

            # hide minor tick labels (optional but cleaner)
            a.xaxis.set_minor_formatter(mticker.NullFormatter())

        else:
            # linear scale
            a.set_xscale("linear")

            # ticks auto but integer-only labels
            a.xaxis.set_major_locator(mticker.MaxNLocator(integer=True))
            a.xaxis.set_major_formatter(mticker.FuncFormatter(int_formatter))

        # ---------------- Y AXIS ----------------
        if y_scale == "log":
            a.set_yscale("log", base=y_base)

            if y_base == 10:
                a.yaxis.set_major_formatter(mticker.LogFormatterMathtext(base=10))
            else:
                a.yaxis.set_major_formatter(mticker.FuncFormatter(int_formatter))

            a.yaxis.set_minor_formatter(mticker.NullFormatter())

        else:
            a.set_yscale("linear")
            a.yaxis.set_major_locator(mticker.MaxNLocator(integer=True))
            a.yaxis.set_major_formatter(mticker.FuncFormatter(int_formatter))

def create_plot(plot_id: str, config: Dict):
    """Generate a single plot based on configuration"""
    
    print(f"\n{'='*60}")
    print(f"Generating: {plot_id}")
    print(f"{'='*60}")
    
    breakAxis = config.get('broken_y_axis', False)

    # Load all CSV files
    dataframes = {}
    for key, filepath in config['csv_files'].items():
        try:
            df = pd.read_csv(filepath)
            dataframes[key] = df
            print(f"✓ Loaded {key}: {Path(filepath).name}")
        except FileNotFoundError:
            print(f"✗ File not found: {filepath}")
        except Exception as e:
            print(f"✗ Error loading {key}: {e}")
    
    if not dataframes:
        print("No data loaded. Skipping plot.")
        return
    
    # Create figure
    fig_width, fig_height = config.get('figure_size', (GLOBAL_STYLE['figure_width'], GLOBAL_STYLE['figure_height']))

    if breakAxis:
        fig=plt.figure(figsize=(fig_width, fig_height), dpi=GLOBAL_STYLE['dpi'])
        ax = brokenaxes.brokenaxes(
            ylims=config.get('y_breaks'),  # Show 0-5 and 10-13, skip 5-10
            height_ratios=config.get('height_ratios', [1, 1]),
            hspace=0.05,  # Space between the broken sections
            despine=True,
            fig=fig
        )
    else:
        fig, ax = plt.subplots(figsize=(fig_width, fig_height), dpi=GLOBAL_STYLE['dpi'])

    # Plot kPath variants (0, 1, 2, N)
    for i, variant in enumerate(['0', '1', '2', 'N']):
        key = f'kpath{variant}'
        if key not in dataframes:
            continue
        
        df = dataframes[key]
        if config['x_column'] not in df.columns or config['y_column'] not in df.columns:
            print(f"Warning: {key} missing required columns")
            continue
        
        label = f'kPath{variant}'
        ax.plot(df[config['x_column']], df[config['y_column']],
               label=label,
               color=KPATH_COLORS[i],
               marker=MARKERS[i],
               linestyle='-',
               linewidth=GLOBAL_STYLE['line_width'],
               markersize=GLOBAL_STYLE['marker_size'],
               markevery=1,
               markerfacecolor=('auto'),
               markeredgecolor='auto',
               markeredgewidth=1.5)
    
    # Plot kLev variants (0, 1, 2, N)
    for i, variant in enumerate(['0', '1', '2', 'N']):
        key = f'klev{variant}'
        if key not in dataframes:
            continue
        
        df = dataframes[key]
        if config['x_column'] not in df.columns or config['y_column'] not in df.columns:
            print(f"Warning: {key} missing required columns")
            continue
        
        label = f'kLev{variant}'
        ax.plot(df[config['x_column']], df[config['y_column']],
               label=label,
               color=KLEV_COLORS[i],
               marker=MARKERS[i],
               linestyle='-',
               linewidth=GLOBAL_STYLE['line_width'],
               markersize=GLOBAL_STYLE['marker_size'],
               markevery=1,
               markerfacecolor=('none'),
               markeredgecolor='auto',
               markeredgewidth=1.5)

    apply_axis_formatting(ax, config)

    # Set ranges if specified
    if config.get('x_range'):
        for a in iter_axes(ax):
            a.set_xlim(config['x_range'])
    
    if config['y_range'] and not breakAxis:
        ax.set_ylim(config['y_range'])
    
    # Labels and title
    ax.set_xlabel(config['x_label'], fontsize=GLOBAL_STYLE['label_fontsize'], labelpad=25)
    ax.set_ylabel(config['y_label'], fontsize=GLOBAL_STYLE['label_fontsize'])
    ax.set_title(config['title'], fontsize=GLOBAL_STYLE['title_fontsize'], pad=15)
    
    # Tick parameters
    # ax.tick_params(labelsize=GLOBAL_STYLE['tick_fontsize'])
    for a in iter_axes(ax):
        a.tick_params(labelsize=GLOBAL_STYLE['tick_fontsize'])
    
    # Grid
    if config.get('grid', False):
        for a in iter_axes(ax):
            a.grid(True, alpha=GLOBAL_STYLE['grid_alpha'],
                linestyle=GLOBAL_STYLE['grid_linestyle'])
            if config['x_scale'] == 'log' or config['y_scale'] == 'log':
                a.grid(True, which='minor', alpha=GLOBAL_STYLE['grid_alpha']/2, linestyle=':')
    
    # Legend (add if enabled for this plot)
    if config.get('legend', False):
        if is_brokenaxes(ax):
            handles, labels = ax.axs[0].get_legend_handles_labels()
            ax.legend(handles, labels, loc='best', fontsize=GLOBAL_STYLE['legend_fontsize'],
                    framealpha=0.9, ncol=2)
        else:
            ax.legend(loc='best', fontsize=GLOBAL_STYLE['legend_fontsize'],
                    framealpha=0.9, ncol=2)

    # Tight layout
    plt.tight_layout()
    
    # Save
    output_path = get_file_path(GLOBAL_STYLE['output_dir'], plot_id, broken=breakAxis)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    plt.savefig(output_path, dpi=GLOBAL_STYLE['dpi'], bbox_inches='tight')
    plt.close()
    
    print(f"✓ Saved to: {output_path}")

def generate_global_legend(output_file: str = 'plots/paper/global_legend.png'):
    """Generate a standalone legend for all plots"""
    
    fig, ax = plt.subplots(figsize=(10, 1.5), dpi=GLOBAL_STYLE['dpi'])
    ax.axis('off')
    
    # Create dummy plots for legend
    handles = []
    labels = []
    
    for i, variant in enumerate(['0', '1', '2', 'N']):
        # kPath
        line, = ax.plot([], [], color=KPATH_COLORS[i], marker=MARKERS[i], 
                       linestyle='-', linewidth=GLOBAL_STYLE['line_width'],
                       markersize=GLOBAL_STYLE['marker_size'], 
                       label=f'kPath{variant}')
        handles.append(line)
        labels.append(f'kPath{variant}')
    
    for i, variant in enumerate(['0', '1', '2', 'N']):
        # kLev
        line, = ax.plot([], [], color=KLEV_COLORS[i], marker=MARKERS[i], 
                       linestyle='-', linewidth=GLOBAL_STYLE['line_width'],
                       markersize=GLOBAL_STYLE['marker_size'], 
                       label=f'kLev{variant}')
        handles.append(line)
        labels.append(f'kLev{variant}')
    
    # Create legend
    legend = ax.legend(handles, labels, loc='center', 
                      fontsize=GLOBAL_STYLE['legend_fontsize']+1,
                      ncol=8, frameon=False)
    
    # Save
    output_path = Path(output_file)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    plt.savefig(output_path, dpi=GLOBAL_STYLE['dpi'], bbox_inches='tight')
    plt.close()
    
    print(f"\n✓ Global legend saved to: {output_path}")

def generate_global_legend_v2(output_file: str = 'plots/paper/global_legend_v2.png'):
    """Generate a standalone legend for all plots"""
    
    fig, ax = plt.subplots(figsize=(10, 0.8), dpi=GLOBAL_STYLE['dpi'])
    ax.axis('off')
    
    # Create dummy plots for legend
    handles = []
    labels = []
    
    for i, variant in enumerate(['0', '1', '2', 'N']):
        # kPath
        line, = ax.plot([], [], color=KPATH_COLORS[i], marker=MARKERS[i], 
                       linestyle='-', 
                       linewidth=GLOBAL_STYLE['line_width'],
                       markersize=GLOBAL_STYLE['marker_size'],
                       markerfacecolor=('auto'),
                       markeredgecolor='auto',
                       markeredgewidth=1.5,
                       label=f'kPath{variant}')
        handles.append(line)
        labels.append(f'kPath{variant}')

               
    
    for i, variant in enumerate(['0', '1', '2', 'N']):
        # kLev
        line, = ax.plot([], [], color=KLEV_COLORS[i], marker=MARKERS[i], 
                       linestyle='-', linewidth=GLOBAL_STYLE['line_width'],
                       markersize=GLOBAL_STYLE['marker_size'], 
                       markerfacecolor=('none'),
                       markeredgecolor='auto',
                       markeredgewidth=1.5,
                       label=f'kLev{variant}')
        handles.append(line)
        labels.append(f'kLev{variant}')
    
    # Create legend WITH BORDER
    legend = ax.legend(handles, labels, loc='center', 
                      fontsize=GLOBAL_STYLE['legend_fontsize']+2,
                      ncol=8, 
                      frameon=True,  # Enable frame
                      fancybox=False,  # Square corners
                      edgecolor='black',  # Border color
                      framealpha=1.0)  # Solid background
    
    # Make the border thicker
    legend.get_frame().set_linewidth(1)
    
    # Save with tight bounding box
    output_path = Path(output_file)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    plt.savefig(output_path, dpi=GLOBAL_STYLE['dpi'], bbox_inches='tight', 
                pad_inches=0.05)
    plt.close()
    
    print(f"\n✓ Global legend saved to: {output_path}")

def main():
    import argparse
    
    parser = argparse.ArgumentParser(description='Generate paper plots with fine control')
    parser.add_argument('plots', nargs='*', 
                       help='Plot IDs to generate (default: all)')
    parser.add_argument('--list', action='store_true',
                       help='List all available plot IDs')
    parser.add_argument('--legend', action='store_true',
                       help='Generate only the global legend')
    
    args = parser.parse_args()
    
    if args.list:
        print("\nAvailable plot IDs:")
        for plot_id in PLOT_CONFIGS.keys():
            print(f"  - {plot_id}")
        return
    
    if args.legend:
        generate_global_legend_v2()
        return
    
    # Determine which plots to generate
    if args.plots:
        plot_ids = args.plots
    else:
        plot_ids = list(PLOT_CONFIGS.keys())
    
    # Generate plots
    for plot_id in plot_ids:
        if plot_id not in PLOT_CONFIGS:
            print(f"\n✗ Unknown plot ID: {plot_id}")
            continue
        
        create_plot(plot_id, PLOT_CONFIGS[plot_id])
    
    # Generate global legend -- not by default
    # print("\n" + "="*60)
    # generate_global_legend()
    
    print("\n" + "="*60)
    print("All plots generated successfully!")
    print("="*60)

if __name__ == '__main__':
    main()

# source venv/bin/activate
# pip install pandas matplotlib numpy
# deactivate

# Generate all 9 plots + global legend
# python3 scripts/random_scripts_v2/paper_plots.py

# Generate specific plots only
# python3 scripts/random_scripts_v2/paper_plots.py varn_logn_k2 varn_sqrtn_k2

# List all available plot IDs
# python3 scripts/random_scripts_v2/paper_plots.py --list

# Generate only the global legend
# python3 scripts/random_scripts_v2/paper_plots.py --legend
