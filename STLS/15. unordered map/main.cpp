#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

//
// WHY std::unordered_map?
//
// Problem:
// - std::map gives sorted keys but log(N) complexity
// - Sorting is often unnecessary when just fast access is needed
//
// Solution:
// - `std::unordered_map<Key, Value>`
//     - Uses hash table (like Python's dict)
//     - Average O(1) insert, erase, find
//     - Keys are NOT sorted
//

void basic_usage() {
    cout << "=== std::unordered_map Basics ===\n";

    unordered_map<string, int> population;

    population["India"] = 1400;
    population["USA"] = 331;
    population["China"] = 1440;

    for (const auto& [country, people] : population) {
        cout << country << " → " << people << "M\n";
    }

    cout << "Population of USA: " << population["USA"] << "M\n";
}

void find_and_insert() {
    cout << "\n=== find(), insert(), and default insertion ===\n";

    unordered_map<int, string> idName;

    idName.insert({101, "Alice"});
    idName.insert({102, "Bob"});

    // find()
    auto it = idName.find(101);
    if (it != idName.end())
        cout << "Found 101 → " << it->second << endl;

    // operator[] inserts default if not found
    cout << "Name for 103: " << idName[103] << endl;  // inserts with default ""

    // insert again: no effect
    auto result = idName.insert({102, "NewBob"});
    cout << "Inserted 102 again? " << boolalpha << result.second << endl;
}

void erase_and_bucket_info() {
    cout << "\n=== erase() and hash table internals ===\n";

    unordered_map<string, int> stock = {
        {"AAPL", 150},
        {"GOOG", 2800},
        {"MSFT", 310}
    };

    stock.erase("GOOG");

    for (auto& [ticker, price] : stock)
        cout << ticker << " → $" << price << endl;

    cout << "Total buckets: " << stock.bucket_count() << endl;
    cout << "Load factor: " << stock.load_factor() << endl;
}

int main() {
    basic_usage();
    find_and_insert();
    erase_and_bucket_info();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::unordered_map
============================================================================

C++11:
- Introduced unordered_map, unordered_set, unordered_multimap
- Backed by hash table
- Keys must be hashable (std::hash<T>)

C++14:
- More flexible hashing and performance tuning

C++17:
- Node handle support: `.extract()`, `.merge()`

C++20:
- constexpr support
- Improved performance via bucket interface

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Keys are **not sorted**
- Provides average O(1) lookup/insertion
- Worst-case lookup is O(N) (if many hash collisions)
- Iterator order is **not stable**
- Accessing a key with `[]` will **insert** it if not found
- Use `.at(key)` to **avoid inserting** by accident (throws if not found)

============================================================================
COMPARISON – map vs unordered_map
============================================================================

| Feature               | map<Key, T>        | unordered_map<Key, T> |
|-----------------------|--------------------|------------------------|
| Key order             |  Sorted          |  Unordered          |
| Lookup complexity     | O(log N)           | O(1) avg (O(N) worst) |
| Underlying structure  | Red-black tree     | Hash table            |
| Supports duplicates   |  No              |  No                 |
| Iteration order       | By sorted keys     | Arbitrary             |
| Memory use            | Compact            | Slightly higher       |

============================================================================
CHEAT SHEET – std::unordered_map
============================================================================

Declaration:
    unordered_map<Key, Value> m;

Insertion:
    m[key] = value;
    m.insert({k, v});
    m.emplace(k, v);             // C++11

Access:
    m[key];                      // inserts default if key not found
    m.at(key);                   // throws if key not found
    m.find(k);                   // returns iterator or end()
    m.count(k);                  // 0 or 1

Removal:
    m.erase(key);
    m.erase(it);

Other:
    m.bucket_count();            // number of buckets
    m.load_factor();             // items per bucket (avg)
    m.max_load_factor();         // can set to control rehashing

Iteration:
    for (auto& [k, v] : m) { ... }

*/

