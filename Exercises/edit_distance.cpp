/* We use iterative dinamic programming to compute ed[i][j] = the edit distance of the
 * substrings s[0..i) and t[0..j). By applying one of the 3 moves we can see easily
 * as reducing to one of the previous case ed[i][j-1], ed[i-1][j], ed[i-1][j-1].
 * 
 * 
 * time: O(m*n);	memory: O(m*n)
 */

#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends


class Solution {
  public:
    int editDistance(string s, string t) {
        int n = s.length(), m = t.length();
        int ed[n+1][m+1];           //ed[i][j] = editDistance(s[0..i-1],t[0..j-1])
        ed[0][0] = 0;           // empty string
        for (int i=0; i<=n; i++) ed[i][0] = i;       // the distance from empty string 
        for (int j=0; j<=m; j++) ed[0][j] = j;       // is always the length
    
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                ed[i][j] = min(ed[i][j-1] + 1 ,      // add r[j] after i-th char of s
                           min(ed[i-1][j] + 1,       // remove i-th char of s 
                               ed[i-1][j-1] + 1-(s[i-1]==t[j-1])));   // replace i-th char of s with s[j]
            }
        }
        return ed[n][m];
    }
};


// { Driver Code Starts.
int main() {
    int T;
    cin >> T;
    while (T--) {
        string s, t;
        cin >> s >> t;
        Solution ob;
        int ans = ob.editDistance(s, t);
        cout << ans << "\n";
    }
    return 0;
}
  // } Driver Code Ends 
