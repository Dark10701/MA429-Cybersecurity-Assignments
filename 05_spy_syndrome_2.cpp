// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;
struct Node {
    int nxt[26], word;
    Node() { fill(nxt, nxt + 26, -1); word = -1; }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; string t; cin >> n >> t;
    int m; cin >> m;
    vector<Node> trie(1);
    vector<string> words(m);
    for (int id = 0; id < m; ++id) {
        cin >> words[id];
        string w = words[id];
        for (char &c : w) c = tolower((unsigned char)c);
        reverse(w.begin(), w.end());
        int v = 0;
        for (char c : w) {
            int x = c - 'a';
            if (trie[v].nxt[x] == -1) {
                trie[v].nxt[x] = (int)trie.size();
                trie.emplace_back();
            }
            v = trie[v].nxt[x];
        }
        trie[v].word = id;
    }
    vector<int> prev(n + 1, -1), chosen(n + 1, -1);
    prev[0] = 0;
    for (int i = 0; i < n; ++i) {
        if (prev[i] == -1) continue;
        int v = 0;
        for (int j = i; j < n; ++j) {
            int x = t[j] - 'a';
            if (trie[v].nxt[x] == -1) break;
            v = trie[v].nxt[x];
            if (trie[v].word != -1 && prev[j + 1] == -1) {
                prev[j + 1] = i;
                chosen[j + 1] = trie[v].word;
            }
        }
    }
    vector<string> ans;
    for (int p = n; p > 0; ) {
        int id = chosen[p];
        ans.push_back(words[id]);
        p = prev[p];
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}