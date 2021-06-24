/* The total damage is the sum of all damages plus again the damage wich comes from doubling
 * the damage of some spells. The sum of all damages is independent fo the order we choose.
 * In order to maximize the bonus damage we would like to double the |L| most powerful spells,
 * where |L| is the number of lightning spells. We are able to do that, exept in the following case:
 * if the |L| most powerful spells are of type lightning we cannot double all of them, but 
 * instead we can double a fire spell if there is one.
 *
 * We are going to keep track of the ordered lists of known lightning spells, fire spells, |L| most powerful 
 * spells, other weaker spells.
 * We use the STL set<int> implementation of binary search tree to have insertion, deletion and
 * access to min and max elements in log(N).
 * 
 * time: O(N*log(N));	memory: O(N)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, tp, d;


int main () {
	cin >> N;
	
	ll sum=0, bonus=0;		//sum of damages of all spells; Bonus damage got by doubling
	set<int> F, L;			//set of damages of known Fire and Lighting spells
	set<int> pow, others;	//set of damages of most powerful spells we want to double
	
	for (int i=0; i<N; ++i) {
		cin >> tp >> d;
		
		if (d>0) {
			if (tp==0) {			// learning a Fire spell
				F.insert(d);
				pow.insert(d);
				bonus += d - *pow.begin();
				others.insert(*pow.begin());
				pow.erase(*pow.begin());
			} else {				// learning a Lightning spell
				L.insert(d);
				others.insert(d);
				bonus += *others.rbegin();
				pow.insert(*others.rbegin());
				others.erase(*others.rbegin());
			}
		} else {
			if (tp==0) {			// forgetting a Fire spell
				F.erase(-d);
				if (pow.count(-d)) {
					bonus += d;
					pow.erase(-d);
					if (others.size()) {
						bonus += *others.rbegin();
						pow.insert(*others.rbegin());
						others.erase(*others.rbegin());
					}
				} else {
					others.erase(-d);
				}
			} else {			// forgetting a Lightning spell
				L.erase(-d);
				if (pow.count(-d)) {
					bonus += d;
					pow.erase(-d);
				} else {
					bonus -= *pow.begin();
					others.erase(-d);
					others.insert(*pow.begin());
					pow.erase(*pow.begin());
				}
			}
		}
		sum += d;
		ll ans = sum;
		if (L.size() && *pow.begin() > *L.begin()) {	// there is at least one Ligning spell not among the most powerful 
			// thus we can double the most powerful spells
			ans += bonus;	
		} else {
			if (others.size() == 0) 	// all the spells are Lightning spells
				// thus we will not double the weakest
				ans += bonus - *pow.begin();	
			else if (L.size() && others.size())		// the lightning spells are the strongest
													// and there is at least one fire spell
				// thus we can't double one lightning, but we can double the strongest fire spell
				ans += bonus - *pow.begin() + *others.rbegin();	
		} 
		cout << ans << endl;
	}
	 
	return 0;
}

