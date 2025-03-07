import csv
import os
import argparse

def read_csv_and_write_to_files(csv_file_path, output_dir, graph_label, algo, variant):
    # Ensure the output directory exists
    os.makedirs(output_dir, exist_ok=True)

    # Read the CSV file
    with open(csv_file_path, mode='r') as csvfile:
        csvreader = csv.reader(csvfile)
        header = next(csvreader)  # Skip the header row

        for row in csvreader:
            # Extract the relevant data from the CSV row
            k = row[0]
            time = row[1]
            memory = row[2]
            passes = row[3]

            # Create the file name
            file_name = f"{graph_label}_{algo}_{variant}_{k}"
            file_path = os.path.join(output_dir, file_name)

            # Write the data to the file
            with open(file_path, mode='a') as file:
                file.write(f"{time},{memory},{passes}\n")

    print(f"Data written to files in {output_dir}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Read CSV and write data to corresponding files.")
    parser.add_argument("csv_file_path", help="Path to the input CSV file")
    parser.add_argument("output_dir", help="Directory where the output files are located")
    parser.add_argument("graph_label", help="Label of the graph")
    parser.add_argument("algo", help="Algorithm used (e.g., klev, kpath)")
    parser.add_argument("variant", help="Variant of the algorithm (e.g., 0, 1, 2, N)")

    args = parser.parse_args()

    read_csv_and_write_to_files(args.csv_file_path, args.output_dir, args.graph_label, args.algo, args.variant)