#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {
    int n;
    cin >> n;

    map<int, int> f;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        f[a]++;

        auto l = f.begin();
        auto r = prev(f.end());

        int ans = 0;
        if (f.size() == 2 and l->second == 1) {
            ans = r->first * 2;
        } else {
            ans = l->first + r->first;
        }

        cout << ans << " \n"[i == n - 1];
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

/*
6 2
3 2 4 5 3 6
2
2 4
3 6
*/