// P035.cpp - Count subarrays with given XOR (k)

#include <bits/stdc++.h>
using namespace std;

long long optimal(const vector<int>& nums, int k) {
    unordered_map<int, long long> freq;
    int prefixXor = 0;
    long long count = 0;

    for (int num : nums) {
        prefixXor ^= num;
        if (prefixXor == k) count++;
        int want = prefixXor ^ k;
        if (freq.count(want)) count += freq[want];
        freq[prefixXor]++;
    }
    return count;
}

int main() {
    vector<int> nums = {4, 2, 2, 6, 4};
    int k = 6;
    cout << optimal(nums, k) << "\n";
    return 0;
}
