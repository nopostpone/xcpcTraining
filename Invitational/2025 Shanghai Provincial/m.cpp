#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

using i128 = __int128;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y;
    cin >> n >> x >> y;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += __builtin_popcount(a[i]);
    }

    i64 ans = 1e18;
    i64 cur = 0;
    for (int d = 31; d >= 0; d--) {
        for (int i = 0; i < n; i++) {
            if (a[i] >> d & 1) {
                cur++;
                cnt--;
            }
        }
        i128 res = (i128)1 * d * y + i128(cnt + cur) * x;
        if (res < 1e18) {
            ans = min(ans, (i64)res);
        }
        
        cur *= 2;
    }
    cout << ans << "\n";

    return 0;
}

/*
6 1 1
1 1 4 5 1 4

5 2 5
10 7 9 0 3

*/