// Name: Aditya Patil | Roll No.: 23MAB0F01
#include <bits/stdc++.h>
using namespace std;

int ask(int c, int r) {
    cout << "? " << c << ' ' << r << endl;
    int h;
    if (!(cin >> h) || h == -1) exit(0);
    return h;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    int x = 1;
    int c = ask(n, x);
    int steps = n - c;
    int r = (steps == 0 ? x : ask(steps, x));
    cout << "! " << c << ' ' << r << endl;
    return 0;
}