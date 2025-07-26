#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

void solve() {
    i64 a, b, x, y;
    cin >> a >> b >> x >> y;

    if (a != x and b != y) {
        cout << "No\n";
        return;
    }
    bool ok = true;
    for (int i = 0; i < 60; i++) {
        int da = a >> i & 1;
        int db = b >> i & 1;
        int dx = x >> i & 1;
        int dy = y >> i & 1;

        if (da == 0 and dx) {
            ok = false;
        }
        if (dy == 0 and db) {
            ok = false;
        }
    }

    cout << (ok ? "Yes" : "No") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

/*
4 
 3  6 3 6
7 4 5 4
5 4 3 4
2 4 3 5

*/