#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

bool chmax(auto &a, auto b) {
    if (b > a) {
        a = b;
        return true;
    }
    return false;
}

void prepare() {
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

    vector<array<int, 2>> dp(n);
    vector<int> f(n, -1);

    [&](this auto &&self, int x, int p) -> void {
        dp[x][1] = 1;
        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            self(y, x);
            dp[x][0] += dp[y][0];
            dp[x][1] += dp[y][0];
        }

        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            if (chmax(dp[x][0], dp[x][0] - dp[y][0] + dp[y][1])) {
                f[x] = y;
            }
        }

    } (0, -1);

    string ans(n, '0');
    [&](this auto &&self, int x, int p) -> void {
        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            ans[y] = ans[x] ^ (f[x] == y);

            self(y, x);
        }
    } (0, -1);

    cout << ans.substr(1) << endl;
}

void play() {
    int n;
    string s;
    cin >> n >> s;
    s = '0'  + s;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        if (s[u] != s[v]) {
            cout << "take" << endl;
        } else {
            cout << "ignore" << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string op;
    cin >> op;

    if (op == "prepare") {
        prepare();
    } else {
        play();
    }

    return 0;
}

/*
prepare      
3
1 2
1 3
*/