/* We treat separately the case of sum not multiple of 3.
 * In the case of sum equal to 0, the answer is just a funcion of the number of position
 * with prefix sum equal to 0.
 * In the general case we want to count the couple of positions (i,j) with prefix sum
 * respectively equal to sum/3 and sum*2/3.
 * So we read the array in order, count the valid i values, and every time we find a 
 * valid value for j we add to the answer the number of valid values for i we found yet. 
 * 
 * time: O(N);	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

int N;

int main () {
	cin >> N; 
	int A[N];
	long long sum = 0;
	for (int i=0; i<N; i++) {		// input + calculate sum
		cin >> A[i];
		sum += A[i];
	}
	if (sum%3) {			// modulo 3 check
		cout << 0 << endl;
		return 0;
	}
	
	long long a = 0, s = 0, ans = 0;
	for (int i=0; i<N; i++) {
		s += A[i];
		a += (s == sum/3);				// update number of valid values for i
		if (s == sum/3*2 && i<N-1)		// if valid j -> update answer
			ans += a;
	}
	if (sum == 0) {						// case of sum = 0
		cout << (a-1)*(a-2)/2;
	} else {
		cout << ans << endl;
	}
	
	return 0;
}