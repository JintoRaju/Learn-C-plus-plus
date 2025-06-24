#include <iostream>
#include <variant>     // for std::variant, std::visit
#include <string>
#include <vector>
using namespace std;

//
// WHY std::variant?
//
// Problem:
// - Need a variable that can hold **one of several types**, but only **one at a time**
// - Classic `union` is unsafe (doesn't track type), `any` is too generic (no type list)
//
// Solution:
// - `std::variant<Ts...>` stores **exactly one of the listed types**
// - Type-safe, introspectable, and compatible with `std::visit()`
//

void basic_variant_usage() {
    cout << "=== std::variant Basics ===\n";

    variant<int, float, string> v;

    v = 42;        // holds int
    cout << "int: " << get<int>(v) << endl;

    v = 3.14f;     // now holds float
    cout << "float: " << get<float>(v) << endl;

    v = "hello";   // now holds string (std::string implicitly constructed)
    cout << "string: " << get<string>(v) << endl;

    // Check current type
    if (holds_alternative<string>(v)) {
        cout << "Currently holding string\n";
    }
}

void access_and_visit() {
    cout << "\n=== Accessing and Visiting ===\n";

    variant<int, string> data = "OpenAI";

    // Safe access using std::visit
    visit([](auto&& val) {
        cout << "Holds: " << val << endl;
    }, data);

    // Trying wrong type throws exception
    try {
        cout << get<int>(data) << endl;  // invalid: currently string
    } catch (const bad_variant_access& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void visitor_example() {
    cout << "\n=== Custom Visitor ===\n";

    variant<int, string, vector<int>> item = vector<int>{1, 2, 3};

    auto visitor = [](const auto& value) {
        using T = decay_t<decltype(value)>;
        if constexpr (is_same_v<T, int>)
            cout << "Integer: " << value << endl;
        else if constexpr (is_same_v<T, string>)
            cout << "String: " << value << endl;
        else if constexpr (is_same_v<T, vector<int>>) {
            cout << "Vector<int>: ";
            for (int x : value) cout << x << " ";
            cout << endl;
        }
    };

    visit(visitor, item);
}

int main() {
    basic_variant_usage();
    access_and_visit();
    visitor_example();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::variant
============================================================================

C++17:
- Introduced `std::variant<T1, T2, ...>`
- Safer alternative to union
- Allows one value from a known set of types
- Supports:
    • std::get<T>(), std::get<N>()
    • std::holds_alternative<T>()
    • std::visit(visitor, variant)

C++20:
- constexpr support for visit()
- Better integration with lambdas and templates
- Improved type deduction and match

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Always holds one and only one value at a time
- Throws `std::bad_variant_access` if wrong type accessed
- Internally stores all types — memory = max(sizeof(Ts...))
- Variant is type-indexed at runtime
- Use `std::visit` to safely operate on the contained value
- Works well with lambdas + `if constexpr` + `is_same_v`

============================================================================
CHEAT SHEET – std::variant
============================================================================

Declaration:
    variant<int, string> v;

Assignment:
    v = 10;
    v = "hello"s;

Access:
    get<int>(v);                    // throws if wrong type
    get<0>(v);                      // access by index
    holds_alternative<string>(v);  // true if string is held

Safe Visit:
    visit([](auto&& val) { cout << val; }, v);

Match with types (visitor pattern):
    visit(overloaded{
        [](int x) { ... },
        [](const string& s) { ... }
    }, v);

Custom Visitor with `if constexpr` (C++17):
    auto visitor = [](auto&& val) {
        if constexpr (is_same_v<decltype(val), int>) { ... }
    };

Notes:
- Default-initialized variant holds the first type
- Cannot hold references (e.g., variant<int, int&> is invalid)
- Variant can be empty only if valueless due to exception

============================================================================
COMPARISON – variant vs any vs union
============================================================================

| Feature             | std::variant         | std::any                | union (C-style)        |
|---------------------|----------------------|--------------------------|-------------------------|
| Type-safe access    |  Yes              |  Requires cast        |  Unsafe               |
| Multiple types      |  Chosen list       |  Any type             |  But manual mgmt      |
| Holds reference     |  No               |  Yes                  |  Yes (raw)            |
| Type info           |  Via visitor       |  Via typeid           |  No runtime info      |
| Size efficiency     |  Compact (max)     |  Bigger (typeid info) |  Compact              |
| Use case            | Known variant set    | Unknown dynamic type    | Low-level memory unions |

*/

