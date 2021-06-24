/* By reading the array from right to left, it is easy to find the leaders
 * 
 * time: O(N);	memory: O(N)
 */

// { Driver Code Starts.
#include <bits/stdc++.h>
using namespace std;
 // } Driver Code Ends


vector<int> leaders(int arr[], int n){
    vector <int> ans;
    int Max = 0;
    for (int i=n-1; i>=0; --i) {
		if (arr[i] >= Max) {
			Max = arr[i];
			ans.push_back(arr[i]);
		}
	}
	reverse(ans.begin(), ans.end());
	return ans;
}


// { Driver Code Starts.
int main()
{
   long long t;
   cin >> t;//testcases
   while (t--)
   {
       long long n;
       cin >> n;//total size of array
        
        int a[n];
        
        //inserting elements in the array
        for(long long i =0;i<n;i++){
            cin >> a[i];
        }
        
        //calling leaders() function
        vector<int> v = leaders(a, n);
        
        //printing elements of the vector
        for(auto it = v.begin();it!=v.end();it++){
            cout << *it << " ";
        }
        
        cout << endl;

   }
}
// } Driver Code Ends