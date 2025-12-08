// P019.cpp - Word Ladder II (all shortest transformation sequences)

#include <bits/stdc++.h>
using namespace std;

bool diff_by_one_2(const string& a, const string& b) {
    int diff = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] != b[i]) {
            diff++;
            if (diff > 1) return false;
        }
    }
    return diff == 1;
}

// Brute: DFS exploring all paths, tracking global minimum length
vector<vector<string>> brute(const string& startWord,
                             const string& targetWord,
                             const vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    int INF = INT_MAX;
    int minStep = INF;
    vector<vector<string>> minList;

    function<void(string,int,unordered_set<string>&,vector<string>&)>
    dfs = [&](string word, int step,
              unordered_set<string>& visited, vector<string>& path) {
        if (word == targetWord) {
            if (step < minStep) {
                minStep = step;
                minList.clear();
            }
            if (step == minStep) {
                minList.push_back(path);
            }
            return;
        }
        for (auto &next : wordList) {
            if (!visited.count(next) && diff_by_one_2(word, next)) {
                visited.insert(next);
                path.push_back(next);
                dfs(next, step + 1, visited, path);
                path.pop_back();
                visited.erase(next);
            }
        }
    };

    unordered_set<string> visited;
    visited.insert(startWord);
    vector<string> path = {startWord};
    dfs(startWord, 1, visited, path);
    return minList;
}

// Optimal: BFS + parents graph + backtracking
vector<vector<string>> optimal(const string& startWord,
                               const string& targetWord,
                               const vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (!wordSet.count(targetWord)) return {};

    queue<string> q;
    q.push(startWord);
    unordered_map<string, vector<string>> parents;
    unordered_set<string> visited;
    visited.insert(startWord);
    bool found = false;

    while (!q.empty() && !found) {
        int sz = q.size();
        unordered_set<string> next_level;
        for (int _ = 0; _ < sz; _++) {
            string word = q.front(); q.pop();
            for (int i = 0; i < (int)word.size(); i++) {
                string temp = word;
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    temp[i] = ch;
                    if (wordSet.count(temp) && !visited.count(temp)) {
                        parents[temp].push_back(word);
                        if (temp == targetWord) found = true;
                        next_level.insert(temp);
                    }
                }
            }
        }
        for (auto &w : next_level) {
            visited.insert(w);
            q.push(w);
        }
    }

    vector<vector<string>> res;
    if (!found) return res;

    function<void(const string&, vector<string>&)> backtrack =
        [&](const string& word, vector<string>& path) {
            if (word == startWord) {
                vector<string> rev = path;
                reverse(rev.begin(), rev.end());
                res.push_back(rev);
                return;
            }
            for (auto &p : parents[word]) {
                path.push_back(p);
                backtrack(p, path);
                path.pop_back();
            }
        };

    vector<string> path = {targetWord};
    backtrack(targetWord, path);
    return res;
}

int main() {
    string startWord = "hit";
    string targetWord = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};

    cout << "Brute:\n";
    auto r1 = brute(startWord, targetWord, wordList);
    for (auto &seq : r1) {
        for (size_t i = 0; i < seq.size(); i++) {
            cout << seq[i];
            if (i + 1 < seq.size()) cout << "->";
        }
        cout << "\n";
    }

    cout << "\nOptimal:\n";
    auto r2 = optimal(startWord, targetWord, wordList);
    for (auto &seq : r2) {
        for (size_t i = 0; i < seq.size(); i++) {
            cout << seq[i];
            if (i + 1 < seq.size()) cout << "->";
        }
        cout << "\n";
    }
    return 0;
}
