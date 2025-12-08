// P008.cpp - Find the missing number in [0..n]

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i <= n; i++) {
        bool found = false;
        for (int j = 0; j < n; j++) {
            if (arr[j] == i) {
                found = true;
                break;
            }
        }
        if (!found) return i;
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
