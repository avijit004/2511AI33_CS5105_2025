// P004.cpp - Remove duplicates (assuming sorted array)

#include <bits/stdc++.h>
using namespace std;

vector<int> brute(const vector<int>& arr) {
    set<int> s(arr.begin(), arr.end());   // unique + sorted
    vector<int> res(s.begin(), s.end());
    return res;
}

vector<int> optimal(vector<int> arr) {
    int n = arr.size();
    if (n == 0) return arr;
    int i = 0;
    for (int j = 1; j < n; j++) {
        if (arr[i] != arr[j]) {
            i++;
            arr[i] = arr[j];
        }
    }
    arr.resize(i + 1);
    return arr;
}

int main() {
    cout << "Enter elements: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> arr;
    int x;
    while (ss >> x) arr.push_back(x);

    vector<int> b = brute(arr);
    vector<int> o = optimal(arr);

    cout << "Brute: ";
    for (int v : b) cout << v << " ";
    cout << "\nOptimal: ";
    for (int v : o) cout << v << " ";
    cout << "\n";

    return 0;
}