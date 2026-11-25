// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    const uint32_t LIMIT = (1u << 30);
    mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

    while (T--) {
        vector<int> bits(30);
        iota(bits.begin(), bits.end(), 0);
        shuffle(bits.begin(), bits.end(), rng);

        // A balanced mask makes the two possible operator explanations
        // similarly unlikely when the first response equals x.
        uint32_t x = 0;
        for (int i = 0; i < 15; ++i) x |= (1u << bits[i]);

        uint32_t o;
        cout << x << endl;
        if (!(cin >> o) || o == UINT32_MAX) return 0;

        uint32_t m0 = rng() & (LIMIT - 1);
        uint32_t m1 = rng() & (LIMIT - 1);
        while (m1 == m0) m1 = rng() & (LIMIT - 1);

        cout << m0 << ' ' << m1 << endl;
        uint32_t r;
        if (!(cin >> r) || r == UINT32_MAX) return 0;

        uint32_t v0 = r ^ m0;
        uint32_t v1 = r ^ m1;

        auto possible = [&](uint32_t v) {
            return ((v & x) == o) || ((v | x) == o);
        };

        bool ok0 = possible(v0);
        bool ok1 = possible(v1);

        int answer;
        if (ok0 != ok1) answer = ok1 ? 1 : 0;
        else answer = (rng() & 1u); // randomized tie-break for indistinguishable candidates

        cout << answer << endl;
    }
    return 0;
}