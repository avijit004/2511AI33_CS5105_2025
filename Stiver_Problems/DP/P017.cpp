// P017.cpp - Count subsets with difference k (S1 - S2 = k)

#include <bits/stdc++.h>
using namespace std;

// reduce to subset sum target = (k + totalSum)/2

long long countSubsetsTarget(const vector<int>& arr, int target) {
    int n = arr.size();
    vector<long long> prev(target + 1, 0), curr(target + 1, 0);
    prev[0] = 1;
    if (n > 0 && arr[0] <= target) prev[arr[0]]++;

    for (int i = 1; i < n; i++) {
        curr.assign(target + 1, 0);
        curr[0] = 1;
        for (int j = 1; j <= target; j++) {
            long long not_pick = prev[j];
            long long pick = 0;
            if (arr[i] <= j) pick = prev[j - arr[i]];
            curr[j] = pick + not_pick;
        }
        prev = curr;
    }
    return prev[target];
}

// brute
long long brute(const vector<int>& arr, int k) {
    int tot = accumulate(arr.begin(), arr.end(), 0);
    if ((k + tot) % 2 != 0) return 0;
    int target = (k + tot) / 2;
    if (target < 0) return 0;
    return countSubsetsTarget(arr, target);
}

// optimal is same formula, using DP
long long optimal(const vector<int>& arr, int k) {
    int tot = accumulate(arr.begin(), arr.end(), 0);
    if ((k + tot) % 2 != 0) return 0;
    int target = (k + tot) / 2;
    if (target < 0) return 0;
    return countSubsetsTarget(arr, target);
}

int main() {
    cout << "Enter arr: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> arr;
    int x;
    while (ss >> x) arr.push_back(x);
    cout << "Enter difference: ";
    int k;
    cin >> k;

    cout << "Brute: " << brute(arr, k) << "\n";
    cout << "Optimal: " << optimal(arr, k) << "\n";
    return 0;
}
