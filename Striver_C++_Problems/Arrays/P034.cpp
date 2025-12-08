// P034.cpp - 4Sum (return all quadruplets with given target)

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> optimal(vector<int> nums, int target) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;

    for (int i = 0; i < n - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        for (int j = i + 1; j < n - 2; j++) {
            // literal translation: j>0 in Python (slightly odd but kept)
            if (j > 0 && nums[j] == nums[j - 1]) continue;

            int k = j + 1;
            int l = n - 1;
            while (k < l) {
                long long tot = (long long)nums[i] + nums[j] + nums[k] + nums[l];
                if (tot == target) {
                    res.push_back({nums[i], nums[j], nums[k], nums[l]});
                    k++;
                    l--;
                    while (k < l && nums[k] == nums[k - 1]) k++;
                    while (l > k && nums[l] == nums[l + 1]) l--;
                } else if (tot > target) {
                    l--;
                } else {
                    k++;
                }
            }
        }
    }
    return res;
}

int main() {
    vector<int> nums = {1,0,-1,0,-2,2};
    int target = 0;
    auto ans = optimal(nums, target);

    cout << "Optimal: [\n";
    for (auto &q : ans) {
        cout << "  [";
        for (size_t i = 0; i < q.size(); i++) {
            cout << q[i];
            if (i + 1 < q.size()) cout << ", ";
        }
        cout << "]\n";
    }
    cout << "]\n";
    return 0;
}
