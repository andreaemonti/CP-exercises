/* We count the digit changes in the strings, that is positions i with s[i]!=s[i-1].
 * - If changes are less than N-2, there are at least 2 position where there is no
 * change, so by flipping the string between two of these, the changes increases by 2.
 * - If changes are N-1 we can glip the substring from 0 to the position with no digit
 * change and get a alternating string.
 * - If the changes are N, then s is already an alternating string and we can just flip
 * it entilrely.
 *
 * time: O(N);	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

int N;
string s;

int main () {
	cin >> N >> s;
	int c = 1;
	for(int i=1; i<N; i++) {
		if (s[i] != s[i-1])
			c++;
	}
	cout << min(N,c+2);
	
	return 0;
}
