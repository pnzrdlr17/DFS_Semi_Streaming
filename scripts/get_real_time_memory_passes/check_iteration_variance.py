import os
import sys
import glob

def check_file_variation(file_path, threshold_percent):
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
        return False  # ignore empty files or all-bad lines

    min_val = min(first_values)
    max_val = max(first_values)

    # Calculate percentage difference
    if min_val == 0:
        return True, -1  # Any positive diff is too much if min is zero
    # percent_diff = (max_val - min_val) / min_val * 100
    avg = sum(first_values) / len(first_values)
    percent_diff = (avg - min_val) / min_val * 100

    return percent_diff > threshold_percent, percent_diff

def main(folder_path, threshold_percent):
    threshold_percent = float(threshold_percent)
    pattern = os.path.join(folder_path, '*raw.txt')
    matching_files = glob.glob(pattern)

    if not matching_files:
        print("No matching files found.")
        return

    print(f"Checking files in '{folder_path}' for variation > {threshold_percent:.2f}%:\n")
    for file_path in matching_files:
        flag, val = check_file_variation(file_path, threshold_percent)
        if flag:
            print(f"Variation too high: {os.path.basename(file_path)} {round(val)}")

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python check_variation.py <folder_path> <threshold_percent>")
        sys.exit(1)

    folder = sys.argv[1]
    percentage = sys.argv[2]
    main(folder, percentage)
