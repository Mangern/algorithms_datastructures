#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ll = long long;

/*
 * Basically just max flow, but this program
 * illustrates how you can find the min cut using the same
 * max flow algorithm as max_flow.cpp (Edmond Karp)
 *
 * In this problem, all weights / capacities were 1
 *
 * */
 
const int mxN = 503;
int n, m;
int s, t;
 
vi adj[mxN];
int flo[mxN][mxN];
int par[mxN];
bool vis[mxN];
 
bool bfs() {
    memset(vis, 0, sizeof vis);
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if ((!flo[u][v]) || vis[v])continue;
            q.push(v);
            par[v] = u;
            vis[v] = 1;
        }
    }
    return vis[t];
}
 
int maxFlow() {
    s = 0;
    t = n - 1;
    int ans = 0;
    while (bfs()) {
        int curr = 1e4;
        for (int v = t; v != s; v = par[v]) {
            int u = par[v];
            curr = min(curr, flo[u][v]);
        }
        ans += curr;
        for (int v  = t; v != s; v = par[v]) {
            int u = par[v];
            flo[u][v] -= curr;
            flo[v][u] += curr;
        }
    }
    return ans;
}
 
int main() {
    cin >> n >> m;
 
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b, --a, --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
 
        flo[a][b] = 1;
        flo[b][a] = 1;
    }
 
 
    // First run maxflow to modify the adjacency matrix
    // Such that all edges in the min cut set have capacity 0
    int k = maxFlow();

    vector<array<int,2>> ans(k);
    // Run a bfs from the source
    bfs();

    int p = 0;
    for (int i = 0; i < n; ++i) {
        for (int j : adj[i]) {
            if (vis[i] && !vis[j])ans[p++] = {i+1,j+1};
        }
    }
 
    cout << k << endl;
    for (auto pp : ans)cout << pp[0] << " " << pp[1] << endl;
    return 0;
}
