/* We simply implement a recursive formula to determine the minimum vertex cover for each 
 * subtree, where the root node is takne or not.
 * It's enough to observe that if we take a node, its subtree cover is sum of covers of its
 * children nodes, where we take them all in the cover set.
 * Whereas if a node is not taken, its subtree cover is the union of minimum covers of its
 * children (and they can be taken or not).
 * 
 * 
 * time: O(N);	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> g[100001];
int take[2][100001];
	//take[0][i] = number of cover set of subtree of node i such that i is not taken
	//take[1][i] = number of cover set of subtree of node i such that i is taken

int cover(int x, int in, int from) {
	// from = the node we came from, to dinstinguish sons from parent node in the visit
	if (take[in][x] != -1)
		return take[in][x];
	
	int s=0;
	if (in) {
		for (auto i: g[x])
			s += (i==from ? 0 : min(cover(i,0,x), cover(i,1,x)));
	} else {
		for (auto i: g[x])
			s += (i==from ? 0 : cover(i,1,x));
	}
	take[in][x] = s + in;
	return take[in][x];
}


int main() {
	cin >> N;
	
	int a, b;
	for (int i=1; i<N; i++) {		// the tree has N-1 edges
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	fill(take[0],take[0]+100001,-1);
	fill(take[1],take[1]+100001,-1);
	
	// pick 1 as root adding it to virtual node 0
	g[0].push_back(1);
	cout << cover(0,1,0) - 1 << endl;		//-1 is not ot count the virtul node 0
	
	return 0;
}