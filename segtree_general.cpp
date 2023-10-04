// General segment tree implementation 
// working on an underlying vector of integers (long long)
// T_node is a node struct where you can define custom behaviour
// for merging elements and updating
// See node example further below
//
// T_node must support
// empty constructor
// value constructor
// operator+: (pull)
//      assosiative
//      (identity)
// push(&lchild, &rchild)
template<typename T_node>
struct SegmentTree {
    using ll = long long;

    int arr_size;
    vector<ll> arr;
    vector<T_node> tree;
 
    int left(int p) { return p<<1; }
    int right(int p) { return p<<1|1; }
 
    SegmentTree(vector<ll> arr) {
        this->arr = arr;
        arr_size = arr.size();
        tree = vector<T_node>(arr_size<<2);
 
        build(1, 0, arr_size - 1);
    }
 
    void nodePush(int p, int l, int r) {
        if (l == r)tree[p].push(nullptr, nullptr);
        else tree[p].push(&tree[left(p)], &tree[right(p)]);
    }
 
    void build(int p, int l, int r) {
        if (l == r) {
            tree[p] = T_node(arr[l], l);
            return;
        }
 
        int mid = (l+r)>>1;
 
        build(p<<1, l, mid);
        build(p<<1|1, mid+1, r);
 
        tree[p] = tree[p<<1] + tree[p<<1|1];
    }
 
    ll query(int p, int l, int r, int i, int j) {
        if (r < i || j < l) {
            return 0;
        }
 
        // always push first
        nodePush(p, l, r);
 
        if (i <= l && r <= j) {
            return tree[p].val;
        }
 
        int mid = (l+r)>>1;
        return query(p<<1, l, mid, i, j) + query(p<<1|1, mid+1, r, i, j);
    }
 
 
    void updateInc(int p, int l, int r, int i, int j, ll val) {
        if (r < i || j < l) {
            return;
        }
 
        // check if we can stop
        if (i <= l && r <= j) {
            tree[p].incVal += val;
            return;
        }
 
        // always push
        nodePush(p, l, r);
 
        int mid = (l+r)>>1;
 
        updateInc(p<<1, l, mid, i, j, val);
        updateInc(p<<1|1, mid+1, r, i, j, val);
 
        nodePush(left(p), l, mid);
        nodePush(right(p), mid+1, r);
 
        tree[p] = tree[p<<1] + tree[p<<1|1];
    }
 
 
    void updateSet(int p, int l, int r, int i, int j, ll val) {
        if (r < i || j < l) {
            return;
        }
 
        if (i <= l && r <= j) {
            tree[p].shouldSet = 1;
            tree[p].setVal = val;
            tree[p].incVal = 0;
            return;
        }
 
        nodePush(p, l, r);
 
        int mid = (l+r)>>1;
        updateSet(p<<1, l, mid, i, j, val);
        updateSet(p<<1|1, mid+1, r, i, j, val);
 
        nodePush(left(p), l, mid);
        nodePush(right(p), mid+1, r);
 
        tree[p] = tree[p<<1] + tree[p<<1|1];
    }
 
    ll query(int i, int j) {
        return query(1, 0, n - 1, i, j);
    }
 
    void updateInc(int i, int j, ll val) {
        updateInc(1, 0, n - 1, i, j, val);
    }
 
    void updateSet(int i, int j, ll val) {
        updateSet(1, 0, n - 1, i, j, val);
    }
};


// Example node
struct node {
    ll setVal = 0;
    bool shouldSet = false;
    ll incVal = 0;
    ll val = 0;
    int l, r;
 
    node() {
        val = 0;
        shouldSet = 0;
        incVal = 0;
        l = r = 0;
    }
 
    node(ll val, int idx) {
        this->val = val;
        l = idx; 
        r = idx;
    }
 
    // Not part of interface, only used internally
    void clear() {
        shouldSet = 0;
        incVal = 0;
    }
 
    // Not part of interface
    // Simply helper to push logic to a child
    void pushSingle(node* child) {
        if (shouldSet) {
            child->shouldSet = 1;
            child->setVal = setVal;
            child->incVal = incVal;
        } else {
            child->incVal += incVal; 
        }
    }
 
    // Part of interface
    // Defines how an update should propagate to child nodes
    // Generally this is defined by how a "range update query" works
    void push(node* lchild, node* rchild) {
        // apply pending updates
        ll len = r - l + 1;
        if (shouldSet) {
            val = len * setVal;
        }
 
        val += len * incVal;
 
        // push to children
        if (l != r) {
            pushSingle(lchild);
            pushSingle(rchild);
        }
 
        clear();
    }
 
 
    // Part of interface
    // Defines how to combine self with sibling to create parent node
    // In this case 
    node operator+(const node& right) {
        node ret;
 
        ret.l = l;
        ret.r = right.r;
        ret.val = val + right.val;
 
        return ret;
    }
};
 
