#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

//
// WHY std::unordered_multimap?
//
// Problem:
// - Need key-value storage with duplicate keys
// - But don't care about sorting
//
// Solution:
// - `std::unordered_multimap<Key, Value>`
//     - Uses a hash table internally (like `unordered_map`)
//     - Allows **duplicate keys**
//     - Offers average O(1) insert/find/erase
//

void basic_usage() {
    cout << "=== std::unordered_multimap Basics ===\n";

    unordered_multimap<string, int> scores;

    scores.insert({"Alice", 85});
    scores.insert({"Bob", 90});
    scores.insert({"Alice", 95});  // duplicate key allowed

    for (const auto& [name, score] : scores) {
        cout << name << " → " << score << endl;
    }

    cout << "Count of 'Alice': " << scores.count("Alice") << endl;
}

void search_equal_range() {
    cout << "\n=== equal_range() and find() ===\n";

    unordered_multimap<string, int> logins = {
        {"John", 1001},
        {"Jane", 1002},
        {"John", 1003}
    };

    auto [first, last] = logins.equal_range("John");

    cout << "All logins for John: ";
    for (auto it = first; it != last; ++it) {
        cout << it->second << " ";
    }
    cout << endl;

    auto it = logins.find("John");
    if (it != logins.end()) {
        cout << "One match for John: " << it->second << endl;
    }
}

void erase_examples() {
    cout << "\n=== erase() Examples ===\n";

    unordered_multimap<int, string> mmap = {
        {1, "One"},
        {2, "Two"},
        {2, "Deux"},
        {3, "Three"}
    };

    cout << "Before erase:\n";
    for (const auto& [k, v] : mmap) cout << k << " → " << v << endl;

    mmap.erase(2);  // removes all entries with key == 2

    cout << "After erase of key 2:\n";
    for (const auto& [k, v] : mmap) cout << k << " → " << v << endl;
}

int main() {
    basic_usage();
    search_equal_range();
    erase_examples();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::unordered_multimap
============================================================================

C++11:
- Introduced in standard
- Uses hash table (via std::hash<Key>)
- Allows duplicate keys
- No ordering guaranteed

C++14:
- Added transparent comparators support

C++17:
- Node handle support: `.extract()`, `.merge()`

C++20:
- constexpr-compatible
- Range integration improved

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Keys are NOT sorted or ordered
- Multiple entries per key are allowed
- `find(k)` returns one of the entries with key `k`
- Use `equal_range(k)` to iterate all values for key
- `count(k)` returns number of entries with that key
- `erase(k)` removes all entries for key
- `erase(it)` removes a specific instance

============================================================================
COMPARISON – unordered_multimap vs others
============================================================================

| Feature               | unordered_map       | unordered_multimap     | multimap            |
|-----------------------|---------------------|--------------------------|----------------------|
| Duplicates allowed    | ❌ No              | ✅ Yes                  | ✅ Yes               |
| Sorted keys           | ❌ No              | ❌ No                   | ✅ Yes               |
| Underlying structure  | Hash table          | Hash table              | Red-black tree       |
| Average lookup time   | O(1)                | O(1)                    | O(log N)             |
| Iteration order       | Unordered           | Unordered               | Sorted               |

============================================================================
CHEAT SHEET – std::unordered_multimap
============================================================================

Declaration:
    unordered_multimap<Key, Value> umm;

Insertion:
    umm.insert({k, v});
    umm.emplace(k, v);             // C++11+

Search:
    umm.find(k);                   // returns iterator to one match
    umm.equal_range(k);            // returns pair<first, last>
    umm.count(k);                  // returns # of matches

Removal:
    umm.erase(k);                  // all matching
    umm.erase(it);                 // one element

Iteration:
    for (auto& [k, v] : umm) { ... }

Advanced:
    umm.bucket_count();            // hash table bucket count
    umm.load_factor();             // hash table fill ratio

*/

