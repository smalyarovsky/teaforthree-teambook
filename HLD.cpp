class HLD {
    public:
        vector<int> par, siz, head, tin, tout, ord;
    
        int dfs1(int i, vector<vector<int>> &g) {
            for (auto &t: g[i])
                if (t != par[i]) {
                    par[t] = i;
                    siz[i] += dfs1(t, g);
                    if (siz[t] > siz[g[i][0]] || g[i][0] == par[i]) swap(t, g[i][0]);
                }
            return siz[i];
        }
    
        void dfs2(int i, int &x, const vector<vector<int>> &g) {
            tin[i] = x;
            ++x;
            for (auto t: g[i])
                if (t != par[i]) {
                    head[t] = (x == tin[i] + 1 ? head[i] : t);
                    dfs2(t, x, g);
                }
            tout[i] = x;
        }
    
        // Assumes the tree is connected and r is the root
        HLD(vector<vector<int>> g, int r = 0)
                : par(g.size(), -1), siz(g.size(), 1), head(g.size(), r), tin(g.size()), ord(g.size()), tout(g.size()) {
            dfs1(r, g);
            int x = 0;
            dfs2(r, x, g);
            for (int i = 0; i < g.size(); ++i) ord[tin[i]] = i;
        }
    
        // Returns intervals corresponding to the path between a and b in descending order
        vector<pair<int, int>> path(int a, int b) {
            vector<pair<int, int>> res;
            for (;; b = par[head[b]]) {
                if (tin[b] < tin[a]) swap(a, b);
                if (tin[head[b]] <= tin[a]) {
                    res.emplace_back(tin[a], tin[b] + 1);
                    return res;
                }
                res.emplace_back(tin[head[b]], tin[b] + 1);
            }
        }
    
        // Returns interval corresponding to the subtree of node i
        pair<int, int> subtree(int i) {
            return {tin[i], tin[i] + siz[i]};
        }
    
        int lca(int a, int b) {
            for (;; b = par[head[b]]) {
                if (tin[b] < tin[a]) swap(a, b);
                if (tin[head[b]] <= tin[a]) return a;
            }
        }
    
        bool isp(int a, int b) {
            return tin[a] <= tin[b] && tout[a] >= tout[b];
        }
    };