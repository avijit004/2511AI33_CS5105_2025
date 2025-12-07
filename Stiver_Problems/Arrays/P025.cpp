// P025.cpp - Next permutation

#include <bits/stdc++.h>
using namespace std;

vector<int> optimal(vector<int> nums) {
    int n = nums.size();
    int i = n - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }
    if (i >= 0) {
        int j = n - 1;
        while (j >= 0 && nums[j] <= nums[i]) {
            j--;
        }
        if (j >= 0) swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
    return nums;
}

int main() {
    cout << "Enter array: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> nums;
    int x;
    while (ss >> x) nums.push_back(x);

    auto o = optimal(nums);
    cout << "Optimal: ";
    for (int v : o) cout << v << " ";
    cout << "\n";
    return 0;
}
