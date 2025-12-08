// P040.cpp - Max area of island after flipping at most one 0

#include <bits/stdc++.h>
using namespace std;

int dr4b[4] = {0,1,-1,0};
int dc4b[4] = {1,0,0,-1};

// Brute: try flipping every 0, DFS over whole grid each time
int brute(vector<vector<int>> grid) {
    int row = grid.size();
    int col = grid[0].size();
    int max_area = 0;

    function<void(int,int,vector<vector<bool>>&,int&)> dfs =
        [&](int r, int c, vector<vector<bool>>& visited, int &cnt) {
            visited[r][c] = true;
            cnt++;
            for (int k = 0; k < 4; k++) {
                int nr = r + dr4b[k], nc = c + dc4b[k];
                if (0 <= nr && nr < row && 0 <= nc && nc < col &&
                    grid[nr][nc] == 1 && !visited[nr][nc]) {
                    dfs(nr, nc, visited, cnt);
                }
            }
        };

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 0) {
                grid[i][j] = 1;
                vector<vector<bool>> visited(row, vector<bool>(col, false));
                int local_max = 0;
                for (int r = 0; r < row; r++) {
                    for (int c = 0; c < col; c++) {
                        if (grid[r][c] == 1 && !visited[r][c]) {
                            int cnt = 0;
                            dfs(r, c, visited, cnt);
                            local_max = max(local_max, cnt);
                        }
                    }
                }
                max_area = max(max_area, local_max);
                grid[i][j] = 0;
            }
        }
    }
    if (max_area == 0) return row * col;
    return max_area;
}

// DSU for optimal solution
struct DSU2 {
    vector<int> parent, size;
    DSU2(int V) : parent(V), size(V,1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        if (size[px] >= size[py]) {
            parent[py] = px;
            size[px] += size[py];
        } else {
            parent[px] = py;
            size[py] += size[px];
        }
    }
};

int optimal(const vector<vector<int>>& grid) {
    int row = grid.size();
    int col = grid[0].size();
    DSU2 dsu(row * col);

    auto idx = [col](int r, int c) { return r * col + c; };

    // union all adjacent 1's
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 1) {
                for (int k = 0; k < 4; k++) {
                    int nr = i + dr4b[k], nc = j + dc4b[k];
                    if (0 <= nr && nr < row && 0 <= nc && nc < col &&
                        grid[nr][nc] == 1) {
                        dsu.unite(idx(i,j), idx(nr,nc));
                    }
                }
            }
        }
    }

    int max_area = 0;
    // consider flipping each 0
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 0) {
                int area = 1;
                unordered_set<int> seen;
                for (int k = 0; k < 4; k++) {
                    int nr = i + dr4b[k], nc = j + dc4b[k];
                    if (0 <= nr && nr < row && 0 <= nc && nc < col &&
                        grid[nr][nc] == 1) {
                        int root = dsu.find(idx(nr,nc));
                        if (!seen.count(root)) {
                            area += dsu.size[root];
                            seen.insert(root);
                        }
                    }
                }
                max_area = max(max_area, area);
            }
        }
    }

    if (max_area == 0) {
        // either all 1s or all 0s
        return row * col;
    }
    return max_area;
}

int main() {
    vector<vector<int>> grid = {
        {1, 0, 1, 1},
        {1, 0, 0, 1},
        {0, 1, 1, 0},
        {1, 0, 1, 1}
    };

    cout << "Brute Force: " << brute(grid) << "\n";
    cout << "Optimal: " << optimal(grid) << "\n";
    return 0;
}
