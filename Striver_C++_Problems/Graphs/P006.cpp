// P006.cpp - Move all zeros to the end (stable)

#include <bits/stdc++.h>
using namespace std;

vector<int> brute(const vector<int>& nums) {
    int n = nums.size();
    vector<int> temp;
    temp.reserve(n);
    for (int x : nums)
        if (x != 0) temp.push_back(x);
    while ((int)temp.size() < n) temp.push_back(0);
    return temp;
}

vector<int> optimal(vector<int> nums) {
    int n = nums.size();
    int i = 0, j = 0;
    while (j < n) {
        if (nums[j] != 0) {
            swap(nums[i], nums[j]);
            i++;
        }
        j++;
    }
    return nums;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> nums;
    int x;
    while (cin >> x) nums.push_back(x);

    auto b = brute(nums);
    auto o = optimal(nums);

    cout << "Brute: ";
    for (int v : b) cout << v << " ";
    cout << "\nOptimal: ";
    for (int v : o) cout << v << " ";
    cout << "\n";
    return 0;
}
