/* The element a[j]  is modified only by moves on index i<j. So, since moves commutes,
 * we can apply moves with increasing index and we have that after all moves of index i, 
 * a[i] should be equal to b[i]. Thus a greedy approach gives the best solution.
 * Moreover we don't even need to store the entire array.
 * 
 * time: O(N);	memory: O(1)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


int N;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);	//COMMENT IF INTERACTIVE
	cin >> N;
		
	ll ans;
	int b, c=0;
	for (int i=0; i<N; i++) {
		cin >> b;
		ans += abs(b-c);
		c=b;
	}
	
	cout << ans << endl;
		
	return 0;
}