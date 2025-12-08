// P001.cpp - Find maximum element in array

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        bool bigger = false;
        for (int j = 0; j < n; j++) {
            if (arr[j] > arr[i]) {
                bigger = true;
                break;
            }
        }
        if (!bigger) return arr[i];
    }
    return -1;
}

int optimal(const vector<int>& arr) {
    if (arr.empty()) return -1;
    int mx = arr[0];
    for (int x : arr) mx = max(mx, x);
    return mx;
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
