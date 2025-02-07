struct SufArray {
    vector<int> buildSuf(vector<int> s) {
        int n = (int) s.size();
        vector<int> suf(n), suf1(n), c(n), cn(n), pos(n);
        int col = -1;
        vector<pair<int, int>> srt;
        for (int i = 0; i < n; i++) srt.emplace_back(s[i], i);
        sort(srt.begin(), srt.end());
        for (int i = 0; i < n; i++) {
            suf[i] = srt[i].second;
            if (i == 0 || srt[i].first != srt[i - 1].first) {
                col++;
                pos[col] = i;
            }
            c[srt[i].second] = col;
        }

        int l = 1;
        while (l < n) {
            for (int i = 0; i < n; i++) {
                int j = (suf[i] - l + n) % n;
                suf1[pos[c[j]]++] = j;
            }
            col = -1;
            for (int i = 0; i < n; i++) {
                if (i == 0 || c[suf1[i]] != c[suf1[i - 1]] || c[(suf1[i] + l) % n] != c[(suf1[i - 1] + l) % n]) {
                    col++;
                    pos[col] = i;
                }
                cn[suf1[i]] = col;
            }
            swap(suf, suf1);
            swap(c, cn);
            l <<= 1;
        }
        return suf;
    }

    vector<int> buildLCP(vector<int> s, vector<int>& suf) {
        int n = s.size();
        vector<int> lcp(n - 1), pos(n);
        for (int i = 0; i < n; i++) pos[suf[i]] = i;

        int k = 0;
        for (int i = 0; i < n; i++) {
            if (k > 0) k--;
            if (pos[i] == n - 1) continue;

            int j = suf[pos[i] + 1];
            while (max(i + k, j + k) < n && s[i + k] == s[j + k]) k++;
            lcp[pos[i]] = k;
        }
        return lcp;
    }
};