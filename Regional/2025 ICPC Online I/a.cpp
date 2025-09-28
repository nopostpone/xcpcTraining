#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    set<string> all;

    map<string, int> cnt;
    map<string, int> pen;

    array<map<string, int>, 26> unk; // unk team -> pena

    array<map<string, int>, 26> ac;
    array<map<string, int>, 26> rej;

    vector<tuple<string, string, int, string>> info(n);
    for (auto &[team, id, t, res] : info) {
        cin >> team >> id >> t >> res;
        all.insert(team);
    }

    sort(info.begin(), info.end(), 
        [](auto a, auto b) {
            return get<2>(a) < get<2>(b);
        });

    for (auto [team, id, t, res] : info) {
        int x = id[0] - 'A';
        if (ac[x].contains(team)) {
            continue;
        }

        if (res == "Accepted") {

            ac[x][team] = t;
            if (rej[x].contains(team)) {
                ac[x][team] += 20 * rej[x][team];
            }

        } else if (res == "Rejected") {
            rej[x][team]++;
        } else {

            if (not unk[x].contains(team)) {
                unk[x][team] = t;

                if (rej[x].contains(team)) {
                    unk[x][team] += 20 * rej[x][team];
                }
            }
        }
    }

    for (int x = 0; x < 26; x++) {
        for (auto [team, pt] : ac[x]) {
            cnt[team]++;
            pen[team] += pt;
        }
    }

    pair<int, int> best{};
    for (auto team : all) {
        best = max(best, pair(cnt[team], -pen[team]));
    }

    set<string> win;

    for (auto team : all) {
        auto [posic, posip] = pair(cnt[team], -pen[team]);
        for (int x = 0; x < 26; x++) {
            if (unk[x].contains(team)) {
                posic++;
                posip -= unk[x][team];
            }
        }

        if (pair(posic, posip) >= best) {
            win.insert(team);
        }
    }
    for (auto s : win) {
        cout << s << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }    
}

/*
1
4
ASYYPIbf7 D 268 Unknown
3NhYHv8w B 13 Accepted
ASYYPIbf7 B 173 Accepted
dnrkAsPqrA A 107 Accepted
*/