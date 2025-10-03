#!/usr/bin/env python3
"""
Enhanced Parallel Graph Generator Script with HDD Cache

This script uses HDD location as a cache/store of previously generated graphs.
Logic:
1. Check if file exists in HDD location and validates correctly
2. If yes, copy it to input/random_graphs (working directory)
3. If no or validation fails, generate fresh in input/random_graphs
4. Maintain a log of validation failures at HDD location
"""

import os
import subprocess
import argparse
import math
import shutil
from pathlib import Path
from concurrent.futures import ProcessPoolExecutor, as_completed
import time
from typing import List, Tuple, Optional
from datetime import datetime

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
    return (list(range(10, 100, 10)) + list(range(100, 1000, 100)) + 
            list(range(1000, 2000, 200)) + list(range(2000, 5000, 500)) + 
            list(range(5000, 10001, 1000)))

def get_varm_values() -> List[int]:
    """Extract m values from VARM script (complete graph pattern, n=1000)"""
    return (list(range(1000, 10000, 1000)) + list(range(10_000, 20_000, 2000)) + 
            list(range(25_000, 50_000, 5000)) + list(range(50_000, 100_000, 10_000)) + 
            list(range(100_000, 1_000_001, 100_000)) + list(range(2_000_000, 10_000_000, 2_000_000)) + 
            list(range(10_000_000, 40_000_001, 5_000_000)) + [49_995_000])

def read_seed_tokens(seed_file: str, num_seeds: int) -> List[int]:
    """Read seed tokens from file"""
    try:
        with open(seed_file, 'r') as f:
            seeds = [int(line.strip()) for line in f.readlines()[:num_seeds]]
        return seeds
    except FileNotFoundError:
        print(f"Seed file {seed_file} not found!")
        return []

def get_graph_filename(n: int, m: int, seed: int, graph_type: str) -> str:
    """Generate the graph filename based on parameters"""
    return f"graph_{n}_{m}_{graph_type}_{seed}.txt"

def get_hdd_filepath(n: int, m: int, seed: int, graph_type: str, hdd_location: str) -> str:
    """Get the full path in HDD location"""
    filename = get_graph_filename(n, m, seed, graph_type)
    return os.path.join(hdd_location, filename)

def get_working_filepath(n: int, m: int, seed: int, graph_type: str, working_dir: str) -> str:
    """Get the full path in working directory (input/random_graphs)"""
    filename = get_graph_filename(n, m, seed, graph_type)
    return os.path.join(working_dir, filename)

def log_validation_failure(n: int, m: int, seed: int, graph_type: str, reason: str, 
                          hdd_location: str, timestamp: str):
    """Log validation failures to a file in HDD location"""
    log_file = os.path.join(hdd_location, "validation_failures.log")
    filename = get_graph_filename(n, m, seed, graph_type)
    
    try:
        with open(log_file, 'a') as f:
            f.write(f"[{timestamp}] {filename}: {reason}\n")
    except Exception as e:
        print(f"Warning: Could not write to validation log: {e}")

def validate_graph_file(filepath: str, expected_n: int, expected_m: int) -> Tuple[bool, str]:
    """
    Perform lightweight validation of graph file
    Checks:
    1. File exists and is readable
    2. Correct number of vertices (1 to n)
    3. Correct number of edges
    4. No duplicate edges (for undirected graphs)
    5. All vertices are in valid range [1, n]
    """
    try:
        if not os.path.exists(filepath):
            return False, "File does not exist"
        
        if os.path.getsize(filepath) == 0:
            return False, "File is empty"
        
        with open(filepath, 'r') as f:
            lines = f.readlines()
        
        # Skip empty lines and comments if any
        lines = [line.strip() for line in lines if line.strip() and not line.startswith('#')]
        
        if len(lines) == 0:
            return False, "File has no content"
        
        # Check if first line is header (n m) or directly an edge
        first_parts = lines[0].split()
        if len(first_parts) == 2:
            try:
                first_n, first_m = int(first_parts[0]), int(first_parts[1])
                # Check if this looks like a header (large numbers for n, m)
                if first_n == expected_n and first_m == expected_m:
                    # This is a header, skip it
                    edge_lines = lines[1:]
                    has_header = True
                else:
                    # No header, this is an edge
                    edge_lines = lines
                    has_header = False
            except ValueError:
                edge_lines = lines
                has_header = False
        else:
            return False, "Invalid file format"
        
        # Validate edges
        edges_seen = set()
        actual_edge_count = 0
        
        for i, line in enumerate(edge_lines):
            if not line:  # Skip empty lines
                continue
                
            try:
                parts = line.split()
                if len(parts) != 2:
                    return False, f"Invalid edge format at edge {i+1}"
                
                u, v = int(parts[0]), int(parts[1])
                
                # Check vertex range [1, n]
                if u < 1 or u > expected_n or v < 1 or v > expected_n:
                    return False, f"Vertex out of range at edge {i+1}: ({u}, {v})"
                
                # For undirected graphs, normalize edge representation
                edge = tuple(sorted([u, v]))
                
                # Check for self-loops
                if u == v:
                    return False, f"Self-loop found at edge {i+1}: ({u}, {v})"
                
                # Check for duplicates
                if edge in edges_seen:
                    return False, f"Duplicate edge found: {edge}"
                
                edges_seen.add(edge)
                actual_edge_count += 1
                
            except ValueError:
                return False, f"Invalid edge format at edge {i+1}: {line}"
        
        # Final edge count check
        if actual_edge_count != expected_m:
            return False, f"Edge count mismatch: expected {expected_m}, got {actual_edge_count}"
        
        return True, "Validation passed"
        
    except Exception as e:
        return False, f"Validation error: {str(e)}"

def process_single_graph(n: int, m: int, seed: int, graph_type: str, 
                        hdd_location: str, working_dir: str, 
                        project_root: str) -> Tuple[bool, str]:
    """
    Process a single graph:
    1. Check if exists in HDD and validates
    2. If yes, copy to working directory
    3. If no, generate fresh in working directory
    """
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    hdd_path = get_hdd_filepath(n, m, seed, graph_type, hdd_location)
    working_path = get_working_filepath(n, m, seed, graph_type, working_dir)
    
    # Ensure working directory exists
    os.makedirs(working_dir, exist_ok=True)
    
    # Check if file already exists in working directory and is valid
    if os.path.exists(working_path):
        is_valid, msg = validate_graph_file(working_path, n, m)
        if is_valid:
            return True, f"ALREADY_EXISTS in working dir: {working_path}"
    
    # Check if file exists in HDD location
    if os.path.exists(hdd_path):
        # Validate the HDD file
        is_valid, validation_msg = validate_graph_file(hdd_path, n, m)
        
        if is_valid:
            # Copy from HDD to working directory
            try:
                start_time = time.time()
                shutil.copy2(hdd_path, working_path)
                copy_time = time.time() - start_time
                return True, f"COPIED from HDD: {hdd_path} -> {working_path} (Time: {copy_time:.2f}s)"
            except Exception as e:
                return False, f"Error copying from HDD: {str(e)}"
        else:
            # Log validation failure
            log_validation_failure(n, m, seed, graph_type, validation_msg, hdd_location, timestamp)
            print(f"  HDD file failed validation: {validation_msg}, regenerating...")
    
    # File not in HDD or failed validation, generate fresh
    start_time = time.time()
    
    try:
        # Call the main binary with GEN_GRAPH mode
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

        generation_time = time.time() - start_time

        if result.returncode == 0:
            # The binary should generate the file directly in input/random_graphs
            # Verify it was created
            if os.path.exists(working_path):
                # Validate the newly generated file
                is_valid, validation_msg = validate_graph_file(working_path, n, m)
                if is_valid:
                    return True, f"GENERATED: {working_path} (Time: {generation_time:.2f}s)"
                else:
                    return False, f"Generated file failed validation: {validation_msg}"
            else:
                return False, f"Binary succeeded but file not found at expected location: {working_path}"
        else:
            return False, f"Error generating graph: {result.stderr}"

    except Exception as e:
        return False, f"Exception during generation: {str(e)}"

def generate_nm_pairs(experiment_type: str, sparsity: int = 2) -> List[Tuple[int, int]]:
    """Generate (n, m) pairs based on experiment type"""
    pairs = []
    
    if experiment_type == "VARN":
        n_values = get_varn_values()
        for n in n_values:
            m = calculate_m(n, sparsity)
            pairs.append((n, m))

    elif experiment_type == "VARM":
        n = 10000  # Fixed n for VARM
        m_values = get_varm_values()
        for m in m_values:
            pairs.append((n, m))

    elif experiment_type == "VARK":
        n = 10000  # Fixed n for VARK
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
    parser = argparse.ArgumentParser(
        description="Generate graphs in parallel using HDD as cache store"
    )
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
    parser.add_argument("-hdd", "--hdd-location", type=str,
                       default="/media/HDD/Projects/ExpDFS/",
                       help="HDD location (cache store) for graphs")
    parser.add_argument("-w", "--working-dir", type=str,
                       default="input/random_graphs",
                       help="Working directory where graphs are needed (default: input/random_graphs)")

    args = parser.parse_args()

    # Get project root
    project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '../..'))
    working_dir = os.path.join(project_root, args.working_dir)

    # Ensure directories exist
    os.makedirs(args.hdd_location, exist_ok=True)
    os.makedirs(working_dir, exist_ok=True)

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

    print(f"Processing graphs for {len(nm_pairs)} (n,m) pairs with {args.iterations} iterations each")
    print(f"Total graphs to process: {len(nm_pairs) * args.iterations}")
    print(f"Using {args.processes} parallel processes")
    print(f"Graph type: {args.graph_type}")
    print(f"Sparsity: {args.sparsity}")
    print(f"HDD cache location: {args.hdd_location}")
    print(f"Working directory: {working_dir}")
    print(f"Validation failures will be logged to: {os.path.join(args.hdd_location, 'validation_failures.log')}")
    print()

    # Prepare tasks
    tasks = []
    for n, m in nm_pairs:
        for i in range(args.iterations):
            seed = seeds[i]
            tasks.append((n, m, seed, args.graph_type, args.hdd_location, working_dir, project_root))

    # Execute tasks in parallel
    start_time = time.time()
    generated = 0
    copied = 0
    already_exists = 0
    failed = 0

    with ProcessPoolExecutor(max_workers=args.processes) as executor:
        # Submit all tasks
        future_to_task = {
            executor.submit(process_single_graph, *task): task
            for task in tasks
        }

        # Process completed tasks
        for future in as_completed(future_to_task):
            task = future_to_task[future]
            try:
                success, message = future.result()
                if success:
                    if "COPIED" in message:
                        copied += 1
                        print(f"📦 {message}")
                    elif "GENERATED" in message:
                        generated += 1
                        print(f"✓ {message}")
                    elif "ALREADY_EXISTS" in message:
                        already_exists += 1
                        print(f"⏭ {message}")
                    else:
                        print(f"✓ {message}")
                else:
                    failed += 1
                    print(f"✗ {message}")
            except Exception as exc:
                failed += 1
                print(f"✗ Task {task[:4]} generated an exception: {exc}")

    end_time = time.time()
    
    print(f"\n{'='*60}")
    print(f"Graph processing completed in {end_time - start_time:.2f} seconds")
    print(f"{'='*60}")
    print(f"Copied from HDD:          {copied}")
    print(f"Newly generated:          {generated}")
    print(f"Already in working dir:   {already_exists}")
    print(f"Failed:                   {failed}")
    print(f"Total processed:          {copied + generated + already_exists + failed}")
    print(f"{'='*60}")
    
    if failed > 0:
        print(f"\n⚠️  Check validation log at: {os.path.join(args.hdd_location, 'validation_failures.log')}")

if __name__ == "__main__":
    main()
