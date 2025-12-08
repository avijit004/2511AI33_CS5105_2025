// P024.cpp - Arrange positive/negative alternately

#include <bits/stdc++.h>
using namespace std;

vector<int> brute(vector<int> nums) {
    int n = nums.size();
    vector<int> pos, neg;
    for (int x : nums) {
        if (x > 0) pos.push_back(x);
        else neg.push_back(x);
    }
    int p = 0, no = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 != 0) {
            nums[i] = neg[no++];
        } else {
            nums[i] = pos[p++];
        }
    }
    return nums;
}

vector<int> optimal(const vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n);
    int p = 0, neg = 1;
    for (int x : nums) {
        if (x > 0) {
            res[p] = x;
            p += 2;
        } else {
            res[neg] = x;
            neg += 2;
        }
    }
    return res;
}

int main() {
    cout << "Enter array: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> nums;
    int x;
    while (ss >> x) nums.push_back(x);

    auto b = brute(nums);
    auto o = optimal(nums);

    cout << "Brute:  ";
    for (int v : b) cout << v << " ";
    cout << "\nOptimal: ";
    for (int v : o) cout << v << " ";
    cout << "\n";
    return 0;
}
