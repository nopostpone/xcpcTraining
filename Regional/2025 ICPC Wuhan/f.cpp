#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> f(n, -1);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        f[r - 1] = max(f[r - 1], l);
    }
    int ans = 0;
    for (int i = 0, lst = -1; i < n; i++) {
        if (f[i] > lst) {
            lst = i;
            ans++;
        }
    }
    cout << __lg(ans) + 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}