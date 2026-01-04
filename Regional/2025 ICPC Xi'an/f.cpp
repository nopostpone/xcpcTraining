#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> t(n);
    vector<vector<int>> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
        t[i]--;
        vec[t[i]].push_back(i);
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] *= 2;
    }
    vector<bool> face(n);
    for (int i = 0; i < n; i++) {
        int j = t[i];
        if (a[j] > a[i]) {
            face[i] = true;
        }
    }

    vector<bool> vis(n);
    vector<int> b(n);

    auto upd = [&](int x, int y) {
        assert(vis[x]);
        if (face[x] != face[y]) {
            int mid = (a[x] + a[y]) / 2;
            int dis = std::abs(a[x] - a[y]);
            if (std::abs(a[x] - b[x]) > dis / 2) {
                b[y] = mid;
            } else {
                b[y] = b[x];
            }
        } else {
            b[y] = b[x];
        }
    };

    auto dfs = [&](auto &&self, int x) -> void {
        
        for (auto y : vec[x]) {
            if (vis[y]) {
                continue;
            }
            vis[y] = true;
            upd(x, y);

            self(self, y);
        }
    };

    set<pair<int, int>> cand;
    for (int i = 0; i < n; i++) {
        int j = t[i];
        if (face[i] != face[j]) {
            cand.emplace(std::abs(a[i] - a[j]), i);
        }
    }
    while (not cand.empty()) {
        auto [dis, x] = *cand.begin();
        cand.erase(cand.begin());

        if (vis[x]) {
            continue;
        }
        int y = t[x];

        if (vis[y]) {
            int mid = (a[x] + a[y]) / 2;
            int dis = std::abs(a[x] - a[y]);
            if (std::abs(a[y] - b[y]) > dis / 2) {
                b[x] = mid;
            } else {
                b[x] = b[y];
            }
        } else {
            int mid = (a[x] + a[y]) / 2;
            b[x] = mid;
        }
        vis[x] = true;
        dfs(dfs, x);
    }

    for (int i = 0; i < n; i++) {
        assert(vis[i]);
        cout << std::abs(b[i] - a[i]) << " \n"[i == n - 1];
    }

    return 0;
}

/*
3
2 3 1
-1 2 3

10
8 3 6 7 1 8 2 10 8 1
0 -14 5 -3 14 -12 11 8 -18 17
*/