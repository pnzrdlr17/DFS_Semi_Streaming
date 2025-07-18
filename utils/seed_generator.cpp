#include "seed_generator.h"
#include <random>
#include <vector>
#include <climits>

using namespace std;

/**
 * Generates a deterministic sequence of random seeds based on an initial seed token.
 * This uses the same logic as case 3 (FIXNM) in experiment.cpp
 * 
 * @param seed_token The initial seed value
 * @param iterations Number of seeds to generate
 * @return Vector of generated seeds
 */
vector<long long> generateSeedSequence(long long seed_token, int iterations) {
    vector<long long> seeds(iterations);
    mt19937_64 rng(seed_token);
    uniform_int_distribution<long long> dist(1, LLONG_MAX);
    
    for (int i = 0; i < iterations; ++i) {
        seeds[i] = dist(rng);
    }
    
    return seeds;
}

/**
 * Generates a single seed at a specific position in the sequence.
 * This is useful when you only need one specific seed without generating the entire sequence.
 * 
 * @param seed_token The initial seed value
 * @param position The position in the sequence (0-based)
 * @return The seed at the specified position
 */
long long generateSeedAtPosition(long long seed_token, int position) {
    mt19937_64 rng(seed_token);
    uniform_int_distribution<long long> dist(1, LLONG_MAX);
    
    long long result = 0;
    for (int i = 0; i <= position; ++i) {
        result = dist(rng);
    }
    
    return result;
}

/**
 * Prints a sequence of seeds to stdout for debugging/verification purposes.
 * 
 * @param seed_token The initial seed value
 * @param iterations Number of seeds to generate and print
 */
void printSeedSequence(long long seed_token, int iterations) {
    vector<long long> seeds = generateSeedSequence(seed_token, iterations);
    
    cout << "Seed sequence for token " << seed_token << " with " << iterations << " iterations:" << endl;
    for (int i = 0; i < iterations; ++i) {
        cout << "seeds[" << i << "] = " << seeds[i] << endl;
    }
}
