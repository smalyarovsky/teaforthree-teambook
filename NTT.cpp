#include <bits/stdc++.h>

using namespace std;

struct NTT {
    constexpr int MOD = 998244353;

    int norm(int x) {
        if (x < 0) {
            x += MOD;
        }
        if (x >= MOD) {
            x -= MOD;
        }
        return x;
    }

    int add(int a, int b) {
        return a + b < MOD ? a + b : a + b - MOD;
    }

    int mul(int a, int b) {
        return a * (long long) b % MOD;
    }

    int sub(int a, int b) {
        return a >= b ? a - b : a - b + MOD;
    }

    int power(int a, long long p) {
        int ans = 1;
        for (; p > 0; p >>= 1, a = mul(a, a)) {
            if (p & 1) {
                ans = mul(ans, a);
            }
        }
        return ans;
    }

    int inv(int a) {
        return power(a, MOD - 2);
    }

    vector<int> rev;
    vector<int> roots{0, 1};

    void dft(vector<int> &a) {
        int n = (int) a.size();
        if (n == 1) return;

        if (int(rev.size()) != n) {
            int k = __builtin_ctz(n) - 1;
            rev.resize(n);
            for (int i = 0; i < n; i++) {
                rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
            }
        }

        for (int i = 0; i < n; i++) {
            if (rev[i] < i) {
                std::swap(a[i], a[rev[i]]);
            }
        }
        if (int(roots.size()) < n) {
            int k = __builtin_ctz(roots.size());
            roots.resize(n);
            while ((1 << k) < n) {
                int e = power(int(3), (MOD - 1) >> (k + 1));
                for (int i = 1 << (k - 1); i < (1 << k); i++) {
                    roots[i << 1] = roots[i];
                    roots[i << 1 | 1] = mul(roots[i], e);
                }
                k++;
            }
        }
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += k << 1) {
                for (int j = 0; j < k; ++j) {
                    int u = a[i + j], v = mul(a[i + j + k], roots[k + j]);
                    a[i + j] = add(u, v);
                    a[i + j + k] = sub(u, v);
                }
            }
        }
    }

    void idft(vector<int> &a) {
        int n = (int) a.size();
        reverse(a.begin() + 1, a.end());
        dft(a);
        int inverse = norm((1 - MOD) / n);
        for (auto &v: a) v = mul(v, inverse);
    }

    vector<int> mul(vector<int> a, vector<int> b) {
        if (a.empty() || b.empty()) {
            return {};
        }
        int sz = 1, tot = int(a.size() + b.size() - 1);
        while (sz < tot) sz <<= 1;
        a.resize(sz), b.resize(sz);
        dft(a);
        dft(b);
        for (int i = 0; i < sz; ++i) {
            a[i] = mul(a[i], b[i]);
        }
        idft(a);
        a.resize(tot);
        return a;
    }
};