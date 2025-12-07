// P019_P020.cpp - Longest subarray length with sum == target

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& nums, int target) {
    int n = nums.size();
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        int s = 0;
        int length = 0;
        for (int j = i; j < n; j++) {
            s += nums[j];
            length++;
            if (s == target) {
                max_len = max(max_len, length);
            }
        }
    }
    return max_len;
}

// Works for negatives/positives using prefix sum + first occurrence map
int optimal(const vector<int>& nums, int target) {
    int n = nums.size();
    int max_len = 0;
    long long s = 0;
    unordered_map<long long, int> first_idx; // prefix_sum -> first index

    for (int i = 0; i < n; i++) {
        s += nums[i];
        if (s == target) {
            max_len = max(max_len, i + 1);
        }
        long long need = s - target;
        if (first_idx.find(need) != first_idx.end()) {
            max_len = max(max_len, i - first_idx[need]);
        }
        if (first_idx.find(s) == first_idx.end()) {
            first_idx[s] = i;
        }
    }
    return max_len;
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
