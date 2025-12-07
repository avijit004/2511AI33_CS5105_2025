// P039.cpp - Number of islands after each operation (brute + DSU)

#include <bits/stdc++.h>
using namespace std;

// Brute: rebuild visited + DFS for each op
int dr4[4] = {0,1,-1,0};
int dc4[4] = {1,0,0,-1};

void dfs_brute(int r, int c,
               vector<vector<int>>& matrix,
               vector<vector<bool>>& visited,
               int n, int m) {
    visited[r][c] = true;
    for (int k = 0; k < 4; k++) {
        int nr = r + dr4[k], nc = c + dc4[k];
        if (0 <= nr && nr < n && 0 <= nc && nc < m &&
            matrix[nr][nc] == 1 && !visited[nr][nc]) {
            dfs_brute(nr, nc, matrix, visited, n, m);
        }
    }
}

vector<int> brute(int n, int m, int k, const vector<pair<int,int>>& arr) {
    vector<vector<int>> matrix(n, vector<int>(m, 0));
    vector<int> res;
    for (auto [r, c] : arr) {
        int count = 0;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        matrix[r][c] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && matrix[i][j] == 1) {
                    dfs_brute(i, j, matrix, visited, n, m);
                    count++;
                }
            }
        }
        res.push_back(count);
    }
    return res;
}

// DSU for optimal
struct DSU {
    vector<int> parent, rankv;
    DSU(int V) : parent(V), rankv(V,1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        if (rankv[px] > rankv[py]) {
            parent[py] = px;
        } else if (rankv[py] > rankv[px]) {
            parent[px] = py;
        } else {
            parent[py] = px;
            rankv[px]++;
        }
    }
};

vector<int> optimal(int n, int m, int k, const vector<pair<int,int>>& arr) {
    DSU dsu(n * m);
    vector<vector<int>> matrix(n, vector<int>(m, 0));
    vector<int> res;
    int count = 0;

    auto idx = [m](int r, int c) { return r * m + c; };

    for (auto [r, c] : arr) {
        if (matrix[r][c] == 1) { // if duplicate op, just push current count
            res.push_back(count);
            continue;
        }
        matrix[r][c] = 1;
        count++;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr4[k], nc = c + dc4[k];
            if (0 <= nr && nr < n && 0 <= nc && nc < m &&
                matrix[nr][nc] == 1) {
                int a = idx(r,c), b = idx(nr,nc);
                int pa = dsu.find(a), pb = dsu.find(b);
                if (pa != pb) {
                    dsu.unite(pa, pb);
                    count--;
                }
            }
        }
        res.push_back(count);
    }
    return res;
}

int main() {
    int n = 3, m = 3, k = 5;
    vector<pair<int,int>> ops = {{0,0},{0,1},{1,2},{2,1},{1,1}};

    auto b = brute(n,m,k,ops);
    auto o = optimal(n,m,k,ops);

    cout << "Brute:  ";
    for (int v : b) cout << v << " ";
    cout << "\nOptimal: ";
    for (int v : o) cout << v << " ";
    cout << "\n";
    return 0;
}
