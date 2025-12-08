// P009.cpp - Max consecutive 1s in binary array

#include <bits/stdc++.h>
using namespace std;

int optimal(const vector<int>& arr) {
    int count = 0, max_count = 0;
    for (int x : arr) {
        if (x == 1) {
            count++;
        } else {
            max_count = max(max_count, count);
            count = 0;
        }
    }
    max_count = max(max_count, count);
    return max_count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr;
    int x;
    while (cin >> x) arr.push_back(x);

    cout << "Max= " << optimal(arr) << "\n";
    return 0;
}
