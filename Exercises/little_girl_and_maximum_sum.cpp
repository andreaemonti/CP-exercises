/* We count how many times each position is included in the range of a query by 
 * adding +1/-1 in the array of differences. Then we integrate it.
 * We want to put the largest elements in more counted positions.
 * 
 * time: O(N*log(N));	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, q;

int main() {
	cin >> N >> q;
	ll a[N+1];
	int d[N+2];				// array of differences
	fill(d,d+N+1,0);
	
	for (int i=0; i<N; ++i)
		cin >> a[i+1];
	int l, r;
	for (int i=0; i<q; ++i) {
		cin >> l >> r;
		d[l]++;
		d[r+1]--;
	}
	
	for (int i=1; i<=N; i++) 		// we integrate the array
		d[i] += d[i-1];

	sort(a+1,a+N+1);
	sort(d+1,d+N+1);
	ll ans=0;
	for (int i=1; i<=N; i++)
		ans += d[i] * a[i];
	
	cout << ans << endl;
	return 0;
}