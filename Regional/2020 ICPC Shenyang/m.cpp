#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

void fwt(auto &a) {
    int n = a.size();
    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < n; j += 2 * i) {
            for (int k = 0; k < i; k++) {
                auto u = a[j + k];
                auto v = a[i + j + k];
                a[j + k] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    i64 k;
    cin >> n >> m >> k;

    vector<i64> f(1 << m);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        int state = 0;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'A') {
                state |= 1 << j;
            }
        }
        f[state]++;
    }

    fwt(f);
    for (int i = 0; i < 1 << m; i++) {
        f[i] = (f[i] * f[i] - n) / 2;
    }
    fwt(f);

    for (auto &x : f) {
        x >>= m;
    }

    for (int i = 0; i < m; i++) {
        for (int s = 0; s < 1 << m; s++) {
            if (s >> i & 1) {
                f[s] += f[s ^ (1 << i)];
            }
        }
    }

    i64 tot = (i64)n * (n - 1) / 2;

    int ans = ranges::count_if(f, [&](auto x) {
        return tot - x >= k;
    });

    cout << ans << "\n";

    return 0;
}