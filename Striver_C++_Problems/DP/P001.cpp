// P001.cpp - BFS traversal from a start node

#include <bits/stdc++.h>
using namespace std;

vector<int> BruteForce(int V, const unordered_map<int, vector<int>>& adj, int start) {
    vector<int> res;
    queue<int> q;
    q.push(start);
    vector<bool> visited(V + 1, false);
    visited[start] = true;

    while (!q.empty()) {
        int levelsize = q.size();
        for (int _ = 0; _ < levelsize; _++) {
            int node = q.front(); q.pop();
            res.push_back(node);
            auto it = adj.find(node);
            if (it != adj.end()) {
                for (int child : it->second) {
                    if (!visited[child]) {
                        visited[child] = true;
                        q.push(child);
                    }
                }
            }
        }
    }
    return res;
}

vector<int> OptimalApproach(int V, const unordered_map<int, vector<int>>& adj, int start) {
    vector<int> res;
    queue<int> q;
    q.push(start);
    vector<bool> visited(V + 1, false);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front(); q.pop();
        res.push_back(node);
        auto it = adj.find(node);
        if (it != adj.end()) {
            for (int child : it->second) {
                if (!visited[child]) {
                    visited[child] = true;
                    q.push(child);
                }
            }
        }
    }
    return res;
}

int main() {
    unordered_map<int, vector<int>> adj = {
        {1, {2,5}},
        {2, {1,5,3}},
        {3, {2,4,5}},
        {4, {3,5}},
        {5, {1,2,4}}
    };
    int V = 5;
    int start = 1;

    auto b = BruteForce(V, adj, start);
    auto o = OptimalApproach(V, adj, start);

    cout << "By Brute Force: ";
    for (int x : b) cout << x << " ";
    cout << "\nOptimal Approach: ";
    for (int x : o) cout << x << " ";
    cout << "\n";
    return 0;
}
