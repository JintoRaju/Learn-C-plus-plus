#include <iostream>
#include <set>
#include <string>
using namespace std;

//
// WHY std::multiset?
//
// Problem:
// - std::set allows only unique items (e.g., {1,2,3})
// - Sometimes we need to store duplicate values (e.g., {1,2,2,3})
//
// Solution:
// - `std::multiset<T>` is just like `std::set<T>`
//     - Keeps elements **sorted**
//     - **Allows duplicates**
//     - Still offers log(N) insert, find, erase
//

void basic_multiset_usage() {
    cout << "=== std::multiset Basics ===\n";

    multiset<int> ms;

    ms.insert(30);
    ms.insert(10);
    ms.insert(20);
    ms.insert(10);  // allowed!

    cout << "Elements (sorted, duplicates allowed): ";
    for (int val : ms) cout << val << " ";
    cout << endl;

    cout << "Count of 10: " << ms.count(10) << endl;  // returns 2
    cout << "Count of 15: " << ms.count(15) << endl;
}

void erase_all_occurrences() {
    cout << "\n=== Erasing All Occurrences ===\n";

    multiset<string> names = {"Zara", "Anna", "Anna", "John"};

    cout << "Before erase: ";
    for (auto& name : names) cout << name << " ";
    cout << endl;

    names.erase("Anna");  // removes all "Anna"

    cout << "After erase: ";
    for (auto& name : names) cout << name << " ";
    cout << endl;
}

void erase_one_occurrence() {
    cout << "\n=== Erasing Only One Occurrence ===\n";

    multiset<int> ms = {10, 20, 10, 30};

    auto it = ms.find(10);  // finds the first 10
    if (it != ms.end()) ms.erase(it);  // erase only one instance

    for (int x : ms) cout << x << " ";  // should still have one 10
    cout << endl;
}

void range_access_demo() {
    cout << "\n=== Range Access with equal_range ===\n";

    multiset<int> ms = {10, 20, 20, 20, 30};

    auto [first, last] = ms.equal_range(20);  // C++17 structured bindings

    cout << "All 20s: ";
    for (auto it = first; it != last; ++it)
        cout << *it << " ";
    cout << endl;
}

int main() {
    basic_multiset_usage();
    erase_all_occurrences();
    erase_one_occurrence();
    range_access_demo();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::multiset
============================================================================

C++98:
- Introduced with other associative containers
- Sorted by default with `operator<`
- Allows duplicate keys

C++11:
- Added emplace() for in-place insertion
- Move semantics supported
- Range-based for usable

C++14:
- Transparent comparators allowed (advanced use)

C++17:
- `equal_range()` pairs usable with structured bindings
- Node-based operations like `extract()`, `merge()` supported

C++20:
- constexpr support
- Integration with ranges

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Duplicates are **kept**, all sorted in-order
- `count(x)` returns actual number of times `x` appears
- `erase(x)` removes **all** copies of x
- `erase(iterator)` removes **only one** copy
- `equal_range(x)` gives range of iterators to all `x` (like `.lower_bound()` to `.upper_bound()`)

============================================================================
COMPARISON – set vs multiset vs unordered_set
============================================================================

| Feature              | set<T>            | multiset<T>        | unordered_set<T>  |
|----------------------|-------------------|--------------------|-------------------|
| Duplicates allowed   |  No             |  Yes             |  No             |
| Sorted               |  Yes            |  Yes             |  No             |
| Underlying data      | Red-black tree    | Red-black tree     | Hash table        |
| Complexity (insert)  | O(log N)          | O(log N)           | O(1) avg          |
| erase(x) removes     | the key           | all matching keys  | the key           |

============================================================================
CHEAT SHEET – std::multiset
============================================================================

Declaration:
    multiset<T> ms;

Insertion:
    ms.insert(x);
    ms.emplace(args...);         // C++11+

Lookup:
    ms.find(x);                  // iterator to one of them
    ms.count(x);                 // number of times x appears
    ms.equal_range(x);           // pair<first, last>

Erase:
    ms.erase(x);                 // all of them
    ms.erase(it);                // only one element

Iteration:
    for (auto x : ms) { ... }

*/

