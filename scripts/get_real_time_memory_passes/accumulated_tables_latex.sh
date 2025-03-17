#!/bin/bash

# Set variables
groups=("small" "medium" "large")
metrics=("pass" "memory" "time")
algorithms=("kpath" "klev")

# Function to generate LaTeX tables
generate_latex_tables() {
    local group=$1
    local metric=$2
    local algo=$3
    local output_dir=$4
    
    python3 gen_latex_allK_groupwise.py "$group" "$metric" "$algo" "$output_dir"
}

# Parse command-line arguments
if [ $# -eq 0 ]; then
    echo "Usage: $0 {summary|extended}"
    exit 1
fi

mode=$1

# Main loop
output_file="scripts/latex_outputs/accumulated_output/${mode}.tex"

# Ensure the output file and directories exist
if [ -f "$output_file" ]; then
    > "$output_file"  # Clear the file if it exists
else
    mkdir -p "$(dirname "$output_file")"  # Create the directory if it doesn't exist
    touch "$output_file"  # Create the file
fi

if [ "$mode" = "summary" ]; then
    for group in "${groups[@]}"; do
        group_label=$(echo "$group" | awk '{print toupper($0)}')
        echo "%========================${group_label} GRAPHS KPATH-KLEV :: BEGIN========================" >> ${output_file}
        echo "" >> ${output_file}
        for metric in "${metrics[@]}"; do
                python3 scripts/get_real_time_memory_passes/gen_latex_fewK_summary.py "$group" "$metric" scripts/latex_outputs
                cat scripts/latex_outputs/${group}/${metric}/Summary_${group}_${metric}_kPath_kLev.tex >> ${output_file}
                echo "" >> ${output_file}
        done
        echo "%========================${group_label} GRAPHS KPATH-KLEV :: END========================" >> ${output_file}
        echo "" >> ${output_file}
        echo "" >> ${output_file}
    done
elif [ "$mode" = "extended" ]; then
    for group in "${groups[@]}"; do
        for algo in "${algorithms[@]}"; do
            group_label=$(echo "$group" | awk '{print toupper($0)}')
            algo_label=$(echo "$algo" | awk '{print toupper($0)}')
            echo "%========================${group_label} GRAPHS ${algo_label} :: BEGIN========================" >> ${output_file}
            echo "" >> ${output_file}
                for metric in "${metrics[@]}"; do
                    python3 scripts/get_real_time_memory_passes/gen_latex_allK_groupwise.py "$group" "$metric" "$algo" scripts/latex_outputs
                    cat scripts/latex_outputs/${group}/${metric}/${group}_${metric}_${algo}.tex >> ${output_file}
                    echo "" >> ${output_file}
                done
            echo "%========================${group_label} GRAPHS ${algo_label} :: END========================" >> ${output_file}
            echo "" >> ${output_file}
            echo "" >> ${output_file}
        done
    done
else
    echo "Invalid mode: $mode. Use 'summary' or 'extended'."
    exit 1
fi

echo "All outputs accumulated in ${output_file}."
