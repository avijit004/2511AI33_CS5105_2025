// P028.cpp - Spiral traversal (brute + optimal)

#include <bits/stdc++.h>
using namespace std;

vector<int> brute_spiral(const vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<int> result;

    vector<pair<int,int>> directions = {{0,1},{1,0},{0,-1},{-1,0}};
    int dir_idx = 0;
    int x = 0, y = 0;

    for (int step = 0; step < m * n; step++) {
        result.push_back(matrix[x][y]);
        visited[x][y] = true;
        int nx = x + directions[dir_idx].first;
        int ny = y + directions[dir_idx].second;
        if (0 <= nx && nx < m && 0 <= ny && ny < n && !visited[nx][ny]) {
            x = nx; y = ny;
        } else {
            dir_idx = (dir_idx + 1) % 4;
            x += directions[dir_idx].first;
            y += directions[dir_idx].second;
        }
    }
    return result;
}

vector<int> optimal(const vector<vector<int>>& grid) {
    int row = grid.size();
    int col = grid[0].size();
    int left = 0, right = col - 1, top = 0, bottom = row - 1;
    vector<int> res;

    while (right >= left && top <= bottom) {
        for (int i = left; i <= right; i++)
            res.push_back(grid[top][i]);
        top++;

        for (int i = top; i <= bottom; i++)
            res.push_back(grid[i][right]);
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--)
                res.push_back(grid[bottom][i]);
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                res.push_back(grid[i][left]);
            left++;
        }
    }
    return res;
}

int main() {
    vector<vector<int>> matrix = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    auto b = brute_spiral(matrix);
    auto o = optimal(matrix);

    cout << "Brute:   ";
    for (int x : b) cout << x << " ";
    cout << "\nOptimal: ";
    for (int x : o) cout << x << " ";
    cout << "\n";
    return 0;
}
