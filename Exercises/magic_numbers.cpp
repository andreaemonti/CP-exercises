/* See the code below.
 * 
 * 
 * time: O(1);	memory: O(1)
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	cin >> s;
	
	int fours = 3;
	for (auto c : s) {
		if (c == '1') {					// a one: reset number of current series of four
			fours = 0;
		} else if (c == '4') {			// increase the count of fours
			fours++;
			if (fours > 2) {			// if too many fours, exit (1444 is not ammissible)
				cout << "NO" << endl;
				return 0;
			}
		} else {						// a non ammissible digit
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
	return 0;
}