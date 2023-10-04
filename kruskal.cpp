#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
 
template <typename T, size_t N>
using ar = array<T, N>;
 
#define INF (numeric_limits<int>::max())
#define INFLL (numeric_limits<ll>::max())
 
//-----------------------------------------------------------
 
const ll mxN = 1e5+2;
const ll mxM = 2e5+2;
 
int n, m;
ar<int,3> edge[mxM];
 
int p[mxN], rnk[mxN];
int nSets;
 
int parent(int i) {
    if (p[i] == i) return i;
    return p[i] = parent(p[i]);
}
 
bool check(int a, int b) {
    return parent(a) == parent(b);
}
 
void join(int a, int b) {
    if (check(a,b))return;
    nSets--;
 
    a = parent(a);
    b = parent(b);
    if (rnk[a] > rnk[b]) {
        p[b] = a;
    } else {
        p[a] = b;
        if (rnk[a] == rnk[b])rnk[b]++;
    }
}
 
 
void solve() {
    cin >> n >> m;
 
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    nSets = n;
   
    for (int i = 0; i < m; ++i) {
        int a,b,c;
        cin >> a >> b >> c, --a, --b;
        edge[i] = {c,a,b};
    }
 
    ll sum = 0;
 
    sort(edge, edge + m);
    for (int i = 0; i < m; ++i) {
        auto x = edge[i];
        if (!check(x[1], x[2])) {
            join(x[1],x[2]);
            sum += x[0];
        }
    }
 
    if (nSets > 1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << sum << endl;
    }
}
 
int main() {
    int t;
//    cin >> t;
 
    t = 1;
 
    for (int i = 1; i <= t; i++) {
        solve();
    }
    return 0;
}
