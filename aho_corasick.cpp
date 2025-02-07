struct aho_corasick {
    static const int K = 26;

    // MEMORY SENSITIVE, CAREFUL WITH #DEFINE INT LONG LONG
    struct node {
        vector<int> term;
        int go[K], link = -1, p, c, superlink = -1;

        node(char c, int p = -1) : c(c), p(p) {
            fill(go, go + K, -1);
        }
    };

    vector<node> t = {node(0)};

    void add(string &s, int i) {
        int v = 0;
        for (char c : s) {
            if (t[v].go[c - 'a'] == -1) {
                t[v].go[c - 'a'] = (int) t.size();
                t.emplace_back(c - 'a', v);
            }
            v = t[v].go[c - 'a'];
        }
        t[v].term.push_back(i);
    }

    aho_corasick(vector<string> &a) {
        for (int i = 0; i < a.size(); ++i) {
            add(a[i], i);
        }
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (v == 0 || t[v].p == 0) {
                t[v].link = 0;
                t[v].superlink = 0;
            } else {
                t[v].link = t[t[t[v].p].link].go[t[v].c];
                if (!t[t[v].link].term.empty()) {
                    t[v].superlink = t[v].link;
                } else {
                    t[v].superlink = t[t[v].link].superlink;
                }
            }
            for (int c = 0; c < K; ++c) {
                if (t[v].go[c] != -1) {
                    q.push(t[v].go[c]);
                } else if (v == 0) {
                    t[v].go[c] = 0;
                } else {
                    t[v].go[c] = t[t[v].link].go[c];
                }
            }
        }
    }

    int go(int v, int c) {
        return t[v].go[c];
    }
};
