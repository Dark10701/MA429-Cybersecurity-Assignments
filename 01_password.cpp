// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, l;
    cin >> n >> k >> l;
    vector<int> x(k), a(l);
    for (int &v : x) cin >> v;
    for (int &v : a) cin >> v;

    vector<int> terminals;
    int prev = 0;
    for (int i = 1; i <= n; ++i) {
        int cur = binary_search(x.begin(), x.end(), i);
        if (cur != prev) terminals.push_back(i);
        prev = cur;
    }
    if (prev) terminals.push_back(n + 1);

    int m = (int)terminals.size();
    if (m == 0) {
        cout << 0 << '\n';
        return 0;
    }
    if (m % 2) {
        cout << -1 << '\n';
        return 0;
    }

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    const int INF = 1e9;
    vector<vector<int>> dist(m, vector<int>(m, INF));
    for (int s = 0; s < m; ++s) {
        vector<int> d(n + 2, INF);
        queue<int> q;
        d[terminals[s]] = 0;
        q.push(terminals[s]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int len : a) {
                int v1 = u - len, v2 = u + len;
                if (v1 >= 1 && d[v1] == INF) d[v1] = d[u] + 1, q.push(v1);
                if (v2 <= n + 1 && d[v2] == INF) d[v2] = d[u] + 1, q.push(v2);
            }
        }
        for (int j = 0; j < m; ++j) dist[s][j] = d[terminals[j]];
    }

    int N = 1 << m;
    vector<int> dp(N, INF);
    dp[0] = 0;
    for (int mask = 1; mask < N; ++mask) {
        if (__builtin_popcount((unsigned)mask) & 1) continue;
        int i = __builtin_ctz((unsigned)mask);
        int rem = mask ^ (1 << i);
        for (int j = i + 1; j < m; ++j) {
            if (rem & (1 << j)) {
                int sub = rem ^ (1 << j);
                if (dist[i][j] < INF && dp[sub] < INF)
                    dp[mask] = min(dp[mask], dp[sub] + dist[i][j]);
            }
        }
    }
    cout << (dp[N - 1] >= INF ? -1 : dp[N - 1]) << '\n';
    return 0;
}
