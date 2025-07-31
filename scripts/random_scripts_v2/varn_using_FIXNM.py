import os
import subprocess
import argparse
import csv
from pathlib import Path
from datetime import datetime

sparsity_label = {2: "logN", 3: "sqrtN", 4: "N2"}

def run_experiments(iterations, seed_token, sparsity, graph_type):
    output_dir = f"./results/random_v2/VARN/{graph_type}"
    variants = ["0", "1", "2", "N"]
    algorithms = {"kpath": "2", "klev":"3"} # kpath, klev
    k_values = [2, 5, 10]

    print(f"Running experiments with {iterations} iterations, varying N from 10 to 10,000 and seed token {seed_token}")

    Path(output_dir).mkdir(parents=True, exist_ok=True)

    n_values = list(range(10, 100, 10)) + list(range(100, 1000, 100)) + list(range(1000, 2000, 200)) + list(range(2000, 5000, 500)) + list(range(5000, 10001, 1000))

    # Add a timestamped directory for each run
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    run_output_dir = os.path.join(output_dir, f"density_{sparsity_label[sparsity]}_seed_{seed_token}_itr_{iterations}_{timestamp}")
    Path(run_output_dir).mkdir(parents=True, exist_ok=True)

    # Open CSV files for writing
    csv_files = {}
    file_objects = {}
    for algorithm_name, algorithm_code in algorithms.items():
        for variant in variants:
            for k in k_values:
                # Create a unique filename for each algorithm and variant
                results_file = os.path.join(run_output_dir, f"{algorithm_name}{variant}_k{k}.csv")
                csvfile = open(results_file, "w", newline="")
                csvwriter = csv.writer(csvfile, delimiter=',')
                csvwriter.writerow(["N", "Time (s)", "Memory (KB)", "AvgPasses", "AvgHeight"])
                csv_files[(algorithm_name, variant, k)] = csvwriter
                file_objects[(algorithm_name, variant, k)] = csvfile

    for n in n_values:
        try: # Prepare for the Experiment [PREP_EXP]
            subprocess.run(
                ["./bin/main", "PREP_EXP", "3", str(n), str(sparsity), graph_type, str(iterations), str(seed_token)],
                check=True
            ) # 3 for FIXNM type experiment
        except subprocess.CalledProcessError as e:
            print(f"Error generating graph with N={n}, sparsity={sparsity}, iterations={iterations}, seed={seed_token}: {e}")
            continue

        for algorithm_name, algorithm_code in algorithms.items():
            for variant in variants:
                for k in k_values:
                    csvwriter = csv_files[(algorithm_name, variant, k)]

                    print(f"Running {algorithm_name} variant {variant} with N={n}, sparsity={sparsity}, k={k}, seed={seed_token}...")

                    try: # Run the Experiment [RUN_EXP]
                        result = subprocess.run(
                            ["/usr/bin/time", "-f", "%U,%M", "./bin/main", "RUN_EXP", "3", str(n), str(sparsity), graph_type, str(iterations), str(seed_token), algorithm_code, variant, str(k)],
                            stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE,
                            text=True,
                            check=True
                        )
                    except subprocess.CalledProcessError as e:
                        print(f"Error running {algorithm_name} variant {variant} with N={n}, sparsity={sparsity}, k={k}, seed={seed_token}: {e}")
                        continue

                    # Parse the output
                    output = result.stdout.strip().split()
                    user_time_mem = result.stderr.strip()  # Time and memory are in stderr
                    avg_passes = float(output[0])  # Assuming pass count is the last line of stdout
                    avg_height = float(output[1])
                    print(f"      Average Passes: {avg_passes},  Average Height: {avg_height}, Time/Memory: {user_time_mem}")

                    # Extract time and memory
                    try:
                        user_time, memory = map(float, user_time_mem.split(","))
                    except ValueError:
                        print(f"Error parsing time/memory for N={n}, sparsity={sparsity}, seed={seed_token}")
                        continue

                    # Calculate average time
                    avg_time = user_time / float(iterations)
                    memory = memory

                    # Write data to CSV
                    csvwriter.writerow([n, avg_time, memory, avg_passes, avg_height])

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


# Usage: (ulimit -s unlimited; nohup python3 scripts/random_scripts_v2/varn_using_FIXNM.py -i 10 -s 1729 -sp 2 -g UNIFORM > "scripts/random_scripts_v2/logs/varn_n_10K_uniform_logn_seed_1729_itr10_terraforge_run_$(date +%Y%m%d_%H%M%S).log" 2>&1 < /dev/null &)
