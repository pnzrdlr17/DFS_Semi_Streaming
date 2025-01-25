from datetime import datetime
import os
import subprocess
import argparse
import csv
from pathlib import Path

def run_experiments(algorithm, iterations, output_dir):
    variants = ["0", "1", "2", "N", "X"]
    if algorithm == "klev":
        variants.append("Y")




    # Define the graph dataset
    graphs = [
        # {"label": "CU", "n": 49, "m": 107, "path": "./input/CU/download.tsv.contiguous-usa/contiguous-usa/out.contiguous-usa"},
        # {"label": "AJazz", "n": 198, "m": 2742, "path": "./input/AJazz/download.tsv.arenas-jazz/arenas-jazz/out.arenas-jazz"},
        # {"label": "HM", "n": 2426, "m": 16631, "path": "./input/HM/download.tsv.petster-hamster/petster-hamster/out.petster-hamster"},
        # {"label": "ArxAP", "n": 18771, "m": 198050, "path": "./input/ArxAP/download.tsv.ca-AstroPh/ca-AstroPh/out.ca-AstroPh"},
        {"label": "AsCaida", "n": 26475, "m": 53381, "path": "./input/AsCaida/download.tsv.as-caida20071105/as-caida20071105/out.as-caida20071105"},
        # {"label": "BrightK", "n": 58228, "m": 214078, "path": "./input/BrightK/download.tsv.loc-brightkite_edges/loc-brightkite_edges/out.loc-brightkite_edges"},
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
        # Add more bigger graphs here
    ]

    # Ensure output directory exists
    Path(output_dir).mkdir(parents=True, exist_ok=True)

    # Loop over each graph
    for graph in graphs:
        label, n, m, input_path = graph["label"], graph["n"], graph["m"], graph["path"]
        graph_output_dir = os.path.join(output_dir, label)
        Path(graph_output_dir).mkdir(parents=True, exist_ok=True)

        # Add a timestamped directory for each script run
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        run_output_dir = os.path.join(graph_output_dir, f"run_{timestamp}")
        Path(run_output_dir).mkdir(parents=True, exist_ok=True)

        for variant in variants:
            variant_output_dir = os.path.join(run_output_dir, f"{algorithm}_{variant}")
            Path(variant_output_dir).mkdir(parents=True, exist_ok=True)

            aggregate_file = os.path.join(variant_output_dir, f"aggregate_results.csv")
            with open(aggregate_file, "w", newline="") as agg_csvfile:
                agg_csvwriter = csv.writer(agg_csvfile, delimiter=',')
                agg_csvwriter.writerow(["K", "Average User Time (s)", "Average Memory (KB)", "Passes"])

                print(f"\nRunning {label} for variant {variant}...")

                # Loop over values of k (1 to 10)
                for k in range(1, 11):
                    k_output_file = os.path.join(variant_output_dir, f"k_{k}_results.csv")
                    with open(k_output_file, "w", newline="") as k_csvfile:
                        k_csvwriter = csv.writer(k_csvfile, delimiter=',')
                        k_csvwriter.writerow(["K", "Iteration", "User Time (s)", "Memory (KB)", "Passes"])

                        times, memories = [], []
                        for i in range(1, iterations + 1):
                            print(f"  Running k={k}, iteration {i}/{iterations}...")

                            # Execute the binary
                            try:
                                result = subprocess.run(
                                    ["/usr/bin/time", "-f", "%U,%M", "./bin/main", "RUN_ALGO", str(n), str(m), input_path,
                                     "2" if algorithm == "kpath" else "3", variant, str(k)],
                                    stdout=subprocess.PIPE,
                                    stderr=subprocess.PIPE,
                                    text=True,
                                    check=True,
                                    timeout=43200  # 12 hours timeout
                                )
                            except subprocess.TimeoutExpired:
                                print(f"Timeout expired for graph {label}, algorithm {algorithm} variant {variant}")
                                continue
                            except subprocess.CalledProcessError as e:
                                print(f"Error running graph {label}, variant {variant}, k={k}: {e}")
                                continue

                            # Parse the output
                            output_lines = result.stdout.strip().split("\n")
                            user_time_mem = result.stderr.strip()  # Time and memory are in stderr
                            pass_count = "\n".join(output_lines)  # Program output is in stdout
                            print(f"    Passes: {pass_count}, Time/Memory: {user_time_mem}, Output: {output_lines}")

                            # Extract time and memory
                            try:
                                user_time, memory = map(float, user_time_mem.split(","))
                            except ValueError:
                                print(f"Error parsing time/memory for {label}, k={k}, iteration {i}")
                                continue

                            times.append(user_time)
                            memories.append(memory)

                            # Write individual iteration data
                            k_csvwriter.writerow([k, i, user_time, memory, pass_count])

                        # Calculate and save average stats for this k
                        if times and memories:
                            avg_time = round(sum(times) / iterations, 4)
                            avg_memory = round(sum(memories) / iterations, 4)
                            agg_csvwriter.writerow([k, avg_time, avg_memory, pass_count])

            print(f"Results for {label} variant {variant} saved to {variant_output_dir}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run k-path or k-level algorithms on real graphs and capture time and memory data.")
    parser.add_argument(
        "algorithm",
        choices=["kpath", "klev"],
        help="Algorithm to run: kpath (for KPath) or klev (for KLev)"
    )
    parser.add_argument(
        "-i", "--iterations",
        type=int,
        default=3,
        help="Number of iterations for each k (default: 3)"
    )
    parser.add_argument(
        "-o", "--output-dir",
        default="./results/real/time_memory",
        help="Directory to save the results (default: ./results/real/time_memory)"
    )
    args = parser.parse_args()

    run_experiments(args.algorithm, args.iterations, args.output_dir)