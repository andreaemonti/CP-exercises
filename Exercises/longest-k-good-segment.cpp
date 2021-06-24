/* We read sequentially the elements and put them in a queue to optimize memory.
 * We also keep track with a map of how many copies of each element we have in the queue.
 * Every time we read an element we also pop elements from the other end of the queue
 * until the number of different elements is <= K.
 * 
 * time: O(ans) <= O(N);	memory: O(ans) <= O(N)
 */

#include <bits/stdc++.h>
using namespace std;

int K, N, x;
unordered_map<int,int> S;		// map is ok too, but unordered is even faster
queue<int> Q;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);	// fast I/O
	cin >> N >> K;
	
	int uniqs = 0, ans = 0, l;
	for (int i=0; i<N; i++){
		cin >> x;
		
		Q.push(x);				// add element to queue
		if (!S[x])	// if not in current queue, count it
			uniqs++;
		S[x]++;
			
		while(uniqs > K) {		//remove elements from back until we have k uniques
			S[Q.front()]--;
			if (!S[Q.front()])
				uniqs--;
			Q.pop();
		}
		
		if (int(Q.size()) > ans){		// update maximum queue length seen yet
			ans = Q.size();
			l = i+1;
		}
	}
	cout << l - ans + 1 << " " << l << endl;
	return 0;
}

