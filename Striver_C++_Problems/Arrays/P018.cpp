// P018.cpp - Find the single element (others appear twice)

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < n; j++) {
            if (nums[i] == nums[j]) c++;
        }
        if (c != 2) return nums[i];
    }
    return -1;
}

int optimal(const vector<int>& nums) {
    int n = nums.size();
    int res = nums[0];
    for (int i = 1; i < n; i++) {
        res ^= nums[i];
    }
    return res;
}

int main() {
    cout << "Enter elements: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> nums;
    int x;
    while (ss >> x) nums.push_back(x);

    cout << "Brute: " << brute(nums) << "\n";
    cout << "optimal: " << optimal(nums) << "\n";
    return 0;
}
