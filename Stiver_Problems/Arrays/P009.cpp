// P009.cpp - Maximum consecutive 1s in a binary array

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
    cout << "Enter array: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> arr;
    int x;
    while (ss >> x) arr.push_back(x);

    cout << "Max= " << optimal(arr) << "\n";
    return 0;
}
