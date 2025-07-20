#!/usr/bin/env python3
"""
Parallel Graph Generator Script with Load Balancing

This script extracts n and m values from the VARN, VARM, and VARK scripts,
reads seeds from the seed token file, and generates graphs in parallel using
up to 30 processes.
"""

import os
import subprocess
import argparse
import math
from pathlib import Path
from concurrent.futures import ProcessPoolExecutor, as_completed
import time
from typing import List, Tuple

def calculate_m(n: int, sparsity: int) -> int:
    """Calculate m based on n and sparsity, matching experiment.cpp logic"""
    if sparsity == 0:
        return min(2 * n, (n * (n - 1)) // 2)
    elif sparsity == 1:
        return min(5 * n, (n * (n - 1)) // 2)
    elif sparsity == 2:
        return int(n * math.log2(n))
    elif sparsity == 3:
        return int(n * math.sqrt(n))
    elif sparsity == 4:
        return (n * (n - 1)) // 2
    else:
        raise ValueError(f"Invalid sparsity: {sparsity}")

def get_varn_values() -> List[int]:
    """Extract n values from VARN script following experiment.cpp case 0 pattern"""
    # Hardcoded 1K values (following case 0 pattern: start=10, step=10, then step=50 when n >= 100)
    # return [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000]
    
    # Old 10K values (commented out)
    return (list(range(10, 100, 10)) + 
            list(range(100, 1001, 100)) + 
            list(range(1250, 2501, 250)) + 
            list(range(3000, 5001, 500)) + 
            list(range(6000, 10001, 1000)))

def get_varm_values() -> List[int]:
    """Extract m values from VARM script (complete graph pattern, n=1000)"""
    # Hardcoded complete graph values up to n*(n-1)/2 = 499500
    return [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
            2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000,
            12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000,
            30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000,
            200000, 300000, 400000]
    
    # Old 10K values (commented out)
    # return (list(range(1000, 10001, 1000)) + 
    #         list(range(12_500, 25_001, 2_500)) + 
    #         list(range(30_000, 100_000, 10_000)) + 
    #         list(range(100_000, 1_000_001, 100_000)) + 
    #         list(range(2_000_000, 10_000_000, 2_000_000)) + 
    #         list(range(10_000_000, 40_000_001, 5_000_000)) + 
    #         [49_995_000])

def read_seed_tokens(seed_file: str, num_seeds: int) -> List[int]:
    """Read seed tokens from file"""
    try:
        with open(seed_file, 'r') as f:
            seeds = [int(line.strip()) for line in f.readlines()[:num_seeds]]
        return seeds
    except FileNotFoundError:
        print(f"Seed file {seed_file} not found!")
        return []

def generate_single_graph(n: int, m: int, seed: int, graph_type: str) -> Tuple[bool, str]:
    """Generate a single graph file using the main binary and measure generation time"""
    start_time = time.time()
    
    try:
        # Change to the project root directory to run the graph generator
        project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '../..'))
        
        # Call the main binary with GEN_GRAPH mode
        # Usage: ./bin/main GEN_GRAPH <n> <m> <seed> <graph_type>
        cmd = [
            os.path.join(project_root, 'bin/main'),
            'GEN_GRAPH',
            str(n), str(m), str(seed), graph_type
        ]
        
        result = subprocess.run(
            cmd,
            cwd=project_root,
            capture_output=True,
            text=True
        )
        
        end_time = time.time()
        time_taken = end_time - start_time
        
        if result.returncode == 0:
            # Extract the generated file path from stdout
            output_lines = result.stdout.strip().split('\n')
            generated_file = None
            for line in output_lines:
                if 'Generated graph at:' in line:
                    generated_file = line.split('Generated graph at: ')[1].strip()
                    break
            
            return True, f"Generated graph n={n}, m={m}, seed={seed}, type={graph_type} -> {generated_file} (Time: {time_taken:.2f}s)"
        else:
            return False, f"Error generating graph n={n}, m={m}, seed={seed}: {result.stderr}"
            
    except Exception as e:
        return False, f"Exception generating graph n={n}, m={m}, seed={seed}: {str(e)}"

def generate_nm_pairs(experiment_type: str, sparsity: int = 2) -> List[Tuple[int, int]]:
    """Generate (n, m) pairs based on experiment type"""
    pairs = []
    
    if experiment_type == "VARN":
        n_values = get_varn_values()
        for n in n_values:
            m = calculate_m(n, sparsity)
            pairs.append((n, m))
    
    elif experiment_type == "VARM":
        n = 1000  # Fixed n for VARM (reduced from 10000 to 1000)
        m_values = get_varm_values()
        for m in m_values:
            pairs.append((n, m))
    
    elif experiment_type == "VARK":
        n = 1000  # Fixed n for VARK (reduced from 10000 to 1000)
        m = calculate_m(n, sparsity)
        pairs.append((n, m))
    
    elif experiment_type == "ALL":
        # Generate all combinations
        pairs.extend(generate_nm_pairs("VARN", sparsity))
        pairs.extend(generate_nm_pairs("VARM", sparsity))
        pairs.extend(generate_nm_pairs("VARK", sparsity))
        # Remove duplicates
        pairs = list(set(pairs))
    
    # Sort pairs based on n, then m to balance load
    pairs.sort()
    return pairs

def main():
    parser = argparse.ArgumentParser(description="Generate graphs in parallel for experiments")
    parser.add_argument("-e", "--experiment", 
                       choices=["VARN", "VARM", "VARK", "ALL"],
                       default="ALL",
                       help="Experiment type to generate graphs for")
    parser.add_argument("-s", "--sparsity", type=int, default=2,
                       help="Sparsity value (0-4)")
    parser.add_argument("-g", "--graph-type", 
                       choices=["UNIFORM", "POWLAW"],
                       default="UNIFORM",
                       help="Graph type")
    parser.add_argument("-i", "--iterations", type=int, default=10,
                       help="Number of iterations (different seeds) per (n,m) pair")
    parser.add_argument("-p", "--processes", type=int, default=30,
                       help="Maximum number of parallel processes")
    parser.add_argument("-sf", "--seed-file", type=str,
                       default="../../seed_1000x_token_1729.txt",
                       help="Path to seed token file")
    
    args = parser.parse_args()
    
    # Read seed tokens
    seeds = read_seed_tokens(args.seed_file, args.iterations)
    if not seeds:
        print("No seeds found. Exiting.")
        return
    
    if len(seeds) < args.iterations:
        print(f"Warning: Only {len(seeds)} seeds available, but {args.iterations} iterations requested")
        args.iterations = len(seeds)
    
    # Generate (n, m) pairs
    nm_pairs = generate_nm_pairs(args.experiment, args.sparsity)
    
    print(f"Generating graphs for {len(nm_pairs)} (n,m) pairs with {args.iterations} iterations each")
    print(f"Total graphs to generate: {len(nm_pairs) * args.iterations}")
    print(f"Using {args.processes} parallel processes")
    print(f"Graph type: {args.graph_type}")
    print(f"Sparsity: {args.sparsity}")
    
    # Prepare tasks
    tasks = []
    for n, m in nm_pairs:
        for i in range(args.iterations):
            seed = seeds[i]
            tasks.append((n, m, seed, args.graph_type))
    
    # Execute tasks in parallel
    start_time = time.time()
    successful = 0
    failed = 0
    
    with ProcessPoolExecutor(max_workers=args.processes) as executor:
        # Submit all tasks
        future_to_task = {
            executor.submit(generate_single_graph, *task): task 
            for task in tasks
        }
        
        # Process completed tasks
        for future in as_completed(future_to_task):
            task = future_to_task[future]
            try:
                success, message = future.result()
                if success:
                    successful += 1
                    print(f"✓ {message}")
                else:
                    failed += 1
                    print(f"✗ {message}")
            except Exception as exc:
                failed += 1
                print(f"✗ Task {task} generated an exception: {exc}")
    
    end_time = time.time()
    
    print(f"\nGraph generation completed in {end_time - start_time:.2f} seconds")
    print(f"Successful: {successful}")
    print(f"Failed: {failed}")
    print(f"Total: {successful + failed}")

if __name__ == "__main__":
    main()
