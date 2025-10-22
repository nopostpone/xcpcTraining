#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

constexpr i64 inf = 1e18;

constexpr void chmax(auto &a, auto b) {
    if (a < b) {
        a = b;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // dp [point x] [be positive] [be negative]
    vector<array<array<i64, 2>, 2>> dp(n);
    [&](this auto &&self, int x, int p) -> void {
        dp[x][0][0] = 0;
        dp[x][0][1] = -a[x];
        dp[x][1][0] = a[x];
        dp[x][1][1] = 0;

        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            self(y, x);
            
            array<array<i64, 2>, 2> ndp {-inf, -inf, -inf, -inf};

            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    chmax(ndp[i][j], dp[x][i][j] + dp[y][1][1]);
                    for (int k = 0; i + k < 2; k++) {
                        for (int l = 0; j + l < 2; l++) {
                            chmax(ndp[i + k][j + l], dp[x][i][j] + dp[y][k][l]);
                        }
                    }
                }
            }
            dp[x] = move(ndp);
        }
    } (0, -1);

    cout << dp[0][1][1] << "\n";

    return 0;
}