// P042.cpp - Find articulation points (cut vertices) in an undirected graph

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute: remove each vertex and test connectivity ----------
void dfs_brute(int u,
               const vector<vector<int>>& adj,
               vector<bool>& visited,
               int removed) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v] && v != removed) {
            dfs_brute(v, adj, visited, removed);
        }
    }
}

vector<int> brute(int V, const vector<vector<int>>& adj) {
    vector<int> result;
    for (int removed = 0; removed < V; removed++) {
        vector<bool> visited(V, false);
        int start = (removed != 0 ? 0 : 1);
        if (start >= V) { // trivial edge case, but keep safe
            result.push_back(removed);
            continue;
        }
        dfs_brute(start, adj, visited, removed);
        int count = 0;
        for (int i = 0; i < V; i++) {
            if (i == removed) continue;
            if (visited[i]) count++;
        }
        if (count < V - 1) {
            result.push_back(removed);
        }
    }
    if (result.empty()) return {-1};
    return result;
}

// ---------- Optimal: Tarjan's articulation point algorithm ----------
void dfs_ap(int node, int parent,
            const vector<vector<int>>& adj,
            vector<int>& tin,
            vector<int>& low,
            vector<bool>& visited,
            int& timer,
            unordered_set<int>& res) {
    visited[node] = true;
    tin[node] = low[node] = timer++;
    int children = 0;

    for (int nei : adj[node]) {
        if (nei == parent) continue;
        if (!visited[nei]) {
            dfs_ap(nei, node, adj, tin, low, visited, timer, res);
            low[node] = min(low[node], low[nei]);
            if (parent != -1 && low[nei] >= tin[node]) {
                res.insert(node);
            }
            children++;
        } else {
            low[node] = min(low[node], tin[nei]);
        }
    }
    if (parent == -1 && children > 1) {
    ...
        res.insert(node);
    }
}

vector<int> optimal(int V, const vector<vector<int>>& adj) {
    vector<int> tin(V, -1), low(V, -1);
    vector<bool> visited(V, false);
    unordered_set<int> res;
    int timer = 0;

    // Python did dfs(0,-1); we generalize to all components
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs_ap(i, -1, adj, tin, low, visited, timer, res);
        }
    }

    vector<int> ans(res.begin(), res.end());
    sort(ans.begin(), ans.end());
    if (ans.empty()) return {-1};
    return ans;
}

int main() {
    int V = 5;
    vector<vector<int>> adj = {
        {1, 2},
        {0, 2},
        {0, 1, 3, 4},
        {2, 4},
        {2, 3}
    };

    auto b = brute(V, adj);
    auto o = optimal(V, adj);

    cout << "Brute: ";
    for (int x : b) cout << x << " ";
    cout << "\nOptimal: ";
    for (int x : o) cout << x << " ";
    cout << "\n";
    return 0;
}
