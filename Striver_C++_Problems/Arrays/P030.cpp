// P030.cpp - 3Sum: all unique triplets with sum 0

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> brute(const vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> res_set;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    vector<int> trip = {nums[i], nums[j], nums[k]};
                    sort(trip.begin(), trip.end());
                    res_set.insert(trip);
                }
            }
        }
    }
    vector<vector<int>> res(res_set.begin(), res_set.end());
    return res;
}

vector<vector<int>> optimal(vector<int> nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;

    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            long long s = (long long)nums[i] + nums[left] + nums[right];
            if (s == 0) {
                res.push_back({nums[i], nums[left], nums[right]});
                left++;
                right--;
                while (left < right && nums[left - 1] == nums[left]) left++;
                while (left < right && nums[right + 1] == nums[right]) right++;
            } else if (s < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return res;
}

void printTriplets(const vector<vector<int>>& trips) {
    cout << "[\n";
    for (auto &t : trips) {
        cout << "  [";
        for (size_t i = 0; i < t.size(); i++) {
            cout << t[i];
            if (i + 1 < t.size()) cout << ", ";
        }
        cout << "]\n";
    }
    cout << "]\n";
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

    cout << "Brute: \n";
    printTriplets(b);
    cout << "Optimal:\n";
    printTriplets(o);
    return 0;
}
