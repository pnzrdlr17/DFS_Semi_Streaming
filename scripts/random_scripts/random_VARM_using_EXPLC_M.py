import os
import subprocess
import argparse
import csv
from pathlib import Path
from datetime import datetime

def run_experiments_n_10000(iterations, seed_token, graph_type):
    output_dir = f"./results/random/VARM/{graph_type}"
    n = 10000
    # n = 1000
    variants = ["0", "N"]
    algorithms = {"kPath": "2", "kLev":"3"}
    k_values = [2, 5, 10]

    print(f"Running VARM with {iterations} iterations, for N = 100 varying M from 1,000 to 49,995,000 and seed token {seed_token}")

    Path(output_dir).mkdir(parents=True, exist_ok=True)

    # m_values = [100, 500, 1000] + list(range(2_500, 10_000, 2_500)) + list(range(10_000, 30_000, 5_000)) + list(range(30_000, 60_000, 10_000)) + [75_000] + list(range(100_000, 500_000, 100_000)) + [500_000, 750_000, 1_000_000] + list(range(2_500_000, 10_000_000, 2_500_000)) + [10_000_000, 25_000_000, 49_995_000]
    # m_values = list(range(100, 1000, 100)) + list(range(1000, 20000, 1000)) + list(range(20000, 100000, 10000)) + list(range(100000, 400001, 100000)) + [499500]
    
    m_values = list(range(1000, 10001, 1000)) + list(range(12_500, 25_001, 2_500)) + list(range(30_000, 100_000, 10_000)) + list(range(100_000, 1_000_001, 100_000)) + list(range(2_000_000, 10_000_000, 2_000_000)) + list(range(10_000_000, 40_000_001, 5_000_000)) + [49_995_000]

    # Add a timestamped directory for each run
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    kLev_output_dir = os.path.join(output_dir, f"kLev_N_10000_seed_{seed_token}_iter_{iterations}_{timestamp}")
    kPath_output_dir = os.path.join(output_dir, f"kPath_N_10000_seed_{seed_token}_iter_{iterations}_{timestamp}")
    Path(kLev_output_dir).mkdir(parents=True, exist_ok=True)
    Path(kPath_output_dir).mkdir(parents=True, exist_ok=True)

    # Open CSV files for writing
    csv_files = {}
    file_objects = {}
    
    # kPath
    for variant in variants:
        for k in k_values:
            results_file = os.path.join(kPath_output_dir, f"kPath{variant}({k}).csv")
            csvfile = open(results_file, "w", newline="")
            csvwriter = csv.writer(csvfile, delimiter=',')
            csvwriter.writerow(["M", "Time (s)", "Memory (KB)", "Passes"])
            csv_files[("kPath", variant, k)] = csvwriter
            file_objects[("kPath", variant, k)] = csvfile

    # kLev
    for variant in variants:
        for k in k_values:
            results_file = os.path.join(kLev_output_dir, f"kLev{variant}({k}).csv")
            csvfile = open(results_file, "w", newline="")
            csvwriter = csv.writer(csvfile, delimiter=',')
            csvwriter.writerow(["M", "Time (s)", "Memory (KB)", "Passes"])
            csv_files[("kLev", variant, k)] = csvwriter
            file_objects[("kLev", variant, k)] = csvfile


    for m in m_values:
        # Prepare for the Experiment [PREP_EXP]
        try:
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

                    # Run the Experiment [RUN_EXP]
                    try:
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
                    output_lines = result.stdout.strip().split("\n")
                    user_time_mem = result.stderr.strip()  # Time and memory are in stderr
                    avg_passes = round(float(output_lines[-1]), 2)  # Assuming pass count is the last line of stdout
                    print(f"      Average Passes: {avg_passes}, Time/Memory: {user_time_mem}")

                    # Extract time and memory
                    try:
                        user_time, memory = map(float, user_time_mem.split(","))
                    except ValueError as e:
                        print(f"Error parsing time/memory for  N={n}, M={m}, k={k}, seed={seed_token}: {e}")
                        continue

                    # Calculate average time
                    avg_time = round(user_time / iterations, 2)
                    memory = round(memory, 2)

                    # Write data to CSV
                    csvwriter.writerow([m, avg_time, memory, avg_passes])

        # try:
        #     dest = f"/media/user/D2B860A9B8608DB3/UndirectedGraphs/RandomGraphs/VARM_{graph_type}_iter_{iterations}_seed_{seed_token}/"
        #     Path(dest).mkdir(parents=True, exist_ok=True)
        #     subprocess.run(
        #         f"mv input/random_graphs/graph_{n}_{m}_{graph_type}_* "
        #         f"{dest}",
        #         shell=True,
        #         check=True
        #     ) # Move the used graphs to the HDD
        # except subprocess.CalledProcessError as e:
        #     print(f"Error moving graphs for VARM with N={n}, M={m}: {e}")
        #     continue

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

    run_experiments_n_10000(args.iterations, args.seed_token, args.graph_type)
