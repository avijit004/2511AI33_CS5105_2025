// P033.cpp - Merge two sorted arrays into a new sorted array

#include <bits/stdc++.h>
using namespace std;

vector<int> mergeArrays(const vector<int>& nums1, const vector<int>& nums2) {
    int n1 = nums1.size(), n2 = nums2.size();
    vector<int> res;
    res.reserve(n1 + n2);
    int i = 0, j = 0;
    while (i < n1 && j < n2) {
        if (nums1[i] > nums2[j]) {
            res.push_back(nums2[j]);
            j++;
        } else {
            res.push_back(nums1[i]);
            i++;
        }
    }
    while (i < n1) res.push_back(nums1[i++]);
    while (j < n2) res.push_back(nums2[j++]);
    return res;
}

int main() {
    vector<int> nums1 = {1,2,3};
    int m = 3;
    vector<int> nums2 = {2,5,6};
    int n = 3;
    (void)m; (void)n;

    auto res = mergeArrays(nums1, nums2);
    cout << "[";
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i];
        if (i + 1 < res.size()) cout << ", ";
    }
    cout << "]\n";
    return 0;
}
