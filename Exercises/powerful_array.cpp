/* We observe that if we know the result of a query (l,r), and also keep track of 
 * the occurrences of each element in the range a[l..r], we can easily calculate 
 * the answer for the queries (l±1, r±1).
 * Then we can sort the queries according to Mo's algorithm to reduce the complexity
 * to O((N+t)*sqrt(N))
 * 
 * 
 * time: O((N+t)*sqrt(N));	memory: O(N + max) = O(N + 1e6)
 */


#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int,int> ii;

int N, t, a[200002];

ii mo(ii a) {				// (l,r) --> (mo's block, r)
	return ii(floor(a.first/sqrt(N)), a.second);
}

class PowArray{
public:
	ll power;
	int m[1000002];			// m[i]: occurrences of i in the current range
	PowArray(){
		power = 0;
		fill(m,m+1000002,0);
	}
	void Add(int x) {		// add an element 	
		power += x*(2*m[x]+1);
		m[x]++;
	}
	void Remove(int x){		// remove an element
		m[x]--;
		power -= x*(2*m[x]+1);
	}
};

int main() {
	cin >> N >> t;
	for (int i=0; i<N; i++) 
		cin >> a[i+1];
	
	vector<pair<ii,int>> Q(t);		// Q[i]: ((l,r), i) = (query, index)
	int l, r;
	for (int i=0; i<t; i++) {
		cin >> l >> r;
		Q[i] = make_pair(ii(l,r),i);
	}
		
	sort(Q.begin(),Q.end(),
		[](pair<ii,int> a, pair<ii,int> b){			// lambda to sort according 
			return mo(a.first) < mo(b.first);		// to mo's algorithm
		});
	
	l=0, r=0;
	ll ans[t];
	PowArray P = PowArray();
	for (auto q: Q) {
		while(l<q.first.first)
			P.Remove(a[l++]);
		while(l>q.first.first)
			P.Add(a[--l]);
		while(r<q.first.second)
			P.Add(a[++r]);
		while(r>q.first.second)
			P.Remove(a[r--]);
		ans[q.second] = P.power;
	}
	
	for (int i=0; i<t; i++)
		cout << ans[i] << endl;
	
	return 0;
}