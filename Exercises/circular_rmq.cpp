/* We implement from scratch a Segment Tree structure that supports range 
 * minimum query and lazy range update.
 * The circularity of the index is then treated easily by splitting the query 
 * with l>r in two simples queries.
 * 
 * 
 * time: O(N*log(N));	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


class SegTree{
private:
	int size;				// the lowest power of 2 greater than N
	vector<ll> v, lazy;		// v: actual tree; lazy: labels for lazy updates
	
	// We will call (a,b): the range associated to a node in the tree
	// 				(l,r): query range
	
	void lazyPropagate(int nodo, int a, int b) {	// propagate the lazy update to children
		v[nodo] += lazy[nodo];
		if (a<b) {
			lazy[2*nodo] += lazy[nodo];
			lazy[2*nodo+1] += lazy[nodo];
		}
		lazy[nodo] = 0;
		return;
	}
	
	void lazyAdd(int nodo, int a, int b, int l, int r, int x) {		
		// CASE 1) range included in [l,r]
		if (a>=l and b<=r){
			if (a<b)
				lazy[nodo] += x;		// if not a leaf: lazy update
			else 
				v[nodo] += x;
			return;
		}
		// CASE 2) range outside [l,r]
		if (a>r or b<l)
			return;
		// CASE 3) range intersects non trivially [l,r]
		lazyPropagate(nodo, a, b);
		lazyAdd(2*nodo, a, (a+b)/2, l, r, x);
		lazyAdd(2*nodo+1, (a+b)/2+1, b, l, r, x);
		v[nodo] = min(v[2*nodo]+lazy[2*nodo], v[2*nodo+1]+lazy[2*nodo+1]);
		return;
	}
	
	ll lazyMin(int nodo, int a, int b, int l, int r) {
		// CASE 1) range included in [l,r]
		if (a>=l and b<=r){	
			return v[nodo]+lazy[nodo];
		}
		// CASE 2) range outside [l,r]
		if (a>r or b<l)	
			return LLONG_MAX;
			
		// CASE 3) range intersects non trivially [l,r]
		lazyPropagate(nodo, a, b);
		return min(lazyMin(2*nodo, a, (a+b)/2, l, r),
				   lazyMin(2*nodo+1, (a+b)/2+1, b, l, r));
	}
	
public:
	SegTree(vector<ll> u) {			// constructor
		size = 1;
		while (size < (int)u.size()) size *= 2;
		v.resize(2*size,LLONG_MAX);
		lazy.resize(2*size);
		
		for (int i=0; i<(int)u.size(); i++)			// initialize the leaves
			v[size+i] = u[i];
		for (int i=(size+(int)u.size()-1)/2; i>0; i--)	// initialize other nodes
			v[i] = min(v[2*i],v[2*i+1]);
	}
	
	void RangeAdd(int l, int r, ll x) {
		lazyAdd(1, 0, size-1, l, r, x);
	}
	
	ll RangeMin(int l, int r) {
		return	lazyMin(1, 0, size-1, l, r);
	}
	
};

int N, M;

int main() {
	cin >> N;
	vector<ll> a(N);
	
	for (int i=0; i<N; i++)
		cin >> a[i];
		
	SegTree T = SegTree(a);
		
	cin >> M;
	int l,r, v;
	char _;
	cin >> noskipws >> _;
	
	for(int i=0; i<M; i++) {						// in order to detect the type of query we
		cin >> noskipws >> l >> _ >> r >> _; 		// detect if last whitespace read is space or \n
		if (_ != '\n') {
			cin >> noskipws >> v >> _;
			if (l<=r) {
				T.RangeAdd(l,r,v);			// regular query
			} else {
				T.RangeAdd(l,N-1,v);		// cyclic query
				T.RangeAdd(0,r,v);			// 
			}
		} else {
			if (l<=r) {
			cout << T.RangeMin(l,r) << endl;			// regular query
			} else {
				cout << min(T.RangeMin(l,N-1), T.RangeMin(0,r)) << endl;		// cyclic query
			}
		}
	}
	
	return 0;
}