#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <filesystem>
#include <sstream>

// Optimized version with faster parsing and I/O
bool check_file(const std::string& filename) {
    // Extract n and m from filename using regex (cached)
    static std::regex pattern(R"(graph_(\d+)_(\d+)_)");
    std::smatch matches;
    
    if (!std::regex_search(filename, matches, pattern)) {
        return false;
    }
    
    int n = std::stoi(matches[1].str());
    int m = std::stoi(matches[2].str());
    
    // Open file with larger buffer for better I/O performance
    std::ifstream file("input/random_graphs/" + filename);
    if (!file.is_open()) {
        return false;
    }
    
    // Reserve buffer for better performance
    file.sync_with_stdio(false);
    
    std::string line;
    line.reserve(32); // Most lines are short
    
    int line_count = 0;
    int u, v;
    
    while (std::getline(file, line)) {
        line_count++;
        
        // Faster parsing using find instead of stringstream
        size_t space_pos = line.find(' ');
        if (space_pos == std::string::npos) {
            return false;
        }
        
        try {
            u = std::stoi(line.substr(0, space_pos));
            v = std::stoi(line.substr(space_pos + 1));
        } catch (const std::exception&) {
            return false;
        }
        
        if (u < 1 || u > n || v < 1 || v > n) {
            return false;
        }
    }
    
    return line_count == m;
}

int main(int argc, char* argv[]) {
    // Optimize iostream
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string action = (argc > 1) ? argv[1] : "report";
    
    std::vector<std::string> files;
    std::vector<std::string> bad_files;
    
    // Reserve space to avoid reallocations
    files.reserve(1000);
    bad_files.reserve(100);
    
    // List all files that start with "graph_"
    try {
        for (const auto& entry : std::filesystem::directory_iterator("input/random_graphs")) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (filename.size() >= 6 && filename.substr(0, 6) == "graph_") {
                    files.push_back(std::move(filename));
                }
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
        return 1;
    }
    
    // Check each file
    for (const std::string& file : files) {
        if (!check_file(file)) {
            bad_files.push_back(file);
        }
    }
    
    std::cout << "Found " << bad_files.size() << " invalid files out of " << files.size() << '\n';
    
    for (const std::string& file : bad_files) {
        std::cout << "INVALID: " << file << '\n';
        if (action == "remove") {
            try {
                std::filesystem::remove("input/random_graphs/" + file);
            } catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Error removing file " << file << ": " << e.what() << std::endl;
            }
        }
    }
    
    if (action == "remove" && !bad_files.empty()) {
        std::cout << "Removed " << bad_files.size() << " invalid files\n";
    }
    
    return 0;
}

// Usage :: nohup ./scripts/random_scripts/validate_graphs > scripts/random_scripts/validate_graphs_aug_10.log  2>&1 < /dev/null &
