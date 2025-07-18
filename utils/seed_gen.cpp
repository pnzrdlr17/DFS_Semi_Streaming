#include <iostream>
#include <vector>
#include <random>
#include <climits>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <seed_token> <iterations>" << endl;
        cout << "Example: " << argv[0] << " 12345 100" << endl;
        return 1;
    }
    
    long long seed_token = stoll(argv[1]);
    int iterations = stoi(argv[2]);
    
    if (iterations <= 0) {
        cerr << "Error: iterations must be positive" << endl;
        return 1;
    }
    
    // Generate seeds using the same logic as experiment.cpp case 3
    mt19937_64 rng(seed_token);
    uniform_int_distribution<long long> dist(1, LLONG_MAX);
    
    for (int i = 0; i < iterations; ++i) {
        cout << dist(rng) << endl;
    }
    
    return 0;
}
