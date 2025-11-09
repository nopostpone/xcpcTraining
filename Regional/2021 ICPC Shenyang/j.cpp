#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    array<int, 10000> dp {};
    dp.fill(inf);
    dp[0] = 0;

    queue<int> q;
    q.push(0);

    while (not q.empty()) {
        int x = q.front();
        string s = to_string(x);

        q.pop();

        while (s.size() < 4) {
            s = '0' + s;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = i; j < 4; j++) {
                auto t = s;
                for (int k = i; k <= j; k++) {
                    t[k] = (t[k] - '0' + 1) % 10 + '0';
                }
                if (dp[stoi(t)] > dp[stoi(s)] + 1) {
                    dp[stoi(t)] = dp[stoi(s)] + 1;
                    q.push(stoi(t));
                }

                t = s;
                for (int k = i; k <= j; k++) {
                    t[k] = (t[k] - '0' + 9) % 10 + '0';
                }
                if (dp[stoi(t)] > dp[stoi(s)] + 1) {
                    dp[stoi(t)] = dp[stoi(s)] + 1;
                    q.push(stoi(t));
                }

            }
        }
    }

    int t;
    cin >> t;

    while (t--) {
        string s, t;
        cin >> s >> t;

        for (int i = 0; i < 4; i++) {
            t[i] = (t[i] - s[i] + 10) % 10 + '0';
        }
        cout << dp[stoi(t)] << "\n";
    }
}