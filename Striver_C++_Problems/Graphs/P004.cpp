// P004.cpp - Remove duplicates from sorted array

#include <bits/stdc++.h>
using namespace std;

vector<int> brute(const vector<int>& arr) {
    set<int> s(arr.begin(), arr.end());
    return vector<int>(s.begin(), s.end());
}

vector<int> optimal(vector<int> arr) {
    int n = arr.size();
    if (n == 0) return arr;
    int i = 0;
    for (int j = 1; j < n; j++) {
        if (arr[j] != arr[i]) {
            ++i;
            arr[i] = arr[j];
        }
    }
    arr.resize(i + 1);
    return arr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr;
    int x;
    while (cin >> x) arr.push_back(x);

    auto b = brute(arr);
    auto o = optimal(arr);

    cout << "Brute: ";
    for (int v : b) cout << v << " ";
    cout << "\nOptimal: ";
    for (int v : o) cout << v << " ";
    cout << "\n";
    return 0;
}
