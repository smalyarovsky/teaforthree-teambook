struct LiChaoTree {
    const long long inf = 3e18;
    struct line {
        long long k = 0, b = -inf;
    
        line() = default;
    
        line(long long a, long long _b) {
            k = a, b = _b;
        }
    
        long long eval(long long x) {
            return k * x + b;
        }
    };

    vector<line> t;
    int sz;
    vector<int> left, right;

    LiChaoTree(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        t.assign(sz << 1, {}), left.resize(sz << 1), right.resize(sz << 1);
        for (int i = 0; i < sz; ++i) {
            left[i + sz] = i;
            right[i + sz] = i + 1;
        }
        for (int i = sz - 1; i > 0; --i) {
            left[i] = left[i << 1];
            right[i] = right[i << 1 | 1];
        }
    }

    LiChaoTree() = default;

    long long query(int i) {
        long long ans = -inf;
        int x = i + sz;
        while (x > 0) {
            ans = max(ans, t[x].eval(i));
            x >>= 1;
        }
        return ans;
    }

    void update(int x, int lx, int rx, line L) {
        int mid = (lx + rx) >> 1;
        if (t[x].eval(mid) < L.eval(mid)) {
            swap(t[x], L);
        }
        if (lx + 1 == rx) {
            return;
        }
        if (L.k > t[x].k) {
            update(x << 1 | 1, mid, rx, L);
        } else {
            update(x << 1, lx, mid, L);
        }
    }

    void insert(line L) {
        update(1, 0, sz, L);
    }

    void insert(int l, int r, line L) {
        l += sz;
        r += sz;
        while (l < r) {
            if (l & 1) {
                update(l, left[l], right[l], L);
                ++l;
            }
            if (r & 1) {
                --r;
                update(r, left[r], right[r], L);
            }
            l >>= 1;
            r >>= 1;
        }
    }
};
