#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

template <class Info, class Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;

    LazySegmentTree() = delete;
    LazySegmentTree(int n_, const Info &v_ = {}) { init(std::vector<Info>(n_, v_)); }
    LazySegmentTree(const std::vector<Info> &data) { init(data); }

    void init(const std::vector<Info> &data) {
        n = data.size();
        info.assign(4 << std::__lg(n), {});
        tag.assign(4 << std::__lg(n), {});

        auto build = [&](auto self, int p, int l, int r) -> void {
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
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = {};
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
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
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
    template <class F>
    int findFirst(int p, int l, int r, int x, int y, const F &pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        push(p);
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
        push(p);
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

    void rangeGcd(int p, int l, int r, int x, int y, int v) {
        if (l >= y or r <= x) {
            return;
        }

        if (l >= x and r <= y) {
            if (v % info[p].lcm == 0) {
                return;
            }
            if (info[p].sum % info[p].act == 0 and info[p].sum / info[p].act == info[p].lcm) {
                apply(p, {__gcd<int>(info[p].lcm, v)});
                return;
            }
        }
        int m = (l + r) / 2;

        push(p);
        rangeGcd(p * 2, l, m, x, y, v);
        rangeGcd(p * 2 + 1, m, r, x, y, v);
        pull(p);
    };
    void rangeGcd(int l, int r, int x) {
        return rangeGcd(1, 0, n, l, r, x);
    }
};

constexpr i64 inf = (1 << 30);

struct Tag {
    int cov = 0;

    void apply(const Tag &t) {
        if (t.cov) {
            cov = t.cov;
        }
    }
};

struct Info {
    i64 act = 0;
    i64 sum = 0;
    i64 lcm = 1;

    void apply(const Tag &t) {
        if (t.cov) {
            lcm = t.cov;
            sum = act * t.cov;
        }
    }
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.act = a.act + b.act;
    c.sum = a.sum + b.sum;
    
    if (a.lcm > inf) {
        c.lcm = a.lcm;
    } else if (b.lcm > inf) {
        c.lcm = b.lcm;
    } else {
        c.lcm = lcm(a.lcm, b.lcm);
    }

    return c;
}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<Info> info(n);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        info[i] = {1, a, a};
    }
    LazySegmentTree<Info, Tag> seg(info);

    while (q--) {
        int o, l, r, x;
        cin >> o >> l >> r >> x;
        l--;

        if (o) {
            seg.rangeGcd(l, r, x);
            cout << seg.rangeQuery(l, r).sum << "\n";
        } else {
            seg.rangeApply(l, r, {x});
        }

    }
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