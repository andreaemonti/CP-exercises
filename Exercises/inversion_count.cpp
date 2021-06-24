/* We implement the merge sort and count the inversions while sorting
 * 
 * time: O(N*log N);	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 200005;
int T, N;
int A[MAXN];

ll merge_sort ( int a, int b) {
	if (a + 1 == b) {
		return 0;
	}
	ll ans = merge_sort(a, (a+b)/2) + merge_sort((a+b)/2, b);
	vector <int> x, y;
	x.assign(A+a, A+((a+b)/2));
	y.assign(A+((a+b)/2), A+b);
	int i = 0;
	int j = 0;
	while ( i<(int)x.size() || j<(int)y.size() ) {
		if ((x[i] <= y[j] && i<(int)x.size()) || j==(int)y.size()) {
			A[a+i+j] = x[i];
			++i;
		} else {
			A[a+i+j] = y[j];
			ans += (int)x.size() - i;
			++j;
		}
	}
	return ans;
}

int main () {
	cin >> T;
	while (T--) {
		cin >> N; 
		for (int i=0; i<N; ++i) {
			cin >> A[i];
		}
		cout << merge_sort(0,N) << "\n";
	}
	return 0;
}

