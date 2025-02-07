struct hld {
    const int maxn = 50001;
    int dp[maxn];
    bool used[maxn];
    vector<vector<int>> r(maxn);
    vector<int> pr(maxn);
    int dist[maxn];
    int dfs1(int v, int pred){
        used[v] = true;
        pr[v] = pred;
        if(v==0) dist[v] = 0;
        else dist[v] = dist[pred]+1;
        dp[v] = 1;
        for(int g: r[v]){
            if(used[g]) continue;
            dp[v] += dfs1(g,v);
        }
        return dp[v];
    }
    vector<int> euler_tour;
    int head[maxn];
    int pos[maxn];
    void tour (int v, int origin){
        // cerr << v << ' ' << origin << endl;
        head[v] = origin;
        pos[v] = euler_tour.size();
        used[v] = true;
        euler_tour.push_back(v);
        int heavy = -1, heavyd = -1;
        for(int g: r[v]){
            if(used[g]) continue;
            if(dp[g] > heavyd){
                heavyd = dp[g]; heavy = g;
            }
        }
        if(heavy == -1) return;
        tour(heavy,origin);
        for(int g: r[v]){
            if(used[g]) continue;
            if(g==heavy) continue;
            tour(g,g);
        }
    }
    int lca(int a, int b){
        if(head[a] == head[b]) {
            if(dist[a] < dist[b]) return a;
            else return b;
        }
        if(dist[head[a]] < dist[head[b]]){
            b= pr[head[b]];
        }
        else {
            a = pr[head[a]];
        }
        return lca(a,b);
    }
};