// P017.cpp - Count enclaved '1' cells

#include <bits/stdc++.h>
using namespace std;

// Brute: DFS from each '1' to see if region touches border; count internal cells
int brute(const vector<vector<char>>& grid) {
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<bool>> visited(row, vector<bool>(col, false));

    function<bool(int,int,int&)> dfs = [&](int r, int c, int &cnt) -> bool {
        if (r == 0 || c == 0 || r == row-1 || c == col-1) return true;
        visited[r][c] = true;
        cnt++;
        static int dr[4] = {0,1,-1,0};
        static int dc[4] = {1,0,0,-1};
        bool touch = false;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (0 <= nr && nr < row && 0 <= nc && nc < col &&
                !visited[nr][nc] && grid[nr][nc] == '1') {
                if (dfs(nr, nc, cnt)) touch = true;
            }
        }
        return touch;
    };

    int total = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                int cnt = 0;
                bool touches = dfs(i, j, cnt);
                if (!touches) total += cnt;
            }
        }
    }
    return total;
}

// Optimal: BFS from all border '1's, remaining '1's are enclaves
int optimal(vector<vector<char>> grid) {
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<bool>> visited(row, vector<bool>(col, false));
    queue<pair<int,int>> q;

    auto push_if1 = [&](int r, int c) {
        if (grid[r][c] == '1' && !visited[r][c]) {
            visited[r][c] = true;
            q.push({r, c});
        }
    };

    for (int j = 0; j < col; j++) {
        push_if1(0, j);
        push_if1(row - 1, j);
    }
    for (int i = 1; i < row - 1; i++) {
        push_if1(i, 0);
        push_if1(i, col - 1);
    }

    static int dr[4] = {1,0,-1,0};
    static int dc[4] = {0,1,0,-1};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (0 <= nr && nr < row && 0 <= nc && nc < col &&
                grid[nr][nc] == '1' && !visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    int count = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (grid[i][j] == '1' && !visited[i][j]) count++;
    return count;
}

int main() {
    vector<vector<char>> grid = {
        {'0','0','0','0'},
        {'1','0','1','0'},
        {'0','1','1','0'},
        {'0','0','0','0'}
    };

    cout << "Brute: " << brute(grid) << "\n";
    cout << "Optimal: " << optimal(grid) << "\n";
    return 0;
}
