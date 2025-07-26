#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(3);

    int x;
    cin >> x;

    double y = double(x) / 100;
    double ans = 50. + 50. * y;

    cout << "Vivo " << ans << "\n";

    return 0;
}