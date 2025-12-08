// P015.cpp - Count subarrays with sum == target

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& nums, int target) {
    int n = nums.size();
    int c = 0;
    for (int i = 0; i < n; i++) {
        int s = 0;
        for (int j = i + 1; j < n; j++) {   // mirrors your Python
            s += nums[j];
        }
        if (s == target) c++;
    }
    return c;
}

int optimal(const vector<int>& nums, int target) {
    int n = nums.size();
    int c = 0;
    unordered_set<long long> prev_sum;
    long long s = 0;
    for (int v : nums) {
        s += v;
        if (s == target) c++;
        else if (s > target && prev_sum.find(s - target) != prev_sum.end())
            c++;
        prev_sum.insert(s);
    }
    return c;
}

int main() {
    cout << "Enter numbers: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> nums;
    int x;
    while (ss >> x) nums.push_back(x);

    cout << "Enter target: ";
    int target;
    cin >> target;

    cout << "Brute: " << brute(nums, target) << "\n";
    cout << "optimal: " << optimal(nums, target) << "\n";
    return 0;
}
