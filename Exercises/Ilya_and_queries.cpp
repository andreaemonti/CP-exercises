/* We build an array A wich contains in position i the number A[i] of 
 * places j<i such that s[j]==s[j+1].
 * The answer of a query(i,j) is than simply difference of two elements 
 * of A.
 * 
 * time: O(N);	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10e5+1;
int m, A[MAXN], i, j;	
string s;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	cin >> m;
	A[0] = 0;
	for (unsigned i=1; i < s.size(); ++i) {
		if (s[i] == s[i-1]) {
			A[i] = A[i-1] + 1;
		} else
			A[i] = A[i-1];
	}
	for (int k=0; k<m; ++k) {
		cin >> i >> j;
		cout << A[j-1] - A[i-1] << "\n";
	}
	return 0;
}
