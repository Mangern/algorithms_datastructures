/*
 * Handles range minimum/maximum queries
 * Does not handle updates
 * Prep: O(n*lgn) 
 * Each query: O(1)
 * */
#include <bits/stdc++.h>
using namespace std;
 
 
int main() {
    int n, q;
    cin >> n >> q;
 
    vector<int> a(n);
    for (auto& x : a)cin >> x;
 
    const int LOG = 20;
 
    vector<vector<int>> rmq(20, vector<int>(n));
 
    rmq[0] = a;
 
    for (int k = 1; k < LOG; ++k) {
        // each layer covers 1<<k elements
        // k = 1 -> 2
        // k = 2 -> 4
        for (int i = 0; i+(1<<k) <= n; ++i) {
            rmq[k][i] = min(rmq[k-1][i], rmq[k-1][i+(1<<(k-1))]);
            //cout << rmq[k][i] << " \n"[i+(1<<k)==n];
        } 
    }
 
 
    while (q-->0) {
        int x, y;
        cin >> x >> y, --x, --y;
 
        if (x == y) {
            cout << a[x] << endl;
            continue;
        }
 
        int len = y + 1 - x;
 
        // 2^(x+1) >= len
        // x+1 >= lg(len)
        // x >= lg(len) - 1
 
        int p2 = __lg(len);
        if ((1<<p2) == len)--p2;
 
        cout << min(rmq[p2][x], rmq[p2][y+1-(1<<p2)]) << endl;
    }
}
