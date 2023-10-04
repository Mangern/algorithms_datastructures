#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

/*
 * This program finds strongly connected components in a directed graph
 *
 * Stores in array ans the label of the SCC of each node
 *
 * */
 
const int mxN = 1e5+ 3;
 
int n, m;
vi adj[mxN];
vi radj[mxN];
bool vis[mxN];
stack<int> stk;
int ans[mxN];
int label;
 
void dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (vis[v])continue;
        dfs(v);
    }
    stk.push(u);
}
 
void dfs2(int u) {
    vis[u] = 1;
    ans[u] = label;
    for (int v : radj[u]) {
        if (vis[v])continue;
        dfs2(v);
    }
}
 
int main() {
    cin >> n >> m;
 
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b, --a, --b;
 
        adj[a].push_back(b);
        radj[b].push_back(a);
    }
 
    for (int i = 0; i < n; ++i) {
        if (!vis[i])dfs(i);
    }
 
 
    memset(vis, 0, sizeof vis);
 
    while (!stk.empty()) {
        int tp = stk.top();
        stk.pop();
 
        if (!vis[tp]) {
            ++label;
            dfs2(tp);
        }
    }
 
    cout << label << endl;
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
 
/*
 * Classic SCC problem
 * Implementation of Kosaraju algorithm
 * */
