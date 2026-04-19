#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<pair<int, int>> path;

    vector<int> f(n, -1);
    [&](this auto &&self, int x, int p) -> void {
        vector<int> stk;
        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            self(y, x);
            if (f[y] != -1) {
                stk.push_back(f[y]);
            }
        }
        if (stk.empty()) {
            stk.push_back(x);
        }
        while (stk.size() > 1) {
            int u = stk.back();
            stk.pop_back();
            int v = stk.back();
            stk.pop_back();

            path.emplace_back(u, v);
        }

        if (not stk.empty()) {
            if (x == 0) {
                path.emplace_back(0, stk[0]);
            } else {
                f[x] = stk[0];
            }
        }
    } (0, -1); 

    reverse(path.begin(), path.end());
    cout << path.size() << "\n";
    for (auto [u, v] : path) {
        cout << u + 1 << " " << v + 1 << "\n";
    }
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