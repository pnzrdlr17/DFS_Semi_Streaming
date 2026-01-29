import os
import subprocess
from math import ceil
from pathlib import Path
from datetime import datetime
from concurrent.futures import ThreadPoolExecutor, as_completed

# {"label": "Belcastro", "n": 14022, "m": 9027024, "path": "./input/Belcastro/belcastro_n_14022_m_9027024_2.edg"},
# {"label": "ArxAP", "n": 18771, "m": 198050, "path": "./input/ArxAP/download.tsv.ca-AstroPh/ca-AstroPh/out.ca-AstroPh"},
# {"label": "BrightK", "n": 58228, "m": 214078, "path": "./input/BrightK/download.tsv.loc-brightkite_edges/loc-brightkite_edges/out.loc-brightkite_edges"},

# {"label": "Twitch", "n": 168114, "m": 6797557, "path": "./input/Twitch/twitch_gamer_n_168114_m_6797557.edg"},
# {"label": "Gowalla", "n": 196591, "m": 950327, "path": "./input/Gowalla/download.tsv.loc-gowalla_edges/loc-gowalla_edges/out.loc-gowalla_edges"},
# {"label": "Amazon", "n": 334863, "m": 925872, "path": "./input/Amazon/download.tsv.com-amazon/com-amazon/out.com-amazon"},


# Augmented graph dataset with embedded run configurations
graphs = [
    {
        "label": "Belcastro",
        "n": 14022,
        "m": 9027024,
        "base_path": "./input/Belcastro/belcastro_n_14022_m_9027024",
        "run_configs": [
            {"algo": "kpath", "variant": "A", "k": 2, "iterations": 10, "file_number": 1},
            {"algo": "kpath", "variant": "A", "k": 1, "iterations": 10, "file_number": 2},
            {"algo": "kpath", "variant": "B", "k": "C", "iterations": 10, "file_number": 3},
            {"algo": "kpath", "variant": "B", "k": 9, "iterations": 10, "file_number": 4},
            {"algo": "kpath", "variant": "B", "k": 8, "iterations": 10, "file_number": 5},
            {"algo": "kpath", "variant": "B", "k": 7, "iterations": 10, "file_number": 6},
        ]
    },
    {
        "label": "Twitch",
        "n": 168114,
        "m": 6797557,
        "base_path": "./input/Twitch/twitch_gamer_n_168114_m_6797557",
        "run_configs": [
            #{"algo": "kpath", "variant": "C", "k": 1, "iterations": 10, "file_number": 1},
            {"algo": "kpath", "variant": "D", "k": 1, "iterations": 10, "file_number": 2},
            {"algo": "kpath", "variant": "C", "k": "C", "iterations": 10, "file_number": 3},
            {"algo": "kpath", "variant": "C", "k": 9, "iterations": 10, "file_number": 4},
            {"algo": "kpath", "variant": "C", "k": 8, "iterations": 10, "file_number": 5},
            {"algo": "kpath", "variant": "C", "k": 7, "iterations": 10, "file_number": 6},
            {"algo": "kpath", "variant": "C", "k": 6, "iterations": 10, "file_number": 7},
            #{"algo": "kpath", "variant": "B", "k": 1, "iterations": 10, "file_number": 8},
        ]
    },
    {
        "label": "Orkut", 
        "n": 3072441, 
        "m": 117185083, 
        "base_path": "./input/Orkut/orkut_graph_n_3072441_m_117185083",
        "run_configs": [
            {"algo": "kpath", "variant": "A", "k": 2, "iterations": 10, "file_number": 1},
            {"algo": "kpath", "variant": "A", "k": 1, "iterations": 10, "file_number": 3},
            {"algo": "kpath", "variant": "B", "k": "C", "iterations": 10, "file_number": 4},
            #{"algo": "kpath", "variant": "A", "k": 5, "iterations": 10, "file_number": 10},
            #{"algo": "kpath", "variant": "A", "k": 4, "iterations": 10, "file_number": 5},
            #{"algo": "kpath", "variant": "A", "k": 3, "iterations": 10, "file_number": 11},
        ]
    }
]

base_command = ['/usr/bin/time', '-f', '%U,%M', './bin/main', 'RUN_ALGO']

def get_file_path(base_path, file_number):
    """Get the actual file path based on file number"""
    if file_number == 1:
        return f"{base_path}.edg"
    else:
        return f"{base_path}_{file_number}.edg"

def run_command(command, label, algorithm, variant, k): # NO TIMEOUT
    try:
        p = subprocess.Popen(
            command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            start_new_session=True
        )

    except subprocess.CalledProcessError as e:
        print(f"Error running graph {label}, {algorithm}{variant}: {e}, k={k}")
        return None, None, None

    # Parse the output
    stdout, stderr = p.communicate()

    output = stdout.strip().split()
    time_mem = stderr.strip()
    pass_count = output[0]
    # height = output[1]
    print(f"      Passes: {output[0]},  Height: {output[1]}, Time/Memory: {time_mem}")

    try:
        time, memory = map(float, time_mem.split(","))
    except ValueError as e:
        print(f"Error parsing time/memory for {label}, variant {variant}, k={k}: {e}")
        return None, None, None
    
    return time, memory, pass_count

def write_to_file(output, output_file, mode):
    if mode == "append":
        with open(output_file, "a") as file:
            file.write(output)
            file.flush()
    elif mode == "overwrite":
        with open(output_file, "w") as file:
            file.write(output)
            file.flush()
    else:
        print("Invalid mode")

def run_single_config(graph, config, output_dir):
    """Run a single configuration for a graph"""
    label = graph["label"]
    n = graph["n"]
    m = graph["m"]
    base_path = graph["base_path"]
    
    algo = config["algo"]
    variant = config["variant"]
    k = config["k"]
    iterations = config["iterations"]
    file_number = config["file_number"]
    
    # Get the actual file path
    file_path = get_file_path(base_path, file_number)
    
    # Check if file exists
    if not os.path.exists(file_path):
        print(f"❌ File not found: {file_path}")
        return False
    
    k_val = ceil(m / n) if k == "C" else k
    avg_file = os.path.join(output_dir, f"{label}_{algo}_{variant}_{k}.txt")
    raw_file = os.path.join(output_dir, f"{label}_{algo}_{variant}_{k}_raw.txt")

    times = []
    mems = []
    pass_count = 0

    print(f"🚀 Running {label} with {algo}{variant}, k={k_val}, iterations={iterations}, file={file_number}")

    for i in range(iterations):
        print(f"  📊 Iteration {i+1}/{iterations} for {label} {algo}{variant} k={k_val}...")

        # Execute the binary
        time, memory, passes = run_command(
            base_command + [str(n), str(m), file_path, "2" if algo == "kpath" else "3", variant, str(k_val)],
            label, algo, variant, k_val
        )

        if time is None or memory is None or passes is None:
            print(f"    ❌ Error in iteration {i+1}")
            continue

        times.append(float(time))
        mems.append(int(memory))
        pass_count = passes

        # Write individual iteration data
        write_to_file(f'{time},{memory},{passes},{datetime.now().strftime("%Y%m%d_%H%M%S")}\n', raw_file, "append")

    if len(times) == 0 or len(mems) == 0 or pass_count == 0:
        print(f"❌ No valid runs for {label} {algo}{variant} k={k_val}")
        return False

    # Calculate average time and memory
    avg_time = round(sum(times) / len(times), 2)
    avg_mem = round(sum(mems) / len(mems), 2)

    write_to_file(f"{avg_time},{avg_mem},{pass_count}", avg_file, "overwrite")

    print(f"✅ Completed {label} {algo}{variant} k={k_val}: {avg_time}s, {avg_mem}KB")
    return True

def run_all_experiments(output_dir="./results/real/average_concurrent_runs", max_workers=40):
    """Run all experiments defined in the graphs list"""
    Path(output_dir).mkdir(parents=True, exist_ok=True)

    # Collect all configurations to run
    all_configs = []
    for graph in graphs:
        for config in graph["run_configs"]:
            all_configs.append((graph, config))

    total_configs = len(all_configs)
    print(f"🎯 Total configurations to run: {total_configs}")
    print(f"🔄 Running with {max_workers} parallel workers")

    completed_count = 0
    failed_count = 0

    # Run configurations in parallel
    with ThreadPoolExecutor(max_workers=max_workers) as executor:
        # Submit all tasks
        future_to_config = {
            executor.submit(run_single_config, graph, config, output_dir): (graph, config)
            for graph, config in all_configs
        }

        # Process completed tasks
        for future in as_completed(future_to_config):
            graph, config = future_to_config[future]
            completed_count += 1
            
            try:
                success = future.result()
                if success:
                    print(f"✅ [{completed_count}/{total_configs}] Completed {graph['label']} {config['algo']}{config['variant']} k={config['k']}")
                else:
                    failed_count += 1
                    print(f"❌ [{completed_count}/{total_configs}] Failed {graph['label']} {config['algo']}{config['variant']} k={config['k']}")
            except Exception as e:
                failed_count += 1
                print(f"💥 [{completed_count}/{total_configs}] Exception in {graph['label']} {config['algo']}{config['variant']} k={config['k']}: {e}")

    print(f"\n🏁 All experiments completed!")
    print(f"✅ Successful: {completed_count - failed_count}")
    print(f"❌ Failed: {failed_count}")
    print(f"📁 Results saved in {output_dir}")

if __name__ == "__main__":
    # You can adjust max_workers based on your system
    # Recommended: number of CPU cores or number of available graph file copies
    run_all_experiments(max_workers=18)

# Usage: (ulimit -s unlimited; nohup python3 scripts/get_real_time_memory_passes/batch_runner_raw.py > "scripts/get_real_time_memory_passes/logs/batch_run_$(date +%Y%m%d_%H%M%S).log" 2>&1 < /dev/null &)
