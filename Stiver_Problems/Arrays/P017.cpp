// P017.cpp - Merge two sorted arrays (like union merge)

#include <bits/stdc++.h>
using namespace std;

vector<int> optimal(const vector<int>& nums1, const vector<int>& nums2) {
    int n1 = nums1.size(), n2 = nums2.size();
    int i = 0, j = 0;
    vector<int> res;
    while (i < n1 && j < n2) {
        if (nums1[i] < nums2[j]) {
            res.push_back(nums1[i++]);
        } else if (nums2[j] < nums1[i]) {
            res.push_back(nums2[j++]);
        } else {
            res.push_back(nums1[i]);
            i++; j++;
        }
    }
    while (i < n1) res.push_back(nums1[i++]);
    while (j < n2) res.push_back(nums2[j++]);
    return res;
}

int main() {
    cout << "Enter first nums: ";
    string line1;
    getline(cin, line1);
    stringstream ss1(line1);
    vector<int> nums1;
    int x;
    while (ss1 >> x) nums1.push_back(x);

    cout << "Enter second nums: ";
    string line2;
    getline(cin, line2);
    stringstream ss2(line2);
    vector<int> nums2;
    while (ss2 >> x) nums2.push_back(x);

    auto res = optimal(nums1, nums2);
    cout << "Merges: ";
    for (int v : res) cout << v << " ";
    cout << "\n";
    return 0;
}
