/* Since the update queries are all before the point queries we can just write the array of the
 * differences. After all the update queries we integrate it to get the real array and queries
 * become trivial.
 * 
 * 
 * time: O(N);	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

int n, u, q;

void solve() {
	cin >> n >> u;
	
	long long d[n+1];		// array of differences
	fill(d,d+n,0);
	
	int l, r, val;
	for (int i=0; i<u; i++) {		// u updates
		cin >> l >> r >> val;
		d[l] += val;
		d[r+1] -= val;
	}
	for (int i=0; i<n; i++)			// integration
		d[i+1] += d[i];
	
	cin >> q;
	for (int i=0; i<q; i++) {		// q queries
		cin >> l;
		cout << d[l] << endl;
	}
	
	return;
}

int main() {
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}