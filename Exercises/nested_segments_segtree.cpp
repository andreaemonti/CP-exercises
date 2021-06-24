/* We observe that a segment i is nested in j if 
			a_i > a_j  and b_i < b_j
 * We process the segment in decreasing order of right ends (b_i).
 * Each segment we process can contain only segments we already processed. More precisely
 * among those, it contains exactly all the segments with lower left end (a_i).
 * Segment tree to count the number of right ends we already processed, which are
 * lower than the current one.
 *
 * Since the b_i values are in [-1e9,1e9] range we can reduce them to the [0,N] range, 
 * in order to implement the Segment Tree on a vector.
 * 
 * time: O(N*log(N));	memory: O(N)
 */


#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int,int> ii;


int N;
int ans[200001];


class SegTree{
private:
	int size;				// the lowest power of 2 greater than N
	vector<ll> v;		// v: actual tree; lazy: labels for lazy updates
	
public:
	SegTree(int n) {			// constructor
		size = 1;
		while (size < n) size *= 2;
		v.resize(2*size,0);
	}
	
	void PointAdd(int p, int x) {
		for(p=p+size; p>0; p/=2)
			v[p] += x;
	}
	
	int RangeSum(int nodo, int a, int b, int l, int r) {
		// CASE 1) range included in [l,r]
		if (a>=l and b<=r)
			return v[nodo];
		// CASE 2) range outside [l,r]
		if (a>r or b<l)	
			return 0;
			
		// CASE 3) range intersects non trivially [l,r]
		return RangeSum(2*nodo, a, (a+b)/2, l, r) + RangeSum(2*nodo+1, (a+b)/2+1, b, l, r);
	}
	int RangeSum(int l, int r) {
		return	RangeSum(1, 0, size-1, l, r);
	}
	
};


vector <int> Ends;			//Ends will be the list of b_i's in increasing order.
int indexof(int x) {		// Reduction of [-1e9,1e9] range to [0,N] by binary searching in Ends
	int a=0, b=N;
	while(b-a>1) {
		if (Ends[(a+b)/2] > x) {
			b = (a+b)/2;
		} else {
			a = (a+b)/2;
		}
	}
	return a;
}


int main() {
	cin >> N;
	vector <pair<ii,int>> v;	// we keep also track of the index of each segment for output reasons
	
	int a,b;
	for (int i=0; i<N; i++) {
		cin >> a >> b;
		v.push_back(make_pair(ii(a,b),i));		
		Ends.push_back(b);
	}
	sort(Ends.begin(),Ends.end());
	sort(v.begin(), v.end());		// we sort segments by first end (a_i)
	
	SegTree T = SegTree(N);
	for(int i=N-1; i>=0; i--) {
		int j = v[i].second;
		int e = indexof(v[i].first.second);
		ans[j] = T.RangeSum(0,e);
		T.PointAdd(e,1);
	}
	
	for (int i=0; i<N; i++)
		cout << ans[i] << endl;
	
	return 0;
}