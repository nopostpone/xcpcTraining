#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

constexpr i64 inf = 1e18;

void solve() {
    int n, m, v, l, r;
    cin >> n >> m >> v >> l >> r;

    i64 sums = 0;
    vector<array<int, 4>> e(n);
    for (auto &[s, a, b, c] : e) {
        cin >> s >> a >> b >> c;
        sums += s;
    }

    m = min((i64)m, sums);
    r = min((i64)r, sums);

    auto get = [&](i64 x) {
        i64 cnt = 0, sum = 0;

        for (auto [s, a, b, c] : e) {
            if (a + c >= x) {
                cnt++;
                sum += a + c;
            }
            if (a >= x) {
                i64 k = min((i64)s - 1, (a - x) / b);
                cnt += k;
                sum += k * a;
                sum -= k * (b + k * b) / 2;
            }
        }
        return pair(cnt, sum);
    };

    auto work = [&](i64 m) {
        i64 lo = -2e12, hi = 2e12;
        while (lo < hi) {
            i64 x = (lo + hi + inf + 1) / 2 - inf / 2;
            auto [cnt, _] = get(x);
            if (cnt >= m) {
                lo = x;
            } else {
                hi = x - 1;
            }
        }

        auto [cnt, res] = get(lo);
        res -= (cnt - m) * (lo);
        if (l <= m and m <= r) {
            res += v;
        }
        return res;
    };

    auto [maxcnt, maxsum] = get(0);
    if (l <= maxcnt and maxcnt <= r) {
        maxsum += v;
    }
    if (maxcnt > m) {
        maxsum = -inf;
    }

    i64 ans = max({maxsum, work(0), work(m), work(l), work(r)});

    cout << ans << "\n";
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
