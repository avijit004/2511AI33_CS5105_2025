// P011.cpp - Maximum path sum in a matrix with 3 moves

#include <bits/stdc++.h>
using namespace std;

// ----- Brute: recursive DFS from each top row cell -----
int dfsBrute(const vector<vector<int>>& mat, int i, int j) {
    int n = mat.size();
    int m = mat[0].size();
    if (i >= n || j < 0 || j >= m) return INT_MIN; // -inf
    if (i == n - 1) return mat[i][j];

    int down     = dfsBrute(mat, i + 1, j);
    int downRight= dfsBrute(mat, i + 1, j + 1);
    int downLeft = (j > 0 ? dfsBrute(mat, i + 1, j - 1) : INT_MIN);

    int bestNext = max({down, downRight, downLeft});
    if (bestNext == INT_MIN) return INT_MIN;
    return mat[i][j] + bestNext;
}

int brute(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    int maxi = INT_MIN;
    for (int j = 0; j < m; j++) {
        maxi = max(maxi, dfsBrute(matrix, 0, j));
    }
    return maxi;
}

// ----- Optimal: DP -----
int optimal(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, INT_MIN));

    // first row
    for (int j = 0; j < m; j++) dp[0][j] = matrix[0][j];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int best = dp[i - 1][j];
            if (j > 0)     best = max(best, dp[i - 1][j - 1]);
            if (j < m - 1) best = max(best, dp[i - 1][j + 1]);
            if (best == INT_MIN) continue;
            dp[i][j] = matrix[i][j] + best;
        }
    }

    int ans = INT_MIN;
    for (int j = 0; j < m; j++) ans = max(ans, dp[n - 1][j]);
    return ans;
}

int main() {
    vector<vector<int>> grid = {
        {1, 2, 10, 4},
        {100, 3, 2, 1},
        {1, 1, 20, 2},
        {1, 2, 2, 1}
    };
    cout << "Brute: " << brute(grid) << "\n";
    cout << "Optimal: " << optimal(grid) << "\n";
    return 0;
}
