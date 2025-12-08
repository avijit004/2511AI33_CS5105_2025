// P016.cpp - Count subsets with given sum k

#include <bits/stdc++.h>
using namespace std;

// brute: recursion
long long helperBruteCount(const vector<int>& arr, int i, int target) {
    if (target == 0) return 1;
    if (i == 0) return (arr[0] == target) ? 1 : 0;
    long long not_pick = helperBruteCount(arr, i - 1, target);
    long long pick = 0;
    if (arr[i] <= target) pick = helperBruteCount(arr, i - 1, target - arr[i]);
    return pick + not_pick;
}

long long brute(const vector<int>& arr, int k) {
    int n = arr.size();
    if (n == 0) return (k == 0 ? 1 : 0);
    return helperBruteCount(arr, n - 1, k);
}

// optimal: DP counting ways
long long optimal(const vector<int>& arr, int k) {
    int n = arr.size();
    vector<long long> prev(k + 1, 0), curr(k + 1, 0);
    prev[0] = 1;
    if (n > 0 && arr[0] <= k) prev[arr[0]]++;

    for (int i = 1; i < n; i++) {
        curr.assign(k + 1, 0);
        curr[0] = 1;
        for (int j = 1; j <= k; j++) {
            long long not_pick = prev[j];
            long long pick = 0;
            if (arr[i] <= j) pick = prev[j - arr[i]];
            curr[j] = pick + not_pick;
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

    cout << "Brute: " << brute(arr, k) << "\n";
    cout << "Optimal: " << optimal(arr, k) << "\n";
    return 0;
}
