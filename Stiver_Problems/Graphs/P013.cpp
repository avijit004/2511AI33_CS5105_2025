// P013.cpp - Flood fill (brute DFS + "optimal" using a queue)

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> brute_fill(int sr, int sc,
                               vector<vector<int>> image,
                               int newColor) {
    int original = image[sr][sc];
    int row = image.size();
    int col = image[0].size();
    if (original == newColor) return image;

    function<void(int,int)> dfs = [&](int r, int c) {
        image[r][c] = newColor;
        static int dr[4] = {1,0,-1,0};
        static int dc[4] = {0,1,0,-1};
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (0 <= nr && nr < row && 0 <= nc && nc < col &&
                image[nr][nc] == original) {
                dfs(nr, nc);
            }
        }
    };
    dfs(sr, sc);
    return image;
}

// "optimal" version: BFS using a queue (Python used heapq, but ordering not needed)
vector<vector<int>> optimal_fill(int sr, int sc,
                                 vector<vector<int>> image,
                                 int newColor) {
    int original = image[sr][sc];
    int row = image.size();
    int col = image[0].size();
    if (original == newColor) return image;

    queue<pair<int,int>> q;
    q.push({sr, sc});
    image[sr][sc] = newColor;

    static int dr[4] = {1,0,-1,0};
    static int dc[4] = {0,1,0,-1};

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (0 <= nr && nr < row && 0 <= nc && nc < col &&
                image[nr][nc] == original) {
                image[nr][nc] = newColor;
                q.push({nr, nc});
            }
        }
    }
    return image;
}

int main() {
    vector<vector<int>> image = {
        {1,1,1},
        {1,1,0},
        {1,0,1}
    };
    int sr = 1, sc = 1, newColor = 2;

    auto img1 = brute_fill(sr, sc, image, newColor);
    auto img2 = optimal_fill(sr, sc, image, newColor);

    cout << "Brute:\n";
    for (auto &row : img1) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    cout << "\nOptimal:\n";
    for (auto &row : img2) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    return 0;
}
