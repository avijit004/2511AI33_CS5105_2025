// P014_015.cpp - Undirected cycle detection (multiple methods)

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute: for each edge, remove it and check connectivity u->v ----------
bool has_path_without_edge(int V,
                           const vector<vector<int>>& adj,
                           int u, int v,
                           pair<int,int> banned) {
    queue<int> q;
    vector<bool> visited(V, false);
    q.push(u);
    visited[u] = true;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        if (node == v) return true;
        for (int nei : adj[node]) {
            if ((node == banned.first && nei == banned.second) ||
                (node == banned.second && nei == banned.first))
                continue;
            if (!visited[nei]) {
                visited[nei] = true;
                q.push(nei);
            }
        }
    }
    return false;
}

bool brute(int V, const vector<pair<int,int>>& edges) {
    vector<vector<int>> adj(V);
    for (auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    for (auto &e : edges) {
        if (has_path_without_edge(V, adj, e.first, e.second, e))
            return true;
    }
    return false;
}

// ---------- DSU ----------
struct DSU {
    vector<int> parent, rankv;
    DSU(int V) : parent(V), rankv(V,1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    bool unite(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return false;
        if (rankv[pu] > rankv[pv]) {
            parent[pv] = pu;
        } else if (rankv[pv] > rankv[pu]) {
            parent[pu] = pv;
        } else {
            parent[pu] = pv;
            rankv[pv]++;
        }
        return true;
    }
};

bool optimal(int V, const vector<pair<int,int>>& edges) {
    DSU dsu(V);
    for (auto &e : edges) {
        if (!dsu.unite(e.first, e.second)) {
            return true; // cycle found
        }
    }
    return false;
}

// ---------- BFS cycle detection ----------
bool bfs_cycle(int V, const vector<pair<int,int>>& edges) {
    vector<vector<int>> adj(V);
    for (auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }

    vector<bool> visited(V, false);
    for (int start = 0; start < V; start++) {
        if (visited[start]) continue;
        queue<pair<int,int>> q;
        visited[start] = true;
        q.push({start, -1});
        while (!q.empty()) {
            auto [node, parent] = q.front(); q.pop();
            for (int nei : adj[node]) {
                if (!visited[nei]) {
                    visited[nei] = true;
                    q.push({nei, node});
                } else if (nei != parent) {
                    return true;
                }
            }
        }
    }
    return false;
}

// ---------- DFS cycle detection ----------
bool dfs_cycle_util(int node, int parent,
                    const vector<vector<int>>& adj,
                    vector<bool>& visited) {
    visited[node] = true;
    for (int nei : adj[node]) {
        if (!visited[nei]) {
            if (dfs_cycle_util(nei, node, adj, visited)) return true;
        } else if (nei != parent) {
            return true;
        }
    }
    return false;
}

bool dfs_cycle(int V, const vector<pair<int,int>>& edges) {
    vector<vector<int>> adj(V);
    for (auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs_cycle_util(i, -1, adj, visited)) return true;
        }
    }
    return false;
}

int main() {
    int V = 5;
    vector<pair<int,int>> edges = {
        {0,1},{1,2},{2,3},{3,4},{4,1}
    };

    cout << "Brute Force: " << (brute(V, edges) ? "True" : "False") << "\n";
    cout << "Optimal : "    << (optimal(V, edges) ? "True" : "False") << "\n";
    cout << "By BFS: "      << (bfs_cycle(V, edges) ? "True" : "False") << "\n";
    cout << "By DFS: "      << (dfs_cycle(V, edges) ? "True" : "False") << "\n";
    return 0;
}
