// P026.cpp - Set matrix zeroes (brute + optimal)

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> brute(vector<vector<int>> grid) {
    int row = grid.size();
    int col = grid[0].size();
    vector<int> rz(row, 1), cz(col, 1);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 0) {
                rz[i] = 0;
                cz[j] = 0;
            }
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (rz[i] == 0 || cz[j] == 0) grid[i][j] = 0;
        }
    }
    return grid;
}

vector<vector<int>> optimal(vector<vector<int>> grid) {
    int row = grid.size();
    int col = grid[0].size();
    bool fr = false, fc = false;

    for (int j = 0; j < col; j++)
        if (grid[0][j] == 0) fr = true;
    for (int i = 0; i < row; i++)
        if (grid[i][0] == 0) fc = true;

    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            if (grid[i][j] == 0) {
                grid[i][0] = 0;
                grid[0][j] = 0;
            }
        }
    }
    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            if (grid[i][0] == 0 || grid[0][j] == 0)
                grid[i][j] = 0;
        }
    }
    if (fr) {
        for (int j = 0; j < col; j++) grid[0][j] = 0;
    }
    if (fc) {
        for (int i = 0; i < row; i++) grid[i][0] = 0;
    }
    return grid;
}

int main() {
    vector<vector<int>> matrix = {
        {1,1,1},
        {1,0,1},
        {1,1,1}
    };
    auto b = brute(matrix);
    auto o = optimal(matrix);

    cout << "Brute:\n";
    for (auto &r : b) {
        for (int x : r) cout << x << " ";
        cout << "\n";
    }
    cout << "Optimal:\n";
    for (auto &r : o) {
        for (int x : r) cout << x << " ";
        cout << "\n";
    }
    return 0;
}
