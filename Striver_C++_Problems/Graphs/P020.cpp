// P020.cpp - Count islands (8-direction) using DFS + DSU

#include <bits/stdc++.h>
using namespace std;

// Brute: DFS on 8 directions
int brute(vector<vector<int>> grid) {
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<bool>> visited(row, vector<bool>(col, false));
    int dirs[8][2] = {
        {1,0},{0,1},{-1,0},{0,-1},
        {1,1},{1,-1},{-1,1},{-1,-1}
    };

    function<void(int,int)> dfs = [&](int r, int c) {
        visited[r][c] = true;
        for (auto &d : dirs) {
            int nr = r + d[0], nc = c + d[1];
            if (0 <= nr && nr < row && 0 <= nc && nc < col &&
                grid[nr][nc] == 1 && !visited[nr][nc]) {
                dfs(nr, nc);
            }
        }
    };

    int c = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                dfs(i, j);
                c++;
            }
        }
    }
    return c;
}

// DSU for optimal
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

int optimal(const vector<vector<int>>& grid) {
    int row = grid.size();
    int col = grid[0].size();
    DSU dsu(row * col);
    int dirs[8][2] = {
        {1,0},{0,1},{-1,0},{0,-1},
        {1,1},{1,-1},{-1,1},{-1,-1}
    };

    auto idx = [col](int r, int c) { return r * col + c; };

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] != 1) continue;
            for (auto &d : dirs) {
                int nr = i + d[0], nc = j + d[1];
                if (0 <= nr && nr < row && 0 <= nc && nc < col &&
                    grid[nr][nc] == 1) {
                    dsu.unite(idx(i,j), idx(nr,nc));
                }
            }
        }
    }

    unordered_set<int> roots;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 1) {
                roots.insert(dsu.find(idx(i,j)));
            }
        }
    }
    return (int)roots.size();
}

int main() {
    vector<vector<int>> grid = {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,1,0},
        {0,0,0,0},
        {1,1,0,1}
    };

    cout << "Brute: "  << brute(grid)   << "\n";
    cout << "Optimal: " << optimal(grid) << "\n";
    return 0;
}
