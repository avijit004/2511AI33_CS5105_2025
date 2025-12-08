// P023.cpp - Maximum subarray sum

#include <bits/stdc++.h>
using namespace std;

long long brute(const vector<int>& nums) {
    int n = nums.size();
    long long max_sum = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        long long suma = 0;
        for (int j = i; j < n; j++) {
            suma += nums[j];
            max_sum = max(max_sum, suma);
        }
    }
    return max_sum;
}

long long optimal(const vector<int>& nums) {
    int n = nums.size();
    long long cur_sum = nums[0];
    long long max_sum = nums[0];
    for (int i = 1; i < n; i++) {
        cur_sum = max(cur_sum + nums[i], (long long)nums[i]);
        max_sum = max(max_sum, cur_sum);
    }
    return max_sum;
}

int main() {
    cout << "Enter array: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> nums;
    int x;
    while (ss >> x) nums.push_back(x);

    cout << "Brute:  " << brute(nums) << "\n";
    cout << "Optimal: " << optimal(nums) << "\n";
    return 0;
}
