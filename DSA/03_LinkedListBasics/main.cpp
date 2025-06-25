#include <iostream>
using namespace std;

/*
================================================================================
DSA_03_LINKEDLISTBASICS.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O Arrays are fixed in size and costly to insert/delete in the middle.
O Linked Lists allow:
   O Dynamic memory (no fixed size)
   O Efficient insertions/deletions at any point (O(1) if pointer known)
O They’re the basis for stacks, queues, graphs, etc.

================================================================================
TOPICS COVERED
================================================================================
1. Node definition
2. Insertion at head, tail
3. Deletion of node
4. Search
5. Print / Traverse
================================================================================
*/

//------------------------------------------------------------------------------
// 1. DEFINITION OF NODE (SINGLY LINKED LIST)
//------------------------------------------------------------------------------
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

//------------------------------------------------------------------------------
// 2. INSERT AT HEAD (O(1))
//------------------------------------------------------------------------------
void insertAtHead(Node*& head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    head = newNode;
}

//------------------------------------------------------------------------------
// 3. INSERT AT TAIL (O(n))
//------------------------------------------------------------------------------
void insertAtTail(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}

//------------------------------------------------------------------------------
// 4. DELETE A NODE BY VALUE (FIRST OCCURRENCE)
//------------------------------------------------------------------------------
void deleteNode(Node*& head, int val) {
    if (!head) return;
    if (head->data == val) {
        Node* del = head;
        head = head->next;
        delete del;
        return;
    }
    Node* curr = head;
    while (curr->next && curr->next->data != val)
        curr = curr->next;
    if (curr->next) {
        Node* del = curr->next;
        curr->next = curr->next->next;
        delete del;
    }
}

//------------------------------------------------------------------------------
// 5. SEARCH FOR A VALUE
//------------------------------------------------------------------------------
bool search(Node* head, int val) {
    while (head) {
        if (head->data == val) return true;
        head = head->next;
    }
    return false;
}

//------------------------------------------------------------------------------
// 6. PRINT THE LINKED LIST
//------------------------------------------------------------------------------
void printList(Node* head) {
    cout << "[List] ";
    while (head) {
        cout << head->data << " → ";
        head = head->next;
    }
    cout << "null\n";
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11+:
- You can use `nullptr` instead of NULL
- smart pointers (`unique_ptr`) can replace raw pointers (covered later)

================================================================================
TIME COMPLEXITY
================================================================================
Insert at head:     O(1)
Insert at tail:     O(n)
Delete node:        O(n)
Search:             O(n)
================================================================================
BEST PRACTICES
================================================================================
O Always check for null pointer before dereferencing
O Prefer `smart pointers` in modern C++
O Don't forget to `delete` to avoid memory leaks (or use smart pointers)
*/

int main() {
    Node* head = nullptr;

    insertAtHead(head, 30);
    insertAtHead(head, 20);
    insertAtHead(head, 10);
    insertAtTail(head, 40);
    printList(head);  // 10 → 20 → 30 → 40

    cout << "[Search] 20? " << (search(head, 20) ? "Yes" : "No") << "\n";
    cout << "[Search] 50? " << (search(head, 50) ? "Yes" : "No") << "\n";

    deleteNode(head, 20);  // remove 20
    printList(head);       // 10 → 30 → 40

    return 0;
}
