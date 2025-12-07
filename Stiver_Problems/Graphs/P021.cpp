// P021.cpp - Detect cycle in directed graph

#include <bits/stdc++.h>
using namespace std;

// Brute: DFS with recursion stack
bool dfsUtil(int node, const vector<vector<int>>& adj,
             vector<bool>& visited, vector<bool>& inStack) {
    visited[node] = true;
    inStack[node] = true;
    for (int nei : adj[node]) {
        if (!visited[nei]) {
            if (dfsUtil(nei, adj, visited, inStack)) return true;
        } else if (inStack[nei]) {
            return true;
        }
    }
    inStack[node] = false;
    return false;
}

bool brute(int V, const vector<pair<int,int>>& edge) {
    vector<vector<int>> adj(V);
    for (auto &e : edge) {
        adj[e.first].push_back(e.second);
    }
    vector<bool> visited(V, false), inStack(V, false);
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfsUtil(i, adj, visited, inStack)) return true;
        }
    }
    return false;
}

// Optimal: Kahn's algorithm; if topo sort doesn't include all nodes => cycle
bool optimal(int V, const vector<pair<int,int>>& edge) {
    vector<vector<int>> adj(V);
    vector<int> indegree(V, 0);
    for (auto &e : edge) {
        adj[e.first].push_back(e.second);
        indegree[e.second]++;
    }
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    int count = 0;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        count++;
        for (int nei : adj[node]) {
            indegree[nei]--;
            if (indegree[nei] == 0) q.push(nei);
        }
    }
    return count != V;
}

int main() {
    int V = 4;
    vector<pair<int,int>> edges = {{0,1},{1,2},{2,0},{2,3}};
    cout << "Brute: "   << (brute(V, edges)   ? "True" : "False") << "\n";
    cout << "Optimal: " << (optimal(V, edges) ? "True" : "False") << "\n";
    return 0;
}
