import os
import sys
import glob

def check_file_avg_variation(file_path, threshold_percent):
    first_values = []

    with open(file_path, 'r') as f:
        for line in f:
            if line.strip():
                parts = line.strip().split(',')
                try:
                    first_values.append(float(parts[0]))
                except (ValueError, IndexError):
                    continue  # skip malformed lines

    if not first_values:
        return False, -2, -2  # ignore empty or malformed files

    min_val = min(first_values)
    max_val = max(first_values)

    if max_val < 2:
        return False, -2, -2

    threshold_limit = max(min_val + 1, min_val * 1.10)  # 10% above min
    filtered_values = [v for v in first_values if v <= threshold_limit]

    if not filtered_values:
        return True, -1, 0  # if all values were > 10% above min, treat as exceeded

    avg_val = sum(filtered_values) / len(filtered_values)

    percent_diff = (avg_val - min_val) / min_val * 100

    return percent_diff > threshold_percent, percent_diff, len(filtered_values)

def main(folder_path, threshold_percent):
    threshold_percent = float(threshold_percent)
    pattern = os.path.join(folder_path, '*raw.txt')
    matching_files = glob.glob(pattern)

    if not matching_files:
        print("No matching files found.")
        return

    print(f"Checking files in '{folder_path}' for avg-min variation > {threshold_percent:.2f}%:\n")
    for file_path in matching_files:
        flag, val, itr = check_file_avg_variation(file_path, threshold_percent)
        if flag or (itr < 5 and itr >= 0):
            print(f"{os.path.basename(file_path)}   {val}   Iterations {itr}")

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python check_variation.py <folder_path> <threshold_percent>")
        sys.exit(1)

    folder = sys.argv[1]
    percentage = sys.argv[2]
    main(folder, percentage)
