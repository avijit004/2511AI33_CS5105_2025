// P015.cpp - Minimum subset sum difference

#include <bits/stdc++.h>
using namespace std;

// brute: recursion exploring all splits
int helperBruteMinDiff(const vector<int>& arr, int i, int s1, int total) {
    if (i == 0) {
        return abs(total - 2 * s1);
    }
    int not_pick = helperBruteMinDiff(arr, i - 1, s1, total);
    int pick = helperBruteMinDiff(arr, i - 1, s1 + arr[i], total);
    return min(not_pick, pick);
}

int brute(const vector<int>& arr) {
    int n = arr.size();
    int total = accumulate(arr.begin(), arr.end(), 0);
    if (n == 0) return 0;
    return helperBruteMinDiff(arr, n - 1, 0, total);
}

// optimal: subset sum DP up to total/2
int optimal(const vector<int>& arr) {
    int n = arr.size();
    int total = accumulate(arr.begin(), arr.end(), 0);
    int target = total / 2;

    vector<bool> dp(target + 1, false);
    dp[0] = true;
    if (n > 0 && arr[0] <= target) dp[arr[0]] = true;

    for (int i = 1; i < n; i++) {
        for (int j = target; j >= arr[i]; j--) {
            if (dp[j - arr[i]]) dp[j] = true;
        }
    }

    int mini = INT_MAX;
    for (int s1 = 0; s1 <= target; s1++) {
        if (dp[s1]) {
            int diff = abs(total - 2 * s1);
            mini = min(mini, diff);
        }
    }
    return mini == INT_MAX ? 0 : mini;
}

int main() {
    cout << "Enter arr: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> arr;
    int x;
    while (ss >> x) arr.push_back(x);

    cout << "Brute: " << brute(arr) << "\n";
    cout << "Optimal: " << optimal(arr) << "\n";
    return 0;
}
