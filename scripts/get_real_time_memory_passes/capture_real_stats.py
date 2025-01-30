import os
import subprocess
import argparse
import csv
from math import ceil
from datetime import datetime
from pathlib import Path

# Define the graph dataset
graphs = [
    # {"label": "CU", "n": 49, "m": 107, "path": "./input/CU/download.tsv.contiguous-usa/contiguous-usa/out.contiguous-usa"},
    # {"label": "AJazz", "n": 198, "m": 2742, "path": "./input/AJazz/download.tsv.arenas-jazz/arenas-jazz/out.arenas-jazz"},
    # {"label": "HM", "n": 2426, "m": 16631, "path": "./input/HM/download.tsv.petster-hamster/petster-hamster/out.petster-hamster"},
    # {"label": "Belcastro", "n": 14022, "m": 9027024, "path": "./input/Belcastro/belcastro_n_14022_m_9027024.edg"},
    # {"label": "ArxAP", "n": 18771, "m": 198050, "path": "./input/ArxAP/download.tsv.ca-AstroPh/ca-AstroPh/out.ca-AstroPh"},
    # {"label": "AsCaida", "n": 26475, "m": 53381, "path": "./input/AsCaida/download.tsv.as-caida20071105/as-caida20071105/out.as-caida20071105"},
    # {"label": "BrightK", "n": 58228, "m": 214078, "path": "./input/BrightK/download.tsv.loc-brightkite_edges/loc-brightkite_edges/out.loc-brightkite_edges"},
    # {"label": "LMocha", "n": 104103, "m": 2193083, "path": "./input/LMocha/download.tsv.livemocha/livemocha/out.livemocha"},
    # {"label": "FlickrE", "n": 105938, "m": 2316948, "path": "./input/FlickrE/download.tsv.flickrEdges/flickrEdges/out.flickrEdges"},
    # {"label": "WordNet", "n": 146005, "m": 656999, "path": "./input/WordNet/download.tsv.wordnet-words/wordnet-words/out.wordnet-words"},
    # {"label": "Douban", "n": 154908, "m": 327162, "path": "./input/Douban/download.tsv.douban/douban/out.douban"},
    # {"label": "Twitch", "n": 168114, "m": 6797557, "path": "./input/Twitch/twitch_gamer_n_168114_m_6797557.edg"},
    # {"label": "Gowalla", "n": 196591, "m": 950327, "path": "./input/Gowalla/download.tsv.loc-gowalla_edges/loc-gowalla_edges/out.loc-gowalla_edges"},
    # {"label": "Dblp", "n": 317080, "m": 1049866, "path": "./input/Dblp/download.tsv.com-dblp/com-dblp/out.com-dblp"},
    # {"label": "Amazon", "n": 334863, "m": 925872, "path": "./input/Amazon/download.tsv.com-amazon/com-amazon/out.com-amazon"},
    {"label": "RoadnetPA", "n": 1088092, "m": 1541898, "path": "./input/RoadnetPA/roadnetPA_n_1088092_m_1541898.edg"},
    # {"label": "Youtube", "n": 1134890, "m": 2987624, "path": "./input/Youtube/youtube_n_1134890_m_2987624.edg"},
    # {"label": "Skitter", "n": 1696415, "m": 11095298, "path": "./input/Skitter/skitter_n_1696415_m_11095298.edg"},
    {"label": "RoadnetCA", "n": 1965206, "m": 2766607, "path": "./input/RoadnetCA/roadnetCA_n_1965206_m_2766607.edg"},
    # {"label": "Orkut", "n": 3072441, "m": 117185083, "path": "./input/Orkut/orkut_graph_n_3072441_m_117185083.edg"},
    # {"label": "LiveJournal", "n": 3997962, "m": 34681189, "path": "./input/LiveJournal/live_journal_n_3997962_m_34681189.edg"},
    # {"label": "Friendster", "n": 65608366, "m": 1806067135, "path": "./input/Friendster/friendster_n_65608366_m_1806067135.edg"},
]

base_command = ['/usr/bin/time', '-f', '%U,%M', './bin/main', 'RUN_ALGO']

def run_command(command, label, algorithm, variant = None, k = 0):
    try:
        result = subprocess.run(
            command, # Execute the binary
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            check=True,
            timeout=43200  # 12 hours timeout
            # TODO: Ensure proper timeout
        )
    except subprocess.TimeoutExpired:
        print(f"Timeout (12hrs) expired for graph {label}, {algorithm}{variant}, k={k}")
        return None, None, None
    except subprocess.CalledProcessError as e:
        print(f"Error running graph {label}, {algorithm}{variant}: {e}, k={k}")
        return None, None, None

    # Parse the output
    output_lines = result.stdout.strip().split("\n")
    time_mem = result.stderr.strip()  # Time and memory are in stderr
    pass_count = "\n".join(output_lines)  # Program output is in stdout
    print(f"    Passes: {pass_count}, Time/Memory: {time_mem}, Output: {output_lines}")

    try: # Extract time and memory
        time, memory = map(float, time_mem.split(","))
    except ValueError:
        print(f"Error parsing time/memory for {label}, variant {variant}, k={k}: {e}")
        return None, None, None
    
    return time, memory, pass_count

def k_experiments(algorithm, graph, runThreshold, output_dir):
    label, n, m, input_path = graph["label"], graph["n"], graph["m"], graph["path"]
    variants = ["0", "1", "2", "N"]
    
    for variant in variants:
        variant_file = os.path.join(output_dir, f"{algorithm}{variant}.csv")
        with open(variant_file, "w", newline="") as variant_csvfile:
            variant_csvwriter = csv.writer(variant_csvfile, delimiter=',')
            variant_csvwriter.writerow(["K", "Time (s)", "Memory (KB)", "Passes"])

            print(f"\nRunning {label} for variant {variant}...")

            for k in range(1, runThreshold + 1):
                print(f"  Running k={k},...")

                # Execute the binary
                time, memory, pass_count = run_command(
                    base_command + [str(n), str(m), input_path,"2" if algorithm == "kpath" else "3", variant, str(k)],
                    label, algorithm, variant, k
                )
                
                if time is None or memory is None or pass_count is None: 
                    print(f"Error running graph {label}, variant {variant}, k={k}")
                    variant_csvwriter.writerow([k, "N/A", "N/A", "N/A"])
                else:
                    variant_csvwriter.writerow([k, time, memory, pass_count])

        print(f"Results for {label} running {algorithm}{variant} saved to {output_dir}")

def run_simp(graph, output_dir, variant):
    label, n, m, input_path = graph["label"], graph["n"], graph["m"], graph["path"]
    simp_file = os.path.join(output_dir, f"simp{variant}.csv")
    with open(simp_file, "w", newline="") as simp_csvfile:
        simp_csvwriter = csv.writer(simp_csvfile, delimiter=',')
        simp_csvwriter.writerow(["Time (s)", "Memory (KB)", "Passes"])

        print(f"\nRunning {label} for variant {variant}...")
        
        time, memory, pass_count = run_command(base_command + [str(n), str(m), input_path, "0", variant], label, "simp", variant)
        
        simp_csvwriter.writerow([time, memory, pass_count])

    print(f"Results for {label} running simp{variant} saved to {output_dir}")

def run_improv(graph, output_dir):
    label, n, m, input_path = graph["label"], graph["n"], graph["m"], graph["path"]
    improv_file = os.path.join(output_dir, f"improv.csv")
    with open(improv_file, "w", newline="") as improv_csvfile:
        improv_csvwriter = csv.writer(improv_csvfile, delimiter=',')
        improv_csvwriter.writerow(["Time (s)", "Memory (KB)", "Passes"])

        print(f"\nRunning {label} for improv...")
        
        time, memory, pass_count = run_command(base_command + [str(n), str(m), input_path, "1"], label, "improv")
        
        improv_csvwriter.writerow([time, memory, pass_count])

    print(f"Results for {label} running improv saved to {output_dir}")

def run_experiments(algorithm, output_dir):
    Path(output_dir).mkdir(parents=True, exist_ok=True) # Ensure output directory exists

    for graph in graphs: # Loop over each graph
        graph_output_dir = os.path.join(output_dir, graph["label"])
        Path(graph_output_dir).mkdir(parents=True, exist_ok=True)

        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S") # Add a timestamped directory for each script run
        run_output_dir = os.path.join(graph_output_dir, f"{algorithm}_run_{timestamp}")
        Path(run_output_dir).mkdir(parents=True, exist_ok=True)

        if algorithm == "kpath" or algorithm == "klev":
            th = min(10, ceil(graph["m"] / graph["n"]))
            k_experiments(algorithm, graph, max(2, th), run_output_dir) # Run for k=1, 2, ..., min(10, ceil(m/n))
        if algorithm == "simp":
            run_simp(graph, run_output_dir, "0")
            run_simp(graph, run_output_dir, "1")
        if algorithm == "improv":
            run_improv(graph, run_output_dir)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run k-path or k-level algorithms on real graphs and capture time and memory data.")
    parser.add_argument(
        "algorithm",
        choices=["kpath", "klev", "simp", "improv"],
        help="Algorithm to run: kpath (for KPath) or klev (for KLev) or simp (for Simp) or improv (for Improv)"
    )
    parser.add_argument(
        "-o", "--output-dir",
        default="./results/real/sc_optimized_stats",
        help="Directory to save the results (default: ./results/real/sc_optimized_stats)"
    )
    args = parser.parse_args()

    run_experiments(args.algorithm, args.output_dir)
