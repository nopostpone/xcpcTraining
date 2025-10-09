#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

constexpr int P = 998244353;
constexpr int power(int a, int b) {
    int res = 1;
    for (; b; b /= 2, a = (i64)a * a % P) {
        if (b & 1) {
            res = (i64)res * a % P;
        }
    }
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;

    int x = power(2, m) - 1;
    if (x < 0) {
        x += P;
    }
    int ans = power(x, n - 1);
    if (n % 2 == 0) {
        ans += power(P - x, n / 2);
        if (ans >= P) {
            ans -= P;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}