#include <iostream>
#include <vector>
using namespace std;

/*
================================================================================
DSA_01_ARRAYSBASICS.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O Arrays are the most basic way to store a collection of elements.
O They allow:
   O Fast random access (O(1) using index)
   O Simple iteration and storage
O Used as a base for advanced structures like heaps, stacks, matrices, etc.

================================================================================
TOPICS COVERED
================================================================================
1. Fixed-size C-style arrays (int arr[5])
2. Modern C++ `std::vector` (dynamic arrays)
3. Array traversal and bounds
4. Insertion, deletion, search
5. Time & space complexity
================================================================================
*/

//------------------------------------------------------------------------------
// 1. C-STYLE FIXED ARRAY (SIZE KNOWN AT COMPILE TIME)
//------------------------------------------------------------------------------
void fixed_array_demo() {
    int arr[5] = {10, 20, 30, 40, 50};  // size = 5, type = int

    cout << "[Fixed Array] Elements: ";
    for (int i = 0; i < 5; ++i) {
        cout << arr[i] << " ";  // O(1) access
    }
    cout << "\n";
}

//------------------------------------------------------------------------------
// 2. MODERN DYNAMIC ARRAY USING std::vector (C++98+)
//------------------------------------------------------------------------------
void vector_array_demo() {
    vector<int> v = {1, 2, 3};
    v.push_back(4); // O(1) amortized

    cout << "[std::vector] Elements: ";
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

//------------------------------------------------------------------------------
// 3. SEARCH IN ARRAY — LINEAR SEARCH (O(n))
//------------------------------------------------------------------------------
int linear_search(const vector<int>& arr, int key) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == key) return i;
    }
    return -1;
}

//------------------------------------------------------------------------------
// 4. INSERT & DELETE IN VECTOR (O(n))
//------------------------------------------------------------------------------
void insert_delete_demo() {
    vector<int> v = {1, 2, 3, 4, 5};

    // Insert 99 at position 2 (indexing starts from 0)
    v.insert(v.begin() + 2, 99);  // O(n)
    // Delete element at position 4
    v.erase(v.begin() + 4);       // O(n)

    cout << "[Insert/Delete] Resulting Vector: ";
    for (int val : v) {
        cout << val << " ";
    }
    cout << "\n";
}

//------------------------------------------------------------------------------
// 5. COMMON PITFALL: OUT OF BOUNDS ACCESS
//------------------------------------------------------------------------------
void out_of_bounds_demo() {
    vector<int> v = {10, 20, 30};
    cout << "[Out-of-Bounds Demo]\n";
    cout << "Safe access: v.at(2) = " << v.at(2) << "\n";
    // cout << "Unsafe access: v.at(5) = " << v.at(5) << "\n"; // throws exception
    // cout << "Unsafe access: v[5] = " << v[5] << "\n";       // undefined behavior
}

/*
================================================================================
VERSION NOTES
================================================================================
C++98:
- Introduced std::vector

C++11:
- `auto`, range-based for loops (used here)

C++20:
- `std::span` for safe array views (we'll cover later)
- Ranges and concepts for cleaner loops

================================================================================
TIME COMPLEXITY
================================================================================
Access element (index i):     O(1)
Insert/Delete at middle:      O(n)
Search (Linear):              O(n)
Push_back (vector):           O(1) amortized
================================================================================
BEST PRACTICES
================================================================================
O Prefer std::vector over raw arrays — safer and more flexible
O Use `.at()` instead of `[]` to avoid crash
O Avoid insert/delete at middle unless needed
O Don't manually resize C-style arrays — use vector
*/

int main() {
    fixed_array_demo();       // Static array
    vector_array_demo();      // std::vector
    insert_delete_demo();     // Insert/Delete
    out_of_bounds_demo();     // Bound-safe access

    // Try searching for an element
    vector<int> test = {5, 10, 15, 20};
    int index = linear_search(test, 15);
    cout << "[Search] Found 15 at index: " << index << "\n";

    return 0;
}
