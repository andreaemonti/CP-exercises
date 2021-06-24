/* While reading the array we use a double-ended queue to store the 
 * relevant elements between the last K read ones. In particular each 
 * time we read a new element: we put that on the front after having
 * removed the smaller ones; we throw away the old values from the back 
 * and finally read the maximum of the window on the back.
 * 
 * time: O(N)	memory: O(K)
 */

#include <bits/stdc++.h>
using namespace std;
// } Driver Code Ends


typedef pair <int,int> ii;
deque<ii> coda;

vector <int> max_of_subarrays(int *arr, int N, int K){
	coda.clear();
	vector<int> ans;
	for (int i=0; i<N; ++i) {
		while (coda.size() && coda.front().second < arr[i])
			coda.pop_front();
		coda.push_front(ii(i,arr[i]));
		while (coda.size() && coda.back().first <= i-K)
			coda.pop_back();
		if (i>=K-1)		//we read the maximum only after having read K terms
			ans.push_back(coda.back().second);
	}
	return ans;
}


// { Driver Code Starts.
int main() {
	
	int t;
	cin >> t;
	
	while(t--){
		
		int n, k;
		cin >> n >> k;
		
		int arr[n];
		for(int i = 0;i<n;i++) 
			cin >> arr[i];
		
		vector <int> res = max_of_subarrays(arr, n, k);
		for (int i = 0; i < res.size (); i++) 
			cout << res[i] << " ";
		cout << endl;
		
	}
	
	return 0;
}  // } Driver Code Ends
