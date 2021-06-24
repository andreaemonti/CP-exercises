/* We observe that a segment i is nested in j if 
			a_i > a_j  and b_i < b_j
 * We process the segment in decreasing order of right ends (b_i).
 * Each segment we process can contain only segments we already processed. More precisely
 * among those, it contains exactly all the segments with lower left end (a_i).
 * We use a Fenwick tree to count the number of right ends we already processed, which are
 * lower than the current one.
 *
 * Since the b_i values are in [-1e9,1e9] range we can reduce them to the [0,N] range, 
 * in order to be able to implement the Fenwick tree.
 * 
 * time: O(N*log(N));	memory: O(N)
 */



#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int,int> ii;

// ------------- Fenwick tree ------------------------------
class Fenwick {
  private:
    int size;
    vector<ll> v;
  public:
    Fenwick(int N) {
    	size = N;
    	v.resize(N);
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
// ------------------------------------------------------

int N;
int ans[200001];

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
	
	Fenwick ft = Fenwick(N);
	for(int i=N-1; i>=0; i--) {
		int j = v[i].second;
		int e = indexof(v[i].first.second);
		ans[j] = ft.RangeSum(0,e);
		ft.Add(e,1);
	}
	
	for (int i=0; i<N; i++)
		cout << ans[i] << endl;
	
	return 0;
}