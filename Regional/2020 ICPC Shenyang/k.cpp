#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        char c;
        int x;
        cin >> c >> x;

        a[i] = pair(x, c == '+');
    }

    ranges::sort(a, greater());
    double ans = 0;

    int pos[2] {};
    int neg[2] {};
    
    for (int i = 0; i < n; i++) {
        neg[1 - a[i].second]++;
    }

    double lst = 0;
    for (int l = 0, r; l < n; l = r) {
        r = l;
        while (r < n and a[l].first == a[r].first) {
            r++;
        }
        for (int i = l; i < r; i++) {
            if (a[i].second) {
                neg[0]--;
                pos[1]++;
            } else {
                neg[1]--;
                pos[0]++;
            }
        }

        double tpr = double(pos[1]) / (pos[1] + neg[0]);
        double fpr = double(pos[0]) / (pos[0] + neg[1]);

        ans += (1 - fpr) * (tpr - lst);
        lst = tpr;
    }

    cout << ans << endl;

    return 0;
}

/*
8
+ 34
+ 33
+ 26
- 34
- 38
+ 39
- 7
- 27
*/