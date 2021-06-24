/* We tweak the code for the solution of the problem Longest Increasing Subsequence, in order
 * to return as answer the vector res[i] = max length of an increasing subsequence finishing in a[i].
 * We compute then for each i, the length of the longest increasing subsequence ending in i, and
 * the longest decreasing subsequence starting from i (which is the reverse of the LIS for the 
 * reversed initial vector). Then the longest bitonic subsequence with peak at i is the sum of the 
 * two computed length, minus 1. We just need to compute the maximum of this upon varying i.
 * 
 * 
 * time: O(N*log(N));	memory: O(N)
 */


#include<bits/stdc++.h>
using namespace std;
 // } Driver Code Ends

typedef pair<int,int> ii;

class Solution {
    private:
    vector<int> LongestIncreasingSubsequence(vector<int> a) {
        int n = a.size();
        set<ii, greater<ii>> S;       // will contain (arr[i],LIS(i))
        int l;
        vector<int> res;
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
            res.push_back(l);
        }
        return res;
    }
    public:
    int LongestBitonicSequence(vector<int> v) {
	    vector<int> inc, dec;
	    inc = LongestIncreasingSubsequence(v);
	    reverse(v.begin(),v.end());
	    dec = LongestIncreasingSubsequence(v);
	    int ans = 0;
	    for (int i=0; i<(int)v.size(); i++) {
	        ans = max(ans, inc[i]+dec[v.size()-1-i]-1);
	    }
	    return ans;
	}
};



// { Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		vector<int>nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		Solution ob;
		int ans = ob.LongestBitonicSequence(nums);
		cout << ans <<"\n";
	}
	return 0;
}  // } Driver Code Ends