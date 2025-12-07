// P016.cpp - Maximum product subarray (brute + optimal)

#include <bits/stdc++.h>
using namespace std;

long long brute(const vector<int>& nums) {
    int n = nums.size();
    long long max_prod = LLONG_MIN;
    for (int i = 0; i < n - 1; i++) {
        long long prod = 1;
        for (int j = i; j < n; j++) {
            prod *= nums[j];
            max_prod = max(max_prod, prod);
        }
    }
    return max_prod;
}

long long optimal(const vector<int>& nums) {
    int n = nums.size();
    long long min_prod = nums[0], max_prod = nums[0], result = nums[0];
    for (int i = 1; i < n; i++) {
        long long cur = nums[i];
        if (cur < 0) swap(min_prod, max_prod);
        min_prod = min(cur, min_prod * cur);
        max_prod = max(cur, max_prod * cur);
        result = max(result, max_prod);
    }
    return result;
}

int main() {
    cout << "Enter nums: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> nums;
    int x;
    while (ss >> x) nums.push_back(x);

    cout << "Brute: " << brute(nums) << "\n";
    cout << "Optimal: " << optimal(nums) << "\n";
    return 0;
}
