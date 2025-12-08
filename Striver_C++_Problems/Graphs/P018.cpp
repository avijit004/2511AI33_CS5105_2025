// P018.cpp - Word Ladder 1 (shortest transformation length)

#include <bits/stdc++.h>
using namespace std;

bool diff_by_one(const string& a, const string& b) {
    int diff = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] != b[i]) {
            diff++;
            if (diff > 1) return false;
        }
    }
    return diff == 1;
}

int brute(const string& startWord, const string& targetWord,
          const vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    int INF = INT_MAX;
    int minStep = INF;

    function<void(string,int,unordered_set<string>&)> dfs =
        [&](string word, int step, unordered_set<string>& visited) {
            if (word == targetWord) {
                minStep = min(minStep, step);
                return;
            }
            for (auto &next : wordList) {
                if (!visited.count(next) && diff_by_one(word, next)) {
                    visited.insert(next);
                    dfs(next, step + 1, visited);
                    visited.erase(next);
                }
            }
        };

    unordered_set<string> visited;
    visited.insert(startWord);
    dfs(startWord, 1, visited);
    return (minStep == INF ? 0 : minStep);
}

// Optimal: BFS
int optimal(const string& startWord, const string& targetWord,
            const vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (!wordSet.count(targetWord)) return 0;
    queue<pair<string,int>> q;
    q.push({startWord, 1});

    while (!q.empty()) {
        auto [word, step] = q.front(); q.pop();
        if (word == targetWord) return step;
        for (int i = 0; i < (int)word.size(); i++) {
            string temp = word;
            for (char ch = 'a'; ch <= 'z'; ch++) {
                temp[i] = ch;
                if (wordSet.count(temp)) {
                    q.push({temp, step + 1});
                    wordSet.erase(temp);
                }
            }
        }
    }
    return 0;
}

int main() {
    string startWord = "hit";
    string targetWord = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};

    cout << "Brute "   << brute(startWord, targetWord, wordList) << "\n";
    cout << "Optimal " << optimal(startWord, targetWord, wordList) << "\n";
    return 0;
}
