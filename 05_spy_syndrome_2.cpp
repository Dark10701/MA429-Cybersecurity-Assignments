// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int nxt[26];
    int word;
    Node() { fill(nxt, nxt+26, -1); word = -1; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string t;
    cin >> n >> t;
    int m;
    cin >> m;

    vector<Node> trie(1);
    vector<string> words(m);
    for (int id=0; id<m; ++id) {
        cin >> words[id];
        string w=words[id];
        for(char &c:w) c=tolower((unsigned char)c);
        reverse(w.begin(), w.end());
        int v=0;
        for(char c:w){
            int x=c-'a';
            if(trie[v].nxt[x]==-1){
                trie[v].nxt[x]=trie.size();
                trie.emplace_back();
            }
            v=trie[v].nxt[x];
        }
        trie[v].word=id;
    }

    vector<int> prev(n+1,-1), chosen(n+1,-1);
    prev[0]=0;
    for(int i=0;i<n;i++){
        if(prev[i]==-1) continue;
        int 