/* We save in A[i] the number of towers of length i.
 * 
 * time: O(N);	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;
int N, A[MAXN], x, c, max_heigth;	

int main() {
	cin >> N;
	for (int i=0; i<N; ++i) {
		cin >> x;
		++A[x];
	}
	for (int i=0; i<MAXN; ++i) {
		if (A[i]) {
			max_heigth = max(max_heigth, A[i]);
			++c;
		}
	}
	cout << max_heigth << " " << c;
	return 0;
}
