#include <bits/stdc++.h>
using namespace std;

/*
 * z-algorithm creates an array z
 * such that for each index i, z[i] denotes
 * the length of the longest common prefix between
 * s[i:] and s[0:]
 * i.e. the longest substring starting from i 
 * that is also a prefix
 * Complexity O(n)
 *
 * Can be used for pattern matching;
 * if pattern is p
 * and string is s
 * make a string p$s where $ is a character not in the alphabet of p and s
 * then count number of occurences where z[i] == len(p)
 * */
 
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vii = vector<long long>;
 
template <typename T, size_t N>
using ar = array<T, N>;
 
//-----------------------------------------------------------
 
const ll MOD = 1e9 + 7;
const ll BIG = INFLL / 2 - 5;
const int mxN = 201;
const int mxM = 2500;
 
vector<int> z(string s) {
    int n = s.size();
    vector<int> z(n);
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0,min(z[i-x],y-i+1));
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            x = i; y = i+z[i]; z[i]++;
        }
    }
    return z;
}
 
void solve() {
    string s, p;
    cin >> s >> p;
 
    vi zar = z(p + "$" + s);
 
    int ans = 0;
    for (int x : zar) {
        if (x == p.size())++ans;
    }
    cout << ans<<'\n';
}
 
int main() {
    int t = 1;
    
   //cin >> t;
    
 
    for (int i = 1; i <= t; i++) {
        solve();
    }
    return 0;
}
