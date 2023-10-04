#include <bits/stdc++.h>
using namespace std;

/*
 * Single source shortest path that works with negative weights
 * In this case, the algorithm is used to find and report negative
 * cycles
 * */
 
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
 
template <typename T, size_t N>
using ar = array<T, N>;
 
#define INF (numeric_limits<int>::max())
#define INFLL (numeric_limits<ll>::max())

#define all(v) begin(v), end(v)
 
//-----------------------------------------------------------
 
const ll MOD = 1000000007;
const ll BIG = INFLL / 2 - 5;
const int mxN = 2502;
 
int n, m, q;
vector<ar<ll,2>> edge[mxN];
ll dist[mxN];
ll cf[mxN];
 
void solve() {
    cin >> n >> m;
 
    for (int i = 1; i < n; ++i) {
        dist[i] = BIG;
    }
    
    for (int i = 0; i < m; ++i) {
        ll a,b,c;
        cin >> a >> b >> c, a--, b--;
        edge[a].push_back({c, b});
    }
    
    int neg = -1;
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            for (auto [w, j] : edge[k]) {
                if (dist[k] + w < dist[j]) {
                    dist[j] = dist[k] + w; 
                    if (i == n - 1) {
                        neg = k;
                    }
                    cf[j] = k;
                }
            }
        }
    }
    if (neg == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
 
        for (int i = 0; i < n; ++i) {
            neg = cf[neg];
        }
 
 
        vector<int> ans = {neg+1};
        int s = cf[neg];
        while (s != neg) {
            ans.push_back(s + 1);
            s = cf[s];
        }
        ans.push_back(neg + 1);
 
        reverse(all(ans));
 
        for (auto x : ans)cout << x << " ";
        cout << endl;
 
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
