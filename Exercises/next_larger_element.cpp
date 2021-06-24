/* We use a stack to keep the elements we read and we print the next larger element 
 * of each one as soon as we read it.
 * 
 * time: O(N);	memory: O(N) (worst case)
 */

#include<bits/stdc++.h>
using namespace std;
// } Driver Code Ends


// Function to store Next larger elements
typedef long long int ll;
typedef pair<ll,int> lli;

vector <ll> nextLargerElement(long long arr[], int N){
	vector <ll> ans(N,-1);
	stack <lli> pila;
	for (int i=0; i<N; ++i) {
		for (;pila.size() && pila.top().first < arr[i]; pila.pop())
			ans[pila.top().second] = arr[i];
		pila.push(lli(arr[i],i));
	}
	return ans;
}


// { Driver Code Starts.
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		
		int n;
		cin>>n;
		long long arr[n];
		for(int i=0;i<n;i++)
			cin>>arr[i];
		
		
		vector <long long> res = nextLargerElement(arr, n);
		for (long long i : res) cout << i << " ";
		cout<<endl;
	}
	return 0;
}
// } Driver Code Ends
