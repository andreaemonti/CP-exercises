/* Let's denote x_i = f(1,i,a_i) and y_i = f(j,n,a_j).
 * Given those, our task is to calculate the couples (i,j) such that i<j and 
 x_i > y_j. In order to do that efficiently we will calculate ans_i for each i, 
 * that is how many indexes j>i are such that y_j < x_i.
 * We use a fenwick tree/BIT to store the occurrences of numbers in y[i..n] 
 * so that we can have ans_i in logartihmic time with a sum range and point 
 * update the BIT in logarithmic time too.
 *
 * For the creation of the arrays x and y a map would also give a N*log(N) time,
 * but with n=10^6, it gives TLE, so an unordered_map is required.
 * Note that the BIT is also O(N*log(N)) but has a smaller constant factor.
 * 
 * time: O(N*log(N));	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;


#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

class FT{				// FenwickTree implementation
private:
	int size;
	vector<ll> v;
public:
	FT(int n) {
		size = n;
		v.resize(n);
	}
	void Add(int x, ll val) {
		for (; x<size; x |= (x+1)) v[x] += val;
	}
	ll RangeSum(int l, int r) {
		if (l) 
			return RangeSum(0,r)-RangeSum(0,l-1);
		ll res = 0;
		for (; r>=0; r=(r&(r+1))-1) res += v[r];
		return res; 
	}
};
	

int N;
int a[1000002];

int main() {
	
	cin >> N; 
	for (int i=0; i<N; i++)
		cin >> a[i];
	
	unordered_map <int,int> m1, m2;				// use unordered_map here
	int x[N], y[N];
	for (int i=0; i<N; i++) {
		m1[a[i]]++;					//counting previous occurrences of a[i]
		x[i] = m1[a[i]];			// store it to x
		
		m2[a[N-1-i]]++;					// same for y but in reversed order
		y[N-1-i] = m2[a[N-1-i]];		// 
	}

	FT fen = FT(N+1);			// occurrences ranges from 1 to N
	ll ans = 0;
	for (int i=N-1; i>0; i--) {
		fen.Add(y[i],1);
		ans += fen.RangeSum(0,x[i-1]-1);		// x[i-1] since j > i, 
												// x[]-1 since y_j > x_i
	}
	
	cout << ans << endl;
	
	return 0;
}