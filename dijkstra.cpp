#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

/*
 * Single source shortest path when edges are nonnegative
 *
 * */
 
using namespace std;
 
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
 
template <typename T, size_t N>
using ar = array<T, N>;
 
#define INF (numeric_limits<int>::max())
#define INFLL (numeric_limits<ll>::max())
 
//-----------------------------------------------------------
 
const ll MOD = 1000000007;
const int mxN = 1e5 + 2;
 
int n, m, s;
vector<ar<int,2>> edge[mxN];
ll dist[mxN];
priority_queue<ar<ll,2>, vector<ar<ll,2>>, greater<ar<ll,2>>> pq;
 
void solve() {
    cin >> n >> m;
 
    for (int i = 0; i < m; ++i) {
        int a,b,c;
        cin >> a >> b >> c;
        a--, b--;
 
        edge[a].push_back({b, c});
    }
 
    for (int i = 0; i < n; ++i) {
        dist[i] = INFLL;
    }
 
    pq.push({0, 0});
    dist[0] = 0;
 
    while (!pq.empty()) {
        auto tp = pq.top();
        pq.pop();
 
 
        if (tp[0] > dist[tp[1]])continue;
 
        for (auto x : edge[tp[1]]) {
            if (tp[0] + x[1] < dist[x[0]]) {
                dist[x[0]] = tp[0] + x[1];
                pq.push({dist[x[0]], x[0]});
            }
        }
    }
 
    cout << 0;
    for (int i = 1; i < n; ++i) {
        cout << " " << dist[i];
    }
    cout << endl;
}
 
int main() {
    int t;
  //  cin >> t;
 
    t = 1;
 
    for (int i = 1; i <= t; i++) {
        solve();
    }
    return 0;
}
