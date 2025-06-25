#include <iostream>
#include <algorithm>
using namespace std;

/*
================================================================================
DSA_07_AVL_BALANCEDBST.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O Plain BSTs can become skewed (degenerated into linked lists)
O In worst case, BST operations degrade to O(n)
O AVL Trees (introduced in 1962) solve this by:
   O Automatically rebalancing on every insertion/deletion
   O Ensuring height difference (balance factor) between subtrees ≤ 1
O AVL trees always maintain O(log n) height.

================================================================================
TOPICS COVERED
================================================================================
1. Node structure with height
2. Height & balance factor
3. Left & right rotations
4. Insertion with balancing
================================================================================
*/

struct AVLNode {
    int key, height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int val) : key(val), height(1), left(nullptr), right(nullptr) {}
};

//------------------------------------------------------------------------------
// 1. GET HEIGHT OF A NODE
//------------------------------------------------------------------------------
int height(AVLNode* node) {
    return node ? node->height : 0;
}

//------------------------------------------------------------------------------
// 2. GET BALANCE FACTOR OF A NODE
//------------------------------------------------------------------------------
int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

//------------------------------------------------------------------------------
// 3. RIGHT ROTATION (RR)
//------------------------------------------------------------------------------
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

//------------------------------------------------------------------------------
// 4. LEFT ROTATION (LL)
//------------------------------------------------------------------------------
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

//------------------------------------------------------------------------------
// 5. INSERT WITH BALANCING
//------------------------------------------------------------------------------
AVLNode* insert(AVLNode* root, int key) {
    if (!root) return new AVLNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; // No duplicates

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LEFT LEFT CASE
    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    // RIGHT RIGHT CASE
    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    // LEFT RIGHT CASE
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RIGHT LEFT CASE
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

//------------------------------------------------------------------------------
// INORDER TRAVERSAL — AVL IS STILL A BST
//------------------------------------------------------------------------------
void inorder(AVLNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Used nullptr, range-safe loops

C++20:
- More functional-style APIs and ranges (covered later in trees + views)

================================================================================
TIME COMPLEXITY
================================================================================
Insert/Delete/Search:  O(log n)     [Always balanced]

================================================================================
BEST PRACTICES
================================================================================
O AVL maintains strict balance — faster lookup, more rotations
O For write-heavy apps, prefer Red-Black Trees (less rebalancing)
O In real-world apps, use STL maps (usually Red-Black Trees underneath)
*/

int main() {
    AVLNode* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30); // RR rotation
    root = insert(root, 40);
    root = insert(root, 50); // RR rotation
    root = insert(root, 25); // RL rotation

    cout << "[Inorder Traversal] AVL Tree: ";
    inorder(root); cout << "\n";

    return 0;
}
