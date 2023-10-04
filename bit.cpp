// 0-indexed binary indexed tree
// Increment value at index in O(lg n) time
// Range sum query in O(lg n) time
template<typename T>
struct BIT {
    vector<T> tree;
    BIT(int n) {
        tree = vector<T>(n+1, 0);
    }

    // O(n lg n)
    BIT(vector<T> a) {
        BIT(a.size());
        for (int i = 0; i < a.size(); ++i) {
            update(i, a[i]);
        }
    }

    // Returns sum of elements from index 0 to index i (inclusive)
    // 0-indexed
    // O(lg n)
    T rsq(int i) {
        ++i;
        T sum(0);

        for (; i > 0; i -= (i & (-i)))sum += tree[i];
        return sum;
    }

    // Returns sum of elements from index l to index r (inclusive)
    // 0-indexed
    // O(lg n)
    T rsq(int l, int r) {
        return rsq(r) - rsq(l - 1);
    }

    void update(int i, T v) {
        ++i;
        for(; i < tree.size(); i += (i & (-i)))tree[i] += v;
    }
};
