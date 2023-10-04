#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;
template<typename T, size_t N>
using ar = array<T,N>;
/*
 * Implementing CSES Download Speed
 *
 * Using adjacency matrix for maxFlow
 *
 * */
const int mxN = 503;
const ll INF = 2e9;
int n, m;
int s, t;
 
ll adj[mxN][mxN];
bool vis[mxN];
int par[mxN];
 
bool bfs() {
    memset(vis, 0, sizeof vis);
 
    queue<int> q;
    q.push(s);
    vis[s] = 1;
 
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (int v = 0; v < n; ++v) {
            if (!adj[u][v] || vis[v])continue;
            q.push(v);
            par[v] = u;
            vis[v] = 1;
        }
    }
    return vis[t];
}
 
// Simply returns the maximum flow in the network
ll maxFlow() {
    ll ans = 0;
    while (bfs()) {
        ll curr = INF;
 
        for (int v = t; v != s; v = par[v]) {
            int u = par[v];
 
            curr = min(curr, adj[u][v]);
        }
        ans += curr;
 
        for (int v = t; v != s; v = par[v]) {
            int u = par[v];
            adj[u][v] -= curr;
            adj[v][u] += curr;
        }
    }
    return ans;
}
 
int main() {
    cin >> n >> m;
 
    for (int i = 0; i < m; ++i) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        --a, --b;
 
        adj[a][b] += c;
    }
 
    s = 0;
    t = n - 1;
    cout << maxFlow() << '\n';
 
    return 0;
}
