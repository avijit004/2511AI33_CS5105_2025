// P013.cpp - Leaders in array (each element > all on right)

#include <bits/stdc++.h>
using namespace std;

vector<int> brute(const vector<int>& nums) {
    int n = nums.size();
    vector<int> res;
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = i + 1; j < n; j++) {
            if (nums[i] < nums[j]) {
                c = 1;
            }
        }
        if (c == 0) res.push_back(nums[i]);
    }
    return res;
}

vector<int> optimal(const vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return {};
    vector<int> res;
    int maxl = INT_MIN;
    for (int i = n - 1; i >= 0; i--) {
        if (nums[i] > maxl) {
            res.push_back(nums[i]);
            maxl = nums[i];
        }
    }
    // Python returns in order of discovery from right to left; keeping that.
    return res;
}

int main() {
    cout << "Enter numbers: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> nums;
    int x;
    while (ss >> x) nums.push_back(x);

    auto b = brute(nums);
    auto o = optimal(nums);

    cout << "Brute: ";
    for (int v : b) cout << v << " ";
    cout << "\noptimal: ";
    for (int v : o) cout << v << " ";
    cout << "\n";
    return 0;
}
