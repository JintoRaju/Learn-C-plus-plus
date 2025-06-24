#include <iostream>
#include <optional>     // std::optional
#include <string>
using namespace std;

//
// WHY std::optional?
//
// Problem:
// - Many functions return a value only "sometimes"
//   (e.g., searching for a user, dividing numbers)
// - Using nullptr, -1, or error codes is unsafe or unclear
//
// Solution:
// - `std::optional<T>`: holds either a value of type T or nothing
//   (just like nullable types in other languages)
//
// - Safer and clearer than returning raw values, pointers, or booleans
//

optional<string> find_user(int id) {
    if (id == 1) return "Alice";
    else if (id == 2) return "Bob";
    return nullopt;  // no user found
}

void basic_optional_usage() {
    cout << "=== std::optional Basic Usage ===\n";

    optional<int> age;

    age = 25;
    if (age.has_value()) {
        cout << "Age: " << age.value() << endl;
    }

    age.reset();
    if (!age.has_value()) {
        cout << "Age not set.\n";
    }

    // Default fallback if no value
    cout << "Age or fallback: " << age.value_or(18) << endl;
}

void function_return_example() {
    cout << "\n=== Returning optional from function ===\n";

    for (int id : {1, 2, 3}) {
        optional<string> name = find_user(id);
        if (name) {
            cout << "User found: " << *name << endl;
        } else {
            cout << "No user for id: " << id << endl;
        }
    }
}

void optional_comparison_and_bool() {
    cout << "\n=== Comparisons and Boolean Conversion ===\n";

    optional<int> a = 10;
    optional<int> b = nullopt;

    if (a) cout << "a is valid\n";
    if (!b) cout << "b is empty\n";

    // Comparisons
    optional<int> x = 5, y = 5;
    if (x == y) cout << "x and y are equal\n";
}

int main() {
    basic_optional_usage();
    function_return_example();
    optional_comparison_and_bool();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::optional
============================================================================

C++17:
- Introduced in <optional>
- Represents optional value or no value
- Added:
    - `std::optional<T>`
    - `std::nullopt`, `std::nullopt_t`
    - `value_or()`, `emplace()`, `reset()`, `operator*`, `operator->`

C++20:
- Added `constexpr` support
- Comparisons improved
- Integration with coroutines and monadic chaining improved

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- `optional<T>` may or may not hold a value
- Access with `*opt`, `opt.value()`, or `opt.value_or(default)`
- Using `.value()` on an empty optional throws `bad_optional_access`
- Prefer `value_or()` or check `has_value()` before using `.value()`
- Can be used in containers like `vector<optional<T>>`
- `nullopt` is a global constant representing an empty optional

============================================================================
CHEAT SHEET – std::optional
============================================================================

Declaration:
    optional<int> opt;
    optional<string> name = "Alice";

Assigning:
    opt = 42;
    opt.emplace(99);  // in-place construction

Checking:
    opt.has_value();    // true or false
    if (opt) {...}      // implicit bool conversion
    opt != nullopt;

Access:
    *opt;               // dereference
    opt.value();        // throws if empty
    opt.value_or(0);    // fallback value

Reset:
    opt.reset();        // make it empty

Return from function:
    optional<T> find(...);
    return nullopt;

Comparison:
    optional<int> a = 5, b = 5;
    a == b → true

*/

