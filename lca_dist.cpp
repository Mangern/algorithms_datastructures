#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
 
const int mxN = 2e5 + 3;
const int mxE = 18; // ceil(log2(mxN))
 
int n, q;
vi adj[mxN];
int p[mxE][mxN];
int d[mxN];
 
void find_parent(int i, int depth = 0, int parent = -1) {
    p[0][i] = parent;
    d[i] = depth;
    for (int j : adj[i]) {
        if (j == parent)continue;
        find_parent(j, depth + 1, i);
    }
}
 
int get_lca(int a, int b) {
    // WLOG assume depth of a >= depth of b
    if (d[a] < d[b])swap(a,b);
 
    // get a and b to same depth using binary lifting
    int diff = d[a] - d[b];
    for (int k = 0; k < mxE; ++k) {
        if (diff & (1<<k)) {
            a = p[k][a];
        }
    }
 
    // one was parent of the other
    if (a == b)return a;
 
    // jump as far as possible without hitting lca
    for (int k = mxE - 1; k >= 0; --k) {
        if (p[k][a] != p[k][b]) {
            a = p[k][a];
            b = p[k][b];
        }
    }
 
    // the node after the furthest jump possible must be lca
    return p[0][a];
}
 
int main() {
    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    // compute parents / depth
    find_parent(1);
 
    // setup for binary lifting
    for (int k = 1; k < mxE; ++k) {
        for (int i = 1; i <= n; ++i) {
            p[k][i] = p[k-1][p[k-1][i]];
        }
    }
 
    while (q-->0) {
        int a, b;
        cin >> a >> b;
 
        int lca = get_lca(a, b);
 
        cout << (d[a] + d[b] - 2 * d[lca]) << endl;
    }
 
    return 0;
}
