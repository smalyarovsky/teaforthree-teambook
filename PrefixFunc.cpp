vector<int> prefix_function(string s) {
    int n = (int) s.size();
    vector<int> p(n, 0);
    for (int i = 1; i < n; i++) {
        int j = p[i - 1];
        while (s[i] != s[j] && j > 0)
            j = p[j - 1];
        if (s[i] == s[j])
            p[i] = j + 1;
    }
    return p;
}