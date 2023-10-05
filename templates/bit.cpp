// 0 indexed fenwick tree
template<typename t = long long>
struct FenwickTree {
    int n;
    vector<t> tree;
    FenwickTree(int _n) {
        n = _n+1;
        tree = vector<t>(n, t(0));
    }

    t query(int i) {
        ++i;

        t sum(0);
        for (; i > 0; i -= (i & (-i)))sum += tree[i];
        return sum;
    }

    t query(int i, int j) {
        return query(j) - query(i-1);
    }

    void add(int i, t val) {
        ++i;
        for (; i < n; i += (i & (-i))) {
            tree[i] += val;
        }
    }
};
