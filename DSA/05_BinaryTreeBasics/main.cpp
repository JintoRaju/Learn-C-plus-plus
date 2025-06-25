#include <iostream>
#include <queue>
using namespace std;

/*
================================================================================
DSA_05_BINARYTREEBASICS.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
✔ Arrays, Linked Lists are linear structures.
✔ Trees are **non-linear**, used for:
   ➤ Hierarchical data (e.g., File System, XML/HTML)
   ➤ Efficient searching (Binary Search Tree)
   ➤ Balanced operations (AVL, Red-Black Trees)
   ➤ Expression evaluation, decision trees, etc.

================================================================================
TOPICS COVERED
================================================================================
1. Binary Tree Node structure
2. Preorder, Inorder, Postorder traversal (DFS)
3. Level-order traversal (BFS)
4. Building a simple tree
================================================================================
*/

//------------------------------------------------------------------------------
// 1. NODE DEFINITION (BINARY TREE)
//------------------------------------------------------------------------------
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//------------------------------------------------------------------------------
// 2. DEPTH-FIRST TRAVERSALS (Recursive)
//------------------------------------------------------------------------------

// INORDER: Left → Root → Right
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

// PREORDER: Root → Left → Right
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

// POSTORDER: Left → Right → Root
void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

//------------------------------------------------------------------------------
// 3. LEVEL-ORDER TRAVERSAL (Breadth-First Search using Queue)
//------------------------------------------------------------------------------
void levelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        cout << node->val << " ";
        if (node->left)  q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- `nullptr` instead of NULL
- `auto` and range-based `for` (not used here due to pointers)

C++20:
- `concepts`, `std::ranges`, and `views` for tree-like structures (covered later)

================================================================================
TIME COMPLEXITY
================================================================================
For all traversals:
- Time:  O(n)        [Visit every node once]
- Space: O(h) stack  [Recursive depth = height h]

================================================================================
BEST PRACTICES
================================================================================
✔ Always check for null pointers in recursion
✔ Use level-order for shortest path or layer-by-layer problems
✔ Inorder traversal of BST returns sorted order
✔ Use helper functions to separate logic from main()
*/

int main() {
    // Building the following tree:
    //         1
    //       /   \
    //     2       3
    //    / \     /
    //   4   5   6

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);

    cout << "[Inorder]   ";
    inorder(root); cout << "\n";

    cout << "[Preorder]  ";
    preorder(root); cout << "\n";

    cout << "[Postorder] ";
    postorder(root); cout << "\n";

    cout << "[LevelOrder] ";
    levelOrder(root); cout << "\n";

    return 0;
}
