#include <iostream>
#include <list>
using namespace std;

//
// WHY std::list?
//
// Problem:
// - vector/deque allow O(1) insertion/removal only at ends
// - inserting/removing in middle = O(n) due to element shifting
//
// Solution:
// - std::list is a doubly linked list:
//     - Fast O(1) insert/erase at **any position**
//     - No shifting or memory movement
//     - Supports bidirectional iterators
//

void list_basics() {
    cout << "=== std::list Basics ===\n";

    list<int> lst;  // empty list

    lst.push_back(10);  // [10]
    lst.push_front(20); // [20, 10]
    lst.push_back(30);  // [20, 10, 30]

    for (int val : lst) {
        cout << val << " ";
    }
    cout << endl;

    lst.pop_front();  // remove 20
    lst.pop_back();   // remove 30

    cout << "After pop_front and pop_back: ";
    for (int val : lst) cout << val << " ";
    cout << endl;
}

void list_insertion() {
    cout << "\n=== Insertion and Erase ===\n";

    list<int> lst = {1, 2, 3, 4, 5};

    auto it = lst.begin();
    advance(it, 2);  // move iterator to 3rd element (value 3)

    lst.insert(it, 99);   // [1, 2, 99, 3, 4, 5]

    it = lst.begin();
    advance(it, 4);       // now at value 4
    lst.erase(it);        // erase 4

    for (int val : lst) cout << val << " ";
    cout << endl;
}

void list_unique_sort_reverse() {
    cout << "\n=== list::sort, reverse, unique ===\n";

    list<int> lst = {3, 1, 4, 2, 5, 3, 1, 1, 5};

    lst.sort();     // in-place sort (O(n log n))
    lst.unique();   // remove adjacent duplicates
    lst.reverse();  // reverse the list

    for (int x : lst) cout << x << " ";
    cout << endl;
}

void list_splice_demo() {
    cout << "\n=== list::splice ===\n";

    list<int> a = {1, 2, 3};
    list<int> b = {4, 5, 6};

    auto pos = a.end(); // splice at end of `a`
    a.splice(pos, b);   // move all from b into a

    cout << "List a after splice: ";
    for (int x : a) cout << x << " ";
    cout << endl;

    cout << "List b after splice (should be empty): ";
    cout << (b.empty() ? "[empty]" : "not empty") << endl;
}

int main() {
    list_basics();
    list_insertion();
    list_unique_sort_reverse();
    list_splice_demo();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::list
============================================================================

C++98:
- Fully supported: push_front/back, insert, erase, sort, reverse
- Bidirectional iterators (not random access)
- Splice support (fast list merge/move)

C++11:
- Initializer list: list<int> l = {1,2,3};
- Move semantics
- emplace_front/back/insert → construct in-place
- Range-based for loop

C++14:
- std::list got better allocator support

C++17:
- Improved performance for splice under some compilers

C++20:
- Usable in constexpr contexts
- Works with std::ranges views

============================================================================
COMPARISON – list vs vector vs deque
============================================================================

| Feature               | vector       | deque        | list          |
|-----------------------|--------------|--------------|---------------|
| push_front/back       | (O(n)/O(1)) |  (O(1)/O(1)) | (O(1)/O(1)) |
| insert/erase middle   |  slow O(n)  |  slow O(n)  |  fast O(1)   |
| Random access         |  [i]        |  [i]        |  (only iterators) |
| Memory layout         | Contiguous   | Segmented    | Node-based    |
| Iterators             | Random       | Random       | Bidirectional |
| .data() available     |  yes        |  no         |  no          |
| Use case              | Frequent back | Front & back | Frequent insert/remove in middle

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- list is node-based → no random access → can't use `list[i]`
- iterator stays valid even after insert/erase at other positions
- std::list::splice moves elements between lists in O(1) time (no copy/move)
- sort() is member function — uses list's own merge sort internally
- unique() removes **adjacent** duplicates only

============================================================================
CHEAT SHEET – std::list
============================================================================

Declaration:
    list<T> l;
    list<T> l = {a, b, c};  // C++11+

Insertion:
    l.push_back(val);
    l.push_front(val);
    l.insert(pos, val);
    l.emplace_back(val);  // in-place

Deletion:
    l.pop_back(), l.pop_front()
    l.erase(pos), l.clear(), l.remove(val), l.remove_if(pred)

Other:
    l.sort(), l.reverse(), l.unique()
    l.merge(other), l.splice(pos, other)

Iterators:
    list<T>::iterator it = l.begin();
    advance(it, n); // move iterator n steps

*/
