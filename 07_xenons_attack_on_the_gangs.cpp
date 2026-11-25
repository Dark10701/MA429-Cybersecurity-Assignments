// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> g;
vector<vector<short>> par, sub;
vector<vector<long long>> memo;

void buildRooted(int root) {
    vector<int> order;
    order.reserve(n);
    par[root][root] = -1;
    vector<int> st{root};
    while (!st.empty()) {
        int u = st.back(); st.pop_back();
        order.push_back(u);
        for (int v : g[u]) if (v != par[root][u]) {
            par[root][v] = u;
            st.push_back(v);
        }
    }
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i], total = 1;
        for (int v : g[u]) if (par[root][v] == u) total += sub[root][v];
        sub[root][u] = total;
    }
}
long long solve(int u, int v) {
    if (u == v) return 0;
    long long &res = memo[u][v];
    if (res != -1) return res;
    int pu = par[v][u], pv = par[u][v];
    long long ways = 1LL * sub[u][v] * sub[v][u];
    return res = ways + max(solve(pu, v), solve(u, pv));
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    g.assign(n, {});
    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        g[u].push_back(v); g[v].push_back(u);
    }
    par.assign(n, vector<short>(n, -1));
    sub.assign(n, vector<short>(n, 0));
    for (int r = 0; r < n; ++r) buildRooted(r);
    memo.assign(n, vector<long long>(n, -1));
    long long ans = 0;
    for (int u = 0; u < n; ++u)
        for (int v = u + 1; v < n; ++v)
            ans = max(ans, solve(u, v));
    cout << ans << '\n';
    return 0;
}