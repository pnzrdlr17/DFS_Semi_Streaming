import os
import csv

# Hardcoded data for verification
hardcoded_data = {
    'CU': {
        'kpath': {
            '0': {1: 5, 2: 4, 3: 3, 4: 2, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
            '1': {1: 6, 2: 5, 3: 2, 4: 2, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            '2': {1: 5, 2: 2, 3: 2, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 3, 2: 2, 3: 2, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        },
        'klev': {
            '0': {1: 3, 2: 3, 3: 3, 4: 3, 5: 3, 6: 3, 7: 3, 8: 3, 9: 3, 10: 3},
            '1': {1: 3, 2: 3, 3: 3, 4: 3, 5: 3, 6: 3, 7: 3, 8: 3, 9: 3, 10: 2},
            '2': {1: 2, 2: 2, 3: 1, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 1, 2: 1, 3: 1, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        }
    },
    'AJazz': {
        'kpath': {
            '0': {1: 19, 2: 16, 3: 10, 4: 7, 5: 5, 6: 5, 7: 4, 8: 3, 9: 3, 10: 3},
            '1': {1: 21, 2: 16, 3: 9, 4: 7, 5: 5, 6: 4, 7: 3, 8: 3, 9: 2, 10: 2},
            '2': {1: 17, 2: 10, 3: 7, 4: 5, 5: 4, 6: 3, 7: 3, 8: 2, 9: 2, 10: 2},
            'N': {1: 5, 2: 4, 3: 3, 4: 3, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
        },
        'klev': {
            '0': {1: 3, 2: 3, 3: 3, 4: 3, 5: 3, 6: 3, 7: 3, 8: 3, 9: 3, 10: 3},
            '1': {1: 2, 2: 2, 3: 2, 4: 2, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
            '2': {1: 2, 2: 2, 3: 2, 4: 2, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
            'N': {1: 2, 2: 2, 3: 2, 4: 2, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
        }
    },
    'HM': {
        'kpath': {
            '0': {1: 47, 2: 13, 3: 8, 4: 5, 5: 5, 6: 4, 7: 4, 8: 4, 9: 3, 10: 2},
            '1': {1: 43, 2: 14, 3: 7, 4: 4, 5: 4, 6: 3, 7: 3, 8: 3, 9: 1, 10: 1},
            '2': {1: 33, 2: 8, 3: 4, 4: 3, 5: 3, 6: 3, 7: 3, 8: 1, 9: 1, 10: 1},
            'N': {1: 4, 2: 3, 3: 3, 4: 2, 5: 2, 6: 2, 7: 2, 8: 1, 9: 1, 10: 1},
        },
        'klev': {
            '0': {1: 4, 2: 4, 3: 4, 4: 4, 5: 4, 6: 4, 7: 4, 8: 4, 9: 4, 10: 4},
            '1': {1: 4, 2: 4, 3: 4, 4: 4, 5: 4, 6: 4, 7: 4, 8: 4, 9: 4, 10: 4},
            '2': {1: 3, 2: 3, 3: 3, 4: 2, 5: 2, 6: 2, 7: 2, 8: 1, 9: 1, 10: 1},
            'N': {1: 3, 2: 3, 3: 2, 4: 2, 5: 2, 6: 2, 7: 1, 8: 1, 9: 1, 10: 1},
        }
    },
    'ArxAP': {
        'kpath': {
            '0': {1: 231, 2: 33, 3: 17, 4: 12, 5: 10, 6: 6, 7: 7, 8: 3, 9: 3, 10: 3},
            '1': {1: 221, 2: 35, 3: 19, 4: 12, 5: 9, 6: 4, 7: 6, 8: 3, 9: 3, 10: 2},
            '2': {1: 190, 2: 19, 3: 13, 4: 8, 5: 4, 6: 8, 7: 3, 8: 3, 9: 2, 10: 2},
            'N': {1: 5, 2: 4, 3: 3, 4: 3, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
        },
        'klev': {
            '0': {1: 5, 2: 5, 3: 5, 4: 5, 5: 5, 6: 5, 7: 5, 8: 5, 9: 5, 10: 5},
            '1': {1: 4, 2: 4, 3: 4, 4: 4, 5: 4, 6: 4, 7: 4, 8: 4, 9: 4, 10: 4},
            '2': {1: 4, 2: 4, 3: 3, 4: 3, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
            'N': {1: 4, 2: 4, 3: 3, 4: 3, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
        }
    },
    'AsCaida': {
        'kpath': {
            '0': {1: 43, 2: 8, 3: 3, 4: 2, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
            '1': {1: 38, 2: 9, 3: 2, 4: 2, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            '2': {1: 37, 2: 2, 3: 2, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 3, 2: 2, 3: 2, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        },
        'klev': {
            '0': {1: 4, 2: 4, 3: 4, 4: 4, 5: 4, 6: 4, 7: 4, 8: 4, 9: 4, 10: 4},
            '1': {1: 4, 2: 4, 3: 4, 4: 4, 5: 4, 6: 4, 7: 4, 8: 4, 9: 4, 10: 4},
            '2': {1: 2, 2: 2, 3: 1, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 2, 2: 1, 3: 1, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        }
    },
    'BrightK': {
        'kpath': {
            '0': {1: 242, 2: 14, 3: 6, 4: 4, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
            '1': {1: 231, 2: 13, 3: 4, 4: 3, 5: 2, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            '2': {1: 195, 2: 4, 3: 3, 4: 2, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 3, 2: 2, 3: 2, 4: 2, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        },
        'klev': {
            '0': {1: 5, 2: 5, 3: 5, 4: 5, 5: 5, 6: 5, 7: 5, 8: 5, 9: 5, 10: 5},
            '1': {1: 4, 2: 4, 3: 4, 4: 4, 5: 4, 6: 4, 7: 4, 8: 4, 9: 4, 10: 4},
            '2': {1: 3, 2: 2, 3: 2, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 3, 2: 2, 3: 1, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        }
    },
    'LMocha': {
        'kpath': {
            '0': {1: 850, 2: 22, 3: 9, 4: 7, 5: 6, 6: 5, 7: 4, 8: 4, 9: 4, 10: 3},
            '1': {1: 853, 2: 22, 3: 9, 4: 6, 5: 5, 6: 4, 7: 4, 8: 3, 9: 3, 10: 3},
            '2': {1: 692, 2: 10, 3: 6, 4: 5, 5: 4, 6: 4, 7: 3, 8: 3, 9: 3, 10: 2},
            'N': {1: 6, 2: 4, 3: 3, 4: 3, 5: 3, 6: 3, 7: 2, 8: 2, 9: 2, 10: 2},
        },
        'klev': {
            '0': {1: 4, 2: 4, 3: 4, 4: 4, 5: 4, 6: 4, 7: 4, 8: 4, 9: 4, 10: 4},
            '1': {1: 3, 2: 3, 3: 3, 4: 3, 5: 3, 6: 3, 7: 3, 8: 3, 9: 3, 10: 3},
            '2': {1: 3, 2: 3, 3: 3, 4: 3, 5: 3, 6: 3, 7: 3, 8: 2, 9: 2, 10: 2},
            'N': {1: 3, 2: 3, 3: 3, 4: 3, 5: 3, 6: 3, 7: 2, 8: 2, 9: 2, 10: 2},
        }
    },
    'FlickrE': {
        'kpath': {
            '0': {1: 737, 2: 43, 3: 18, 4: 10, 5: 7, 6: 6, 7: 5, 8: 5, 9: 4, 10: 4},
            '1': {1: 831, 2: 35, 3: 15, 4: 11, 5: 6, 6: 5, 7: 4, 8: 5, 9: 3, 10: 3},
            '2': {1: 571, 2: 23, 3: 12, 4: 9, 5: 5, 6: 6, 7: 4, 8: 11, 9: 3, 10: 3},
            'N': {1: 5, 2: 4, 3: 4, 4: 4, 5: 3, 6: 3, 7: 3, 8: 2, 9: 2, 10: 2},
        },
        'klev': {
            '0': {1: 5, 2: 5, 3: 5, 4: 5, 5: 5, 6: 5, 7: 5, 8: 5, 9: 5, 10: 5},
            '1': {1: 4, 2: 4, 3: 4, 4: 4, 5: 4, 6: 4, 7: 4, 8: 4, 9: 4, 10: 4},
            '2': {1: 4, 2: 3, 3: 4, 4: 3, 5: 3, 6: 3, 7: 3, 8: 3, 9: 3, 10: 3},
            'N': {1: 4, 2: 4, 3: 4, 4: 3, 5: 3, 6: 3, 7: 3, 8: 3, 9: 3, 10: 3},
        }
    },
    'WordNet': {
        'kpath': {
            '0': {1: 303, 2: 66, 3: 19, 4: 5, 5: 4, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
            '1': {1: 294, 2: 67, 3: 18, 4: 4, 5: 3, 6: 3, 7: 1, 8: 1, 9: 1, 10: 1},
            '2': {1: 229, 2: 26, 3: 4, 4: 3, 5: 3, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 4, 2: 3, 3: 3, 4: 2, 5: 2, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        },
        'klev': {
            '0': {1: 6, 2: 6, 3: 6, 4: 6, 5: 6, 6: 6, 7: 6, 8: 6, 9: 6, 10: 6},
            '1': {1: 5, 2: 5, 3: 5, 4: 5, 5: 5, 6: 5, 7: 5, 8: 5, 9: 6, 10: 5},
            '2': {1: 4, 2: 3, 3: 2, 4: 2, 5: 2, 6: 2, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 4, 2: 3, 3: 2, 4: 2, 5: 2, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        }
    },
    'Douban': {
        'kpath': {
            '0': {1: 284, 2: 7, 3: 3, 4: 2, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
            '1': {1: 278, 2: 7, 3: 2, 4: 2, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            '2': {1: 214, 2: 2, 3: 2, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 3, 2: 2, 3: 2, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        },
        'klev': {
            '0': {1: 4, 2: 4, 3: 4, 4: 4, 5: 4, 6: 4, 7: 4, 8: 4, 9: 4, 10: 4},
            '1': {1: 3, 2: 3, 3: 3, 4: 3, 5: 3, 6: 3, 7: 3, 8: 3, 9: 3, 10: 3},
            '2': {1: 2, 2: 2, 3: 1, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 2, 2: 1, 3: 1, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        }
    },
    'Gowalla': {
        'kpath': {
            '0': {1: 617, 2: 32, 3: 6, 4: 4, 5: 6, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
            '1': {1: 603, 2: 28, 3: 6, 4: 5, 5: 2, 6: 2, 7: 1, 8: 1, 9: 1, 10: 1},
            '2': {1: 475, 2: 7, 3: 5, 4: 2, 5: 2, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 4, 2: 2, 3: 2, 4: 2, 5: 2, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        },
        'klev': {
            '0': {1: 6, 2: 6, 3: 6, 4: 6, 5: 6, 6: 6, 7: 6, 8: 6, 9: 6, 10: 6},
            '1': {1: 5, 2: 5, 3: 5, 4: 5, 5: 5, 6: 5, 7: 5, 8: 5, 9: 5, 10: 5},
            '2': {1: 4, 2: 3, 3: 2, 4: 2, 5: 2, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 4, 2: 2, 3: 2, 4: 2, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        }
    },
    'Dblp': {
        'kpath': {
            '0': {1: 471, 2: 43, 3: 13, 4: 9, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
            '1': {1: 453, 2: 47, 3: 14, 4: 6, 5: 5, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            '2': {1: 369, 2: 11, 3: 6, 4: 5, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 4, 2: 3, 3: 3, 4: 3, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        },
        'klev': {
            '0': {1: 6, 2: 6, 3: 6, 4: 6, 5: 6, 6: 6, 7: 6, 8: 6, 9: 6, 10: 6},
            '1': {1: 4, 2: 4, 3: 4, 4: 4, 5: 4, 6: 4, 7: 4, 8: 5, 9: 5, 10: 5},
            '2': {1: 3, 2: 2, 3: 2, 4: 2, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 3, 2: 2, 3: 2, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        }
    },
    'Amazon': {
        'kpath': {
            '0': {1: 309, 2: 107, 3: 8, 4: 2, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2},
            '1': {1: 322, 2: 100, 3: 7, 4: 4, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            '2': {1: 246, 2: 7, 3: 4, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 4, 2: 3, 3: 2, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        },
        'klev': {
            '0': {1: 6, 2: 6, 3: 6, 4: 6, 5: 6, 6: 6, 7: 6, 8: 6, 9: 6, 10: 6},
            '1': {1: 5, 2: 5, 3: 5, 4: 5, 5: 5, 6: 5, 7: 5, 8: 5, 9: 5, 10: 5},
            '2': {1: 3, 2: 2, 3: 2, 4: 2, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
            'N': {1: 3, 2: 2, 3: 2, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1},
        }
    }
}

graph_runs = {
    'CU': {
        'kPathRun': '20250116_210345',
        'kLevRun': '20250115_103649',
    },
    'AJazz': {
        'kPathRun': '20250116_210346',
        'kLevRun': '20250115_103649',
    },
    'HM': {
        'kPathRun': '20250116_210347',
        'kLevRun': '20250115_103651',
    },
    'ArxAP': {
        'kPathRun': '20250116_210351',
        'kLevRun': '20250115_103704',
    },
    'AsCaida': {
        'kPathRun': '20250116_210635',
        'kLevRun': '20250115_103905',
    },
    'BrightK': {
        'kPathRun': '20250116_210957',
        'kLevRun': '20250115_103908',
    },
    'LMocha': {
        'kPathRun': '20250116_211408',
        'kLevRun': '20250115_104215',
    },
    'FlickrE': {
        'kPathRun': '20250116_222732',
        'kLevRun': '20250115_110049',
    },
    'WordNet': {
        'kPathRun': '20250116_233806',
        'kLevRun': '20250115_112654',
    },
    'Douban': {
        'kPathRun': '20250116_235808',
        'kLevRun': '20250115_124239',
    },
    'Gowalla': {
        'kPathRun': '20250117_002520',
        'kLevRun': '20250115_124544',
    },
    'Dblp': {
        'kPathRun': '20250117_011000',
        'kLevRun': '20250115_134811',
    },
    'Amazon': {
        'kPathRun': '20250117_121240',
        'kLevRun': '20250116_190606',
    }
}

# Function to verify the data
def verify_real_data():
    base_dir = './results/real/time_memory'
    discrepancies = []
    missing_data = []

    for graph, algos in hardcoded_data.items():
        if graph not in graph_runs:
            missing_data.append(f"Graph info for {graph} not found")
            continue

        graph_run_info = graph_runs[graph]
        for algo, variants in algos.items():
            for variant, k_values in variants.items():
                # Determine the run directory based on the algorithm
                run_dir = graph_run_info['kPathRun'] if algo == 'kpath' else graph_run_info['kLevRun']
                variant_dir = os.path.join(base_dir, graph, f'run_{run_dir}', f'{algo}_{variant}')
                if not os.path.exists(variant_dir):
                    missing_data.append(variant_dir)
                    continue

                aggregate_file = os.path.join(variant_dir, 'aggregate_results.csv')
                if not os.path.exists(aggregate_file):
                    missing_data.append(aggregate_file)
                    continue

                with open(aggregate_file, 'r') as csvfile:
                    csvreader = csv.reader(csvfile)
                    next(csvreader)  # Skip header
                    for row in csvreader:
                        k = int(row[0])
                        actual_passes = int(row[3])
                        if k in k_values:
                            expected_passes = k_values[k]
                            if actual_passes != expected_passes:
                                discrepancies.append((aggregate_file, run_dir, graph, algo, variant, k, expected_passes, actual_passes))

    if discrepancies:
        print("Discrepancies found:")
        for file_path, run_dir, graph, algo, variant, k, expected, actual in discrepancies:
            # print(f"File: {file_path}, K: {k}, Expected Passes: {expected}, Actual Passes: {actual}")
            print (f"Run: {run_dir}--{graph}--{algo}_{variant}, K={k}, Expected Passes: {expected}, Actual Passes: {actual}")
    else:
        print("No discrepancies found.")

    if missing_data:
        print("\nMissing data:")
        for file_path in missing_data:
            print(f"Missing file: {file_path}")
    else:
        print("No missing data.")

def read_aggregate_data(file_path):
    data = {}
    if not os.path.exists(file_path):
        return data

    with open(file_path, 'r') as csvfile:
        csvreader = csv.reader(csvfile)
        next(csvreader)  # Skip header
        for row in csvreader:
            k = int(row[0])
            user_time = float(row[1])
            memory = float(row[2])
            passes = int(row[3])
            data[k] = {'user_time': user_time, 'memory': memory, 'passes': passes}
    return data

def calculate_similarity(data1, data2):
    keys = set(data1.keys()).intersection(set(data2.keys()))
    if not keys:
        return 0

    match_count = 0
    for k in keys:
        if data1[k]['passes'] == data2[k]['passes']:
            match_count += 1
    return match_count

def determine_closest_variant(base_dir, graph, algo, variant):
    known_variants = ['0', '1', '2', 'N']
    run_dir = graph_runs[graph]['kPathRun' if algo == 'kpath' else 'kLevRun']
    unknown_variant_dir = os.path.join(base_dir, graph, f'run_{run_dir}', f'{algo}_{variant}', 'aggregate_results.csv')
    unknown_data = read_aggregate_data(unknown_variant_dir)

    if not unknown_data:
        print(f"Missing data for {graph} {algo}_{variant}")
        return None

    similarities = {}
    for known_variant in known_variants:
        known_variant_dir = os.path.join(base_dir, graph, f'run_{run_dir}', f'{algo}_{known_variant}', 'aggregate_results.csv')
        known_data = read_aggregate_data(known_variant_dir)
        if not known_data:
            continue
        similarity = calculate_similarity(unknown_data, known_data)
        similarities[known_variant] = similarity

    closest_variant = max(similarities, key=similarities.get)
    return closest_variant

def determine_unknown_variants():
    base_dir = './results/real/time_memory'
    graphs = ['CU', 'AJazz', 'HM', 'ArxAP', 'AsCaida', 'BrightK', 'LMocha', 'FlickrE', 'WordNet', 'Douban', 'Gowalla', 'Dblp', 'Amazon']
    algos = ['kpath', 'klev']
    unknown_variants = ['Y']

    for graph in graphs:
        for algo in algos:
            for variant in unknown_variants:
                if variant == 'Y' and algo != 'klev':
                    continue
                closest_variant = determine_closest_variant(base_dir, graph, algo, variant)
                if closest_variant:
                    print(f"The closest known variant to {graph} {algo}_{variant} is {closest_variant}")

# verify_real_data()

# determine_unknown_variants()