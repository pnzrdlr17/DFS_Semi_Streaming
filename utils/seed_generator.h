#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

#include <vector>
#include <iostream>

/**
 * Generates a deterministic sequence of random seeds based on an initial seed token.
 * This uses the same logic as case 3 (FIXNM) in experiment.cpp
 * 
 * @param seed_token The initial seed value
 * @param iterations Number of seeds to generate
 * @return Vector of generated seeds
 */
std::vector<long long> generateSeedSequence(long long seed_token, int iterations);

/**
 * Generates a single seed at a specific position in the sequence.
 * This is useful when you only need one specific seed without generating the entire sequence.
 * 
 * @param seed_token The initial seed value
 * @param position The position in the sequence (0-based)
 * @return The seed at the specified position
 */
long long generateSeedAtPosition(long long seed_token, int position);

/**
 * Prints a sequence of seeds to stdout for debugging/verification purposes.
 * 
 * @param seed_token The initial seed value
 * @param iterations Number of seeds to generate and print
 */
void printSeedSequence(long long seed_token, int iterations);

#endif // SEED_GENERATOR_H
