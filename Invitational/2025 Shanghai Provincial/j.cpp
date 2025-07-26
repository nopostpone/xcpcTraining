#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

struct DSU {
    std::vector<int> f, siz;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) {
        return siz[find(x)];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<array<int, 2>> edges[2] {};
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;

        edges[w].push_back({u, v});
    }

    DSU dsu(n);
    for (auto [u, v] : edges[1]) {
        dsu.merge(u, v);
    }

    int ans = 0;
    for (auto [u, v] : edges[0]) {
        if (dsu.same(u, v)) {
            ans++;
        } else {
            dsu.merge(u, v);
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    for (cin >> T; T--;) {
        solve();
    }

    return 0;
}

/*
1
9 10
1 2 1
2 3 0
3 4 1
4 5 0
5 6 1
6 7 0
7 8 1
8 1 0
2 9 0
9 6 1

*/