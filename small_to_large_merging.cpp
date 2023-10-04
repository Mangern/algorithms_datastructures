#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

/*
 * Problem solved:
 * Each node in the tree has a color
 * Tree is rooted at 0
 * 
 * Illustrates that if you want to merge answers from subtrees, you should
 * merge the smaller sets into the larger sets to reduce complexity
 * */
 
const int mxN = 2e5 + 3;
 
int n;
vi adj[mxN];
int c[mxN];
int ans[mxN];
 
set<int> dfs(int u, int cf = -1) {
    set<int> st;
    st.insert(c[u]);
 
    for (int v : adj[u]) {
        if (v == cf)continue;
        set<int> ret = dfs(v, u);
 
        if (ret.size() > st.size())swap(st,ret);
        for (auto x : ret)st.insert(x);
    }
 
    ans[u] = st.size();
    return st;
}
 
int main() {
    cin >> n;
 
    for (int i = 0; i < n; ++i)cin >> c[i];
 
    for (int i = 0; i < n - 1; ++i) {
        int a,b;
        cin >> a >> b, --a, --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    dfs(0);
 
    cout << ans[0];
    for (int i = 1; i < n; ++i)cout << " " << ans[i];
    cout << '\n';
 
    return 0;
}
