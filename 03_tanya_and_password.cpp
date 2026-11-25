// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;

int id(char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    if ('A' <= c && c <= 'Z') return c - 'A' + 26;
    return c - '0' + 52;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> s(n);
    vector<vector<int>> g(62 * 62);
    vector<int> in(62 * 62), out(62 * 62);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        int u = id(s[i][0]) * 62 + id(s[i][1]);
        int v = id(s[i][1]) * 62 + id(s[i][2]);
        g[u].push_back(v);
        ++out[u];
        ++in[v];
    }

    int start = -1, plus = 0, minus = 0;
    for (int v = 0; v < 62 * 62; ++v) {
        if (out[v] - in[v] == 1) start = v, ++plus;
        else if (in[v] - out[v] == 1) ++minus;
        else if (in[v] != out[v]) {
            cout << "NO\n";
            return 0;
        }
    }
    if (!((plus == 1 && minus == 1) || (plus == 0 && minus == 0))) {
        cout << "NO\n";
        return 0;
    }
    if (start == -1) {
        for (int v = 0; v < 62 * 62; ++v)
            if (out[v]) { start = v; break; }
    }
    if (start == -1) {
        cout << "NO\n";
        return 0;
    }

    vector<int> path;
    vector<int> st{start};
    while (!st.empty()) {
        int u = st.back();
        if (!g[u].empty()) {
            int v = g[u].back();
            g[u].pop_back();
            st.push_back(v);
        } else {
            path.push_back(u);
            st.pop_back();
        }
    }
    if ((int)path.size() != n + 1) {
        cout << "NO\n";
        return 0;
    }
    reverse(path.begin(), path.end());

    auto ch = [](int x) -> char {
        if (x < 26) return char('a' + x);
        if (x < 52) return char('A' + x - 26);
        return char('0' + x - 52);
    };

    cout << "YES\n";
    cout << ch(path[0] / 62) << ch(path[0] % 62);
    for (int i = 1; i < (int)path.size(); ++i)
        cout << ch(path[i] % 62);
    cout << '\n';
    return 0;
}
