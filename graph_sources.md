# Larger Graphs

This document lists the sources for larger graph datasets used in this project and not included as part of the repository. It provides instructions for downloading and converting the graphs into the required format.

## Download Links

1. [**Twitch Gamers Social Network**](https://snap.stanford.edu/data/twitch_gamers.html): [Download Link](https://snap.stanford.edu/data/twitch_gamers.zip)
   - Size: ~30MB compressed, ~86MB uncompressed.
   - Nodes: 168,114
   - Edges: 6,797,557
2. [**LiveJournal social network**](https://snap.stanford.edu/data/com-LiveJournal.html): [Download Link](https://snap.stanford.edu/data/bigdata/communities/com-lj.ungraph.txt.gz)
   - Size: ~125MB compressed, ~500MB uncompressed.
   - Nodes: 3,997,962
   - Edges: 34,681,189
3. [**Friendster social network**](https://snap.stanford.edu/data/com-Friendster.html): [Download Link](https://example.com/graph4)
   - Size: ~8.7GB compressed, ~GB uncompressed.
   - Nodes: 65,608,366
   - Edges: 1,806,067,135
4. [**Orkut social network**](https://snap.stanford.edu/data/com-Orkut.html): [Download Link](https://example.com/graph3)
   - Size: ~450MB compressed, ~1.7GB uncompressed.
   - Nodes: 3,072,441
   - Edges: 117,185,083

<!-- 5. [**Agatha_2015 Sybrandt**](https://sparse.tamu.edu/Sybrandt/AGATHA_2015): [Download Link](https://example.com/graph5)
   - Size: ~900MB compressed, ~4.3GB uncompressed.
   - Nodes: 183,964,077
   - Edges: 11,588,725,964 -->

## Conversion Instructions

1. Download the desired graph file(s) from the links above.
2. In the directory named `utils`, you will find a file named `{graph_name}_parser.cpp` for each graph.
3. Necessary information about the graph format and conversion process is provided in the comments at the top of the respective file.
4. Once you have the graph file formatted as edges in each line, use correct path to it when running any algorithm on it.
