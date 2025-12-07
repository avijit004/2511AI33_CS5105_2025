// P014.cpp - Partition equal subset sum

#include <bits/stdc++.h>
using namespace std;

// brute: check subset with target = total/2
bool helperBrutePE(const vector<int>& arr, int i, int target) {
    if (target == 0) return true;
    if (i == 0) return target == arr[0];
    bool not_pick = helperBrutePE(arr, i - 1, target);
    bool pick = false;
    if (arr[i] <= target) pick = helperBrutePE(arr, i - 1, target - arr[i]);
    return pick || not_pick;
}

bool brute(const vector<int>& arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;
    int n = arr.size();
    if (n == 0) return false;
    return helperBrutePE(arr, n - 1, target);
}

// optimal: subset sum DP to half
bool optimal(const vector<int>& arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 2 != 0) return false;
    int k = sum / 2;
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

    cout << "Brute: " << (brute(arr) ? "True" : "False") << "\n";
    cout << "Optimal: " << (optimal(arr) ? "True" : "False") << "\n";
    return 0;
}
