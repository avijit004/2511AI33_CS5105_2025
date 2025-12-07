// P011.cpp - Remove stones (max stones removed)

#include <bits/stdc++.h>
using namespace std;

// Brute: build graph of stones sharing row/col, count connected components
int brute(const vector<pair<int,int>>& stones) {
    int n = stones.size();
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (stones[i].first == stones[j].first ||
                stones[i].second == stones[j].second) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    vector<bool> visited(n, false);
    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        for (int nei : adj[node]) {
            if (!visited[nei]) dfs(nei);
        }
    };

    int comp = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            comp++;
        }
    }
    return n - comp;
}

// DSU for optimal solution
struct DSU {
    vector<int> parent, rankv;
    DSU(int n) : parent(n), rankv(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    void unite(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;
        if (rankv[pu] > rankv[pv]) parent[pv] = pu;
        else if (rankv[pv] > rankv[pu]) parent[pu] = pv;
        else {
            parent[pu] = pv;
            rankv[pv]++;
        }
    }
};

// Optimal: DSU on rows + columns
int optimal(const vector<pair<int,int>>& stones) {
    int n = stones.size();
    int maxRow = 0, maxCol = 0;
    for (auto &p : stones) {
        maxRow = max(maxRow, p.first);
        maxCol = max(maxCol, p.second);
    }
    int offset = maxRow + 1;
    DSU dsu(maxRow + maxCol + 2);

    for (auto &p : stones) {
        int r = p.first;
        int c = p.second + offset;
        dsu.unite(r, c);
    }

    unordered_set<int> roots;
    for (auto &p : stones) {
        roots.insert(dsu.find(p.first));
    }
    int C = (int)roots.size();
    return n - C;
}

int main() {
    vector<pair<int,int>> stones = {
        {0,0},{0,1},{1,0},{1,2},{2,2},{2,3}
    };
    cout << "Brute Force: " << brute(stones) << "\n";
    cout << "Optimal DSU: " << optimal(stones) << "\n";
    return 0;
}
