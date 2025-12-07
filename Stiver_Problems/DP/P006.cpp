// P006.cpp - Move all zeroes to the end (stable)

#include <bits/stdc++.h>
using namespace std;

vector<int> brute(const vector<int>& nums) {
    int n = nums.size();
    vector<int> temp(n, 0);
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] != 0) {
            temp[k] = nums[i];
            k++;
        }
    }
    return temp;
}

vector<int> optimal(vector<int> nums) {
    int n = nums.size();
    int i = 0, j = 0;
    while (j < n) {
        if (nums[j] == 0) {
            j++;
            continue;
        }
        if (nums[i] == 0) {
            swap(nums[i], nums[j]);
            i++; j++;
        } else {
            i++; j++;
        }
    }
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
