// P005.cpp - Left rotate array by 1

#include <bits/stdc++.h>
using namespace std;

vector<int> brute(const vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return nums;
    vector<int> temp(n);
    for (int i = 1; i < n; i++) temp[i - 1] = nums[i];
    temp[n - 1] = nums[0];
    return temp;
}

vector<int> optimal(vector<int> nums) {
    int n = nums.size();
    if (n == 0) return nums;
    int first = nums[0];
    for (int i = 1; i < n; i++) nums[i - 1] = nums[i];
    nums[n - 1] = first;
    return nums;
}

int main() {
    cout << "Enter elements: ";
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
    cout << "\nOptimal: ";
    for (int v : o) cout << v << " ";
    cout << "\n";
    return 0;
}
