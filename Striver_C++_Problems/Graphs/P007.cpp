// P007.cpp - Linear search (return index)

#include <bits/stdc++.h>
using namespace std;

int linear(const vector<int>& arr, int target) {
    for (int i = 0; i < (int)arr.size(); i++)
        if (arr[i] == target) return i;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> nums;
    int x;
    while (cin >> x) {
        nums.push_back(x);
    }

    // If you want target from input, adapt to read separately like:
    // last int is target, etc.

    // For now, assume last element is target:
    if (nums.empty()) return 0;
    int target = nums.back();
    nums.pop_back();

    cout << linear(nums, target) << "\n";
    return 0;
}
