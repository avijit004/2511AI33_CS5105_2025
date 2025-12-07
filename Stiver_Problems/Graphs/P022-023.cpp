// P022_023.cpp - Topological ordering of DAG

#include <bits/stdc++.h>
using namespace std;

bool is_valid_order(const vector<int>& order,
                    const vector<pair<int,int>>& edges,
                    const vector<int>& pos) {
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        if (pos[u] > pos[v]) return false;
    }
    return true;
}

// Brute: try all permutations
vector<int> Brute(int V, const vector<pair<int,int>>& edges) {
    vector<int> vertices(V);
    iota(vertices.begin(), vertices.end(), 0);
    sort(vertices.begin(), vertices.end());

    do {
        vector<int> pos(V);
        for (int i = 0; i < V; i++) pos[vertices[i]] = i;
        if (is_valid_order(vertices, edges, pos))
            return vertices;
    } while (next_permutation(vertices.begin(), vertices.end()));

    return {}; // none
}

// Optimal: Kahn's algorithm returns one topological order
vector<int> optimal(int V, const vector<pair<int,int>>& edge) {
    vector<vector<int>> adj(V);
    vector<int> indegree(V, 0);
    for (auto &e : edge) {
        int u = e.first, v = e.second;
        adj[u].push_back(v);
        indegree[v]++;
    }
    queue<int> q;
    for (int i = 0; i < V; i++)
        if (indegree[i] == 0) q.push(i);

    vector<int> res;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        res.push_back(node);
        for (int nei : adj[node]) {
            indegree[nei]--;
            if (indegree[nei] == 0) q.push(nei);
        }
    }
    return res;
}

int main() {
    int V = 4;
    vector<pair<int,int>> edges = {{0,1},{0,2},{1,3},{2,3}};
    auto b = Brute(V, edges);
    auto o = optimal(V, edges);

    cout << "Brute : ";
    for (int x : b) cout << x << " ";
    cout << "\nOptimal: ";
    for (int x : o) cout << x << " ";
    cout << "\n";
    return 0;
}
