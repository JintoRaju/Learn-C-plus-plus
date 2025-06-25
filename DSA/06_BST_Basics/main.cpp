#include <iostream>
using namespace std;

/*
================================================================================
DSA_06_BST_BASICS.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O A Binary Search Tree (BST) maintains sorted data in a binary tree format.
O It allows:
   O O(log n) average-case search, insert, delete
   O Fast range queries, floor/ceil, and order-based operations
O Used in maps, sets, DB indexes

================================================================================
TOPICS COVERED
================================================================================
1. BST Node structure
2. Insertion
3. Search
4. Inorder traversal (gives sorted order)
5. Find Min & Max
6. Deletion
================================================================================
*/

//------------------------------------------------------------------------------
// 1. BST NODE DEFINITION
//------------------------------------------------------------------------------
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

//------------------------------------------------------------------------------
// 2. INSERTION INTO BST
//------------------------------------------------------------------------------
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    // Duplicate keys are not inserted
    return root;
}

//------------------------------------------------------------------------------
// 3. SEARCH A KEY
//------------------------------------------------------------------------------
bool search(Node* root, int key) {
    if (!root) return false;
    if (root->key == key) return true;
    return key < root->key ? search(root->left, key) : search(root->right, key);
}

//------------------------------------------------------------------------------
// 4. INORDER TRAVERSAL (LEFT → ROOT → RIGHT)
//------------------------------------------------------------------------------
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

//------------------------------------------------------------------------------
// 5. FIND MINIMUM AND MAXIMUM IN BST
//------------------------------------------------------------------------------
int findMin(Node* root) {
    while (root && root->left)
        root = root->left;
    return root ? root->key : -1;
}

int findMax(Node* root) {
    while (root && root->right)
        root = root->right;
    return root ? root->key : -1;
}

//------------------------------------------------------------------------------
// 6. DELETE A NODE FROM BST
//------------------------------------------------------------------------------
Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Case 1: Node with one or no child
        if (!root->left) {
            Node* rightChild = root->right;
            delete root;
            return rightChild;
        } else if (!root->right) {
            Node* leftChild = root->left;
            delete root;
            return leftChild;
        }

        // Case 2: Node with two children — replace with inorder successor
        Node* successor = root->right;
        while (successor->left) successor = successor->left;
        root->key = successor->key;
        root->right = deleteNode(root->right, successor->key);
    }
    return root;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- nullptr usage instead of NULL
- auto can simplify loops

C++20:
- ranges and views simplify traversal (covered later with std::ranges)

================================================================================
TIME COMPLEXITY
================================================================================
Search / Insert / Delete:
- Best/Average: O(log n)
- Worst: O(n)     (skewed tree — like a linked list)

Inorder traversal: O(n)

================================================================================
BEST PRACTICES
================================================================================
O Inorder traversal of BST = sorted order
O Always balance BSTs (e.g., AVL/Red-Black Trees) for guaranteed O(log n)
O Don’t forget nullptr checks
O Avoid unnecessary recursion when not needed
*/

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    cout << "[Inorder] BST in sorted order: ";
    inorder(root); cout << "\n";

    cout << "[Search] 40? " << (search(root, 40) ? "Found" : "Not found") << "\n";
    cout << "[Min] " << findMin(root) << ", [Max] " << findMax(root) << "\n";

    cout << "[Delete] Deleting 20...\n";
    root = deleteNode(root, 20);
    inorder(root); cout << "\n";

    cout << "[Delete] Deleting 30...\n";
    root = deleteNode(root, 30);
    inorder(root); cout << "\n";

    cout << "[Delete] Deleting 50...\n";
    root = deleteNode(root, 50);
    inorder(root); cout << "\n";

    return 0;
}
