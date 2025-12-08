// P019.cpp - Wildcard matching: ?, * (s1 pattern, s2 text)

#include <bits/stdc++.h>
using namespace std;

// brute recursive
bool allStar(const string& s, int i) {
    for (int k = i; k < (int)s.size(); k++)
        if (s[k] != '*') return false;
    return true;
}

bool helperBruteWM(const string& s1, const string& s2, int i, int j) {
    int n = s1.size();
    int m = s2.size();
    if (i == n && j == m) return true;
    if (i == n && j != m) return false;
    if (j == m) return allStar(s1, i);

    if (s1[i] == s2[j] || s1[i] == '?')
        return helperBruteWM(s1, s2, i + 1, j + 1);
    else if (s1[i] == '*')
        return helperBruteWM(s1, s2, i + 1, j) || helperBruteWM(s1, s2, i, j + 1);
    else
        return false;
}

bool brute(const string& s1, const string& s2) {
    return helperBruteWM(s1, s2, 0, 0);
}

// optimal: DP
bool optimal(const string& s1, const string& s2) {
    int n = s1.size();
    int m = s2.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    dp[0][0] = true;
    for (int j = 1; j <= m; j++)
        dp[0][j] = false;

    for (int i = 1; i <= n; i++) {
        bool allstar = true;
        for (int k = 0; k < i; k++)
            if (s1[k] != '*') { allstar = false; break; }
        dp[i][0] = allstar;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1] || s1[i - 1] == '?') {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (s1[i - 1] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            } else {
                dp[i][j] = false;
            }
        }
    }
    return dp[n][m];
}

int main() {
    cout << "Enter s1: ";
    string s1;
    getline(cin, s1);
    cout << "Enter s2: ";
    string s2;
    getline(cin, s2);

    cout << "Brute: " << (brute(s1,s2) ? "True" : "False") << "\n";
    cout << "Optimal: " << (optimal(s1,s2) ? "True" : "False") << "\n";
    return 0;
}
