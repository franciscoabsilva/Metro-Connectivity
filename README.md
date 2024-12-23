# Metro Connectivity
Second Project for Analysis and Synthesis of Algorithms

## Introduction
This project focuses on developing an algorithm to analyze the connectivity of a metro network, modeled as an undirected multigraph. The goal is to calculate the metro connectivity index `mc = max{ML(e1, e2) | e1, e2 ∈ Metro}`, which represents the maximum number of line changes required to travel between any two stations in the network. The algorithm handles scenarios involving multiple lines, disconnected stations, and different levels of complexity, providing efficient and correct results. The output indicates the metro connectivity index or specific cases such as no required line changes or disconnected stations.

## Input & Output
The input file should be a `.txt` file that contain the following:

- The first line contains three integers `stationsCount`, `connectionsCount` and `linesCount`, representing the number of stations, connections and metro lines.
- The other lines contain each three integers: `id1` and `id2` are the indices of two stations and `idLine` is the index of the line connecting the two stations `id1` and `id2`.
  
The output will be printed to stdout and will contain the follow:

- If no line changes are required between any two stations, output `0`.
- If there exist at least two stations that are not connected, output `-1`.
- Otherwise, the maximum number of line changes between any two stations.

### Example:
```bash
7 8 3
3 2 1
2 7 1
7 5 1
2 6 2
6 4 2
4 1 2
4 1 3
1 5 3
```
The output should be:
```bash
1
```
## Compilation and Execution

To compile and run the program, use the following commands:
```bash
g++ -std=c++11 -O3 -Wall file.cpp -lm
./a.out < filename.txt
```

