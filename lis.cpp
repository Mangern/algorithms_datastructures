#include <bits/stdc++.h>
using namespace std;

/*
 * Find the longest increasing subsequence in array in O(nlgn)
 * */
 
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
 
int main() {
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	
	vi x(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i];
	}
 
	int ans = 0;
	vi dp(n+1);
	for (int i = 0; i < n; i++) {
		
		int l = 1, h = ans;
		while (l <= h) {
			int mid = (l + h) / 2;
			if (x[dp[mid]] < x[i]) {
				l = mid + 1;
			}
			else h = mid - 1;
		}
		int newL = l;
 
		if (newL > ans) {
			dp[newL] = i;
			ans = newL;
		}
		else if (x[i] < x[dp[newL]]) {
			dp[newL] = i;
		}
	}
	cout << ans << endl;
	return 0;
