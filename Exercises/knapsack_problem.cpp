/* We solve with dynamic programming the partial problem knapsack(s,n) which is the same 
 * problem but with knapsack capacity = s and only availlable items fomr 1 to n.
 * We observe that for each s and for each n:
 * - if the n-th elements fits in the sized s knapsack we can take it and reduce to 
 		knapsack(s-size(n-th object), n-1) or don't take it and just reduce to
 		knapsack(s,n-1) ;
 * - if the n-th elements doesn't fit in the sized s knapsack we simply reduce to
 		knapsack(s,n-1) .
 * 
 * time: O(S*N);	memory: O(S*N)
 */

#include <bits/stdc++.h>
using namespace std;

int S, N;
int siz[2001], val[2001];
int dp[2002][2002];			// dp[s][n] = soltion with capacity=s, items=items[:n]

int main () {
	cin >> S >> N;
	for (int i=0; i<N; i++)
		cin >> siz[i] >> val[i];
		
	for (int s=1; s<=S; s++) {
		for (int n=0; n<N; n++) {
			dp[s][n+1] = max(dp[s][n],(s<siz[n] ? 0 : dp[s-siz[n]][n] + val[n]));
		}
	}
	
	cout << dp[S][N] << endl;
	
	return 0;
}