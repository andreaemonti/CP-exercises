/* Given the input array A, for every value x, consider the array B_x
 * such that B_x[i] =| 1 	if A[i] <= x
 				 	 | 0 	otherwise
 * Given B, the answer to the query (l,r,x) is just the sum of elements in 
 * the range B[l..r].
 * It is also easy to construct B_(x+1) from B_x just adding 1 to the positions 
 * where x+1 appears in the input array A.
 * A Fenwick Tree handles these two operations in O(log(N)).  
 *
 * time: O((N+M)*log(N));	memory: O(N)
 */


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

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


int N, M;

int main () {
	cin >> N >> M; 
	
	vector<int> a[N];			// a[x]: vector of positions where appears
	int x;
	for (int i=0; i<N; i++) {
		cin >> x;
		a[x].push_back(i);
	}
	
	vector<ii> Q[N];			// Q[x]: vector of queries with value x
	vector<int> ind[N];			// ind[x][i]: index of the query Q[x][i] in given order
	
	int l, r;
	for (int i=0; i<M; i++) {
		cin >> l >> r >> x;
		Q[x].push_back(ii(l,r));
		ind[x].push_back(i);
	}
	
	Fenwick T = Fenwick(N);
	int ans[M];						// ans[j]: answer to the j-th query
	for (int i=0; i<N; i++) {
		for (auto k : a[i])
			T.Add(k,1);
		for (int j=0; j<(int)Q[i].size(); j++) {
			ans[ind[i][j]] = T.RangeSum(Q[i][j].first,Q[i][j].second);
		}
	}
	
	for (auto k: ans)
		cout << k << endl; 
	
	return 0;
}