#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

template <class Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;

    SegmentTree() = delete;
    SegmentTree(int n_, const Info &v_ = {}) { init(std::vector<Info>(n_, v_)); }
    template <class T>
    SegmentTree(const std::vector<T> &data) {
        init(data);
    }

    template <class T>
    void init(const std::vector<T> &data) {
        n = data.size();
        info.assign(4 << std::__lg(n), {});
        auto build = [&](auto &self, int p, int l, int r) -> void {
            if (r - l == 1) {
                info[p] = data[l];
                return;
            }
            int m = (l + r) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
            pull(p);
        };
        build(build, 1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return {};
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    template <class F>
    int findFirst(int p, int l, int r, int x, int y, const F &pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template <class F>
    int findFirst(int l, int r, const F &pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template <class F>
    int findLast(int p, int l, int r, int x, int y, const F &pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template <class F>
    int findLast(int l, int r, const F &pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

constexpr int inf = 1e9;

struct Info {
    int max = -inf;
};

Info operator+(const Info &a, const Info &b) {
    return {std::max(a.max, b.max)};
}

template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;

    Fenwick(int n_ = 0) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> y[i];
    }

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);

    vector<int> L(n);
    {
        SegmentTree<Info> seg(n);
        ranges::sort(ord, [&](int i, int j) {
            return make_tuple(x[i], y[i], -i) > make_tuple(x[j], y[j], -j);
        });
        for (auto i : ord) {
            int p = seg.findLast(0, i, [&](auto v) {
                return v.max >= y[i];
            });
            L[i] = p;

            seg.modify(i, {y[i]});   
        }
    }
    vector<int> R(n);
    {
        SegmentTree<Info> seg(n);
        ranges::sort(ord, [&](int i, int j) {
            return make_tuple(x[i], y[i], i) > make_tuple(x[j], y[j], j);
        });
        for (auto i : ord) {
            int q = seg.findFirst(i + 1, n, [&](auto v) {
                return v.max >= y[i];
            });
            R[i] = (q == -1 ? n + 1 : q);
        
            seg.modify(i, {y[i]});   
        }
    }
    // { [i, R[i]), add / del }
    vector<vector<tuple<int, int, int>>> e(n + 1);
    for (int i = 0; i < n; i++) {
        // [L[i] + 1, i)
        e[L[i] + 1].emplace_back(i, R[i], 1);
        e[i + 1].emplace_back(i, R[i], -1);
    }
    // {r, i}
    vector<vector<pair<int, int>>> que(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        que[l].emplace_back(r, i);
    }
    
    vector<int> ans(q);
    Fenwick<int> fen(n + 2);
    for (int l = 0; l < n; l++) {
        for (auto [x, y, i] : e[l]) {
            fen.add(x, i);
            fen.add(y, -i);
        }
        for (auto [r, i] : que[l]) {
            ans[i] = fen.sum(r);
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}

/*
8 7
1 9 7 8 0 7 2 3
19 20 5 6 1 14 9 5
1 8
3 7
2 6
4 4
5 7
3 8
6 7
*/