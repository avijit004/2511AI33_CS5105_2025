// P029.cpp - Majority elements (> n/3) (brute + Boyer-Moore 2 candidates)

#include <bits/stdc++.h>
using namespace std;

vector<int> brute(const vector<int>& nums) {
    int n = nums.size();
    unordered_map<int,int> freq;
    for (int x : nums) freq[x]++;
    vector<int> result;
    for (auto &p : freq) {
        if (p.second > n / 3) result.push_back(p.first);
    }
    return result;
}

vector<int> optimal(const vector<int>& nums) {
    int n = nums.size();
    int cand1 = 0, cand2 = 0;
    int count1 = 0, count2 = 0;

    for (int x : nums) {
        if (count1 > 0 && x == cand1) {
            count1++;
        } else if (count2 > 0 && x == cand2) {
            count2++;
        } else if (count1 == 0) {
            cand1 = x;
            count1 = 1;
        } else if (count2 == 0) {
            cand2 = x;
            count2 = 1;
        } else {
            count1--;
            count2--;
        }
    }

    count1 = count2 = 0;
    for (int x : nums) {
        if (x == cand1) count1++;
        else if (x == cand2) count2++;
    }

    vector<int> res;
    if (count1 > n / 3) res.push_back(cand1);
    if (cand2 != cand1 && count2 > n / 3) res.push_back(cand2);
    return res;
}

int main() {
    vector<int> nums;
    int x;
    while (cin >> x) nums.push_back(x);

    auto b = brute(nums);
    auto o = optimal(nums);

    cout << "Brute:  ";
    for (int v : b) cout << v << " ";
    cout << "\nOptimal: ";
    for (int v : o) cout << v << " ";
    cout << "\n";
    return 0;
}
