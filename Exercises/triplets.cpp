/* We read the elements one by one and at each step we keep track, for each
 * possible value x = 0 .. N-1
 * - the number of ELEMENTS of value x we have already read;
 * - the number of COUPLES i,j of elements we already read such that 
 *             i<j  and A[i] < A[j] = x;
 * - the number of TRIPLETS i,j,k of elements such that
 *           i<j<k  and A[i] < A[j] < A[k].
 * 
 * Every time we read a value x we only have to update the ELEMENTS realtive 
 * to value x and COUPLES with A[j]=x, and TRIPLETS.
 * 
 * The key observation is that when we read the kth element, the number of 
 * triplets i,j,k we are looking for is the number of couples i,j of elements we 
 * already read (=> i,j<k) with A[i]<A[j]<A[k].
 * And similarly, if we read the firt j elements, the number of couples i,j with  
 * A[i]<A[j] is the number of elements i we already read (=> i<j) with A[i]<A[j].
 * Thus the operation of updating ELEMENTS, COUPLES, TRIPLETS data structures can be
 * easily done in N*log(N) with a BIT for each one (actually, a single integer is 
 * enough for the triplets).
 
 * time: O(N*log(N));	memory: O(N)
 */


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ------ Binary Indexed Tree -------
class Fenwick {
  private:
    int size;
    vector<ll> v;
	
  public:
    Fenwick(int N) {
    	size = N;
    	v.resize(N,0);
    }
    
    void Add(int p, ll x) {
        for (; p < size; p |= (p+1)) v[p] += x;
    }

    ll RangeSum(int l, int r) {     // Get the sum on the interval [l, r]
        if (l > 0) return RangeSum(0, r) - RangeSum(0, l-1);
        ll res = 0;
        for (; r >= 0; r = (r&(r+1))-1) res += v[r];
        return res;
    }
};
// ------------------------------



int main () {
	int N, x, triplets=0;
	cin >> N; 
	
	Fenwick elements = Fenwick(N);
	Fenwick couples = Fenwick(N);
	
	for (int i=0; i<N; i++) {
		cin >> x;
		elements.Add(x,1);
		couples.Add(x,elements.RangeSum(0,x-1));
		triplets += couples.RangeSum(0,x-1);
	}
	cout << triplets << endl;
	return 0;
}