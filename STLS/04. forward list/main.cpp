#include <iostream>
#include <forward_list>
using namespace std;

//
// WHY std::forward_list?
//
// Problem:
// - std::list is doubly-linked → extra memory for back pointers
// - Unnecessary if you only need single-directional access
//
// Solution (C++11):
// - std::forward_list is a **singly linked list**
// - Saves memory (one pointer per node)
// - Ideal for insert-heavy operations at front or mid
// - Lightweight alternative to list
//

void forward_list_basics() {
    cout << "=== std::forward_list Basics ===\n";

    forward_list<int> fl;

    fl.push_front(10);  // [10]
    fl.push_front(20);  // [20, 10]
    fl.push_front(30);  // [30, 20, 10]

    for (int x : fl) cout << x << " ";
    cout << endl;

    fl.pop_front(); // remove 30

    cout << "After pop_front: ";
    for (int x : fl) cout << x << " ";
    cout << endl;
}

void forward_list_insertion() {
    cout << "\n=== Insertion and Erase ===\n";

    forward_list<int> fl = {1, 2, 3, 4};

    auto prev = fl.before_begin(); // points before first element
    auto curr = fl.begin();
    advance(curr, 2); // move to 3rd element (value = 3)

    fl.insert_after(curr, 99);  // insert after 3
    fl.erase_after(curr);       // erase 99

    for (int x : fl) cout << x << " ";
    cout << endl;
}

void forward_list_algorithms() {
    cout << "\n=== sort, reverse, unique, remove ===\n";

    forward_list<int> fl = {3, 1, 4, 2, 4, 1, 1};

    fl.sort();     // uses merge sort internally
    fl.unique();   // removes adjacent duplicates
    fl.reverse();  // reverse the list

    fl.remove(1);  // remove all 1s

    for (int x : fl) cout << x << " ";
    cout << endl;
}

void forward_list_merge_splice() {
    cout << "\n=== merge and splice_after ===\n";

    forward_list<int> a = {1, 3, 5};
    forward_list<int> b = {2, 4, 6};

    a.merge(b); // both must be sorted
    for (int x : a) cout << x << " ";
    cout << "\nIs b empty after merge? " << boolalpha << b.empty() << endl;

    forward_list<int> x = {10, 20};
    forward_list<int> y = {30, 40};

    auto it = x.before_begin();
    advance(it, 1); // point after 10

    x.splice_after(it, y); // insert y after 10
    cout << "After splice: ";
    for (int val : x) cout << val << " ";
    cout << "\nIs y empty after splice? " << (y.empty() ? "Yes" : "No") << endl;
}

int main() {
    forward_list_basics();
    forward_list_insertion();
    forward_list_algorithms();
    forward_list_merge_splice();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::forward_list
============================================================================

C++11:
- Introduced as lightweight alternative to std::list
- Singly linked list (forward only)
- Functions: push_front, pop_front, insert_after, erase_after
- Supports: sort(), merge(), unique(), reverse()

C++14:
- Improvements to emplace_after and allocators

C++17:
- Safe use of .before_begin()
- More efficient merge under some compilers

C++20:
- Usable in constexpr
- Compatible with std::ranges

============================================================================
DIFFERENCES – forward_list vs list
============================================================================

| Feature             | std::list           | std::forward_list      |
|---------------------|---------------------|-------------------------|
| Node type           | Doubly linked       | Singly linked           |
| Memory usage        | Higher              | Lower                   |
| Insert O(1)         | Anywhere            | After known position    |
| .size()             |  Available         |  Not available         |
| .back()             |  Yes               |  Not available         |
| Iterators           | Bidirectional       | Forward only            |
| Indexing            |  (No [i])          |  (No [i])              |
| Best for            | Heavy insert/erase  | Light memory insertions |

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- No random access (`fl[i]` is invalid)
- No `.size()` — must count manually if needed (O(n))
- Use `before_begin()` when inserting at the start
- `insert_after()` and `erase_after()` take iterator **before** the target
- Ideal for memory-limited systems (embedded, high-performance)

============================================================================
CHEAT SHEET – std::forward_list
============================================================================

Declaration:
    forward_list<T> fl;
    forward_list<T> fl = {a, b, c};  // C++11+

Insertion:
    fl.push_front(val);
    fl.insert_after(it, val);
    fl.emplace_after(it, args);

Removal:
    fl.pop_front();
    fl.erase_after(it);
    fl.remove(val);
    fl.remove_if(pred);

Algorithms:
    fl.sort();       // merge sort
    fl.unique();     // remove adjacent duplicates
    fl.reverse();    // reverse order
    fl.merge(other); // must be sorted
    fl.splice_after(it, other);

Traversal:
    for (auto it = fl.begin(); it != fl.end(); ++it)
    for (int x : fl) // C++11

*/
