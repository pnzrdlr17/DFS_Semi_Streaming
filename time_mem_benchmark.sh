#!/bin/bash

iterations=${1:-1} # Number of iterations per input
timestamp=$(date +"%Y%m%d_%H%M%S")
output_file="output/benchmarks/benchmark_time_memory_$timestamp.csv"

# Initialize the CSV file with headers
echo "input,K,run,user_time,max_mem_kb,program_output" > $output_file

inputs=(
    # "CU 49 107 ./input/CU/download.tsv.contiguous-usa/contiguous-usa/out.contiguous-usa"
    # "AJazz 198 2742 ./input/AJazz/download.tsv.arenas-jazz/arenas-jazz/out.arenas-jazz"
    # "HM 2426 16631 ./input/HM/download.tsv.petster-hamster/petster-hamster/out.petster-hamster"
    # "ArxAP 18771 198050 ./input/ArxAP/download.tsv.ca-AstroPh/ca-AstroPh/out.ca-AstroPh"
    # "AsCaida 26475 53381 ./input/AsCaida/download.tsv.as-caida20071105/as-caida20071105"
    # "BrightK 58228 214078 ./input/BrightK/download.tsv.loc-brightkite_edges/loc-brightkite_edges/out.loc-brightkite_edges"
    # "LMocha 104103 2193083 ./input/LMocha/download.tsv.livemocha/livemocha/out.livemocha"
    "FlickrE 105938 2316948 ./input/FlickrE/download.tsv.flickrEdges/flickrEdges/out.flickrEdges"
    # "WordNet 146005 656999 ./input/WordNet/download.tsv.wordnet-words/wordnet-words/out.wordnet-words"
    # "Douban 154908 327162 ./input/Douban/download.tsv.douban/douban/out.douban"
    # "Gowalla 196591 950327 ./input/Gowalla/download.tsv.loc-gowalla_edges/loc-gowalla_edges/out.loc-gowalla_edges"
    # "Dblp 317080 1049866 ./input/Dblp/download.tsv.com-dblp/com-dblp/out.com-dblp"
    # "Amazon 334863 925872 ./input/Amazon/download.tsv.com-amazon/com-amazon/out.com-amazon"
)

# The heuristic variants are the 7th parameter in the main_REAL function which can be {0, 1, 2, N, X}

# Loop through each input
for input_data in "${inputs[@]}"; do
    # Parse the input values (Label, N, M, and INPUT_PATH)
    label=$(echo "$input_data" | awk '{print $1}')
    N=$(echo "$input_data" | awk '{print $2}')
    M=$(echo "$input_data" | awk '{print $3}')
    INPUT_PATH=$(echo "$input_data" | awk '{print $4}')

    # Iterate over all the variants (0, 1, 2, N, X) for kLev and kPath
    for variant in 0 1 2 N X; do
        # Display the variant for clarity
        echo "Variant $variant:"
        echo "Variant $variant:" >> $output_file

        # Run the command for varying values of K (1 to 10)
        for K in {1..10}; do
            # Execute the command multiple times for each K
            for i in $(seq 1 $iterations); do
                # Display the current progress in the terminal
                echo "Running $label - N=$N, M=$M, K=$K - Iteration $i/$iterations..."

                # Construct and execute the command
                result=$(gtime -f "%U,%M" ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 2 0 "$K" "$variant" 2>&1) # 2 for KPath
                # result=$(gtime -f "%U,%M" ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 3 0 "$K" 2>&1) # 3 for KLev with all the heuristice i.e. kLevN

                # Split the result into program output and time/memory usage
                program_output=$(echo "$result" | head -n -1) # All lines except the last contain program output
                user_time_mem=$(echo "$result" | tail -1)    # Last line contains time/memory from gtime

                # Save the results in the CSV
                echo "$label,$K,$i,$user_time_mem,\"$program_output\"" >> $output_file
            done
        done

        echo "" >> $output_file # Add an empty line after each variant
    done
done

echo "Benchmarking complete. Results saved in $output_file."