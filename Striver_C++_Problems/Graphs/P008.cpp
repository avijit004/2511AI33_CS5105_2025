// P008.cpp - Find missing number in [0..n]

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& arr) {
    int n = arr.size();
    for (int val = 0; val <= n; val++) {
        bool found = false;
        for (int x : arr) {
            if (x == val) {
                found = true;
                break;
            }
        }
        if (!found) return val;
    }
    return -1;
}

int optimal(const vector<int>& arr) {
    int n = arr.size();
    long long total = 1LL * n * (n + 1) / 2;
    long long sum = 0;
    for (int x : arr) sum += x;
    return (int)(total - sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> nums;
    int x;
    while (cin >> x) nums.push_back(x);

    cout << "Brute: " << brute(nums) << "\n";
    cout << "Optimal: " << optimal(nums) << "\n";
    return 0;
}
