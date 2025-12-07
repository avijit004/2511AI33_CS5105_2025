// P011.cpp - Maximum subarray sum (brute + Kadane)

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& arr) {
    int n = arr.size();
    int max_sum = 0;
    for (int i = 0; i < n - 1; i++) {
        int curr_sum = 0;
        for (int j = i; j < n; j++) {
            curr_sum += arr[j];
            max_sum = max(max_sum, curr_sum);
        }
    }
    return max_sum;
}

int optimal(const vector<int>& arr) {
    int n = arr.size();
    int curr_sum = 0, max_sum = 0;
    for (int i = 0; i < n; i++) {
        if (curr_sum < 0) curr_sum = 0;
        curr_sum += arr[i];
        max_sum = max(max_sum, curr_sum);
    }
    return max_sum;
}

int main() {
    cout << "Enter array: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> arr;
    int x;
    while (ss >> x) arr.push_back(x);

    cout << "Brute: " << brute(arr) << "\n";
    cout << "Optimal: " << optimal(arr) << "\n";
    return 0;
}
