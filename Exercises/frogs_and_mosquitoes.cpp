/* We say that a frog is dominated by other frogs if it will never be able 
 * to eat, since it's action range is covered by another frog at its left.
 * We keep only the non-dominated frogs in a set ordered with respect to
 * the position of the tip of the tongues. This way, given a mosquito,
 * it is easy to find the frog that will eat it, by the use of lower_bound.
 * We also keep the mosquitos on a (multi)set, so that when a a frog grows, we can easily
 * find whether and which mosquitos will be eaten upon that growth.
 * 
 * 
 * time: O(N*log(N) + M*log(M));	memory: O(N+M)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int,int> ii;

int N, M;
set<ii> frogs;			// frogs: will contain only the set of frog able to eat
multiset<ii> mosquitos;	// mosquitos: the set of alive mosquitos

auto add_frog(int x, ll l) {			// add the frog at 'x' with tongue length 'l', returns its pointer
	// we add the frog, makign sure that:
	//	- it is not dominated by one we already have
	//	- if it dominates other frogs, we delete them from the set
	
	auto it = frogs.lower_bound(ii(x+l,0));		
	
	if (it != frogs.end() && it->second <= x)	
		return frogs.end();	
	if (it == frogs.end() or it->first > x+l) {		
		if (it == frogs.begin())
			return frogs.insert(ii(x+l,x)).first;
		it--;
	}
	while(true) {
		if (it->second > x) {
			if (it == frogs.begin()) {
				frogs.erase(it);
				break;
			} else {
				frogs.erase(it--);
			}
		} else {
			break;
		}
	}
	return frogs.insert(ii(x+l,x)).first;
}

int main() {
	cin >> N >> M;

	int ind2pos[N];						// maps FrogIndex -> position
	unordered_map<int,int> pos2eaten;	// maps frog position -> mosquitos eaten
	unordered_map<int,ll> pos2len;		// maps frog position -> tongue length 
	
	int x;
	ll l, s;
	for (int i=0; i<N; i++) {		// we add frogs
		cin >> x >> l;
		ind2pos[i] = x;
		pos2len[x] = l;
		add_frog(x,l);
	}
	for (int i=0; i<M; i++) {		// process mosquitos
		cin >> x >> s;
		auto eater = frogs.lower_bound(ii(x,0));		// find the candidate frog to eat the mosquito
		for (auto it = mosquitos.insert(ii(x,s)); it != mosquitos.end() && eater!=frogs.end(); mosquitos.erase(it++)) {
			int eater_pos = eater->second;
			x = it->first;
			s = it->second;
			if (eater_pos <= x && eater->first >= x) {		// the frog actually eats it
				pos2eaten[eater_pos]++;
				pos2len[eater_pos] += s;
				frogs.erase(eater);									// we remove it 
				eater = add_frog(eater_pos,pos2len[eater_pos]);		// and add it back with longer tongue
			} else {
				break;
			}
		}
	}
	for (int i=0; i<N; i++) {
		cout << pos2eaten[ind2pos[i]] << " " << pos2len[ind2pos[i]] << "\n";
	}
	return 0;
}