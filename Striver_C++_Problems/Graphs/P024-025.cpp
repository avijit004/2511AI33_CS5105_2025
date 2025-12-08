// P024_025.cpp - Check if all tasks can be finished

#include <bits/stdc++.h>
using namespace std;

bool is_valid_order2(const vector<int>& order,
                     const vector<pair<int,int>>& edges,
                     const vector<int>& pos) {
    for (auto &e : edges) {
        int u = e.first;
        int v = e.second;
        // in Python: if pos[v] > pos[u]: return False
        // so requirement is pos[v] <= pos[u]
        if (pos[v] > pos[u]) return false;
    }
    return true;
}

// Brute: try all permutations, return True if any respects constraints
bool Brute(int N, int P, const vector<pair<int,int>>& array) {
    vector<int> vertices(N);
    iota(vertices.begin(), vertices.end(), 0);
    sort(vertices.begin(), vertices.end());

    do {
        vector<int> pos(N);
        for (int i = 0; i < N; i++) pos[vertices[i]] = i;
        if (is_valid_order2(vertices, array, pos)) return true;
    } while (next_permutation(vertices.begin(), vertices.end()));

    return false;
}

// Optimal: Kahn, using the same graph they used (edge v->u)
bool optimal(int N, int P, const vector<pair<int,int>>& array) {
    vector<vector<int>> adj(N);
    vector<int> indegree(N, 0);
    for (auto &e : array) {
        int u = e.first, v = e.second;
        adj[v].push_back(u);
        indegree[u]++;
    }
    queue<int> q;
    for (int i = 0; i < N; i++)
        if (indegree[i] == 0) q.push(i);

    int count = 0;
    vector<int> res;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        count++;
        res.push_back(node);
        for (int nei : adj[node]) {
            indegree[nei]--;
            if (indegree[nei] == 0) q.push(nei);
        }
    }
    return count == N;
}

int main() {
    int N = 4;
    int P = 3;
    vector<pair<int,int>> array = {{1,0},{2,1},{3,2}};

    cout << "Brute: "  << (Brute(N, P, array) ? "True" : "False") << "\n";
    cout << "Optimal: " << (optimal(N, P, array) ? "True" : "False") << "\n";
    return 0;
}
