import os
import argparse
import math

# Define the graph datasets
graphs = {
    "small": [
        {"label": "Belcastro", "n": 14022, "m": 9027024},
        {"label": "ArxAP", "n": 18771, "m": 198050},
        {"label": "BrightK", "n": 58228, "m": 214078}
    ],
    "medium": [
        {"label": "Twitch", "n": 168114, "m": 6797557},
        {"label": "Gowalla", "n": 196591, "m": 950327},
        {"label": "Amazon", "n": 334863, "m": 925872}
    ],
    "large": [
        {"label": "RoadnetPA", "n": 1088092, "m": 1541898},
        {"label": "RoadnetCA", "n": 1965206, "m": 2766607},
        {"label": "Orkut", "n": 3072441, "m": 117185083},
        {"label": "LiveJournal", "n": 3997962, "m": 34681189},
        {"label": "KonectDblp", "n": 7577304, "m": 12282059}
    ]
}

# Define the algorithms and heuristics
algorithms = ["kpath", "klev"]
heuristics = ["0", "1", "2", "N"]

# Format n and m values
def format_number(value):
    if value >= 1_000_000:
        return f"{value / 1_000_000:.2f}M" if value < 10_000_000 else f"{value / 1_000_000:.1f}M" if value < 100_000_000 else f"{value / 1_000_000:.0f}M"
    elif value >= 1_000:
        return f"{value / 1_000:.2f}K" if value < 10_000 else f"{value / 1_000:.1f}K" if value < 100_000 else f"{value / 1_000:.0f}K"
    else:
        return str(value)
    
# Function to format cell values
def format_value(value):
    value = float(value)
    if value < 1:
        return f"{value:.2f}"
    elif value < 10:
        return f"{value:.2f}" if value % 1 != 0 else f"{value:.0f}"
    elif value < 100:
        return f"{value:.1f}" if value % 1 != 0 else f"{value:.0f}"
    else:
        return f"{value:.0f}"

def get_value(data, metric):
    if data == "ERROR":
        return "T"
    else:
        data = data.split(",")
        if metric == "time":
            return format_value(data[0])
        elif metric == "memory":
            return format_value(float(data[1]) / 1024)  # Convert KB to MB
        elif metric == "pass":
            return data[2]

def generate_latex_table(group, metric, algo, output_dir):
    if group not in graphs:
        raise ValueError("Invalid group. Choose from 'small', 'medium', or 'large'.")
    if metric not in ["time", "memory", "pass"]:
        raise ValueError("Invalid metric. Choose from 'time', 'memory', or 'pass'.")
    if algo not in algorithms:
        raise ValueError("Invalid algorithm. Choose from 'kpath' or 'klev'.")

    # Create the output directory if it doesn't exist
    os.makedirs(output_dir, exist_ok=True)

    # Initialize the LaTeX content
    latex_content = []
    latex_content.append("\\begin{table}[h!]\n")
    latex_content.append("\\centering\n")
    latex_content.append("\\scalebox{0.75}{\n")
    latex_content.append("\\begin{tabular}{ |p")
    latex_content.append("{1.6cm}" if group == "large" else "{1.3cm}")
    latex_content.append("|p{0.9cm}|p{0.9cm}|p{0.8cm} |p{1.3cm}|p{.8cm}| p{.8cm}|p{.8cm}|p{.8cm}|p{.8cm}|p{.8cm}| p{.8cm}|p{.8cm}|p{.8cm}|p{.8cm}|p{0.8cm}| }\n")
    latex_content.append("\\hline\n")
    latex_content.append("Dataset & $n$ & $m$ & $m/n$ & Heuristic & $k=1$ & $2$ & $3$ & $4$ & $5$ & $6$ & $7$ & $8$ & $9$ & $10$ & $\\left\\lceil m/n\\right\\rceil$\\\\\n")
    latex_content.append("\\hline\n")

    # Initialize reduction storage
    reductions = {k: [] for k in list(range(1, 11)) + ["C"]}

    for graph in graphs[group]:
        label = graph["label"]
        n = format_number(graph["n"])
        m = format_number(graph["m"])
        mn_ratio = graph["m"] / graph["n"]

        latex_content.append(f"\\multirow{{4}}{{*}}{{{label}}} & \\multirow{{4}}{{*}}{{{n}}} & \\multirow{{4}}{{*}}{{{m}}} & \\multirow{{4}}{{*}}{{{mn_ratio:.2f}}}\n")

        for heuristic in heuristics:
            row_label = f"{algo[0]}{algo[1].upper()}{algo[2:]}{heuristic}"

            if (heuristic != "0"):
                latex_content.append("& & &  ")
            
            latex_content.append(f"& \\texttt{{{row_label}}} ")

            for k in range(1, 11):
                file_name = os.path.join("results/real/table_data", f"{label}_{algo}_{heuristic}_{k}.txt")
                if os.path.exists(file_name):
                    with open(file_name, "r") as data_file:
                        data = data_file.readline().strip()
                        latex_content.append(f"& {get_value(data, metric)} ")
                else:
                    latex_content.append("& - ")

            # Handle k=C (m/n)
            file_name = os.path.join("results/real/table_data", f"{label}_{algo}_{heuristic}_C.txt")
            if os.path.exists(file_name):
                with open(file_name, "r") as data_file:
                    data = data_file.readline().strip()
                    latex_content.append(f"& {get_value(data, metric)} \\\\\n")
            else:
                latex_content.append("& - \\\\\n")

        # For pass table add a row for the reduction in passes from heuristic 0 to N
        # if metric == "pass":
        #     latex_content.append("& & &  & Red$\%$ ")
        #     for k in list(range(1, 11)) + ["C"]:
        #         file_name_0 = os.path.join("results/real/table_data", f"{label}_{algo}_0_{k}.txt")
        #         file_name_N = os.path.join("results/real/table_data", f"{label}_{algo}_N_{k}.txt")
        #         if os.path.exists(file_name_0) and os.path.exists(file_name_N):
        #             with open(file_name_0, "r") as data_file_0, open(file_name_N, "r") as data_file_N:
        #                 data_0 = data_file_0.readline().strip().split(",")
        #                 data_N = data_file_N.readline().strip().split(",")
        #                 if data_0[2] != "ERROR" and data_N[2] != "ERROR":
        #                     pass_0 = float(data_0[2])
        #                     pass_N = float(data_N[2])
        #                     if pass_0 != 0:
        #                         reduction = int(((pass_0 - pass_N) / pass_0) * 100)
        #                         reductions[k].append(reduction)
        #                         latex_content.append(f"& {reduction} ")
        #                     else:
        #                         latex_content.append("& - ")
        #                 else:
        #                     latex_content.append("& - ")
        #         else:
        #             latex_content.append("& - ")
        #     latex_content.append("\\\\\n")

        latex_content.append("\\hline\n")

    # if metric == "pass":
    #     latex_content.append("Average  & -  & - & - & - ")
    #     for k in list(range(1, 11)) + ["C"]:
    #         if reductions[k]:
    #             avg_reduction = int(sum(reductions[k]) / len(reductions[k]))
    #             latex_content.append(f"& {avg_reduction} ")
    #         else:
    #             latex_content.append("& - ")
    #     latex_content.append("\\\\\n")
    #     latex_content.append("\\hline\n")

    latex_content.append("\\end{tabular}}\n")
    latex_content.append(f"\\caption{{{metric.capitalize()} comparison for {algo[0]}{algo[1:].capitalize()} algorithm on {group.capitalize()} graphs.}}\n")
    latex_content.append("\\label{label}\n")
    latex_content.append("\\end{table}\n")

    # Write the LaTeX content to the output file
    output_file = os.path.join(output_dir, f"{group}_{metric}_{algo}.tex")
    with open(output_file, "w") as f:
        f.writelines(latex_content)

    print(f"LaTeX table written to {output_file}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate LaTeX table from data files.")
    parser.add_argument("group", help="Group of graphs (small, medium, large)")
    parser.add_argument("metric", help="Metric to display (time, memory, pass)")
    parser.add_argument("algo", help="Algorithm (kpath, klev)")
    parser.add_argument("output_dir", help="Directory to save the LaTeX table")

    args = parser.parse_args()

    generate_latex_table(args.group, args.metric, args.algo, args.output_dir)

# Usage: python gen_latex_allK_groupwise.py small time kpath output/