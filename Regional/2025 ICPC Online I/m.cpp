#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

constexpr i64 inf = 1e18;

constexpr void chmin(auto &x, auto y) {
    if (y < x) {
        x = y;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> p(n, -1), pw(n), ord;
    [&](this auto &&self, int x) -> void {
        ord.push_back(x);
        for (auto [y, w] : adj[x]) {
            if (y == p[x]) {
                continue;
            }

            p[y] = x;
            pw[y] = w;
            self(y);
        }
    } (0);

    vector<i64> dp(n, inf);
    dp[0] = 0;

    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        edges.emplace_back(u, v);
        edges.emplace_back(v, u);
    }

    for (int t = 0; t <= n; t++) {
        for (int i = n - 1; i > 0; i--) {
            int x = ord[i];
            chmin(dp[p[x]], dp[x] + pw[x]);
        }
        for (int i = 1; i < n; i++) {
            int x = ord[i];
            chmin(dp[x], dp[p[x]] + pw[x]);
        }

        cout << accumulate(dp.begin(), dp.end(), i64()) << "\n";

        auto ndp = dp;
        for (auto [u, v] : edges) {
            chmin(ndp[v], dp[u]);
        }
        dp = move(ndp);
    }

    return 0;
}