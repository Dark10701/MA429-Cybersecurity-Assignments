// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    struct Change { int child, root, oldSize; };
    vector<int> p, sz;
    vector<Change> history;
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { while (p[x] != x) x = p[x]; return x; }
    int snapshot() const { return (int)history.size(); }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) { history.push_back({-1, -1, 0}); return; }
        if (sz[a] < sz[b]) swap(a, b);
        history.push_back({b, a, sz[a]});
        p[b] = a; sz[a] += sz[b];
    }
    void rollback(int snap) {
        while ((int)history.size() > snap) {
            auto c = history.back(); history.pop_back();
            if (c.child == -1) continue;
            p[c.child] = c.child;
            sz[c.root] = c.oldSize;
        }
    }
    int size(int x) { return sz[find(x)]; }
};
struct Edge { int u, v; };
struct Query { int type, x, y; };
int q;
vector<vector<Edge>> seg;

void addInterval(int v, int l, int r, int ql, int qr, Edge e) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) { seg[v].push_back(e); return; }
    int mid = (l + r) / 2;
    addInterval(v * 2, l, mid, ql, qr, e);
    addInterval(v * 2 + 1, mid + 1, r, ql, qr, e);
}
void dfs(int v, int l, int r, DSU &dsu, const vector<Query> &queries, vector<int> &ans) {
    int snap = dsu.snapshot();
    for (auto e : seg[v]) dsu.unite(e.u, e.v);
    if (l == r) {
        if (queries[l].type == 2) ans[l] = dsu.size(queries[l].x);
    } else {
        int mid = (l + r) / 2;
        dfs(v * 2, l, mid, dsu, queries, ans);
        dfs(v * 2 + 1, mid + 1, r, dsu, queries, ans);
    }
    dsu.rollback(snap);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> q >> k;
    vector<Query> queries(q);
    vector<int> day(q);
    int currentDay = 0;
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].type;
        day[i] = currentDay;
        if (queries[i].type == 1) {
            cin >> queries[i].x >> queries[i].y;
            --queries[i].x; --queries[i].y;
        } else if (queries[i].type == 2) {
            cin >> queries[i].x;
            --queries[i].x;
            queries[i].y = -1;
        } else {
            queries[i].x = queries[i].y = -1;
            ++currentDay;
        }
    }
    seg.resize(4 * q + 4);
    for (int i = 0; i < q; ++i) if (queries[i].type == 1) {
        int expireDay = day[i] + k;
        int lo = i + 1, hi = q;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (day[mid] >= expireDay) hi = mid;
            else lo = mid + 1;
        }
        int last = lo - 1;
        if (i <= last)
            addInterval(1, 0, q - 1, i, last, {queries[i].x, queries[i].y});
    }
    vector<int> ans(q, -1);
    DSU dsu(n);
    dfs(1, 0, q - 1, dsu, queries, ans);
    for (int i = 0; i < q; ++i)
        if (queries[i].type == 2) cout << ans[i] << '\n';
    return 0;
}