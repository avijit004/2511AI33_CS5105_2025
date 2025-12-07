// P012.cpp - Two-robot maximum cherries collection

#include <bits/stdc++.h>
using namespace std;

// ----- Brute: DFS(i, j1, j2) -----
int dfsChoco(const vector<vector<int>>& grid, int i, int j1, int j2) {
    int n = grid.size();
    int m = grid[0].size();

    if (j1 < 0 || j1 >= m || j2 < 0 || j2 >= m) return INT_MIN; // -inf
    if (i == n - 1) {
        if (j1 == j2) return grid[i][j1];
        return grid[i][j1] + grid[i][j2];
    }

    int res = (j1 == j2) ? grid[i][j1] : (grid[i][j1] + grid[i][j2]);
    int maxi = INT_MIN;
    for (int dj1 = -1; dj1 <= 1; dj1++) {
        for (int dj2 = -1; dj2 <= 1; dj2++) {
            int val = dfsChoco(grid, i + 1, j1 + dj1, j2 + dj2);
            maxi = max(maxi, val);
        }
    }
    if (maxi == INT_MIN) return INT_MIN;
    return res + maxi;
}

int brute(const vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    return dfsChoco(grid, 0, 0, m - 1);
}

// ----- Optimal: bottom-up DP with prev[m][m] -----
int optimal(const vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    const int NEG_INF = INT_MIN / 4;
    vector<vector<int>> prev(m, vector<int>(m, NEG_INF));

    // base: last row
    for (int j1 = 0; j1 < m; j1++) {
        for (int j2 = 0; j2 < m; j2++) {
            if (j1 == j2) prev[j1][j2] = grid[n - 1][j1];
            else prev[j1][j2] = grid[n - 1][j1] + grid[n - 1][j2];
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        vector<vector<int>> curr(m, vector<int>(m, NEG_INF));
        for (int j1 = 0; j1 < m; j1++) {
            for (int j2 = 0; j2 < m; j2++) {
                int maxi = NEG_INF;
                for (int dj1 = -1; dj1 <= 1; dj1++) {
                    for (int dj2 = -1; dj2 <= 1; dj2++) {
                        int nj1 = j1 + dj1;
                        int nj2 = j2 + dj2;
                        if (nj1 < 0 || nj1 >= m || nj2 < 0 || nj2 >= m) continue;
                        int val = prev[nj1][nj2];
                        if (val == NEG_INF) continue;
                        if (j1 == j2) val += grid[i][j1];
                        else val += grid[i][j1] + grid[i][j2];
                        maxi = max(maxi, val);
                    }
                }
                curr[j1][j2] = maxi;
            }
        }
        prev.swap(curr);
    }

    return prev[0][m - 1];
}

int main() {
    vector<vector<int>> mat = {
        {2, 3, 1, 2},
        {3, 4, 2, 2},
        {5, 6, 3, 5}
    };
    cout << "Brute: " << brute(mat) << "\n";
    cout << "Optimal: " << optimal(mat) << "\n";
    return 0;
}
