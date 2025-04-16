import os
import subprocess
import argparse
import csv
import math
from pathlib import Path
from datetime import datetime

sparsity_label = {2: "logN", 3: "sqrtN", 4: "N2"}

def run_experiments(iterations, seed_token, sparsity, graph_type):
    output_dir = f"./results/random/VARN/{graph_type}"
    variants = ["0", "N"]
    algorithms = {"kpath": "2", "klev":"3"} # kpath, klev
    k = 10

    print(f"Running experiments with {iterations} iterations, varying N from 10 to 10,000 and seed token {seed_token}")

    Path(output_dir).mkdir(parents=True, exist_ok=True)

    # n_values = list(range(10, 101, 10)) + list(range(150, 550, 50)) + list(range(600, 1100, 100)) + list(range(1200, 2200, 200)) + list(range(2500, 5500, 500)) + list(range(6000, 11000, 1000))
    n_values = list(range(10, 100, 10)) + list(range(100, 1001, 50)) 

    # Add a timestamped directory for each run
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    run_output_dir = os.path.join(output_dir, f"{sparsity_label[sparsity]}_seed_{seed_token}_itr_{iterations}_k_{k}_{timestamp}")
    Path(run_output_dir).mkdir(parents=True, exist_ok=True)

    # Open CSV files for writing
    csv_files = {}
    file_objects = {}
    for algorithm_name, algorithm_code in algorithms.items():
        for variant in variants:
            results_file = os.path.join(run_output_dir, f"{algorithm_name}_{variant}.csv")
            csvfile = open(results_file, "w", newline="")
            csvwriter = csv.writer(csvfile, delimiter=',')
            csvwriter.writerow(["N", "Time (s)", "Memory (KB)", "Passes"])
            csv_files[(algorithm_name, variant)] = csvwriter
            file_objects[(algorithm_name, variant)] = csvfile

    for n in n_values:
        # Prepare for the Experiment [PREP_EXP]
        try:
            subprocess.run(
                ["./bin/main", "PREP_EXP", "3", str(n), str(sparsity), graph_type, str(iterations), str(seed_token)],
                check=True
            ) # 3 for FIXNM type experiment
        except subprocess.CalledProcessError as e:
            print(f"Error generating graph with N={n}, sparsity={sparsity}, iterations={iterations}, seed={seed_token}: {e}")
            continue

        for algorithm_name, algorithm_code in algorithms.items():
            for variant in variants:
                csvwriter = csv_files[(algorithm_name, variant)]

                print(f"Running {algorithm_name} variant {variant} with N={n}, sparsity={sparsity}, seed={seed_token}...")

                # Run the Experiment [RUN_EXP]
                try:
                    result = subprocess.run(
                        ["/usr/bin/time", "-f", "%U,%M", "./bin/main", "RUN_EXP", "3", str(n), str(sparsity), graph_type, str(iterations), str(seed_token), algorithm_code, variant, str(k)],
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE,
                        text=True,
                        check=True
                    )
                except subprocess.CalledProcessError as e:
                    print(f"Error running {algorithm_name} variant {variant} with N={n}, sparsity={sparsity}, seed={seed_token}: {e}")
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
                    print(f"Error parsing time/memory for N={n}, sparsity={sparsity}, seed={seed_token}")
                    continue

                # Calculate average time
                avg_time = round(user_time / iterations, 2)
                memory = round(memory, 2)

                # Write data to CSV
                csvwriter.writerow([n, avg_time, memory, avg_passes])

        # if (sparsity == 2):
        #     m = int(n * math.log2(n))
        # elif (sparsity == 3):
        #     m = int(n * math.sqrt(n))
        # elif (sparsity == 4):
        #     m = int((n * (n - 1)) / 2)
        # try:
        #     dest = f"/media/user/D2B860A9B8608DB3/UndirectedGraphs/RandomGraphs/VARN_{graph_type}_{sparsity_label[sparsity]}_iter_{iterations}_seed_{seed_token}/"
        #     Path(dest).mkdir(parents=True, exist_ok=True)
        #     subprocess.run(
        #         f"mv input/random_graphs/graph_{n}_{m}_{graph_type}_* "
        #         f"{dest}",
        #         shell=True,
        #         check=True
        #     ) # Move the used graphs to the HDD
        # except subprocess.CalledProcessError as e:
        #     print(f"Error moving graphs for VARN with N={n}, M={m}: {e}")
        #     continue

    for csvfile in file_objects.values():
        csvfile.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate random powerlaw graphs and run k-path and k-level algorithms to capture time, memory, and pass count.")
    parser.add_argument(
        "-i", "--iterations",
        type=int,
        default=100,
        help="Number of iterations to run for each combination (default: 1)"
    )
    parser.add_argument(
        "-s", "--seed-token",
        type=int,
        required=True,
        help="Seed token to generate random seeds",
        default=1729
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

    run_experiments(args.iterations, args.seed_token, args.sparsity, args.graph_type)