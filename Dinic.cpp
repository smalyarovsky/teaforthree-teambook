struct Dinic {
    const int INF = INT_MAX;

    struct e {
        int u, c, f;
        e(int u, int c): u(u), c(c), f(0) {}
    };
    
    int n, m;
    vector<e> edges;
    vector<vector<int>> g;
    vector<int> d, ptrs;

    Dinic() = default;
    Dinic(int n, int m) {
        this->n = n;
        this->m = m;
        edges.clear();
        g.assign(n, {});
        d.assign(n, INF);
        ptrs.assign(n, 0);
    }
    
    void addEdge(int v, int u, int c) {
        int sz = (int)edges.size();
        edges.emplace_back(u, c);
        edges.emplace_back(v, 0);
        g[v].push_back(sz);
        g[u].push_back(sz + 1);
    }
    
    bool bfs(int s, int t) {
        queue<int> q;
        q.push(s);
        d.assign(n, -1);
        d[s] = 0;
    
        while (!q.empty()) {
            int v = q.front();
            q.pop();
    
            for (int i : g[v]) {
                if (edges[i].c - edges[i].f > 0 && d[edges[i].u] == -1) {
                    d[edges[i].u] = d[v] + 1;
                    q.push(edges[i].u);
                }
            }
        }
        return (d[t] != -1);
    }
    
    int dfs(int v, int t, int flow) {
        if (flow == 0 || v == t) return flow;
        if (d[v] >= d[t] && v != t) return 0;
    
        for (; ptrs[v] < (int)g[v].size(); ptrs[v]++) {
            int i = g[v][ptrs[v]];
            if (d[edges[i].u] == d[v] + 1 && edges[i].c - edges[i].f > 0) {
                int fl = dfs(edges[i].u, t, min(flow, edges[i].c - edges[i].f));
                if (fl == 0) continue;
    
                edges[i].f += fl;
                edges[i ^ 1].f -= fl;
                return fl;
            }
        }
        return 0;
    }
    
    int dinicAlgo(int s, int t) {
        int flow = 0, it = 0;
        while (bfs(s, t)) {
            ptrs.assign(n, 0);
            int f;
            while ((f = dfs(s, t, INF))) {
                flow += f;
            }
            it++;
        }
        return flow;
    }
};