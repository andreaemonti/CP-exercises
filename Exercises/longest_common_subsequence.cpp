/* We use dynamic programming to calculate iteratively the longest common subsequence of the strings str1[0..i] 
 * and str2[0..j]. Look at the code for the simple casistics.
 * 
 * 
 * time: O(|str1|*|str2|);	memory: O(|str1|*|str2|)
 */


 // { Driver Code Starts.
#include<bits/stdc++.h>
const int mod=1e9+7;
using namespace std;
 // } Driver Code Ends


class Solution{
    public:
    //Function to find the length of longest common subsequence in two strings.
    int lcs(int x, int y, string s1, string s2) {
        int dp[x+1][y+1];
        for (int i=0; i<=x; i++)
            fill(dp[i],dp[i]+y+1,0);
        
        for (int i=0; i<x; i++) {
            for (int j=0; j<y; j++) {
                if (s1[i] == s2[j]) {				// last character of s1[0..i] and s2[0..j] match:
                    dp[i+1][j+1] = dp[i][j] + 1;	// the L.C.S. is the one with (i-1,j-1) followed by s1[i]
                } else {							// if the last char do not match:
                    dp[i+1][j+1] = max(dp[i][j+1],dp[i+1][j]);	// we discard the last char of s1 or of s2
                }
            }
        }
        return dp[x][y];
    }
};


// { Driver Code Starts.
int main() {
    int t,n,k,x,y;
    cin>>t;
    while(t--)
    {
        cin>>x>>y;          // Take size of both the strings as input
        string s1,s2;
        cin>>s1>>s2;        // Take both the string as input
        Solution ob;
        cout << ob.lcs(x, y, s1, s2) << endl;
    }
    return 0;
}
  // } Driver Code Ends