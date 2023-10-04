class UnionFind {
    int num_sets;
    vector<int> p, rnk, sz;

    UnionFind(int n) {
        num_sets = n;
        p = vector<int>(n);
        iota(begin(p), end(p),0);
        rnk = vector<int>(n,0);
        sz = vector<int>(n,1);
    }
 
    int find(int i) {
        if (p[i] == i)return i;
        return p[i] = find(p[i]);
    }
 
    bool check(int i, int j) {
        return find(i)==find(j);
    }
 
    // Return false if i and j are already in the same set
    // Return true  if the two sets were merged
    bool join(int i, int j) {
        i = find(i);
        j = find(j);
        if (i == j)return 0;
        if (rnk[i] < rnk[j]) {
            sz[j] += sz[i];
            p[i] = j;
        } else {
            sz[i] += sz[j];
            p[j] = i;
            if (rnk[i] == rnk[j]) {
                ++rnk[i];
            }
        }
        --num_sets;
        return 1;
    }
};
