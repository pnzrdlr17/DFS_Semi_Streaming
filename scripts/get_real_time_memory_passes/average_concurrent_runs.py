import os
import subprocess
import argparse
import signal
from math import ceil
from pathlib import Path
from datetime import datetime
import time

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
    # {"label": "RoadnetPA", "n": 1088092, "m": 1541898, "path": "./input/RoadnetPA/roadnetPA_n_1088092_m_1541898.edg"},
    # {"label": "Youtube", "n": 1134890, "m": 2987624, "path": "./input/Youtube/youtube_n_1134890_m_2987624.edg"},
    # {"label": "Skitter", "n": 1696415, "m": 11095298, "path": "./input/Skitter/skitter_n_1696415_m_11095298.edg"},
    # {"label": "RoadnetCA", "n": 1965206, "m": 2766607, "path": "./input/RoadnetCA/roadnetCA_n_1965206_m_2766607.edg"},
    # {"label": "Orkut", "n": 3072441, "m": 117185083, "path": "./input/Orkut/orkut_graph_n_3072441_m_117185083.edg"},
    # {"label": "LiveJournal", "n": 3997962, "m": 34681189, "path": "./input/LiveJournal/live_journal_n_3997962_m_34681189.edg"},
    # {"label": "KonectDblp", "n": 7577304, "m": 12282059, "path": "./input/KonectDblp/konect_dblp_n_7577304_m_12282059.edg"},
    # {"label": "Friendster", "n": 65608366, "m": 1806067135, "path": "./input/Friendster/friendster_n_65608366_m_1806067135.edg"},
]

base_command = ['/usr/bin/time', '-f', '%U,%M', './bin/main', 'RUN_ALGO']

def run_command(command, label, algorithm, variant = None, k = 0):
    try:
        p = subprocess.Popen(
            command, # Execute the binary
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            start_new_session=True  # Creates a new process group, allowing us to kill the process and its children
        )

        result = p.wait(timeout=43200)  # 12 hours timeout

    except subprocess.TimeoutExpired:
        os.killpg(os.getpgid(p.pid), signal.SIGTERM) # Kill the process and its children
        return f"Timeout (12hrs) expired for graph {label}, {algorithm}{variant}, k={k}.\nProcess killed."
    except subprocess.CalledProcessError as e:
        return f"Error running graph {label}, {algorithm}{variant}: {e}, k={k}"

    # Parse the output
    stdout, stderr = p.communicate() # Get stdout/stderr

    output_lines = stdout.strip().split("\n")
    time_mem = stderr.strip()  # Time and memory are in stderr
    pass_count = "\n".join(output_lines)  # Program output is in stdout
    print(f"    Passes: {pass_count}, Time/Memory: {time_mem}, Output: {output_lines}")

    try: # Extract time and memory
        time, memory = map(float, time_mem.split(","))
    except ValueError as e:
        print(f"Error parsing time/memory for {label}, variant {variant}, k={k}: {e}")
        return None, None, None
    
    return time, memory, pass_count


def write_to_file(output, output_file, mode):
    if mode == "append":
        with open(output_file, "a") as file:
            file.write(output)
    elif mode == "overwrite":
        with open(output_file, "w") as file:
            file.write(output)
    else:
        print("Invalid mode")

def k_experiments(algorithm, iterations, graph, output_dir):
    label, n, m, input_path = graph["label"], graph["n"], graph["m"], graph["path"]
    variants = ["N", "2", "1", "0"]
    
    for variant in variants:
        for k in ["C", 10, 5, 2, 1]:
            k_val = ceil(m / n) if k == "C" else k
            avg_file = os.path.join(output_dir, f"{label}_{algorithm}_{variant}_{k}.txt")
            raw_file = os.path.join(output_dir, f"{label}_{algorithm}_{variant}_{k}_raw.txt")

            times = []
            mems = []
            pass_count = 0

            for i in range(iterations):
                print(f"Iteration {i+1}/{iterations} for Graph {label} running {algorithm}{variant} with k={k_val}...")

                # Execute the binary
                time, memory, passes = run_command(
                    base_command + [str(n), str(m), input_path,"2" if algorithm == "kpath" else "3", variant, str(k_val)],
                    label, algorithm, variant, k_val
                )

                if time is None or memory is None or passes is None:
                    print(f"Error running graph {label}, variant {variant}, k={k_val}")
                    continue

                # Parse the output

                times.append(float(time))
                mems.append(int(memory))
                pass_count = passes

                # Write individual iteration data
                write_to_file(f"{avg_time},{avg_mem},{pass_count},{datetime.now()}", raw_file, "append") # append

            if len(times) == 0 or len(mems) == 0 or pass_count == 0:
                print(f"No valid runs for graph {label}, variant {variant}, k={k_val}")
                continue

            # Calculate average time and memory
            avg_time = round(sum(times) / len(times), 2)
            avg_mem = round(sum(mems) / len(mems), 2)

            write_to_file(f"{avg_time},{avg_mem},{pass_count}", avg_file, "overwrite")

        print(f"Results for {label} running {algorithm}{variant} saved to {output_dir}")


def run_experiments(algorithm, iterations, output_dir):
    Path(output_dir).mkdir(parents=True, exist_ok=True) # Ensure output directory exists

    for graph in graphs: # Loop over each graph
       if algorithm == "kpath" or algorithm == "klev":
        k_experiments(algorithm,iterations, graph, output_dir)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run k-path or k-level algorithms on real graphs and capture time and memory data.")
    parser.add_argument(
        "algorithm",
        choices=["kpath", "klev", "simp", "improv"],
        help="Algorithm to run: kpath (for KPath) or klev (for KLev) or simp (for Simp) or improv (for Improv)"
    )
    parser.add_argument(
        "-i", "--iterations",
        type=int,
        default=1,
        help="Number of iterations to run (default: 1)"
    )
    parser.add_argument(
        "-o", "--output-dir",
        default="./results/real/average_concurrent_runs",
        help="Directory to save the results (default: ./results/real/average_concurrent_runs)"
    )
    args = parser.parse_args()

    run_experiments(args.algorithm, args.iterations, args.output_dir)
