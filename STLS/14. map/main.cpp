#include <iostream>
#include <map>
#include <string>
using namespace std;

//
// WHY std::map?
//
// Problem:
// - Need a key → value dictionary (like Python dict or JS object)
// - Need keys to be sorted automatically
//
// Solution:
// - `std::map<Key, Value>` stores unique keys in sorted order (by default, ascending)
// - Internally uses red-black tree (logarithmic insert, find, erase)
// - Syntax: m[key] = value;
//

void basic_map_usage() {
    cout << "=== std::map Basics ===\n";

    map<string, int> age;

    age["Alice"] = 30;
    age["Bob"] = 25;
    age["Charlie"] = 28;

    // Overwrites existing key
    age["Bob"] = 26;

    for (const auto& pair : age) {
        cout << pair.first << " → " << pair.second << endl;
    }

    cout << "Age of Bob: " << age["Bob"] << endl;  // access by key
}

void insert_and_find() {
    cout << "\n=== insert() and find() ===\n";

    map<int, string> idName;

    idName.insert({101, "Alice"});
    idName.insert(make_pair(102, "Bob"));

    auto result = idName.insert({102, "DuplicateBob"});  // not inserted
    cout << "Inserted 102 again? " << boolalpha << result.second << endl;

    auto it = idName.find(101);
    if (it != idName.end())
        cout << "Found 101 → " << it->second << endl;
}

void erase_and_bounds() {
    cout << "\n=== erase() and bounds ===\n";

    map<int, string> m = {
        {10, "A"},
        {20, "B"},
        {30, "C"},
        {40, "D"}
    };

    m.erase(20);  // erase by key

    auto it1 = m.lower_bound(25);  // first key >= 25 → 30
    auto it2 = m.upper_bound(30);  // first key > 30 → 40

    if (it1 != m.end()) cout << "lower_bound(25): " << it1->first << endl;
    if (it2 != m.end()) cout << "upper_bound(30): " << it2->first << endl;
}

void structured_binding_and_emplace() {
    cout << "\n=== C++17 structured bindings + emplace ===\n";

    map<int, string> m;
    m.emplace(1, "One");  // C++11+: more efficient
    m.emplace(2, "Two");

    for (const auto& [key, value] : m) {  // C++17
        cout << key << " => " << value << endl;
    }
}

int main() {
    basic_map_usage();
    insert_and_find();
    erase_and_bounds();
    structured_binding_and_emplace();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::map
============================================================================

C++98:
- Introduced in STL
- Internally uses red-black tree (balanced BST)
- Keys are always unique and sorted (operator< by default)

C++11:
- `emplace()` for in-place construction
- Move support and efficiency improvements

C++14:
- Transparent comparators supported (for heterogeneous keys)

C++17:
- Structured bindings (`for (auto [k,v] : map)`)
- Node-based ops: `.extract()`, `.merge()`

C++20:
- Fully usable in `constexpr` where applicable
- Integration with ranges and views

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Access with `operator[]` inserts default if key doesn't exist:
    int val = m["new"];  // creates new key "new" with default value (e.g., 0)
- Prefer `.at()` for safe access: throws if key is absent
- Iteration is sorted by key (ascending by default)
- Keys are **unique**
- If you need duplicate keys → use `std::multimap`

============================================================================
COMPARISON – map vs unordered_map vs multimap
============================================================================

| Feature             | map<K,V>            | unordered_map<K,V>    | multimap<K,V>       |
|---------------------|---------------------|------------------------|----------------------|
| Sorted keys         |  Yes              |  No                 |  Yes               |
| Duplicates allowed  |  No               |  No                 |  Yes               |
| Lookup complexity   | O(log N)            | O(1) avg              | O(log N)             |
| Order of iteration  | By key (sorted)     | Unordered             | Sorted               |
| Underlying data     | Red-black tree      | Hash table            | Red-black tree       |

============================================================================
CHEAT SHEET – std::map
============================================================================

Declaration:
    map<string, int> m;

Insertion:
    m["key"] = value;
    m.insert({k, v});
    m.emplace(k, v);         // C++11

Access:
    m[key];                  // insert if not found
    m.at(key);               // throws if key not found
    m.find(k);               // iterator
    m.count(k);              // 0 or 1

Removal:
    m.erase(k);              // by key
    m.erase(it);             // by iterator

Bounds:
    m.lower_bound(k);
    m.upper_bound(k);

Iteration:
    for (auto& [k, v] : m) { ... }  // C++17
    for (auto it = m.begin(); it != m.end(); ++it) { ... }

*/

