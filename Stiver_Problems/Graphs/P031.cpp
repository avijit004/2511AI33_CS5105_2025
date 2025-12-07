// P031.cpp - Longest zero-sum subarray length

#include <bits/stdc++.h>
using namespace std;

int optimal(const vector<int>& nums) {
    long long prefix_sum = 0;
    unordered_map<long long,int> seen;
    int max_len = 0;

    for (int i = 0; i < (int)nums.size(); i++) {
        prefix_sum += nums[i];
        if (prefix_sum == 0) {
            max_len = i + 1;
        } else if (seen.count(prefix_sum)) {
            max_len = max(max_len, i - seen[prefix_sum]);
        } else {
            seen[prefix_sum] = i;
        }
    }
    return max_len;
}

int main() {
    vector<int> arr = {15, -2, 2, -8, 1, 7, 10, 23};
    cout << "Optimal: " << optimal(arr) << "\n";
    return 0;
}
