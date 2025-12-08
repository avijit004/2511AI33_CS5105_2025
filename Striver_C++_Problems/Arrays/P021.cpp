// P021.cpp - Two Sum (return indices)

#include <bits/stdc++.h>
using namespace std;

vector<int> brute(const vector<int>& nums, int target) {
    int n = nums.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

vector<int> optimal(const vector<int>& nums, int target) {
    int n = nums.size();
    unordered_map<int, int> seen; // value -> index
    for (int i = 0; i < n; i++) {
        int need = target - nums[i];
        if (seen.count(need)) {
            return {seen[need], i};
        }
        seen[nums[i]] = i;
    }
    return {-1, -1};
}

int main() {
    cout << "Enter array: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> nums;
    int x;
    while (ss >> x) nums.push_back(x);

    cout << "Enter target: ";
    int target;
    cin >> target;

    auto b = brute(nums, target);
    auto o = optimal(nums, target);

    cout << "Brute:  [" << b[0] << ", " << b[1] << "]\n";
    cout << "Optimal: [" << o[0] << ", " << o[1] << "]\n";
    return 0;
}
