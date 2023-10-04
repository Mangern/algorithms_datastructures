/*
 * This is a rather involved example of using heavy light decomposition
 * The idea is that you divide each edge into one of two different types:
 * heavy and light
 * heavy edges are ones connecting a node to its largest subtree
 * light edges are all other edges
 *
 * This is useful for doing range queries on trees
 *
 * The idea is that there are O(lg n) light edges on the path from a node
 * to the root of the tree
 *
 * So such a path can be divided into O(lg n) "ranges" of heavy edges
 * Meaning that if you want to do range queries on a tree you do the following:
 * 1. Do a heavy light decomposition using a dfs
 * 2. Ensure that you always visit heavy children before light children
 * 3. Record the time of visit for each node
 * 4. The resulting times will be consecutive numbers if you follow a path
 *    consisting of heavy edges
 * 5. Use the resulting times as indices in a range query structure, such
 *    as segment tree.
 * 6. To query a path from a to b, split the path into two parts:
 *    from a to lca(a,b) and from b to lca(a,b)
 * 7. Divide the resulting paths into O(lg n) segments on which you can do
 *    range queries in O(lg n)
 *    For a total of O(lg²n) per query
 *
 * */
#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
 
const int mxN = 2e5+5;
const int K = 20;

 
int n,q;
vi adj[mxN];
int sz[mxN];
int p[K][mxN];
int idx[mxN];
int h_top[mxN];
int depth[mxN];
int id_time;
 
int st[mxN * 2];
int arr[mxN];
 
void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) st[i] = max(st[i<<1], st[i<<1|1]);
}
 
void update(int p, int value) {  // set value at position p
  for (st[p += n] = value; p > 1; p >>= 1) st[p>>1] = max(st[p], st[p^1]);
}
 
int rmq(int l, int r) { 
  int res = 0;
  for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
    if (l&1)res = max(res, st[l++]);
    if (r&1)res = max(res, st[--r]);
  }
  return res;
}
 
void dfs_sz(int u, int cf = -1, int d = 0) {
    sz[u] = 1;
    p[0][u] = cf;
    depth[u] = d;
    for (int v : adj[u]) if (v != cf) {
        dfs_sz(v, u, d + 1);
        sz[u] += sz[v];
    }
}
 
void dfs_hld(int u, int cf = -1) {
    int sz_max = -1, h_child = -1;
    idx[u] = id_time++;
 
    if (h_top[u] == -1)h_top[u] = u;
 
    for (int v : adj[u]) if (v != cf) {
        if (sz[v] > sz_max) {
            sz_max = sz[v];
            h_child = v;
        }
    }
    if (h_child == -1)return;
 
    h_top[h_child] = h_top[u];
    dfs_hld(h_child, u);
 
    for (int v : adj[u]) if (v != cf && v != h_child) {
        dfs_hld(v, u);
    }
}
 
int lca(int u, int v) {
    if (depth[u] > depth[v])swap(u, v);
 
    int dif = depth[v] - depth[u];
 
    for (int k = 0; k < K; ++k) if (dif & (1<<k)) {
        v = p[k][v];
    }
 
    if (u == v)return u;
 
    for (int k = K - 1; k >= 0; --k) if (p[k][u] != p[k][v]) {
        u = p[k][u];
        v = p[k][v];
    }
    return p[0][u];
}
 
int solve(int u, int v) {
    int l = lca(u, v);
 
 
    int mx = max(arr[idx[u]], arr[idx[v]]);
 
    if (u == h_top[u])u = p[0][u];
 
    while (depth[h_top[u]] > depth[l]) {
        mx = max(mx, rmq(idx[h_top[u]], idx[u]));
        u = p[0][h_top[u]];
    }
 
    if (depth[u] >= depth[l])mx = max(mx, rmq(idx[l], idx[u]));
 
    while (depth[h_top[v]] > depth[l]) {
        mx = max(mx, rmq(idx[h_top[v]], idx[v]));
        v = p[0][h_top[v]];
    }
    if (depth[v] >= depth[l])mx = max(mx, rmq(idx[l], idx[v]));
    return mx;
}
 
int main() {
    memset(h_top, -1, sizeof h_top);
    scanf("%d %d", &n, &q);
    vi val(n);
    for (int i = 0; i < n; ++i)scanf("%d", &val[i]);
 
    int u,v;
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d %d", &u, &v);
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_sz(0);
    dfs_hld(0);
 
    for (int k = 1; k < K; ++k) {
        for (int i = 0; i < n; ++i) {
            p[k][i] = p[k-1][p[k-1][i]];
        }
    }
 
    for (int i = 0; i < n; ++i) {
        arr[idx[i]] = val[i];
        st[idx[i]+n] = val[i];
    }
 
    build();
 
 
    while (q-->0) {
        int t, a, b;
        scanf("%d %d %d", &t, &a, &b);
 
        if (t == 1) {
            update(idx[a-1], b);
            arr[idx[a-1]] = b;
            //cout << "updated" << endl;
        } else {
            int res = solve(a - 1, b - 1);
            printf("%d ", res);
        }
    }
    printf("\n");
    return 0;
}
