// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;

struct RollbackDSU {
    struct Change { int type, child, root, oldSize, oldXor; };
    vector<int> p, sz, xr;
    vector<Change> history;
    int bad = 0;

    RollbackDSU(int n) : p(n), sz(n, 1), xr(n, 0) {
        iota(p.begin(), p.end(), 0);
    }
    pair<int,int> find(int x) {
        int parity = 0;
        while (p[x] != x) {
            parity ^= xr[x];
            x = p[x];
        }
        return {x, parity};
    }
    int snapshot() const { return (int)history.size(); }
    void addEdge(int a, int b) {
        auto [ra, xa] = find(a);
        auto [rb, xb] = find(b);
        if (ra == rb) {
            if ((xa ^ xb) != 1) {
                ++bad;
                history.push_back({1, -1, -1, 0, 0});
            } else {
                history.push_back({0, -1, -1, 0, 0});
            }
            return;
        }
        if (sz[ra] < sz[rb]) {
            swap(ra, rb);
            swap(xa, xb);
        }
        history.push_back({2, rb, ra, sz[ra], xr[rb]});
        p[rb] = ra;
        xr[rb] = xa ^ xb ^ 1;
        sz[ra] += sz[rb];
    }
    void rollback(int snap) {
        while ((int)history.size() > snap) {
            Change c = history.back();
            history.pop_back();
            if (c.type == 1) --bad;
            else if (c.type == 2) {
                p[c.child] = c.child;
                xr[c.child] = c.oldXor;
                sz[c.root] = c.oldSize;
            }
        }
    }
};

struct Edge { int u, v; };
int n, q;
vector<vector<Edge>> seg;

void addInterval(int node, int l, int r, int ql, int qr, Edge e) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        seg[node].push_back(e);
        return;
    }
    int mid = (l + r) / 2;
    addInterval(node * 2, l, mid, ql, qr, e);
    addInterval(node * 2 + 1, mid + 1, r, ql, qr, e);
}
void dfs(int node, int l, int r, RollbackDSU &dsu, vector<string> &ans) {
    int snap = dsu.snapshot();
    for (auto e : seg[node]) dsu.addEdge(e.u, e.v);
    if (l == r) ans[l] = (dsu.bad == 0 ? "YES" : "NO");
    else {
        int mid = (l + r) / 2;
        dfs(node * 2, l, mid, dsu, ans);
        dfs(node * 2 + 1, mid + 1, r, dsu, ans);
    }
    dsu.rollback(snap);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    seg.resize(4 * q + 4);
    map<pair<int,int>, int> opened;
    for (int i = 0; i < q; ++i) {
        int x, y; cin >> x >> y; --x; --y;
        if (x > y) swap(x, y);
        pair<int,int> e = {x, y};
        auto it = opened.find(e);
        if (it == opened.end()) opened[e] = i;
        else {
            addInterval(1, 0, q - 1, it->second, i - 1, {x, y});
            opened.erase(it);
        }
    }
    for (auto [e, start] : opened)
        addInterval(1, 0, q - 1, start, q - 1, {e.first, e.second});

    vector<string> ans(q);
    RollbackDSU dsu(n);
    dfs(1, 0, q - 1, dsu, ans);
    for (const string &s : ans) cout << s << '\n';
    return 0;
}