// P007.cpp - Linear search

#include <bits/stdc++.h>
using namespace std;

int linear(const vector<int>& arr, int target) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int main() {
    cout << "Enter elements: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> nums;
    int x;
    while (ss >> x) nums.push_back(x);

    cout << "Enter target: ";
    int target;
    cin >> target;

    cout << linear(nums, target) << "\n";
    return 0;
}
