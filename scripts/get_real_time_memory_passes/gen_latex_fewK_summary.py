import os
import argparse
import math

# Define the graph datasets
graphs = {
    "small": [
        # {"label": "CU", "n": 49, "m": 107},
        # {"label": "AJazz", "n": 198, "m": 2742},
        # {"label": "HM", "n": 2426, "m": 16631},
        {"label": "Belcastro", "n": 14022, "m": 9027024},
        {"label": "ArxAP", "n": 18771, "m": 198050},
        # {"label": "AsCaida", "n": 26475, "m": 53381},
        {"label": "BrightK", "n": 58228, "m": 214078}
    ],
    "medium": [
        # {"label": "LMocha", "n": 104103, "m": 2193083},
        # {"label": "FlickrE", "n": 105938, "m": 2316948},
        # {"label": "WordNet", "n": 146005, "m": 656999},
        # {"label": "Douban", "n": 154908, "m": 327162},
        {"label": "Twitch", "n": 168114, "m": 6797557},
        {"label": "Gowalla", "n": 196591, "m": 950327},
        # {"label": "Dblp", "n": 317080, "m": 1049866},
        {"label": "Amazon", "n": 334863, "m": 925872}
    ],
    "large": [
        # {"label": "RoadnetPA", "n": 1088092, "m": 1541898},
        # {"label": "Youtube", "n": 1134890, "m": 2987624},
        # {"label": "Skitter", "n": 1696415, "m": 11095298},
        # {"label": "RoadnetCA", "n": 1965206, "m": 2766607},
        {"label": "Orkut", "n": 3072441, "m": 117185083},
        {"label": "LiveJournal", "n": 3997962, "m": 34681189},
        {"label": "KonectDblp", "n": 7577304, "m": 12282059},
        # {"label": "Friendster", "n": 65608366, "m": 1806067135}
    ]
}

# Define the algorithms and heuristics
algorithms = ["kpath", "klev"]
heuristics = ["0", "1", "2", "N"]
k_values = ["1", "2", "5", "10", "C"]

results_dir = "results/real/avg_filtered"

# Format n and m values
def format_number(value):
    if value >= 1_000_000:
        return f"{value / 1_000_000:.2f}M" if value < 10_000_000 else f"{value / 1_000_000:.1f}M" if value < 100_000_000 else f"{value / 1_000_000:.0f}M"
    elif value >= 1_000:
        return f"{value / 1_000:.2f}K" if value < 10_000 else f"{value / 1_000:.1f}K" if value < 100_000 else f"{value / 1_000:.0f}K"
    else:
        return str(value)
    
def get_formatted_value(data, metric):
    if data == "ERROR":
        return "T"
    else:
        data = data.split(",")
    
    if metric == "time":
        value = float(data[0])
        if value >= 3600:
            return f"{value / 3600:.2f}h" if value < 36000 else f"{value / 3600:.1f}h" if value < 360000 else f"{value / 3600:.0f}h"
        elif value >= 60:
            return f"{value / 60:.2f}m" if value < 600 else f"{value / 60:.1f}m" if value < 6000 else f"{value / 60:.0f}m"
        else:
            return f"{value:.2f}s" if value < 10 else f"{value:.1f}s" if value < 100 else f"{value:.0f}s"
    elif metric == "memory":
        value = float(data[1])
        if value >= 1_048_576:  # 1024 * 1024
            return f"{value / 1_048_576:.2f}G" if value < 10_485_760 else f"{value / 1_048_576:.1f}G" if value < 104_857_600 else f"{value / 1_048_576:.0f}G"
        elif value >= 1024:
            return f"{value / 1024:.2f}M" if value < 10_240 else f"{value / 1024:.1f}M" if value < 102_400 else f"{value / 1024:.0f}M"
        else:
            return f"{value:.2f}K" if value < 10 else f"{value:.1f}K" if value < 100 else f"{value:.0f}K"
    elif metric == "pass":
        return data[2]

def generate_latex_table(group, metric, output_dir):
    if group not in graphs:
        raise ValueError("Invalid group. Choose from 'small', 'medium', or 'large'.")
    if metric not in ["time", "memory", "pass"]:
        raise ValueError("Invalid metric. Choose from 'time', 'memory', or 'pass'.")

    # Create the output directory if it doesn't exist
    output_dir = os.path.join(output_dir, group, metric)
    os.makedirs(output_dir, exist_ok=True)

    # Initialize the LaTeX content
    latex_content = []
    latex_content.append("\\begin{table}[h!]\n")
    latex_content.append("\\centering\n")
    latex_content.append("\\scalebox{0.75}{\n")
    latex_content.append("\\begin{tabular}{ |p")
    latex_content.append("{1.6cm}" if group == "large" else "{1.3cm}")
    latex_content.append("|p{0.9cm}|p{0.9cm}|p{0.8cm} |p{1.3cm}|p{.8cm}| p{.8cm}|p{.8cm}|p{.8cm}|p{.8cm}|p{.8cm}| p{.8cm}|p{.8cm}|p{.8cm}|p{.8cm}| }\n")
    latex_content.append("\\hline\n")
    latex_content.append("\\multirow{2}{*}{Dataset} & \\multirow{2}{*}{$n$} & \\multirow{2}{*}{$m$} & \\multirow{2}{*}{$m/n$} & Algorithm & \\multicolumn{5}{c|}{\\texttt{kPath}} & \\multicolumn{5}{c|}{\\texttt{kLev}} \\\\\n")
    latex_content.append("\\cline{5-15}\n")
    latex_content.append("& & & & k & $1$ & $2$ & $5$ & $10$ & $\\left\\lceil m/n\\right\\rceil$ & $1$ & $2$ & $5$ & $10$ & $\\left\\lceil m/n\\right\\rceil$\\\\\n")

    latex_content.append("\\hline\n")

    # Initialize reduction storage
    reductions = {(algo, k): [] for algo in algorithms for k in k_values}

    for graph in graphs[group]:
        label = graph["label"]
        n = format_number(graph["n"])
        m = format_number(graph["m"])
        mn_ratio = graph["m"] / graph["n"]

        latex_content.append(f"\\multirow{{4}}{{*}}{{{label}}} & \\multirow{{4}}{{*}}{{{n}}} & \\multirow{{4}}{{*}}{{{m}}} & \\multirow{{4}}{{*}}{{{mn_ratio:.2f}}}\n")

        for heuristic in heuristics:
            row_label = f"Variant{heuristic}"

            if (heuristic != "0"):
                latex_content.append("& & &  ")
            
            latex_content.append(f"& \\texttt{{{row_label}}} ")

            for algo in algorithms:
                for k in k_values:
                    file_name = os.path.join(results_dir, f"{label}_{algo}_{heuristic}_{k}.txt")
                    if os.path.exists(file_name):
                        with open(file_name, "r") as data_file:
                            data = data_file.readline().strip()
                            latex_content.append(f"& {get_formatted_value(data, metric)} ")
                    else:
                        latex_content.append("& - ")

            latex_content.append("\\\\\n")

            # For pass table add a row for the reduction in passes from heuristic 0 to N
        if metric == "pass":
            latex_content.append("& & &  & Red$\%$ ")
            for algo in algorithms:
                for k in k_values:
                    file_name_0 = os.path.join(results_dir, f"{label}_{algo}_0_{k}.txt")
                    file_name_N = os.path.join(results_dir, f"{label}_{algo}_N_{k}.txt")
                    if os.path.exists(file_name_0) and os.path.exists(file_name_N):
                        with open(file_name_0, "r") as data_file_0, open(file_name_N, "r") as data_file_N:
                            data_0 = data_file_0.readline().strip()
                            data_N = data_file_N.readline().strip()
                            if data_0 == "ERROR" or data_N == "ERROR":
                                latex_content.append("& - ")
                            else:
                                pass_0 = int(data_0.split(",")[2])
                                pass_N = int(data_N.split(",")[2])
                                if pass_0 == 0:
                                    latex_content.append("& - ")
                                else:
                                    reduction = int(((pass_0 - pass_N) / pass_0) * 100)
                                    reductions[(algo, k)].append(reduction)
                                    latex_content.append(f"& {reduction} ")
                    else:
                        latex_content.append("& - ")
            latex_content.append("\\\\\n")

        latex_content.append("\\hline\n")
    
    if metric == "pass":
        latex_content.append("Average  & -  & - & - & - ")
        for algo in algorithms:
            for k in k_values:
                if reductions[(algo, k)]:
                    avg_reduction = int(sum(reductions[(algo, k)]) / len(reductions[(algo, k)]))
                    latex_content.append(f"& {avg_reduction} ")
                else:
                    latex_content.append("& - ")
        latex_content.append("\\\\\n")
        latex_content.append("\\hline\n")

    latex_content.append("\\end{tabular}}\n")
    latex_content.append(f"\\caption{{{metric.capitalize()} comparison for kPath and kLev algorithms on {group.capitalize()} graphs.}}\n")
    latex_content.append("\\label{label}\n")
    latex_content.append("\\end{table}\n")

    # Write the LaTeX content to the output file
    output_file = os.path.join(output_dir, f"Summary_{group}_{metric}_kPath_kLev.tex")
    with open(output_file, "w") as f:
        f.writelines(latex_content)

    print(f"LaTeX table written to {output_file}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate LaTeX table from data files.")
    parser.add_argument("group", help="Group of graphs (small, medium, large)")
    parser.add_argument("metric", help="Metric to display (time, memory, pass)")
    parser.add_argument("output_dir", help="Directory to save the LaTeX table")

    args = parser.parse_args()

    generate_latex_table(args.group, args.metric, args.output_dir)

# Usage: python3 scripts/get_real_time_memory_passes/gen_latex_fewK_summary.py large memory scripts/latex_outputs
