// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;
static const long long MOD = 1000000007LL;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        int sum = 0;
        for (char c : s) sum += c - 'a';
        vector<long long> dp(sum + 1), ndp(sum + 1);
        dp[0] = 1;
        int used = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            fill(ndp.begin(), ndp.end(), 0);
            long long window = 0;
            for (int v = 0; v <= sum; ++v) {
                if (v <= used) window = (window + dp[v]) % MOD;
                if (v - 26 >= 0) window = (window - dp[v - 26] + MOD) % MOD;
                ndp[v] = window;
            }
            dp.swap(ndp);
            used += 25;
        }
        cout << (dp[sum] - 1 + MOD) % MOD << '\n';
    }
    return 0;
}