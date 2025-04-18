import os
import csv
import sys

from pathlib import Path

def process_file(input_path: Path, output_path: Path):
    try:
        with open(input_path, 'r') as f:
            reader = csv.reader(f)
            rows = list(reader)

        if not rows:
            raise ValueError(f"{input_path.name} is empty")

        # Parse all rows into float values
        parsed = []
        passes = set()
        for row in rows:
            if len(row) != 4:
                raise ValueError(f"Invalid row format in {input_path.name}: {row}")
            time, mem, p, _ = row
            time = float(time)
            mem = float(mem)
            p = int(p)
            parsed.append((time, mem, p))
            passes.add(p)

        if len(passes) != 1:
            raise ValueError(f"Inconsistent pass values in {input_path.name}: {passes}")

        pass_val = passes.pop()
        times = [row[0] for row in parsed]
        min_time = min(times)

        # Calculate threshold based on min_time
        if min_time < 1.0:
            threshold = min_time + 0.5
        elif min_time < 3.0:
            threshold = min_time + 1.0
        else:
            threshold = min_time * 1.10  # 10% margin

        # Filter entries
        filtered = [(t, m) for (t, m, _) in parsed if t <= threshold]

        if len(filtered) < 5:
            raise ValueError(f"{input_path.name}: Filtered entries count {len(filtered)} less than 5")
        elif len(filtered) > 10: # Keep the 10 smallest time values
            filtered = sorted(filtered, key=lambda x: x[0])[:10]

        # Average time and memory
        avg_time = sum(t for t, _ in filtered) / len(filtered)
        avg_mem = sum(m for _, m in filtered) / len(filtered)

        # Write output
        output_file = output_path / input_path.name.replace("_raw", "")
        with open(output_file, 'w') as out_f:
            out_f.write(f"{avg_time:.2f},{avg_mem:.2f},{pass_val}\n")

        # print(f"[OK] Processed {input_path.name} -> {output_file.name}")

    except Exception as e:
        print(f"[ERROR] {input_path.name}: {e}")


def main(input_dir, output_dir):
    input_dir = Path(input_dir)
    output_dir = Path(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    for file in input_dir.glob("*raw.txt"):
        process_file(file, output_dir)


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python script.py <input_dir> <output_dir>")
        sys.exit(1)

    main(sys.argv[1], sys.argv[2])

# Usage: python3 scripts/get_real_time_memory_passes/average_raw_data_helper.py results/real/average_concurrent_runs results/real/avg_filtered