struct FFT {
    constexpr int FFT_LG = 20, FFT_N = 1 << FFT_LG;
    const double PI = acos(-1);
    complex<double> roots[FFT_N];

    void init_roots() {
        for (int i = 0; i < FFT_N / 2; ++i) {
            auto alp = 2 * PI * i / FFT_N;
            roots[i + FFT_N / 2] = {cos(alp), sin(alp)};
        }
        for (int i = FFT_N / 2 - 1; i > -1; --i) {
            roots[i] = roots[i << 1];
        }
    }

    vector<int> rev;

    void dft(vector<complex<double>> &a) {
        int n = (int) a.size();
        if (n == 1) return;

        if ((int) rev.size() != n) {
            int k = __builtin_ctz(n) - 1;
            rev.resize(n);
            for (int i = 0; i < n; ++i) {
                rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
            }
        }

        for (int i = 0; i < n; ++i) {
            if (rev[i] < i) {
                swap(a[rev[i]], a[i]);
            }
        }

        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += k << 1) {
                for (int j = 0; j < k; ++j) {
                    auto u = a[i + j], v = a[i + j + k] * roots[k + j];
                    a[i + j] = u + v;
                    a[i + j + k] = u - v;
                }
            }
        }
    }

    void idft(vector<complex<double>> &a) {
        int n = (int) a.size();
        reverse(a.begin() + 1, a.end());
        dft(a);
        for (auto &v: a) v /= n;
    }

    vector<ll> mul(vector<int> &a, vector<int> &b) {
        if (a.empty() || b.empty()) {
            return {};
        }
        int sz = 1, tot = int(a.size() + b.size() - 1);
        while (sz < tot) sz <<= 1;

        vector<complex<double>> new_a(sz), new_b(sz);
        for (int i = 0; i < (int) a.size(); ++i) new_a[i] = a[i];
        for (int i = 0; i < (int) b.size(); ++i) new_b[i] = b[i];

        dft(new_a), dft(new_b);
        for (int i = 0; i < sz; ++i) {
            new_a[i] *= new_b[i];
        }
        idft(new_a);
        vector<ll> ans(tot);
        for (int i = 0; i < tot; ++i) {
            ans[i] = round(new_a[i].real());
        }
        return ans;
    }
};