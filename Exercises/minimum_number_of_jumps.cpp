/* We read the array on order and at i-th position we keep track of:
 * dist = number of jumps needed to arrive to i-th element
 * x 	= greatest position with distance = current dist 
 * y 	= greatest position with distance = current dist + 1
 * At every position we update dist, x, y and stop as soon as y goes past last position 
 * or when we visit a position we cannot reach (i>x).
 * 
 * time: O(N);	memory: O(1) (If only we wouldn't save the entire array)
 */


#include<bits/stdc++.h>
using namespace std;
 // } Driver Code Ends


// Function to return minimum number of jumps to end of array

class Solution{
  public:
    int minJumps(int arr[], int n){
        int dist = 0, x = 0, y = arr[0];
        for (int i=0; i<n && i<=x; i++) {		// note i<=x control to detect getting stuck at a 0
            y = max(y,i+arr[i]);
            if (y>=n-1) {
                return dist + 1;
            }
            if (i==x) {
                dist++;
                x = y;
            }
        }
        return -1;
    }
};


// { Driver Code Starts.
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,i,j;
        cin>>n;
        int arr[n];
        for(int i=0; i<n; i++)
            cin>>arr[i];
        Solution obj;
        cout<<obj.minJumps(arr, n)<<endl;
    }
    return 0;
}
  // } Driver Code Ends
