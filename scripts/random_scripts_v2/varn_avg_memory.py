import os
import subprocess
import argparse
import csv
from pathlib import Path
from datetime import datetime
from typing import List
import math

sparsity_label = {2: "logN", 3: "sqrtN", 4: "N2"}

def read_seed_tokens(seed_file: str, num_seeds: int) -> List[int]:
    """Read seed tokens from file"""
    try:
        with open(seed_file, 'r') as f:
            seeds = [int(line.strip()) for line in f.readlines()[:num_seeds]]
        return seeds
    except FileNotFoundError:
        print(f"Seed file {seed_file} not found!")
        return []
    
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

def get_graph_filename(n: int, m: int, seed: int, graph_type: str) -> str:
    """Generate the graph filename based on parameters"""
    return f"graph_{n}_{m}_{graph_type}_{seed}.txt"


def run_experiments(iterations, seed_token, seed_file, sparsity, graph_type):
    base_output_dir = f"./results/random_v2/VARN/{graph_type}"
    variants = ["0", "1", "2", "N"]
    algorithms = {"kpath": "2", "klev":"3"} # kpath, klev
    k_values = [2, 5, 10]


    seeds = read_seed_tokens(seed_file, iterations)

    if not seeds:
        print("No seeds found. Exiting.")
        return

    if len(seeds) < args.iterations:
        print(f"Warning: Only {len(seeds)} seeds available, but {args.iterations} iterations requested")
        args.iterations = len(seeds)


    print(f"Running experiments with {iterations} iterations, varying N from 10 to 10,000 and seed token {seed_token}")

    Path(base_output_dir).mkdir(parents=True, exist_ok=True)

    n_values = list(range(10, 100, 10)) + list(range(100, 1000, 100)) + list(range(1000, 2000, 200)) + list(range(2000, 5000, 500)) + list(range(5000, 10001, 1000))

    # Add a timestamped directory for each run
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    run_id = f"seed_{seed_token}_itr_{iterations}_{timestamp}"

    # Open CSV files for writing
    csv_files = {}
    file_objects = {}

    for algorithm_name, algorithm_code in algorithms.items():
        for k in k_values:# Create directory structure: UNIFORM/logN/kPath/k2/
            dir_path = os.path.join(
                base_output_dir,
                sparsity_label[sparsity],               # logN
                algorithm_name,                         # kPath
                f"k{k}"                                 # k2
            )
            Path(dir_path).mkdir(parents=True, exist_ok=True)
            
            for variant in variants:
                csv_filename = f"{algorithm_name}{variant}_k{k}_{run_id}.csv"
                csv_filepath = os.path.join(dir_path, csv_filename)

                # Open CSV file and write header
                csvfile = open(csv_filepath, "w", newline="", buffering=1)
                csvwriter = csv.writer(csvfile, delimiter=',')
                csvwriter.writerow(["N", "Time (s)", "Memory (KB)", "AvgPasses", "AvgHeight"])

                # Store the CSV writer and file object
                csv_files[(algorithm_name, variant, k)] = csvwriter
                file_objects[(algorithm_name, variant, k)] = csvfile

                print(f"Created: {csv_filepath}")

    # Create all the graphs first
    for n in n_values:
        try: # Prepare for the Experiment [PREP_EXP]
            subprocess.run(
                ["./bin/main", "PREP_EXP", "3", str(n), str(sparsity), graph_type, str(iterations), str(seed_token)],
                check=True
            ) # 3 for FIXNM type experiment
        except subprocess.CalledProcessError as e:
            print(f"Error generating graph with N={n}, sparsity={sparsity}, iterations={iterations}, seed={seed_token}: {e}")
            continue

    for n in n_values:
        m = calculate_m(n, sparsity)
        for algorithm_name, algorithm_code in algorithms.items():
            for k in k_values:
                for variant in variants:
                    csvwriter = csv_files[(algorithm_name, variant, k)]

                    print(f"Running {algorithm_name} variant {variant} with N={n}, sparsity={sparsity}, k={k}, seed={seed_token}...")

                    # try: # Run the Experiment [RUN_EXP]
                    #     result = subprocess.run(
                    #         ["/usr/bin/time", "-f", "%U,%M", "./bin/main", "RUN_EXP", "3", str(n), str(sparsity), graph_type, str(iterations), str(seed_token), algorithm_code, variant, str(k)],
                    #         stdout=subprocess.PIPE,
                    #         stderr=subprocess.PIPE,
                    #         text=True,
                    #         check=True
                    #     )
                    # except subprocess.CalledProcessError as e:
                    #     print(f"Error running {algorithm_name} variant {variant} with N={n}, sparsity={sparsity}, k={k}, seed={seed_token}: {e}")
                    #     continue

                    avg_time = 0
                    avg_memory = 0
                    avg_passes = 0
                    avg_height = 0

                    for i in range(iterations):
                        try: 
                            result = subprocess.run(
                            ["/usr/bin/time", "-f", "%U,%M", "./bin/main", "RUN_ALGO", str(n), str(m), get_graph_filename(n, m, seeds[i], graph_type), algorithm_code, variant, str(k)],
                            stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE,
                            text=True,
                            check=True
                        )
                        except subprocess.CalledProcessError as e:
                            print(f"Error running {algorithm_name} variant {variant} with N={n}, sparsity={sparsity}, k={k}, seed={seeds[i]}: {e}")
                            continue
                        
                        # Parse the output
                        output = result.stdout.strip().split()
                        user_time_mem = result.stderr.strip()  # Time and memory are in stderr
                        avg_passes += float(output[0])  # Assuming pass count is the first value of stdout
                        avg_height += float(output[1])  # Assuming height is the second value of stdout
                        print(f"      Passes: {avg_passes},  Height: {avg_height}, Time/Memory: {user_time_mem}")

                        # Extract time and memory
                        try:
                            user_time, memory = map(float, user_time_mem.split(","))
                        except ValueError:
                            print(f"Error parsing time/memory for N={n}, sparsity={sparsity}, seed={seed_token}")
                            continue

                        # Calculate average time
                        avg_time += user_time
                        avg_memory += memory

                    avg_time /= float(iterations)
                    avg_memory /= float(iterations)
                    avg_passes /= float(iterations)
                    avg_height /= float(iterations)

                    # Write data to CSV
                    csvwriter.writerow([n, avg_time, avg_memory, avg_passes, avg_height])

    for csvfile in file_objects.values():
        csvfile.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate random powerlaw graphs and run k-path and k-level algorithms to capture time, memory, and pass count.")
    parser.add_argument(
        "-i", "--iterations",
        type=int,
        default=10,
        help="Number of iterations to run for each combination (default: 10)"
    )
    parser.add_argument(
        "-s", "--seed-token",
        type=int,
        required=True,
        help="Seed token to generate random seeds",
        default=1729
    )
    parser.add_argument(
        "-sf", "--seed-file", 
        type=str,
        default="../../seed_1000x_token_1729.txt",
        help="Path to seed token file"
    )
    parser.add_argument(
        "-sp", "--sparsity",
        type=int,
        required=True,
        help="Sparsity value for the graph generation (2 or 3)",
        default=2
    )
    parser.add_argument(
        "-g", "--graph-type",
        type=str,
        required=True,
        help="Graph generation type for the random graphs [UNIFORM, POWLAW]",
        default="UNIFORM"
    )
    args = parser.parse_args()

    run_experiments(args.iterations, args.seed_token, args.seed_file, args.sparsity, args.graph_type)


# Usage: (ulimit -s unlimited; nohup python3 scripts/random_scripts_v2/varn_avg_memory.py -i 10 -s 1729 -sf seed_1000x_token_1729.txt -sp 2 -g UNIFORM > "scripts/random_scripts_v2/logs/varn_n_10K_uniform_logn_seed_1729_itr10_terraforge_run_$(date +%Y%m%d_%H%M%S).log" 2>&1 < /dev/null &)
