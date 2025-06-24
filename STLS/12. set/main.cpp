#include <iostream>
#include <set>
#include <string>
using namespace std;

//
// WHY std::set?
//
// Problem:
// - Need a sorted collection where elements are unique
// - Need fast lookup, insertion, deletion (log N time)
//
// Solution:
// - `std::set<T>` is an ordered container (uses balanced BST: red-black tree)
//     - All elements are automatically sorted
//     - All elements are unique (no duplicates allowed)
//     - Logarithmic complexity: insert, find, erase → O(log N)
//

void basic_set_usage() {
    cout << "=== std::set Basics ===\n";

    set<int> s;

    s.insert(40);
    s.insert(10);
    s.insert(30);
    s.insert(10);  // duplicate, ignored

    cout << "Elements (sorted & unique): ";
    for (int val : s) cout << val << " ";
    cout << endl;

    cout << "Contains 30? " << boolalpha << (s.count(30) > 0) << endl;
    cout << "Contains 25? " << (s.count(25) > 0) << endl;
}

void set_search_erase() {
    cout << "\n=== Search and Erase ===\n";

    set<string> names = {"Anna", "John", "Zara"};

    auto it = names.find("John");
    if (it != names.end()) {
        cout << "Found: " << *it << endl;
        names.erase(it);  // erase by iterator
    }

    cout << "After erase: ";
    for (const auto& name : names) cout << name << " ";
    cout << endl;
}

void set_bounds_and_range() {
    cout << "\n=== Lower and Upper Bounds ===\n";

    set<int> s = {10, 20, 30, 40};

    auto it1 = s.lower_bound(25);  // first element ≥ 25 → 30
    auto it2 = s.upper_bound(30);  // first element > 30  → 40

    if (it1 != s.end()) cout << "lower_bound(25): " << *it1 << endl;
    if (it2 != s.end()) cout << "upper_bound(30): " << *it2 << endl;
}

int main() {
    basic_set_usage();
    set_search_erase();
    set_bounds_and_range();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::set
============================================================================

C++98:
- Introduced std::set and std::multiset
- All elements are unique
- Internally uses red-black tree (balanced BST)
- Provides: insert, erase, find, count, lower_bound, upper_bound

C++11:
- Move semantics supported
- insert() → accepts move-enabled objects
- emplace() added for in-place construction
- Range-based for loops usable with set
- `auto` deduction helps with iterators

C++14:
- Transparent comparators (`set<Key, Compare>`) support (advanced)

C++17:
- Improved performance via node handle & splicing
- `.extract()`, `.merge()` support (for tree surgery between containers)

C++20:
- Fully usable with constexpr
- More STL-algorithm integrations

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Inserting an existing value → silently ignored
- Insertion order doesn't matter → elements always stored sorted
- `count(x)` always 0 or 1 — no duplicates allowed
- Iterators are **bidirectional**, not random-access
- Invalidates only the erased element, not others
- Supports custom comparators via functor or lambda

============================================================================
COMPARISON – set vs unordered_set vs multiset
============================================================================

| Feature             | set<T>              | unordered_set<T>     | multiset<T>           |
|---------------------|----------------------|------------------------|------------------------|
| Sorted?             |  Yes               |  No                 |  Yes                 |
| Unique elements?    |  Yes               |  Yes               |  No (allows dupes)   |
| Underlying type     | Balanced tree        | Hash table           | Balanced tree          |
| Lookup complexity   | O(log N)             | O(1) average          | O(log N)               |
| Order of elements   | Ascending (default)  | No order             | Ascending (default)    |

============================================================================
CHEAT SHEET – std::set
============================================================================

Declaration:
    set<T> s;
    set<string> names;

Insertion:
    s.insert(x);            // ignores duplicates
    s.emplace(args...);     // C++11+

Search:
    s.find(x);              // returns iterator or end()
    s.count(x);             // 0 or 1

Removal:
    s.erase(x);             // by value
    s.erase(it);            // by iterator

Bounds:
    s.lower_bound(x);       // first element ≥ x
    s.upper_bound(x);       // first element > x

Iterate:
    for (auto val : s) { ... }

*/

