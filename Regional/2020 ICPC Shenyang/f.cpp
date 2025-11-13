#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

constexpr int inf = 2e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> suf(n + 1);
    suf[n] = inf;
    for (int i = n; i; i--) {
        suf[i - 1] = min(suf[i], a[i - 1]);
    }

    int ans = 1;
    for (int i = 1, cur = a[0]; i < n; i++) {
        if (suf[i] >= cur) {
            ans++;
        }
        cur = max(cur, a[i]);
    }

    cout << ans << "\n";

    return 0;
}