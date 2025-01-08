#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#define ll long long int
using namespace std;

enum Mode {
    RUN_ALGO,  // Running the algorithm
    GEN_GRAPH,  // Generating a graph
    PREP_EXP, // Preparing for an experiment
    RUN_EXP, // Running an experiment
};

// Declare global variables as extern
extern Mode mode;
extern ll n, m, k, seed_token;
extern int algorithm, experiment_type, sparsity, iterations;
extern char variant;
extern string filePath, graph_type;
extern ifstream fileStream;
extern string modesText;

Mode parseArgs(int argc, char *argv[]);

#endif // PARSER_H