struct TwoSat {
    int n;
    vector<vector<int>> e;
    vector<bool> ans;

    TwoSat(int n) : n(n), e(2 * n), ans(n) {}

    TwoSat() = default;

    void either(int u, bool f, int v, bool g) {
        e[2 * u + !f].push_back(2 * v + g);
        e[2 * v + !g].push_back(2 * u + f);
    }

    void setValue(int v, bool f) {
        either(v, f, v, f);
    }

    void equal(int a, int b) {
        either(a, false, b, true);
        either(b, false, a, true);
    }

    void not_equal(int a, int b) {
        either(a, true, b, true);
        either(a, false, b, false);
    }

    bool satisfiable() {
        vector<int> id(2 * n, -1), tin(2 * n, -1), fup(2 * n, -1);
        vector<int> stk;
        int T = 0, cnt = 0;
        function<void(int)> tarjan = [&](int u) {
            stk.push_back(u);
            tin[u] = fup[u] = T++;
            for (auto v: e[u]) {
                if (tin[v] == -1) {
                    tarjan(v);
                    fup[u] = min(fup[u], fup[v]);
                } else if (id[v] == -1) {
                    fup[u] = min(fup[u], tin[v]);
                }
            }
            if (tin[u] == fup[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
                ++cnt;
            }
        };
        for (int i = 0; i < 2 * n; ++i) if (tin[i] == -1) tarjan(i);
        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }

    vector<bool> answer() { return ans; }
};