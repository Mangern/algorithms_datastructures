#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
 
/*
 * Algorithm for solving 2sat by finding sccs
 *
 * Problem description:
 * Uolevi's family is going to order a large pizza and eat it together. 
 * A total of n family members will join the order, and there are m possible toppings. 
 * The pizza may have any number of toppings.
 *
 * Each family member gives two wishes concerning the toppings of the pizza. 
 * The wishes are of the form "topping x is good/bad". 
 * Your task is to choose the toppings so that at least one wish from everybody becomes true
 *  (a good topping is included in the pizza or a bad topping is not included).
 *
 *  n,m <= 1e5
 * */
 
const int mxN = 2e5+3; // double verticies, good and bad
 
int n, m;
vi adj[mxN];
vi radj[mxN];
bool vis[mxN];
stack<int> st;
int topo[mxN];
bool ans[mxN];
 
void dfs1(int u) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    st.push(u);
}
 
void dfs2(int u, int o) {
    topo[u] = o;
    for (int v : radj[u]) {
        if (topo[v] == -1)dfs2(v, o);
    }
}
 
 
int no(int val) {
    if (val & 1)return val - 1;
    else return val + 1;
}
 
int si(char c, int val) {
    if (c == '-')return 2 * val + 1;
    else return 2 * val;
}
 
int main() {
    memset(topo, -1, sizeof topo);
    cin >> n >> m;
 
    for (int i = 0; i < n; ++i) {
        char c, d;
        int a, b;
        cin >> c >> a;
        cin >> d >> b;
        --a;
        --b;
 
        adj[no(si(c,a))].push_back(si(d, b));
        radj[si(d,b)].push_back(no(si(c,a)));
        adj[no(si(d,b))].push_back(si(c, a));
        radj[si(c,a)].push_back(no(si(d,b)));
    }
 
    m *= 2;
 
    for (int i = 0; i < m; ++i) {
        if (!vis[i])dfs1(i);
    }
 
    for (int i = 0, j = 0; i < m; ++i) {
        int u = st.top();
        st.pop();
 
        if (topo[u] == -1) {
            dfs2(u, j++);
        }
    }
 
    for (int i = 0; i < m; i += 2) {
        if (topo[i] == topo[i+1]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
 
        ans[i/2] = topo[i] > topo[i+1];
    }
 
    for (int i = 0; i < m / 2; ++i) {
        cout << (ans[i] ? '+' : '-') << " ";
    }
    cout << endl;
 
    return 0;
}
