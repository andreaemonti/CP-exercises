/* A greedy approach works. We just have to order meetings by end time and then 
 * by reading the sorted array, pick one only the meetings that fit with the previously 
 * picked.
 * 
 * 
 * time: O();	memory: O()
 */


#include <bits/stdc++.h>
using namespace std;
 // } Driver Code Ends

typedef pair<int,int> ii;
class Solution
{
    public:
    int maxMeetings(int start[], int end[], int n) {
        ii meetings[n];
        for (int i=0; i<n; i++)
            meetings[i] = ii(end[i],start[i]);
        sort(meetings,meetings+n);
        
        int ans = 0;
        int libero=0;				// the first available moment to pick another meeting
        for (int i=0; i<n; ) {
            libero = meetings[i].first+1;
            ans++;
            while(meetings[i].second < libero && i<n)
                i++;
        }
        
        return ans;
    }
};


// { Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int start[n], end[n];
        for (int i = 0; i < n; i++) cin >> start[i];

        for (int i = 0; i < n; i++) cin >> end[i];

        Solution ob;
        int ans = ob.maxMeetings(start, end, n);
        cout << ans << endl;
    }
    return 0;
}  // } Driver Code Ends