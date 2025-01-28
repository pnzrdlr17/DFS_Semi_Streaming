import os
import subprocess
import argparse
import csv
from pathlib import Path
from datetime import datetime
import math

def run_experiments(algorithm, output_dir, thresholdFactor=1):
    variants = ["0", "1", "2", "N", "X"]
    if algorithm == "klev":
        variants.append("Y")

    # Define the graph dataset
    graphs = [
        {"label": "CU", "n": 49, "m": 107, "path": "./input/CU/download.tsv.contiguous-usa/contiguous-usa/out.contiguous-usa"},
        {"label": "AJazz", "n": 198, "m": 2742, "path": "./input/AJazz/download.tsv.arenas-jazz/arenas-jazz/out.arenas-jazz"},
        {"label": "HM", "n": 2426, "m": 16631, "path": "./input/HM/download.tsv.petster-hamster/petster-hamster/out.petster-hamster"},
        {"label": "ArxAP", "n": 18771, "m": 198050, "path": "./input/ArxAP/download.tsv.ca-AstroPh/ca-AstroPh/out.ca-AstroPh"},
        {"label": "AsCaida", "n": 26475, "m": 53381, "path": "./input/AsCaida/download.tsv.as-caida20071105/as-caida20071105/out.as-caida20071105"},
        {"label": "BrightK", "n": 58228, "m": 214078, "path": "./input/BrightK/download.tsv.loc-brightkite_edges/loc-brightkite_edges/out.loc-brightkite_edges"},
        # {"label": "LMocha", "n": 104103, "m": 2193083, "path": "./input/LMocha/download.tsv.livemocha/livemocha/out.livemocha"},
        # {"label": "FlickrE", "n": 105938, "m": 2316948, "path": "./input/FlickrE/download.tsv.flickrEdges/flickrEdges/out.flickrEdges"},
        # {"label": "WordNet", "n": 146005, "m": 656999, "path": "./input/WordNet/download.tsv.wordnet-words/wordnet-words/out.wordnet-words"},
        # {"label": "Douban", "n": 154908, "m": 327162, "path": "./input/Douban/download.tsv.douban/douban/out.douban"},
        # {"label": "Gowalla", "n": 196591, "m": 950327, "path": "./input/Gowalla/download.tsv.loc-gowalla_edges/loc-gowalla_edges/out.loc-gowalla_edges"},
        # {"label": "Dblp", "n": 317080, "m": 1049866, "path": "./input/Dblp/download.tsv.com-dblp/com-dblp/out.com-dblp"},
        # {"label": "Amazon", "n": 334863, "m": 925872, "path": "./input/Amazon/download.tsv.com-amazon/com-amazon/out.com-amazon"},
        # {"label": "Twitch", "n": 168114, "m": 6797557, "path": "./input/Twitch/twitch_gamer_n_168114_m_6797557.edg"},
        # {"label": "LiveJournal", "n": 3997962, "m": 34681189, "path": "./input/LiveJournal/live_journal_n_3997962_m_34681189.edg"},
        # {"label": "Orkut", "n": 3072441, "m": 117185083, "path": "./input/Orkut/orkut_graph_n_3072441_m_117185083.edg"},
        # {"label": "Friendster", "n": 65608366, "m": 1806067135, "path": "./input/Friendster/friendster_n_65608366_m_1806067135.edg"}, #277
        # {"label": "Belcastro", "n": 14022, "m": 9027024, "path": "./input/Belcastro/belcastro_n_14022_m_9027024.edg"},
        # Add more bigger graphs here
    ]

    # Memory scaling steps (KB)
    memory_steps = [1000, 2000] + list(range(5000, 26000, 1000)) + list(range(30000, 55000, 5000)) + list(range(60000, 110000, 10000)) + list(range(200000, 1100000, 100000))

    # Ensure output directory exists
    Path(output_dir).mkdir(parents=True, exist_ok=True)

    # Loop over each graph
    for graph in graphs:
        label, n, m, input_path = graph["label"], graph["n"], graph["m"], graph["path"]
        k_threshold = int(math.ceil(thresholdFactor * math.ceil(m / n)))
        # k_threshold = max(k_threshold, 10)  # Ensure a minimum threshold of 10
        graph_output_dir = os.path.join(output_dir, label)
        Path(graph_output_dir).mkdir(parents=True, exist_ok=True)

        # Add a timestamped directory for each run
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        run_output_dir = os.path.join(graph_output_dir, f"run_{timestamp}")
        Path(run_output_dir).mkdir(parents=True, exist_ok=True)

        for variant in variants:
            results_file = os.path.join(run_output_dir, f"{algorithm}_{variant}.csv")
            with open(results_file, "w", newline="") as csvfile:
                csvwriter = csv.writer(csvfile, delimiter=',')
                csvwriter.writerow(["Memory Limit (KB)", "Optimal K", "Passes", "Actual Memory (KB)", "Max Valid K (within limit)"])

                print(f"\nRunning {label} for variant {variant}...")

                for memory_limit in memory_steps:
                    print(f"  Running with memory limit {memory_limit} KB...")

                    optimal_k = None
                    min_passes = float('inf')
                    actual_memory = None
                    max_valid_k = None

                    for k in range(1, k_threshold + 1):
                        print(f"  Testing k={k}...")

                        try:
                            result = subprocess.run(
                                ["gtime", "-f", "%U,%M", "./bin/main", "RUN_ALGO", str(n), str(m), input_path,
                                    "2" if algorithm == "kpath" else "3", variant, str(k)],
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                text=True,
                                check=True
                            )
                        except subprocess.CalledProcessError as e:
                            print(f"Error running graph {label}, variant {variant}, k={k}: {e}")
                            continue

                        # Parse the output
                        output_lines = result.stdout.strip().split("\n")
                        user_time_mem = result.stderr.strip()  # Time and memory are in stderr
                        pass_count = int(output_lines[-1])  # Assuming pass count is the last line of stdout
                        print(f"    Passes: {pass_count}, Time/Memory: {user_time_mem}")

                        # Extract memory usage
                        try:
                            _, memory = map(float, user_time_mem.split(","))
                        except ValueError:
                            print(f"Error parsing memory for {label}, k={k}")
                            continue

                        # Check if memory is within the limit
                        if memory <= memory_limit:
                            # Update if the number of passes is improved
                            if pass_count < min_passes:
                                min_passes = pass_count
                                optimal_k = k
                                actual_memory = memory

                            # Update the maximum valid k within the given limit
                            max_valid_k = k


                    # Write the results to the CSV file
                    if optimal_k is None:
                        csvwriter.writerow([memory_limit, "N/A", "N/A", "N/A", "N/A"])
                    else:
                        csvwriter.writerow([memory_limit, optimal_k, min_passes, actual_memory, max_valid_k])
                        print(f"Optimal k for {label} variant {variant} given {memory_limit}KB is {optimal_k} with {min_passes} passes")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run k-path or k-level algorithms on real graphs and capture pass vs memory data.")
    parser.add_argument(
        "algorithm",
        choices=["kpath", "klev"],
        help="Algorithm to run: kpath (for KPath) or klev (for KLev)"
    )
    parser.add_argument(
        "-o", "--output-dir",
        default="./results/real/memory_vs_passes",
        help="Directory to save the results (default: ./results/real/memory_vs_passes)"
    )
    parser.add_argument(
        "-t", "--threshold-factor",
        type=float,
        default=1,
        help="Threshold factor for KPath algorithm (default: 1)"
    )
    args = parser.parse_args()

    run_experiments(args.algorithm, args.output_dir, args.threshold_factor)