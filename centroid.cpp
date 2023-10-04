#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
 
// Simple program that finds a centroid of a tree
// 1-indexed
//
// 
 
const int mxN = 2e5 + 4;
 
int n;
int sz[mxN]; // size of subtree rooted at node i
vi adj[mxN]; // adjacency list representation of tree
 
void dfs_size(int u, int cf = -1) {
    int s = 1;
    for (int v : adj[u]) {
        if (v != cf) {
            dfs_size(v, u);
            s += sz[v];
        }
    }
    sz[u] = s;
}
 
int centroid(int u = 1, int cf = -1) {
    for (int v : adj[u]) {
        if (v == cf)continue;
        if (sz[v] > n / 2) {
            return centroid(v, u);
        }
    }
 
    return u;
}
 
int main() {
    cin >> n;
 
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    dfs_size(1);
    cout << centroid() << '\n';
 
    return 0;
}
