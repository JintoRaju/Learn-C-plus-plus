#include <iostream>
#include <deque>
using namespace std;

//
// WHY std::deque?
//
// Problem:
// - `std::vector` allows efficient insertions/removals only at the back.
// - Insertions/removals at front are costly (O(n)) in vector.
//
// Solution:
// - `std::deque` supports:
//     - Fast O(1) push/pop at BOTH front and back
//     - Random access like vector
// - Internally: segmented memory blocks (not a flat buffer)
//

void deque_basics() {
    cout << "=== std::deque Basics ===\n";

    deque<int> dq;

    dq.push_back(10);  // back insert
    dq.push_front(20); // front insert
    dq.push_back(30);

    // Current deque: [20, 10, 30]
    for (size_t i = 0; i < dq.size(); ++i) {
        cout << "dq[" << i << "] = " << dq[i] << endl;
    }

    dq.pop_front();  // remove 20
    dq.pop_back();   // remove 30

    cout << "After pop_front and pop_back:\n";
    for (int x : dq) {
        cout << x << " ";
    }
    cout << endl;
}

void deque_advanced() {
    cout << "\n=== Advanced Operations ===\n";

    deque<int> d = {1, 2, 3, 4, 5};

    d.insert(d.begin() + 2, 99);  // insert at middle
    d.erase(d.begin() + 1);       // remove second element

    for (auto it = d.begin(); it != d.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Using at() – bounds-checked
    cout << "d.at(2) = " << d.at(2) << endl;

    d.clear();  // remove all elements
    cout << "After clear(), is empty? " << boolalpha << d.empty() << endl;
}

void deque_capacity() {
    cout << "\n=== Size, Shrink and Resize ===\n";

    deque<int> d(5, 7);  // 5 elements, all 7

    cout << "Initial size: " << d.size() << endl;

    d.resize(3);       // shrink
    d.resize(6, -1);   // expand, new values = -1

    for (int x : d) cout << x << " ";
    cout << endl;
}

int main() {
    deque_basics();
    deque_advanced();
    deque_capacity();
    return 0;
}

/*
===========================================================================
VERSION NOTES – std::deque
===========================================================================

C++98:
- Introduced std::deque<T>
- Features:
    - Random access (like vector)
    - O(1) push_front, push_back
    - No capacity() or reserve()
    - Not contiguous: cannot use .data()

C++11:
- Added initializer_list support:
    deque<int> d = {1,2,3};

- Move semantics:
    deque<string> d = move(oldDeque);

- Range-based for loop support

C++14:
- Enhanced emplace functions

C++17:
- std::deque::data() still not present (because memory is segmented)

C++20:
- Can be used in constexpr contexts
- Compatible with ranges and views (via std::ranges)

===========================================================================
COMPARISON – deque vs vector
===========================================================================

| Feature              | vector              | deque               |
|----------------------|---------------------|---------------------|
| Random access        |  Fast              |  Fast             |
| push_back            |  Fast              |  Fast             |
| push_front           |  Slow (O(n))       |  Fast (O(1))      |
| pop_front            |  Slow              |  Fast             |
| insert in middle     |  Slow              |  Slow             |
| .data()              |  available         |  not available    |
| Contiguous memory    |  Yes               |  No               |
| Capacity() support   |  Yes               |  No               |
| Use case             | Stack-like          | Double-ended queue  |

===========================================================================
TINY BUT IMPORTANT DETAILS
===========================================================================

- std::deque is NOT contiguous — std::data() is missing
- Ideal for frequent insertions/removals at front **and** back
- Avoid using deque if you rely on pointer math or raw data access
- Unlike vector, no reserve()/capacity() — memory growth handled differently
- Iterator invalidation:
    - insert/erase anywhere invalidates all iterators after it
    - push_front/push_back may invalidate all iterators (implementation defined)

===========================================================================
CHEAT SHEET – std::deque
===========================================================================

Creation:
    deque<T> dq;
    deque<T> dq(n);              // n default-initialized
    deque<T> dq(n, val);         // n elements of value val
    deque<T> dq = {a, b, c};     // C++11 initializer

Adding/Removing:
    dq.push_back(val);
    dq.push_front(val);
    dq.pop_back();
    dq.pop_front();

Access:
    dq[i], dq.at(i), dq.front(), dq.back()

Modifying:
    dq.insert(pos, val);
    dq.erase(pos);
    dq.clear(), dq.resize(n), dq.empty()

Iteration:
    for (auto x : dq)            // C++11+
    for (auto it = dq.begin(); it != dq.end(); ++it)

*/
