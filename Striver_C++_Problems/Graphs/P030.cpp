// P030.cpp - 3Sum (brute + optimal 2-pointer)

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
    return vector<vector<int>>(res_set.begin(), res_set.end());
}

vector<vector<int>> optimal(vector<int> nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;

    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        int left = i + 1, right = n - 1;
        while (left < right) {
            long long s = (long long)nums[i] + nums[left] + nums[right];
            if (s == 0) {
                res.push_back({nums[i], nums[left], nums[right]});
                left++;
                right--;
                while (left < right && nums[left] == nums[left - 1]) left++;
                while (left < right && nums[right] == nums[right + 1]) right--;
            } else if (s < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return res;
}

int main() {
    vector<int> nums;
    int x;
    while (cin >> x) nums.push_back(x);

    auto b = brute(nums);
    auto o = optimal(nums);

    auto printTriplets = [](const vector<vector<int>>& arr) {
        cout << "[\n";
        for (auto &t : arr) {
            cout << "  [";
            for (size_t i = 0; i < t.size(); i++) {
                cout << t[i];
                if (i + 1 < t.size()) cout << ", ";
            }
            cout << "]\n";
        }
        cout << "]\n";
    };

    cout << "Brute:\n";
    printTriplets(b);
    cout << "Optimal:\n";
    printTriplets(o);
    return 0;
}
