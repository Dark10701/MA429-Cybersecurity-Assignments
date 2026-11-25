// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    const uint32_t M = (1u << 30) - 1;
    mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

    while (T--) {
        uint32_t x = 1, o;
        cout << x << endl;
        cin >> o;
        if (o == 0) {
            uint32_t m0 = 0, m1 = 1, r;
            cout << m0 << ' ' << m1 << endl;
            cin >> r;
            cout << ((r & 1u) ? 1 : 0) << endl;
        } else if (o != 1) {
            int bit = __builtin_ctz(o & ~1u);
            uint32_t m0 = 0, m1 = (1u << bit), r;
            cout << m0 << ' ' << m1 << endl;
            cin >> r;
            cout << ((((r >> bit) & 1u) == 0) ? 1 : 0) << endl;
        } else {
            uint32_t m0 = 0;
            uint32_t m1 = (rng() & M) | 1u; // random odd value
            uint32_t r;
            cout << m0 << ' ' << m1 << endl;
            cin >> r;

            int ans;
            if (r == 0) ans = 0;
            else if (r == m1) ans = 1;
            else if ((r & 1u) == 0) ans = 1;
            else ans = 0;
            cout << ans << endl;
        }
    }
    return 0;
}
