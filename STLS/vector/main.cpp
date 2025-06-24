#include <iostream>
#include <vector>
#include <string>
using namespace std;

//
// WHY std::vector?
//
// Problem:
// - C-style arrays have fixed size.
// - Need to manage memory manually using new/delete.
// - Can't resize at runtime.
//
// Solution:
// - std::vector is a dynamic array:
//     - Automatically resizes as needed
//     - Provides safe access, memory management
//     - Move-enabled since C++11
//

// Function taking vector by value (uses move semantics if rvalue is passed)
void consume_vector(vector<string> v) {
    cout << "[consume_vector] Received vector of size " << v.size() << endl;
}

// Function taking by reference (no copy or move)
void inspect_vector(const vector<string>& v) {
    cout << "[inspect_vector] First item = " << (v.empty() ? "empty" : v[0]) << endl;
}

int main() {
    cout << "=== Vector Basics ===\n";

    vector<int> v1; // empty vector

    // Add elements
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    cout << "Size = " << v1.size() << ", Capacity = " << v1.capacity() << endl;

    // Access
    for (size_t i = 0; i < v1.size(); ++i) {
        cout << "v1[" << i << "] = " << v1[i] << endl;
    }

    // Range-based for loop (C++11+)
    for (int val : v1) {
        cout << val << " ";
    }
    cout << endl;

    //
    // Initialization Forms
    //
    cout << "\n=== Initialization ===\n";

    vector<int> v2 = {10, 20, 30};      // C++11 initializer list
    vector<int> v3(5, 100);             // 5 elements, each 100
    vector<int> v4(v2);                 // copy constructor
    vector<int> v5 = move(v3);          // move constructor (C++11+)

    cout << "v2 size = " << v2.size() << endl;
    cout << "v3 moved, now size = " << v3.size() << endl;
    cout << "v5 (moved from v3), size = " << v5.size() << endl;

    //
    // Resizing and Clearing
    //
    cout << "\n=== Resizing ===\n";
    vector<int> v = {1, 2, 3, 4, 5};
    v.resize(3);         // truncate to 3 elements
    v.resize(6, -1);     // expand to 6 with new elements = -1
    v.clear();           // removes all elements

    cout << "After clear(): size = " << v.size() << ", capacity = " << v.capacity() << endl;

    //
    // Capacity Management
    //
    cout << "\n=== Capacity and Reserve ===\n";

    vector<int> large;
    large.reserve(10); // pre-allocate for 10 elements
    for (int i = 0; i < 8; ++i) {
        large.push_back(i);
        cout << "After push_back(" << i << "): size = " << large.size()
             << ", capacity = " << large.capacity() << endl;
    }

    //
    // Move Semantics in Action
    //
    cout << "\n=== Move Semantics ===\n";

    vector<string> names;
    names.push_back("Alice");
    names.push_back("Bob");

    consume_vector(move(names)); // move instead of copy
    inspect_vector(names);       // names is now in valid but unspecified state

    return 0;
}

/*
============================================================================
VERSION NOTES – std::vector
============================================================================

C++98:
- Introduced std::vector in <vector>
- Dynamic resizing, RAII-based memory
- Element access: v[i], v.at(i)
- Supports copy, clear(), resize()

C++11:
- Introduced initializer_list: vector<int> v = {1, 2, 3};
- Move semantics: efficient transfer of resources (move constructor, move assignment)
- emplace_back(): in-place construction (e.g. objects)

C++14:
- Extended support for `auto`, generic lambdas with vector

C++17:
- Copy elision improvements: fewer unnecessary moves/copies
- `data()` is now safe to call even on empty vectors

C++20:
- `constexpr` vector usage allowed in constant expressions
- Works seamlessly with ranges and views (`std::ranges::view`)

============================================================================
VECTOR CHEAT SHEET – ALL IN ONE PLACE
============================================================================

Creation:
    vector<T> v;              // empty vector
    vector<T> v(n);           // n default-initialized elements
    vector<T> v(n, val);      // n elements, all = val
    vector<T> v = {a, b, c};  // initializer list (C++11)

Adding:
    v.push_back(x);           // adds at end
    v.emplace_back(args...);  // constructs at end (C++11+)

Removing:
    v.pop_back();             // remove last
    v.clear();                // remove all

Access:
    v[i], v.at(i)             // at() is bounds-checked
    v.front(), v.back()

Resizing:
    v.resize(n);              // trims or expands
    v.reserve(n);             // pre-allocate capacity
    v.shrink_to_fit();        // reduce capacity

Iterating:
    for (auto x : v)          // C++11+
    for (auto it = v.begin(); it != v.end(); ++it)

Other:
    v.size(), v.capacity(), v.empty()
    move(v), copy(v), swap(v1, v2)

============================================================================
MOVE SEMANTICS WITH VECTOR
============================================================================

- When passing vector by value:
    - If argument is an rvalue → move constructor used
    - If argument is an lvalue → copy constructor used

- To force move: use std::move(v)

- After move, original vector is still valid but size/data may be empty

============================================================================
*/
