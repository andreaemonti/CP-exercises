/* We use dynamic programming to calculate if it possible to obtain s as sum of 
 * some elements among the first n elements of the array.
 * 
 * 
 * 
 * time: O(N*sum);	memory: O(N*sum)
 */

// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
// User function Template for C++


// bool dp[100002][102];

class Solution{
public:
    int equalPartition(int N, int arr[]){
        int S = 0;
        for (int i=0; i<N; i++)
            S += arr[i];
            
        if (S%2)
            return 0;
        
        bool dp[S/2+1][N+1];		// dp[s][n]=true if can obtain s as sum of some elements in arr[0:n]
        for(int i=0; i<S/2+1; i++) 	// set all dp to false
            for(int j=0; j<N+1; j++)
                dp[i][j]=false;
        fill(dp[0],dp[0]+N,true);	// sum s=0 can be obtained with any elements available
        
        for(int s=1; s<=S/2; s++) {
            for (int n=0; n<N; n++){		// we consider the element x = arr[n]
                if ((arr[n]<=s && dp[s-arr[n]][n-1]) // we can get s-x with first n-1 elements
                or (arr[n]==s and n==0) 			 // x = s
                or (n && dp[s][n-1]) )				 // we could already get s without x
                	dp[s][n] = true;
            }
            
        }
            
        return dp[S/2][N-1];
        
    }
};

// { Driver Code Starts.

int main(){
    int t;
    cin>>t;
    while(t--){
        int N;
        cin>>N;
        int arr[N];
        for(int i = 0;i < N;i++)
            cin>>arr[i];
        
        Solution ob;
        if(ob.equalPartition(N, arr))
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }
    return 0;
}  // } Driver Code Ends