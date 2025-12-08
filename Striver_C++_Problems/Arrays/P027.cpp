// P027.cpp - Rotate N x N matrix

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> brute(const vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[j][n - 1 - i] = grid[i][j];
        }
    }
    return res;
}

vector<vector<int>> optimal(vector<vector<int>> grid) {
    int n = grid.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(grid[i][j], grid[j][i]);
        }
    }
    for (int i = 0; i < n; i++) {
        reverse(grid[i].begin(), grid[i].end());
    }
    return grid;
}

void printMatrix(const vector<vector<int>>& m) {
    cout << "[\n";
    for (auto &row : m) {
        cout << "  [";
        for (size_t j = 0; j < row.size(); j++) {
            cout << row[j];
            if (j + 1 < row.size()) cout << ", ";
        }
        cout << "]\n";
    }
    cout << "]\n";
}

int main() {
    vector<vector<int>> mat2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    auto b = brute(mat2);
    auto o = optimal(mat2);

    cout << "Brute: \n";
    printMatrix(b);
    cout << "Optimal: \n";
    printMatrix(o);
    return 0;
}
