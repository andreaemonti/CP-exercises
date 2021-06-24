// CODE GIVEN BY THE PLATFORM:

#include <bits/stdc++.h>

using namespace std;

// Tree Node
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to Build Tree
Node *buildTree(string str) {
    // Corner Case
    if (str.length() == 0 || str[0] == 'N') return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str;) ip.push_back(str);

    // Create the root of the tree
    Node *root = new Node(stoi(ip[0]));

    // Push the root to the queue
    queue<Node *> queue;
    queue.push(root);

    // Starting from the second element
    int i = 1;
    while (!queue.empty() && i < ip.size()) {

        // Get and remove the front of the queue
        Node *currNode = queue.front();
        queue.pop();

        // Get the current Node's value from the string
        string currVal = ip[i];

        // If the left child is not null
        if (currVal != "N") {

            // Create the left child for the current Node
            currNode->left = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if (i >= ip.size()) break;
        currVal = ip[i];

        // If the right child is not null
        if (currVal != "N") {

            // Create the right child for the current Node
            currNode->right = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}

int maxPathSum(Node *);

int main() {
    int tc;
    scanf("%d ", &tc);
    while (tc--) {
        string treeString;
        getline(cin, treeString);
        Node *root = buildTree(treeString);
        cout << maxPathSum(root) << "\n";
    }
    return 0;
}// } Driver Code Ends


/*
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};
*/

// MY SOLUTION HERE
/* We implement a recursive function to calculate the max sum among the paths 
 * from each node to every leaf under it. 
 * Meanwile, we update global variable whenever we examine a node with two 
 * children: we consider the maxSumPath candidate given by the node and the 
 * recursive maxPathSumDown of its two children.
 * 
 * time: O(N);	memory: O(tree height) <= O(N)
 */

int ans;
int maxPathSumDown(Node* n){
    if (n->left==NULL && n->right==NULL)
        return n->data;
    int R = INT_MIN, L = INT_MIN;
    if (n->left != NULL)
        L = maxPathSumDown(n->left);
    if (n->right != NULL)
        R = maxPathSumDown(n->right);
    if (n->left != NULL && n->right != NULL)
        ans = max(ans,R+L+n->data);
    return max(L,R) + n->data;
}

int maxPathSum(Node* root) { 
    ans = INT_MIN;
    maxPathSumDown(root);
    return ans;
}