// from Jiangly
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 x;
    cin >> x;

    vector<int> a;
    auto dfs = [&](this auto &&self, i64 res, int n, int lst) -> void {
        if (res == x) {
            cout << "Yes\n" << n << "\n";
            vector<int> ans;
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < a[i]; j++) {
                    ans.push_back(i + 1);
                }
            }
            for (int i = 0; i < n; i++) {
                cout << ans[i] << " \n"[i == n - 1];
            }

            exit(0);
        }

        for (int i = 1; i <= lst; i++) {
            i64 val = (res << i) + (1ll << (n + i)) - (1ll << n);

            if (val > x) {
                break;
            }
            a.push_back(i);
            self(val, n + i, i);

            a.pop_back();
        }
    };
    dfs(0, 0, 60);

    cout << "No\n";

    return 0;
}