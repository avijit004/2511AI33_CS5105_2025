// P016.cpp - Surrounded regions ("O" inside captured)

#include <bits/stdc++.h>
using namespace std;

// Brute: DFS for each 'O', only flip if the region doesn't touch border
vector<vector<char>> brute(vector<vector<char>> grid) {
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<bool>> visited(row, vector<bool>(col, false));

    function<bool(int,int,vector<pair<int,int>>&)> dfs =
        [&](int r, int c, vector<pair<int,int>>& cells) -> bool {
            visited[r][c] = true;
            bool touch_border = (r == 0 || c == 0 || r == row-1 || c == col-1);
            cells.push_back({r, c});
            static int dr[4] = {0,1,-1,0};
            static int dc[4] = {1,0,0,-1};
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (0 <= nr && nr < row && 0 <= nc && nc < col &&
                    !visited[nr][nc] && grid[nr][nc] == 'O') {
                    if (dfs(nr, nc, cells)) touch_border = true;
                }
            }
            return touch_border;
        };

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 'O' && !visited[i][j]) {
                vector<pair<int,int>> cells;
                bool touches_border = dfs(i, j, cells);
                if (!touches_border) {
                    for (auto &p : cells) {
                        grid[p.first][p.second] = 'X';
                    }
                }
            }
        }
    }
    return grid;
}

// Optimal: mark border 'O's, flip the rest
vector<vector<char>> optimal(vector<vector<char>> grid) {
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<bool>> visited(row, vector<bool>(col, false));
    queue<pair<int,int>> q;

    auto push_if_O = [&](int r, int c) {
        if (grid[r][c] == 'O' && !visited[r][c]) {
            visited[r][c] = true;
            q.push({r, c});
        }
    };

    for (int j = 0; j < col; j++) {
        push_if_O(0, j);
        push_if_O(row - 1, j);
    }
    for (int i = 1; i < row - 1; i++) {
        push_if_O(i, 0);
        push_if_O(i, col - 1);
    }

    static int dr[4] = {1,0,-1,0};
    static int dc[4] = {0,1,0,-1};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (0 <= nr && nr < row && 0 <= nc && nc < col &&
                grid[nr][nc] == 'O' && !visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 'O' && !visited[i][j]) grid[i][j] = 'X';
        }
    }
    return grid;
}

int main() {
    vector<vector<char>> matrix = {
        {'X','X','X','X'},
        {'X','O','O','X'},
        {'X','X','O','X'},
        {'X','O','X','X'}
    };

    auto r1 = brute(matrix);
    cout << "Brute:\n";
    for (auto &row : r1) {
        for (char c : row) cout << c << " ";
        cout << "\n";
    }
    auto r2 = optimal(matrix);
    cout << "\nOptimal:\n";
    for (auto &row : r2) {
        for (char c : row) cout << c << " ";
        cout << "\n";
    }
    return 0;
}
