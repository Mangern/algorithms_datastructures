#include <bits/stdc++.h>
using namespace std;

/*
 * All pair shortest path
 * Algorithm itself on line 50
 *
 * */
 
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
 
template <typename T, size_t N>
using ar = array<T, N>;
 
#define INF (numeric_limits<int>::max())
#define INFLL (numeric_limits<ll>::max())
 
#define all(x) begin(x), end(x)
 
//-----------------------------------------------------------
 
const ll MOD = 1000000007;
const ll BIG = INFLL / 2 - 5;
const int mxN = 502;
 
int n, m, q;
ll dist[mxN][mxN];
 
void solve() {
    cin >> n >> m >> q;
 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)dist[i][j] = 0;
            else dist[i][j] = BIG;
        }
    }
 
    for (int i = 0; i < m; ++i) {
        int a,b,c;
        cin >> a >> b >> c;
        a--, b--;
 
        dist[a][b] = min(dist[a][b], (ll)c);
        dist[b][a] = min(dist[b][a], (ll)c);
    }
 
    // The algorithm
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
 
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
 
    for (int i = 0; i < q; ++i) {
        int a,b;
        cin >> a >> b;
        a--,b--;
 
        if (dist[a][b] == BIG) {
            cout << -1 << endl;
        } else {
            cout << dist[a][b] << endl;
        }
    }
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
