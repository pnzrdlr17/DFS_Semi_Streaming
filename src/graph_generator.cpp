#include "graph_generator.h"
#define ll long long int
using namespace std;

extern const string randomGraphsDirectory;

/*SEGTREE*/

Segtree::Segtree(ll n) {
    size = 1;
    while (size < n) size *= 2;
    val.assign(size * 2, 0LL);
}

void Segtree::set(ll i, ll v) {
    set(i, v, 0, 0, size);
}

void Segtree::set(ll i, ll v, ll x, ll lx, ll rx) {
    if (lx == rx - 1) {
        val[x] = v;
        return;
    }
    ll mid = (lx + rx) / 2;
    if (i < mid) set(i, v, 2 * x + 1, lx, mid);
    else set(i, v, 2 * x + 2, mid, rx);
    val[x] = val[2 * x + 1] + val[2 * x + 2];
}

ll Segtree::get(ll l, ll r) {
    return get(l, r, 0, 0, size);
}

ll Segtree::get(ll l, ll r, ll x, ll lx, ll rx) {
    if (rx <= l || r <= lx) return 0;
    if (l <= lx && rx <= r) return val[x];
    ll mid = (lx + rx) / 2;
    return get(l, r, 2 * x + 1, lx, mid) + get(l, r, 2 * x + 2, mid, rx);
}

/*SEGTREE*/

string generate_file_name(ll n, ll m, const string& type, ll seed) {
    stringstream ss;
    ss << "graph_" << n << "_" << m << "_" << type << "_" << seed << ".txt";
    return ss.str();
}

bool file_exists(const string& filePath) {
    /*namespace fs = std::filesystem;
    return fs::exists(filePath);*/

    ifstream file(filePath);
    bool exists = file.good();
    file.close();
    return exists;
}

// TODO: Try segment tree for better performance
// Function to select a node based on preferential attachment (probability proportional to degree)
ll select_node_by_degree(const vector<ll>& values, mt19937& rng) {
    uniform_int_distribution<ll> dist(0, accumulate(values.begin(), values.end(), 0) - 1);  // Choose a random number in the cumulative degree range
    ll random_value = dist(rng);

    ll cumulative_sum = 0;
    for (ll i = 0; i < values.size(); ++i) {
        cumulative_sum += values[i];
        if (random_value < cumulative_sum) {
            return i;
        }
    }

    return -1;  // This should never happen if the degrees are correct
}

// Barabási-Albert Model: Power-Law Graph
void generate_power_law_graph(ll n, ll m, ll seed, string &filePath) {
    mt19937 rng = mt19937(seed);
    uniform_int_distribution<int> dist;

    ofstream fileStream(filePath);

    vector<ll> values(n, 1);
    set<pair<ll, ll>> edge_visited; // Set of edges to avoid duplicate edges

    for (ll i = 0; i < m; i++) {
        // following preferential attachment
        ll node1 = select_node_by_degree(values, rng);  // Select a node based on degree
        ll node2 = select_node_by_degree(values, rng);

        if (node1 != node2 && edge_visited.find({node1, node2}) == edge_visited.end() &&
            edge_visited.find({node2, node1}) == edge_visited.end()) {

            fileStream << node1 + 1 << " " << node2 + 1 << "\n"; // Add the edge

            edge_visited.insert({node1, node2});
            edge_visited.insert({node2, node1});
            values[node1]++;
            values[node2]++;
        }
        else i--;  // try again
    }

    fileStream.close();
}

// Erdős-Rényi Model: Uniform Random Graph
void generate_uniform_graph(ll n, ll m, ll seed, string &filePath) {
    double p = static_cast<double>(3.0 * m) / (n * (n - 1));
    /*using p = (2.0 * m) / (n * (n - 1) may give lesser than m edges, hence increasing it slightly*/
    mt19937 rng = mt19937(seed);
    uniform_real_distribution<double> dist(0.0, 1.0);

    ofstream fileStream(filePath);

    ll edge_count = 0;
    for (ll i = 0; i < n; ++i) {
        for (ll j = i + 1; j < n; ++j) {
            if (dist(rng) < p && edge_count < m) { // Add edges randomly based on probability p
                fileStream << i + 1 << " " << j + 1 << "\n";
                edge_count++;
            }
            if (edge_count >= m) break;
        }
        if (edge_count >= m) break;
    }

    fileStream.close();

    if (edge_count < m) {
        cerr << "Warning: Could not generate the required number of edges\n";
        string newFilePath = generate_file_name(n, edge_count, "UNIFORM", seed);
        if (rename(filePath.c_str(), newFilePath.c_str()) != 0) {
            cerr << "Error renaming file\n";
            exit(1);
        }
        filePath = newFilePath;
    }
}

ll select_node_by_probability(Segtree& st, ll n, mt19937& rng, ll total_weight) {
    uniform_int_distribution<ll> dist(0, total_weight - 1);
    ll random_value = dist(rng);

    ll low = 0, high = n - 1;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (random_value >= st.get(0, mid + 1))
            low = mid;
        else
            high = mid - 1;
    }

    if (st.get(0, high + 1) <= random_value) return high;
    if (st.get(0, low + 1) <= random_value) return low;

    return n - 1;
}

void generate_power_law_graph_old(ll n, ll m, ll seed, string &filePath) {
    mt19937 rng(seed);
    Segtree st(n);

    vector<vector<ll>> graph(n, vector<ll>());
    set<pair<ll, ll>> edge_visited;

    for (ll i = 0; i < n; ++i) {
        st.set(i, 1); // Initialize the segment tree
    }

    ofstream fileStream(filePath);
    ll edge_count = 0, total_weight = st.get(0, n);;

    for (ll i = 0; i < m; ++i) {
        ll node1 = select_node_by_probability(st, n, rng, total_weight);
        ll node2 = select_node_by_probability(st, n, rng, total_weight);

        if (node1 == node2 || edge_visited.count({node1, node2}) != 0) {
            i--; // Retry for this edge
            continue;
        }

        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
        edge_visited.insert({node1, node2});
        edge_visited.insert({node2, node1});

        fileStream << node1 + 1 << " " << node2 + 1 << "\n";
        edge_count++;

        // Update degrees in segment tree : optimized implementation of same logic
        auto update_node = [&](ll node) {
            ll new_degree = graph[node].size();
            ll new_val = (new_degree + 1) * (new_degree + 1) * (new_degree + 1);
            total_weight -= st.get(node, node + 1);
            total_weight += new_val;
            st.set(node, new_val);
        };

        update_node(node1);
        update_node(node2);
    }


    fileStream.close();

    // Handle cases where fewer edges were written than requested
    if (edge_count < m) {
        cerr << "Warning: Could not generate the required number of edges\n";

        // Rename the file to reflect the actual edge count
        string newFilePath = generate_file_name(n, edge_count, "POWERLAW", seed);
        if (rename(filePath.c_str(), newFilePath.c_str()) != 0) {
            cerr << "Error renaming file\n";
            exit(1);
        }
        filePath = newFilePath;
    }
}

void generate_uniform_graph_old(ll n, ll m, ll seed, string &filePath) {
    vector<pair<ll, ll>> edges;
    for (ll i = 1; i <= n; ++i) {
        for (ll j = i + 1; j <= n; ++j) {
            edges.emplace_back(i, j);
        }
    }

    mt19937 rng(seed);
    shuffle(edges.begin(), edges.end(), rng);

    ofstream fileStream(filePath);

    for (ll i = 0; i < m; ++i) {
        fileStream << edges[i].first << " " << edges[i].second << "\n";
    }

    fileStream.close();
}

string generateRandomGraph(ll n, ll m, ll seed_token, string graph_type) {
    if (m > (n * (n - 1)) / 2) {
        cerr << "Invalid number of edges (m), must not be more than n*(n-1)/2\n";
        exit(1);
    }

    string filePath = randomGraphsDirectory + generate_file_name(n, m, graph_type, seed_token);

    if (file_exists(filePath)) {
        return filePath; // Graph already exists no need to generate it again
    }

    if (graph_type == "POWLAW") {
        generate_power_law_graph_old(n, m, seed_token, filePath);
        return filePath;
    }

    if (graph_type == "UNIFORM") {
        generate_uniform_graph_old(n, m, seed_token, filePath);
        return filePath;
    }

    return "Invalid graph generation type";
}