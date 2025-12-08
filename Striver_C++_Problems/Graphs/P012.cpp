// P012.cpp - DFS traversal of undirected graph

#include <bits/stdc++.h>
using namespace std;

vector<int> dfs_traversal(int n, const vector<pair<int,int>>& edges) {
    vector<vector<int>> adj(n);
    for (auto &e : edges) {
        int r = e.first, c = e.second;
        adj[r].push_back(c);
        adj[c].push_back(r);
    }
    vector<bool> visited(n, false);
    vector<int> res;

    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        res.push_back(node);
        for (int nei : adj[node]) {
            if (!visited[nei]) dfs(nei);
        }
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs(i);
    }
    return res;
}

int main() {
    int n = 5;
    vector<pair<int,int>> edges = {{0,1},{0,2},{1,3},{1,4}};

    auto ans = dfs_traversal(n, edges);
    for (int v : ans) cout << v << " ";
    cout << "\n";
    return 0;
}
