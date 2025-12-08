// P010.cpp - Majority element (appears at least n/2 times assumed)

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) count++;
        }
        if (count >= n / 2) {
            return arr[i];
        }
    }
    return -1;
}

int optimal(const vector<int>& arr) {
    int n = arr.size();
    int ele = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (count == 0) {
            ele = arr[i];
            count = 1;
        } else if (ele == arr[i]) {
            count++;
        } else {
            count--;
        }
    }
    // (Optionally could verify ele is majority here)
    return ele;
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
