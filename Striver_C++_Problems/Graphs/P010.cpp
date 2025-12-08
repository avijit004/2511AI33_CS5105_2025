// P010.cpp - Majority element (appears >= n/2 times)

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < n; j++)
            if (arr[i] == arr[j]) c++;
        if (c >= n / 2) return arr[i];
    }
    return -1;
}

int optimal(const vector<int>& arr) {
    int ele = 0, count = 0;
    for (int x : arr) {
        if (count == 0) {
            ele = x;
            count = 1;
        } else if (x == ele) {
            count++;
        } else {
            count--;
        }
    }
    // Assuming majority element exists as in typical problem statement.
    return ele;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr;
    int x;
    while (cin >> x) arr.push_back(x);

    cout << "Brute: " << brute(arr) << "\n";
    cout << "Optimal: " << optimal(arr) << "\n";
    return 0;
}
