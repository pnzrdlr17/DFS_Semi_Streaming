import os
import subprocess
import argparse
import csv
from pathlib import Path
from datetime import datetime

def run_experiments(iterations, seed_token, output_dir):
    variants = ["0", "N"]
    algorithms = {"kpath": "2", "klev":"3"} # kpath, klev
    sparsity_values = [2, 3]
    k = 10

    Path(output_dir).mkdir(parents=True, exist_ok=True)

    n_values = list(range(10, 101, 10)) + list(range(150, 550, 50)) + list(range(600, 1100, 100)) + list(range(1200, 2200, 200)) + list(range(2500, 5500, 500)) + list(range(6000, 11000, 1000))

    # Add a timestamped directory for each run
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    run_output_dir = os.path.join(output_dir, f"run_{timestamp}_seed_{seed_token}")
    Path(run_output_dir).mkdir(parents=True, exist_ok=True)

    for sparsity in sparsity_values:
        sparsity_folder = f"sparsity_logN" if sparsity == 2 else f"sparsity_sqrtN"
        sparsity_folder += f"_seed_{seed_token}_k{k}"
        sparsity_output_dir = os.path.join(run_output_dir, sparsity_folder)
        Path(sparsity_output_dir).mkdir(parents=True, exist_ok=True)

        # Open CSV files for writing
        csv_files = {}
        file_objects = {}
        for algorithm_name, algorithm_code in algorithms.items():
            for variant in variants:
                results_file = os.path.join(sparsity_output_dir, f"{algorithm_name}_{variant}_results.csv")
                csvfile = open(results_file, "w", newline="")
                csvwriter = csv.writer(csvfile, delimiter=',')
                csvwriter.writerow(["N", "Time (s)", "Memory (KB)", "Passes"])
                csv_files[(algorithm_name, variant)] = csvwriter
                file_objects[(algorithm_name, variant)] = csvfile

        for n in n_values:
            # Prepare for the Experiment [PREP_EXP]
            try:
                subprocess.run(
                    ["./bin/main", "PREP_EXP", "3", str(n), str(sparsity), "UNIFORM", str(iterations), str(seed_token)],
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
                            ["/usr/bin/time", "-f", "%U,%M", "./bin/main", "RUN_EXP", "3", str(n), str(sparsity), "UNIFORM", str(iterations), str(seed_token), algorithm_code, variant, str(k)],
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

        for csvfile in file_objects.values():
            csvfile.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate random uniform graphs and run k-path and k-level algorithms to capture time, memory, and pass count.")
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
        "-o", "--output-dir",
        default="./results/random/uniform_figure_2",
        help="Directory to save the results (default: ./results/random/uniform_figure_2)"
    )
    args = parser.parse_args()

    run_experiments(args.iterations, args.seed_token, args.output_dir)