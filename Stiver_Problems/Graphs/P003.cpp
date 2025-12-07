// P003.cpp - Check if array is sorted non-decreasing

#include <bits/stdc++.h>
using namespace std;

bool brute(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j]) return false;
    return true;
}

bool optimal(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr;
    int x;
    while (cin >> x) arr.push_back(x);

    cout << "Brute: " << (brute(arr) ? "True" : "False") << "\n";
    cout << "Optimal: " << (optimal(arr) ? "True" : "False") << "\n";
    return 0;
}
