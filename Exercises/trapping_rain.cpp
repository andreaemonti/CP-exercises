/*
 * Observation: the water level at i is equal to the minimum between the maximum A[j] 
 * with j<i and the maximum A[j] with j>i.
 * For this purpose we can first compute Left_max[i] = max value of A[j] with j<i.
 * Similarly we compute Right_max (it's not necessary to save the entire array)
 * and in the same cycle we compute the water level.
 * The amount of water stored at i is 0 if
 * A[i] > water_level, water_level - A[i] otherwise.
 * 
 * time: O(N)	memory: O(N)
 */
 
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e7+2;
int T, N, ans, A[MAXN], Left_max[MAXN], Right_max;

int main () {
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i=0; i<N; ++i) {
			cin >> A[i];
			Left_max[i+1] = max(Left_max[i], A[i]);
		}
		Right_max = A[N-1];
		ans = 0;
		for (int i=N-2; i>0; --i) {
			Right_max = max(Right_max, A[i]);
			ans += max( 0, min(Right_max, Left_max[i]) - A[i]);
		}
		cout << ans << "\n";
	}
	return 0;
}

