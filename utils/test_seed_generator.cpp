#include "seed_generator.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long seed_token = 12345;
    int iterations = 5;
    
    cout << "Testing seed generator with seed_token = " << seed_token << " and iterations = " << iterations << endl;
    cout << "=========================================" << endl;
    
    // Test 1: Generate full sequence
    cout << "Test 1: Full sequence generation" << endl;
    vector<long long> seeds = generateSeedSequence(seed_token, iterations);
    for (int i = 0; i < iterations; ++i) {
        cout << "seeds[" << i << "] = " << seeds[i] << endl;
    }
    cout << endl;
    
    // Test 2: Generate individual seeds at specific positions
    cout << "Test 2: Individual seed generation" << endl;
    for (int i = 0; i < iterations; ++i) {
        long long seed_at_pos = generateSeedAtPosition(seed_token, i);
        cout << "seed at position " << i << " = " << seed_at_pos << endl;
    }
    cout << endl;
    
    // Test 3: Verify deterministic behavior
    cout << "Test 3: Deterministic behavior verification" << endl;
    vector<long long> seeds2 = generateSeedSequence(seed_token, iterations);
    bool deterministic = true;
    for (int i = 0; i < iterations; ++i) {
        if (seeds[i] != seeds2[i]) {
            deterministic = false;
            break;
        }
    }
    cout << "Deterministic: " << (deterministic ? "YES" : "NO") << endl;
    cout << endl;
    
    // Test 4: Different seed_token produces different sequence
    cout << "Test 4: Different seed_token test" << endl;
    long long different_token = 67890;
    vector<long long> different_seeds = generateSeedSequence(different_token, iterations);
    cout << "Seeds with token " << different_token << ":" << endl;
    for (int i = 0; i < iterations; ++i) {
        cout << "seeds[" << i << "] = " << different_seeds[i] << endl;
    }
    
    return 0;
}
