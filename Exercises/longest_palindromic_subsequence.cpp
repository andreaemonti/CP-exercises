/* We use dynamic programming to calculate iteratively the longest palindromic subsequence S[i..j].
 * Look at the code for the simple casistics.
 * 
 * 
 * time: O(N^2);	memory: O(N^2)
 */


 // { Driver Code Starts.
#include<bits/stdc++.h>
using namespace std;

int longestPalinSubseq (string A);
int32_t main() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        cout << longestPalinSubseq (s) << endl;
    }
}
// Contributed By: Pranay Bansal
// } Driver Code Ends


int longestPalinSubseq (string S){
    int n = S.length();
    
    int dp[n+1][n+1];
    for (int i=0; i<=n; i++)
        fill(dp[i],dp[i]+n+1,0);
    
    for (int i=n-1; i>=0; i--) {
        for (int j=i; j<n; j++) {
            if (S[i] == S[j]) {		// first and last characters match
                dp[i][j] = ((i==j) ? 1 : dp[i+1][j-1] + 2);		// the L.P.S. is the one of S[i+1..j-1] 
                												// except in the case i==j, where it is 1
            } else {					// otherwise we discard one of the two ends of S[i..j]
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);		// and reduce to S[i+1..j] and S[i..j-1]
            }
        }
    }
    
    return dp[0][n-1];
}