// P038.cpp - Count inversions using merge sort (nums = {6,4,1,2,7})

#include <bits/stdc++.h>
using namespace std;

long long c = 0;

void mergeVec(vector<int>& nums, int l, int mid, int h) {
    int n1 = mid - l + 1;
    int n2 = h - mid;
    vector<int> arr1(n1), arr2(n2);
    for (int i = 0; i < n1; i++) arr1[i] = nums[l + i];
    for (int j = 0; j < n2; j++) arr2[j] = nums[mid + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) {
            nums[k++] = arr1[i++];
        } else {
            nums[k++] = arr2[j++];
            c += (n1 - i);
        }
    }
    while (i < n1) nums[k++] = arr1[i++];
    while (j < n2) nums[k++] = arr2[j++];
}

void mergesort(vector<int>& nums, int l, int h) {
    if (l < h) {
        int mid = (l + h) / 2;
        mergesort(nums, l, mid);
        mergesort(nums, mid + 1, h);
        mergeVec(nums, l, mid, h);
    }
}

int main() {
    vector<int> nums = {6,4,1,2,7};
    mergesort(nums, 0, (int)nums.size() - 1);
    cout << "Optimal: " << c << "\n";
    return 0;
}
