#include <iostream>
#include <map>
#include <string>
using namespace std;

//
// WHY std::multimap?
//
// Problem:
// - `std::map` allows only one value per key (unique keys)
// - Need multiple values per key (e.g., a word appearing on many pages)
//
// Solution:
// - `std::multimap<Key, Value>` stores keys in sorted order
//   and allows duplicate keys!
// - Uses red-black tree internally (log N ops)
//

void basic_multimap_usage() {
    cout << "=== std::multimap Basics ===\n";

    multimap<string, int> mm;

    mm.insert({"apple", 1});
    mm.insert({"banana", 2});
    mm.insert({"apple", 3});   // duplicate key allowed
    mm.insert({"banana", 4});

    for (const auto& [key, value] : mm) {
        cout << key << " → " << value << endl;
    }

    cout << "Count of 'apple': " << mm.count("apple") << endl;
}

void search_and_range() {
    cout << "\n=== equal_range() and find() ===\n";

    multimap<string, int> phonebook = {
        {"Alice", 123},
        {"Bob", 456},
        {"Alice", 789}
    };

    // equal_range returns [first, last) of all entries with the key
    auto [first, last] = phonebook.equal_range("Alice");

    cout << "All phone numbers for Alice: ";
    for (auto it = first; it != last; ++it) {
        cout << it->second << " ";
    }
    cout << endl;

    // find() just returns the first occurrence
    auto it = phonebook.find("Alice");
    if (it != phonebook.end()) {
        cout << "First Alice entry: " << it->second << endl;
    }
}

void erase_all_for_key() {
    cout << "\n=== Erase All for a Key ===\n";

    multimap<int, string> m = {
        {1, "One"},
        {2, "Two"},
        {2, "Deux"},
        {3, "Three"}
    };

    cout << "Before erase:\n";
    for (auto& [k, v] : m)
        cout << k << " → " << v << endl;

    m.erase(2);  // removes all entries with key = 2

    cout << "After erase:\n";
    for (auto& [k, v] : m)
        cout << k << " → " << v << endl;
}

int main() {
    basic_multimap_usage();
    search_and_range();
    erase_all_for_key();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::multimap
============================================================================

C++98:
- Introduced with STL associative containers
- Allows duplicate keys
- Internally uses red-black tree (sorted)

C++11:
- Added `emplace()` for in-place construction
- Move support
- `range-based for` usable

C++17:
- Node-based operations (`extract()`, `merge()`)
- Structured bindings (`auto [k, v]`)

C++20:
- Constexpr-friendly
- More integration with ranges library

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Keys are sorted (by default ascending)
- Allows duplicate keys (unlike `std::map`)
- `find(key)` returns first match (others accessible via equal_range)
- `count(key)` gives number of matches
- `erase(key)` removes **all** matching keys
- `erase(it)` removes only one specific element

============================================================================
COMPARISON – map vs multimap vs unordered_map
============================================================================

| Feature               | map<K,V>           | multimap<K,V>         | unordered_map<K,V>  |
|-----------------------|--------------------|------------------------|---------------------|
| Duplicates allowed    |  No              |  Yes                |  No              |
| Sorted keys           |  Yes             |  Yes                |  No              |
| Underlying structure  | Red-black tree     | Red-black tree         | Hash table          |
| Iteration order       | Sorted             | Sorted                | Unordered           |
| Lookup speed          | O(log N)           | O(log N)              | O(1) avg            |

============================================================================
CHEAT SHEET – std::multimap
============================================================================

Declaration:
    multimap<Key, Value> m;

Insertion:
    m.insert({k, v});
    m.emplace(k, v);           // C++11+

Search:
    m.find(k);                 // returns iterator to *first* match
    m.equal_range(k);          // returns pair<first, last>
    m.count(k);                // returns how many times key appears

Erase:
    m.erase(k);                // removes all
    m.erase(it);               // removes one occurrence

Iteration:
    for (auto& [k, v] : m) { ... }  // C++17+

*/

