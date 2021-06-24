/* We push every element (strength, (i,j)) in a vector, sort them, then 
 * simply read from the greatest to the smallest.
 * 
 * time: O(N^2*log N);	memory: O(N^2)
 */

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef pair<int, ii> iii;
const int MAXN = 801;
int N, x, teammate[MAXN];	
vector <iii> link;

int main() {
	cin >> N;
	for (int i=2; i<=2*N; ++i) {
		for (int j=1; j<i; ++j) {
			cin >> x;
			link.push_back(iii(x, ii(i,j)));
		}
	}
	sort(link.begin(), link.end());
	for (int i=(int)link.size()-1; i>=0; --i) {
		if (teammate[link[i].second.first]==0 && teammate[link[i].second.second]==0) {
			teammate[link[i].second.first] = link[i].second.second;
			teammate[link[i].second.second] = link[i].second.first;
		}
	}
	for (int i=1; i<=2*N; ++i) 
		cout << teammate[i] << " ";
	return 0;
}
