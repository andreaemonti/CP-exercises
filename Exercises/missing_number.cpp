/* Observing the sum of given number modulus n is enough to determine 
 * the missing one. We can keep track just of it.
 *
 * time: O(N);	memory: O(1)
 */

#include <bits/stdc++.h>
using namespace std;

int MissingNumber(vector<int>& array, int n);

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> array(n - 1);
        for (int i = 0; i < n - 1; ++i) cin >> array[i];

        cout << MissingNumber(array, n) << "\n";
    }
    return 0;
}
// } Driver Code Ends


int MissingNumber(vector<int>& array, int n) {
    int s = 0;
	for (int i=0; i<n-1; ++i) {	// calculates the sum of given elements modulo n
		s = (s+array[i])%n;
    }
	return n%2 ? n-s : (3*n/2-s-1)%n+1 ;
}