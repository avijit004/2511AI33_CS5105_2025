// P014.cpp - Longest consecutive sequence

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& nums) {
    int n = nums.size();
    int longest = 0;
    for (int i = 0; i < n - 1; i++) {
        int seq = 0;
        int x = nums[i];
        while (find(nums.begin(), nums.end(), x) != nums.end()) {
            seq++;
            x++;
        }
        longest = max(longest, seq);
    }
    return longest;
}

int optimal(const vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int longest = 0;
    for (int num : nums) {
        if (s.find(num - 1) == s.end()) { // start of a sequence
            int x = num;
            int seq = 0;
            while (s.find(x) != s.end()) {
                seq++;
                x++;
            }
            longest = max(longest, seq);
        }
    }
    return longest;
}

int main() {
    cout << "Enter numbers: ";
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
