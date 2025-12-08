// P002.cpp - Second largest element

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return -1;

    int max1;
    // find max1
    for (int i = 0; i < n; i++) {
        bool bigger = false;
        for (int j = 0; j < n; j++) {
            if (arr[j] > arr[i]) {
                bigger = true;
                break;
            }
        }
        if (!bigger) {
            max1 = arr[i];
            break;
        }
    }

    // find second max < max1
    int max2 = INT_MIN;
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (arr[i] == max1) continue;
        bool bigger = false;
        for (int j = 0; j < n; j++) {
            if (arr[j] > arr[i] && arr[j] < max1) {
                bigger = true;
                break;
            }
        }
        if (!bigger) {
            max2 = arr[i];
            found = true;
        }
    }
    return found ? max2 : -1;
}

int optimal(const vector<int>& a) {
    int n = a.size();
    if (n < 2) return -1;
    int max1, max2;
    if (a[0] > a[1]) {
        max1 = a[0]; max2 = a[1];
    } else {
        max1 = a[1]; max2 = a[0];
    }
    for (int i = 2; i < n; i++) {
        if (a[i] > max1) {
            max2 = max1;
            max1 = a[i];
        } else if (a[i] > max2 && a[i] != max1) {
            max2 = a[i];
        }
    }
    return max2;
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
