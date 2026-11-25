// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;
static const long long MOD = 1000000007LL;

struct DSU {
    vector<int> p, sz;
    int comps;
    DSU(int n): p(n), sz(n,1), comps(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { while (p[x] != x) x = p[x] = p[p[x]]; return x; }
    void unite(int a, int b) {
        a=find(a); b=find(b);
        if (a==b) return;
        if (sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b]; --comps;
    }
};

long long modpow(long long a, long long e) {
    long long r=1;
    while(e){ if(e&1) r=r*a%MOD; a=a*a%MOD; e>>=1; }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,k;
    cin >> n >> m >> k;
    vector<long long> c(n);
    for (auto &x:c) cin >> x;
    vector<tuple<long long,int,int>> edges;
    edges.reserve(m);
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v; --u;--v;
        edges.emplace_back(c[u]^c[v],u,v);
    }
    sort(edges.begin(), edges.end());

    vector<long long> pw2(n+1);
    pw2[0]=1;
    for(int i=1;i<=n;i++) pw2[i]=pw2[i-1]*2%MOD;

    long long totalX = modpow(2,k);
    long long ans = ((totalX - (long long)0) % MOD) * pw2[n] % MOD;
    long long distinct = 0;

    for(int i=0;i<m;){
        int j=i;
        DSU dsu(n);
        long long key=get<0>(edges[i]);
        while(j<m && get<0>(edges[j])==key){
            dsu.unite(get<1>(edges[j]),get<2>(edges[j]));
            ++j;
        }
        ans = (ans - pw2[n] + MOD) % MOD;
        ans = (ans + pw2[dsu.comps]) % MOD;
        ++distinct;
        i=j;
    }
    cout << ans << '\n';
    return 0;
}
