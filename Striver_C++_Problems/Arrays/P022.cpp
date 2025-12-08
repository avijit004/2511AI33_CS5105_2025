// P022.cpp - Sort array of 0s, 1s, 2s

#include <bits/stdc++.h>
using namespace std;

vector<int> brute(vector<int> nums) {
    int count0 = 0, count1 = 0, count2 = 0;
    for (int n : nums) {
        if (n == 0) count0++;
        else if (n == 1) count1++;
        else count2++;
    }
    int i = 0;
    for (int k = 0; k < count0; k++) nums[i++] = 0;
    for (int k = 0; k < count1; k++) nums[i++] = 1;
    for (int k = 0; k < count2; k++) nums[i++] = 2;
    return nums;
}

vector<int> optimal(vector<int> nums) {
    int n = nums.size();
    int low = 0, mid = 0, high = n - 1;
    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
    return nums;
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
