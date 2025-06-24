#include <iostream>
#include <utility>  // for std::pair, std::make_pair
#include <string>
#include <vector>
using namespace std;

//
// WHY std::pair?
//
// Problem:
// - Functions can return only one value (without creating a struct)
// - Need to group two related values (like key-value, coordinates, min-max)
//
// Solution:
// - `std::pair<T1, T2>` holds exactly TWO values of (possibly) different types
// - Used heavily in maps, tuples, and algorithm results
//

// Function returning two values as a pair
pair<int, int> min_max(int a, int b) {
    if (a < b)
        return {a, b};  // uniform initialization (C++11+)
    else
        return make_pair(b, a);  // traditional (C++98)
}

void basic_pair_usage() {
    cout << "=== Basic std::pair Usage ===\n";

    pair<string, int> person("Alice", 30);

    cout << "Name: " << person.first << ", Age: " << person.second << endl;

    auto result = min_max(20, 50);
    cout << "Min: " << result.first << ", Max: " << result.second << endl;
}

void structured_binding_and_comparison() {
    cout << "\n=== Structured Binding and Comparison ===\n";

    pair<int, string> p1 = {1, "One"};
    pair<int, string> p2 = {2, "Two"};

    // Structured bindings (C++17)
    auto [num, word] = p2;
    cout << "num = " << num << ", word = " << word << endl;

    // Comparison: lexicographical
    if (p1 < p2)
        cout << "p1 < p2 (lexicographically)\n";
}

void pair_in_vector() {
    cout << "\n=== std::pair Inside Containers ===\n";

    vector<pair<string, int>> products = {
        {"Pen", 10},
        {"Book", 50},
        {"Pencil", 5}
    };

    for (const auto& [name, price] : products) {  // C++17
        cout << name << " → ₹" << price << endl;
    }
}

int main() {
    basic_pair_usage();
    structured_binding_and_comparison();
    pair_in_vector();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::pair
============================================================================

C++98:
- Introduced in <utility>
- Supports `.first`, `.second`
- Created using `std::make_pair(a, b)`

C++11:
- Uniform initialization support: `pair<int, string> p = {1, "One"}`
- Move constructor and emplace operations

C++17:
- Structured bindings support: `auto [a, b] = pair;`
- Comparisons like `<`, `>`, etc. (lexicographic) improved

C++20:
- Fully constexpr-friendly
- Integrates with STL algorithms and ranges better

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- `pair<T1, T2>` is a struct with public fields: `.first`, `.second`
- `make_pair(a, b)` auto-deduces types (C++98+)
- Can be compared lexicographically (`<`, `==`, etc.)
- Common in `map<K, V>` as `pair<const K, V>`
- Ideal for returning multiple values from functions
- Replace with `tuple` for more than 2 values

============================================================================
COMPARISON – pair vs tuple vs struct
============================================================================

| Feature        | std::pair         | std::tuple           | struct                   |
|----------------|-------------------|-----------------------|---------------------------|
| Values         | 2                 | Any count             | Custom named members      |
| Access         | .first/.second    | std::get<>() or bind  | By name                   |
| Comparisons    | ✅ Built-in       | ✅ Built-in            | ✅ If overloaded           |
| Heterogeneous? | ✅ Yes            | ✅ Yes                | ✅ Yes                    |
| Use case       | Quick pair        | >2 items, algorithm   | Full type definition      |

============================================================================
CHEAT SHEET – std::pair
============================================================================

Declaration:
    pair<int, string> p = {1, "One"};
    auto p2 = make_pair("A", 100);

Access:
    p.first, p.second;

Comparison:
    if (p1 < p2) { ... }   // lexicographic

Structured Binding (C++17):
    auto [a, b] = p;

Use in containers:
    vector<pair<string, int>> v;

Returning from function:
    return make_pair(a, b);

*/

