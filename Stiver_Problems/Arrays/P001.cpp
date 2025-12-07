// P001.cpp - Find maximum element (brute and optimal)

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        bool bigger = false;
        for (int j = 0; j < n; j++) {
            if (arr[j] > arr[i]) {
                bigger = true;
                break;
            }
        }
        if (!bigger) return arr[i];
    }
    return -1;
}

int optimal(const vector<int>& arr) {
    if (arr.empty()) return -1;
    int max_ele = arr[0];
    for (int x : arr) {
        if (x > max_ele) max_ele = x;
    }
    return max_ele;
}

int main() {
    cout << "Enter elements: ";
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