// P036.cpp - Repeating and missing number using sum/square formulas

#include <bits/stdc++.h>
using namespace std;

// returns {A, B} where A = repeating, B = missing
vector<long long> optimal(const vector<int>& nums) {
    long long n = nums.size();
    long long s1 = n * (n + 1) / 2;
    long long q1 = n * (n + 1) * (2 * n + 1) / 6;
    long long s = 0, q = 0;
    for (int x : nums) {
        s += x;
        q += 1LL * x * x;
    }
    long long d1 = s - s1;       // A - B
    long long d2 = q - q1;       // A^2 - B^2 = (A-B)(A+B)
    long long d  = d2 / d1;      // A + B
    long long A = (d1 + d) / 2;  // repeating
    long long B = A - d1;        // missing
    return {A, B};
}

int main() {
    vector<int> nums = {1, 2, 2, 4};
    auto ans = optimal(nums);
    cout << "[" << ans[0] << ", " << ans[1] << "]\n";
    return 0;
}
