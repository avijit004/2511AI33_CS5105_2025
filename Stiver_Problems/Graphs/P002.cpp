// P002.cpp - Second largest element

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return -1;

    int largest = INT_MIN, second = INT_MIN;
    for (int x : arr) largest = max(largest, x);

    for (int x : arr) {
        if (x != largest) second = max(second, x);
    }
    return (second == INT_MIN ? -1 : second);
}

int optimal(const vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return -1;

    int max1 = INT_MIN, max2 = INT_MIN;
    for (int x : arr) {
        if (x > max1) {
            max2 = max1;
            max1 = x;
        } else if (x > max2 && x != max1) {
            max2 = x;
        }
    }
    return (max2 == INT_MIN ? -1 : max2);
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
