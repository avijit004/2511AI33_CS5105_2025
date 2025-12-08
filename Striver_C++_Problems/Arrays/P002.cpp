// P002.cpp - Find second largest element

#include <bits/stdc++.h>
using namespace std;

int brute(const vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return -1;

    // First find the maximum
    int max1 = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max1) max1 = arr[i];
    }

    // Now find the largest element that is not beaten by any other (except maybe max1)
    int best = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] == max1) continue;
        bool bigger = false;
        for (int j = 0; j < n; j++) {
            if (arr[j] > arr[i] && arr[j] <= max1) {
                bigger = true;
                break;
            }
        }
        if (!bigger && arr[i] > best) {
            best = arr[i];
        }
    }

    return (best == INT_MIN ? -1 : best);
}

int optimal(const vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return -1;

    int max1, max2;
    if (arr[0] > arr[1]) {
        max1 = arr[0];
        max2 = arr[1];
    } else {
        max1 = arr[1];
        max2 = arr[0];
    }

    for (int i = 2; i < n; i++) {
        if (arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        } else if (arr[i] > max2) {
            max2 = arr[i];
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

