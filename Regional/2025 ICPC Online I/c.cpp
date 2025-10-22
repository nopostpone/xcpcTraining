#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

void solve() {
    int m, n;
    cin >> m >> n;

    map<int, vector<int>> f;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        f[l].push_back(r);
    }

    priority_queue<int, vector<int>, greater<>> q;
    int ans = n;

    for (const auto &[l, vec] : f) {
        int nl = (l == f.rbegin()->first ? n : f.upper_bound(l)->first);
        for (auto r : vec) {
            q.push(r);
        }
        for (int j = l; j < nl; j++) {
            while (not q.empty() and q.top() <= j) {
                q.pop();
            }
            if (q.empty()) {
                break;
            }
            ans--;
            q.pop();
        }
    }

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