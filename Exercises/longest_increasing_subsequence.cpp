/* We parse the array from left to right and construct the longest increasing sequence.
 * We store in a set (BST) the pairs (a[i], LIS(i)) for which exists an increasing 
 * sequence of length LIS(i) that ends at the i-th element of the array.
 * We observe that if we have a couple (a,l) we can discard all the other stored couples (a',l')
 * such that a' >= a and l' <= l, since a sequnce which can continue the one associated to 
 * (a',l') wuold give also a non shorted one continuing from (a,l).
 * (*): By doing these, the set always contain a sequence of couples with (obviously strictly increasing
 * a[i]'s but also strictly increasing l's). 
 * See te code for more details.
 * 
 * time: O(N*log(N));	memory: O(N)
 */


#include<bits/stdc++.h>
using namespace std;
 // } Driver Code Ends



typedef pair<int,int> ii;

class Solution {
    public:
    int longestSubsequence(int n, int a[]) {
        set<ii, greater<ii>> S;       // will contain (arr[i],LIS(i))
        int ans = 1, l;
        for (int i=0; i<n; i++) {
            // find element from which to extend the LIS
            auto it = S.upper_bound(ii(a[i],0));
            // compute the new candidate length
            if (it == S.end()) {     
                l =1;
            } else {
                l = it->second + 1;
            }
            // insert the element
            it = S.insert(ii(a[i],l)).first;
            // eventually remove another with same l and not lower a[j] (it is only one thanks to (*))
            if (it != S.begin() && (--it)->second == l)
                S.erase(it);
            ans = max(ans,l);
        }
        return ans;
    }
};



// { Driver Code Starts.
int main()
{
    //taking total testcases
    int t,n;
    cin>>t;
    while(t--)
    {
        //taking size of array
        cin>>n;
        int a[n];
        
        //inserting elements to the array
        for(int i=0;i<n;i++)
            cin>>a[i];
        Solution ob;
        //calling method longestSubsequence()
        cout << ob.longestSubsequence(n, a) << endl;
    }
}
  // } Driver Code Ends