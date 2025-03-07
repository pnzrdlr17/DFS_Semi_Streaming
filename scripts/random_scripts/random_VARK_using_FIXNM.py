import os
import subprocess
import argparse
import csv
from pathlib import Path
from datetime import datetime

sparsity_label = {2: "logN", 3: "sqrtN", "4": "N"}

def run_experiments_n_10000(iterations, seed_token, sparsity, graph_type):
    n = 10000
    variants = ["0", "N"]
    algorithms = {"kPath": "2", "kLev":"3"}

    output_dir = f"./results/random/VARK/{graph_type}"
    Path(output_dir).mkdir(parents=True, exist_ok=True)

    print(f"Running VARK with {iterations} iterations, for N = 10,000 and sparsity code {sparsity} for k from 1 to N and seed token {seed_token}")

    k_values = list(range(1, 25, 1)) + list(range(25, 50, 5)) + list(range(50, 100, 10)) 
    + list(range(100, 1000, 100)) + list(range(1000, 5000, 500)) + list(range(5000, 10000, 1000))

    # Add a timestamped directory for each run
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    sparsity_dir = os.path.join(output_dir, f"sparsity_{sparsity_label[sparsity]}_N_10000_seed_{seed_token}_iter_{iterations}_{timestamp}")
    Path(sparsity_dir).mkdir(parents=True, exist_ok=True)

    # Open CSV files for writing
    csv_files = {}
    file_objects = {}
    for algorithm_name, algorithm_code in algorithms.items():
        for variant in variants:
            results_file = os.path.join(sparsity_dir, f"{algorithm_name}{variant}.csv")
            csvfile = open(results_file, "w", newline="")
            csvwriter = csv.writer(csvfile, delimiter=',')
            csvwriter.writerow(["K", "Time (s)", "Memory (KB)", "Passes"])
            csv_files[(algorithm_name, variant)] = csvwriter
            file_objects[(algorithm_name, variant)] = csvfile

    print(f"Generating {iterations} graphs with N={n}, sparsity={sparsity}, seed={seed_token}...")

    try: # Prepare for the Experiment [PREP_EXP]
        subprocess.run(
            ["./bin/main", "PREP_EXP", "3", str(n), str(sparsity), graph_type, str(iterations), str(seed_token)],
            check=True
        ) # 3 for FIXNM type experiment
    except subprocess.CalledProcessError as e:
        print(f"Error generating graph with N={n}, sparsity={sparsity}, iterations={iterations}, seed={seed_token}: {e}")


    for algorithm_name, algorithm_code in algorithms.items():
        for variant in variants:
            for k in k_values:
                csvwriter = csv_files[(algorithm_name, variant)]

                print(f"Running FIXNM with {algorithm_name}{variant} for N={n}, sparsity={sparsity}, k={k}, seed={seed_token}...")

                try:  # Run the Experiment [RUN_EXP]
                    result = subprocess.run(
                        ["/usr/bin/time", "-f", "%U,%M", "./bin/main", "RUN_EXP", "3", str(n), str(sparsity), graph_type, str(iterations), str(seed_token), algorithm_code, variant, str(k)],
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE,
                        text=True,
                        check=True
                    )
                except subprocess.CalledProcessError as e:
                    print(f"Error running FIXNM with {algorithm_name}{variant} for N={n}, sparsity={sparsity}, k={k}, seed={seed_token}: {e}")
                    continue

                # Parse the output
                output_lines = result.stdout.strip().split("\n")
                user_time_mem = result.stderr.strip()  # Time and memory are in stderr
                avg_passes = round(float(output_lines[-1]), 2)  # Assuming pass count is the last line of stdout
                print(f"      Average Passes: {avg_passes}, Time/Memory: {user_time_mem}")

                # Extract time and memory
                try:
                    user_time, memory = map(float, user_time_mem.split(","))
                except ValueError:
                    print(f"Error parsing time/memory for N={n}, sparsity={sparsity}, k={k}, seed={seed_token}")
                    continue

                # Calculate average time
                avg_time = round(user_time / iterations, 2)
                memory = round(memory, 2)

                # Write data to CSV
                csvwriter.writerow([k, avg_time, memory, avg_passes])

    for csvfile in file_objects.values():
        csvfile.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate random powerlaw graphs and run k-path and k-level algorithms to capture time, memory, and pass count.")
    parser.add_argument(
        "-i", "--iterations",
        type=int,
        default=1,
        help="Number of iterations to run for each combination (default: 1)"
    )
    parser.add_argument(
        "-s", "--seed-token",
        type=int,
        required=True,
        help="Seed token to generate random seeds"
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

    run_experiments_n_10000(args.iterations, args.seed_token, args.sparsity, args.graph_type)