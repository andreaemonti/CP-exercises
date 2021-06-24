/* We first exponential search a force value high enoughe to climb the ladder.
 * Then we binary search the minimum value possible.
 *
 * time: O(N*log(MaxHeight));	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+2;
int T, N, A[MAXN];

bool Scala(int k) {
	for(int i=0; i<N; ++i) {
		if (A[i+1]-A[i] > k) {
			return false;
		} else if (A[i+1]-A[i] == k) {
			k--;
		}
	}
	return true;
}

int main () {
	cin >> T;
	for(int t=1; t<=T; ++t) {
		cin >> N; 
		for (int i=1; i<=N; ++i) {	//A[0] = 0 is the ground 
			cin >> A[i];
		}
		int a=0, b = 1;
		while(!Scala(b))
			b *= 2;
		while(a+1 < b) {
			if (Scala((a+b)/2)) {
				b = (a+b)/2;
			} else
				a = (a+b)/2;
		}
		cout << "Case " << t << ": " << b << endl;
	}
	return 0;
}