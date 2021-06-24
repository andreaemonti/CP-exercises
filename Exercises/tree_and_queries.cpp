/* We apply Mo's algorithm to the linearization of the tree given by a DFS.
 * See the code to more details.
 * 
 *
 * time: O(N + M*log(M));	memory: O(N+M)
 */


#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int,int> ii;


class KV{		// class to keep track of elements in the currently observed range
public:
	int color[100002];		// color[c]: occurrences of color c in current range
	int atleast[100002]; 	// atleast[k]: number of colors in current 
							// 			   range with at least k ocurrences
	KV(){
		fill(color, color+100002, 0);
		fill(atleast, atleast+100002, 0);
	}
	void Add(int x) {		// add an element 	
		color[x]++;
		atleast[color[x]]++;
	}
	void Remove(int x){		// remove an element
		atleast[color[x]]--;
		color[x]--;
	}
};


int N, M, c[100002];
vector<int> g[100002];			// adjacency matrix of the tree
int ans[100002];				// we store here answers to queries


int A[100002];						// linearization of the tree
int open[100002], close[100002];	// A[open[v]..close[v]]: linearization of subtree of v
bool visto[100002];	

void dfs(int nodo) {
    static int t = 0;
    A[t] = nodo;
    open[nodo] = t++;
	visto[nodo] = true;
    for(int x : g[nodo]) {
        if(!visto[x]) {
            dfs(x);
        }
    }
    close[nodo] = t-1;
}


ii mo(ii a) {								// (l,r) --> (mo's block number, r)
	return ii(floor(a.first/sqrt(N)), a.second);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);	// fast I/O
	cin >> N >> M;
	for (int i=1; i<N+1; i++)
		cin >> c[i];
		
	// create the sparse adjacency marix
	int a, b;
	for (int i=1; i<N; i++) {
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	// linearize the tree to a vector via dfs
	dfs(1);
	
	// read queries and translate them to linearized indexes
	vector<ii> Q;
	int v, k[M];
	for (int i=0; i<M; i++) {
		cin >> v >> k[i];
		Q.push_back(ii(open[v], close[v]));
	}
	
	// sort according to Mo's alg
	vector<int> Qind(M);
	iota(Qind.begin(),Qind.end(),0);
	sort(Qind.begin(),Qind.end(),
		[&](int i, int j){					// lambda to sort according 
			return mo(Q[i]) < mo(Q[j]);		// to mo's algorithm
		});
	
	// actual query processing
	int l=0, r=0;
	KV P = KV();
	P.Add(c[1]);
	ll ans[M];
	for (auto i: Qind) {
		while(l<Q[i].first)
			P.Remove(c[A[l++]]);
		while(l>Q[i].first)
			P.Add(c[A[--l]]);
		while(r<Q[i].second)
			P.Add(c[A[++r]]);
		while(r>Q[i].second)
			P.Remove(c[A[r--]]);
		ans[i] = P.atleast[k[i]];
	}
	
	for (int i=0; i<M; i++)
		cout << ans[i] << endl;
	
	return 0;
}