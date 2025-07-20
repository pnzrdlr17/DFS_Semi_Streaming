#!/usr/bin/env python3
import os, sys, re

def check_file(f):
    n, m = map(int, re.findall(r'graph_(\d+)_(\d+)_', f)[0])
    lines = open(f'input/random_graphs/{f}').readlines()
    if len(lines) != m: return False
    for line in lines:
        u, v = map(int, line.split())
        if not (1 <= u <= n and 1 <= v <= n): return False
    return True

action = sys.argv[1] if len(sys.argv) > 1 else 'report'
files = [f for f in os.listdir('input/random_graphs') if f.startswith('graph_')]
bad_files = [f for f in files if not check_file(f)]

print(f"Found {len(bad_files)} invalid files out of {len(files)}")
for f in bad_files: 
    print(f"INVALID: {f}")
    if action == 'remove': os.remove(f'input/random_graphs/{f}')

if action == 'remove' and bad_files:
    print(f"Removed {len(bad_files)} invalid files")
