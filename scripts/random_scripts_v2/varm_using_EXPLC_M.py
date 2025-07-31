import os
import subprocess
import argparse
import csv
from pathlib import Path
from datetime import datetime

def run_experiments(iterations, seed_token, graph_type):
    base_output_dir = f"./results/random_v2/VARM/{graph_type}"
    n = 10000
    variants = ["0", "1", "2", "N"]
    algorithms = {"kpath": "2", "klev":"3"} # kpath, klev
    k_values = [2, 5, 10]

    print(f"Running VARM with {iterations} iterations, for N = {n} varying M from {n/10} to {n*(n-1)/2} and seed token {seed_token}")

    Path(base_output_dir).mkdir(parents=True, exist_ok=True)
    
    m_values = list(range(1000, 10000, 1000)) + list(range(10_000, 20_000, 2000)) + list(range(25_000, 50_000, 5000)) + list(range(50_000, 100_000, 10_000)) + list(range(100_000, 1_000_001, 100_000)) + list(range(2_000_000, 10_000_000, 2_000_000)) + list(range(10_000_000, 40_000_001, 5_000_000)) + [49_995_000]

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
                algorithm_name,                         # kPath
                f"k{k}"                                 # k2
            )
            Path(dir_path).mkdir(parents=True, exist_ok=True)
            
            for variant in variants:
                csv_filename = f"{algorithm_name}{variant}_k{k}_{run_id}.csv"
                csv_filepath = os.path.join(dir_path, csv_filename)

                # Open CSV file and write header
                csvfile = open(csv_filepath, "w", newline="")
                csvwriter = csv.writer(csvfile, delimiter=',')
                csvwriter.writerow(["M", "Time (s)", "Memory (KB)", "AvgPasses", "AvgHeight"])

                # Store the CSV writer and file object
                csv_files[(algorithm_name, variant, k)] = csvwriter
                file_objects[(algorithm_name, variant, k)] = csvfile

                print(f"Created: {csv_filepath}")


    for m in m_values:
        try: # Prepare for the Experiment [PREP_EXP]
            subprocess.run(
                ["./bin/main", "PREP_EXP", "4", str(n), str(m), graph_type, str(iterations), str(seed_token)], 
                check=True
            ) # 4 for EXPLC_M
        except subprocess.CalledProcessError as e:
            print(f"Error generating graph with N={n}, M={m}, iterations={iterations}, seed={seed_token}: {e}")
            continue

        for algorithm_name, algorithm_code in algorithms.items():
            for variant in variants:
                for k in k_values:
                    csvwriter = csv_files[(algorithm_name, variant, k)]

                    print(f"Running EXPLC_M with {algorithm_name}{variant} for N={n}, M={m}, k={k}, seed={seed_token}...")

                    try: # Run the Experiment [RUN_EXP]
                        result = subprocess.run(
                            ["/usr/bin/time", "-f", "%U,%M", "./bin/main", "RUN_EXP", "4", str(n), str(m), graph_type, str(iterations), str(seed_token), algorithm_code, variant, str(k)],
                            stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE,
                            text=True,
                            check=True
                        )
                    except subprocess.CalledProcessError as e:
                        print(f"Error running EXPLC_M with {algorithm_name}{variant} for N={n}, M={m}, k={k}, seed={seed_token}: {e}")
                        continue

                    # Parse the output
                    output = result.stdout.strip().split()
                    user_time_mem = result.stderr.strip()  # Time and memory are in stderr
                    avg_passes = float(output[0])  # Assuming pass count is the first value of stdout
                    avg_height = float(output[1])  # Assuming height is the second value of stdout
                    print(f"      Average Passes: {avg_passes}, Time/Memory: {user_time_mem}")

                    # Extract time and memory
                    try:
                        user_time, memory = map(float, user_time_mem.split(","))
                    except ValueError as e:
                        print(f"Error parsing time/memory for  N={n}, M={m}, k={k}, seed={seed_token}: {e}")
                        continue

                    # Calculate average time
                    avg_time = user_time / float(iterations)

                    # Write data to CSV
                    csvwriter.writerow([m, avg_time, memory, avg_passes, avg_height])

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
        "-g", "--graph-type",
        type=str,
        required=True,
        help="Graph generation type for the random graphs [UNIFORM, POWLAW]",
        default="UNIFORM"
    )
    args = parser.parse_args()

    run_experiments(args.iterations, args.seed_token, args.graph_type)
