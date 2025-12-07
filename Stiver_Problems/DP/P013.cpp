// P013.cpp - Subset sum: does any subset sum to k?

#include <bits/stdc++.h>
using namespace std;

// brute: recursion
bool helperBrute(const vector<int>& arr, int i, int target) {
    if (target == 0) return true;
    if (i == 0) return arr[0] == target;
    bool not_pick = helperBrute(arr, i - 1, target);
    bool pick = false;
    if (arr[i] <= target) pick = helperBrute(arr, i - 1, target - arr[i]);
    return pick || not_pick;
}

bool brute(const vector<int>& arr, int k) {
    int n = arr.size();
    if (n == 0) return (k == 0);
    return helperBrute(arr, n - 1, k);
}

// optimal: 1D DP
bool optimal(const vector<int>& arr, int k) {
    int n = arr.size();
    vector<bool> prev(k + 1, false), curr(k + 1, false);
    prev[0] = true;
    if (n > 0 && arr[0] <= k) prev[arr[0]] = true;

    for (int i = 1; i < n; i++) {
        curr[0] = true;
        for (int target = 1; target <= k; target++) {
            bool not_pick = prev[target];
            bool pick = false;
            if (arr[i] <= target) pick = prev[target - arr[i]];
            curr[target] = pick || not_pick;
        }
        prev = curr;
    }
    return prev[k];
}

int main() {
    cout << "Enter elements: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> arr;
    int x;
    while (ss >> x) arr.push_back(x);
    cout << "Enter target: ";
    int k;
    cin >> k;

    cout << "Brute: " << (brute(arr, k) ? "True" : "False") << "\n";
    cout << "Optimal: " << (optimal(arr, k) ? "True" : "False") << "\n";
    return 0;
}
