# Parallel Graph Generator

This script generates random graphs in parallel for the DFS Semi-Streaming experiments.

## Features

- **Extracts n,m values** from VARN, VARM, and VARK experiment configurations
- **Deterministic seed generation** using the seed token file
- **Parallel processing** with up to 30 processes (configurable)
- **Multiple experiment types** support
- **Progress tracking** and error handling

## Usage

```bash
python3 parallel_graph_generator.py [OPTIONS]
```

## Options

- `-e, --experiment`: Experiment type (`VARN`, `VARM`, `VARK`, `ALL`) [default: ALL]
- `-s, --sparsity`: Sparsity value (0-4) [default: 2]
- `-g, --graph-type`: Graph type (`UNIFORM`, `POWLAW`) [default: UNIFORM]
- `-i, --iterations`: Number of iterations (different seeds) per (n,m) pair [default: 10]
- `-p, --processes`: Maximum number of parallel processes [default: 30]
- `-sf, --seed-file`: Path to seed token file [default: ../../seed_1000x_token_1729.txt]

## Examples

```bash
# Generate graphs for all experiments with 10 iterations each
python3 parallel_graph_generator.py

# Generate only VARN graphs with different sparsity
python3 parallel_graph_generator.py -e VARN -s 3 -i 5

# Generate POWLAW graphs with more processes
python3 parallel_graph_generator.py -g POWLAW -p 50

# Generate graphs for VARM experiment only
python3 parallel_graph_generator.py -e VARM -i 20
```

## What it does

1. **Reads seed tokens** from the specified seed file
2. **Generates (n,m) pairs** based on the experiment type:
   - **VARN**: Varies n from 10 to 10,000 with calculated m based on sparsity
   - **VARM**: Fixed n=10,000 with varying m from 1,000 to 49,995,000
   - **VARK**: Fixed n=10,000 with calculated m based on sparsity
   - **ALL**: Combines all above experiments
3. **Generates graphs** using the main binary with GEN_GRAPH mode
4. **Processes in parallel** for maximum efficiency

## Generated Files

Files are generated in `../../input/random_graphs/` with the naming convention:
```
graph_{n}_{m}_{graph_type}_{seed}.txt
```

## Performance

- Uses up to 30 parallel processes by default
- Generates 2 graphs in ~3 seconds (depends on graph size)
- Handles timeouts and errors gracefully
- Progress tracking with success/failure counts

## Dependencies

- Python 3.6+
- Built main binary (`../../bin/main`)
- Seed token file (`../../seed_1000x_token_1729.txt`)

## Notes

- The script uses the same deterministic seed generation logic as `experiment.cpp`
- Seeds are read from the token file to ensure reproducible results
- Generated graphs are compatible with the experiment framework
- Error handling includes timeouts and validation
