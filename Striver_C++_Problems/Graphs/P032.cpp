// P032.cpp - Merge intervals

#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> optimal(vector<pair<int,int>> nums) {
    sort(nums.begin(), nums.end(),
         [](const pair<int,int>& a, const pair<int,int>& b){
             return a.first < b.first;
         });

    vector<pair<int,int>> merge;
    for (auto interval : nums) {
        if (merge.empty() || merge.back().second < interval.first) {
            merge.push_back(interval);
        } else {
            merge.back().first  = min(merge.back().first,  interval.first);
            merge.back().second = min(merge.back().second, interval.second);
        }
    }
    return merge;
}

int main() {
    vector<pair<int,int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    auto res = optimal(intervals);
    cout << "Optimal: [";
    for (size_t i = 0; i < res.size(); i++) {
        cout << "[" << res[i].first << "," << res[i].second << "]";
        if (i + 1 < res.size()) cout << ", ";
    }
    cout << "]\n";
    return 0;
}
