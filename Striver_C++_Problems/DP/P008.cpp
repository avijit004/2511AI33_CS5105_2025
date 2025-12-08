// P008.cpp - Find missing number in range [0..n]

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& arr) {
    int n = arr.size();
    for (int v = 0; v <= n; v++) {
        bool found = false;
        for (int x : arr) {
            if (x == v) {
                found = true;
                break;
            }
        }
        if (!found) return v;
    }
    return -1;
}

int optimal(const vector<int>& arr) {
    int n = arr.size();
    long long tot = 1LL * n * (n + 1) / 2;
    long long suma = 0;
    for (int x : arr) suma += x;
    return (int)(tot - suma);
}

int main() {
    cout << "Enter array: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> nums;
    int x;
    while (ss >> x) nums.push_back(x);

    cout << "Brute: " << brute(nums) << "\n";
    cout << "Optimal: " << optimal(nums) << "\n";
    return 0;
}
