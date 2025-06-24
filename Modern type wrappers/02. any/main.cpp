#include <iostream>
#include <any>        // for std::any, std::any_cast
#include <string>
#include <vector>
using namespace std;

//
// WHY std::any?
//
// Problem:
// - Need to store *any type*, not limited to a known set (like variant)
// - Don't want to use unsafe void pointers or manual unions
//
// Solution:
// - `std::any` can store any value (copyable or movable)
// - Type-safe access via `std::any_cast<T>()`
//

void basic_any_usage() {
    cout << "=== std::any Basic Usage ===\n";

    any a;

    a = 42;
    cout << "Stored int: " << any_cast<int>(a) << endl;

    a = string("hello");
    cout << "Stored string: " << any_cast<string>(a) << endl;

    // Check if value exists
    if (a.has_value())
        cout << "Currently holding: " << a.type().name() << endl;

    // Reset the content
    a.reset();
    cout << "After reset, has value? " << boolalpha << a.has_value() << endl;
}

void access_errors_and_safe_cast() {
    cout << "\n=== any_cast Errors and Safe Access ===\n";

    any value = 3.14;

    // Safe cast
    try {
        double d = any_cast<double>(value);
        cout << "Extracted double: " << d << endl;
    } catch (const bad_any_cast& e) {
        cout << "Error: " << e.what() << endl;
    }

    // Unsafe cast (wrong type)
    try {
        int x = any_cast<int>(value);  // throws
    } catch (const bad_any_cast& e) {
        cout << "Caught bad_any_cast: " << e.what() << endl;
    }
}

void pointer_cast_and_mutate() {
    cout << "\n=== Using any_cast Pointer for Mutation ===\n";

    any a = string("OpenAI");

    // Get modifiable pointer
    if (string* pStr = any_cast<string>(&a)) {
        *pStr += " GPT";
        cout << "Modified string: " << *pStr << endl;
    }
}

int main() {
    basic_any_usage();
    access_errors_and_safe_cast();
    pointer_cast_and_mutate();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::any
============================================================================

C++17:
- Introduced in <any>
- Designed for generic containers and plugin APIs
- Holds *any* copyable type
- Provides:
    - `any_cast<T>()`
    - `has_value()`
    - `reset()`
    - `type()`

C++20:
- Now `any` supports `constexpr` usage (limited), better noexcept tagging
- Better performance in some compilers

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- `std::any` stores a copy of the value internally (type-erased)
- Stored type must be **copy-constructible**
- Type info is tracked using `std::type_info`
- Incorrect `any_cast` throws `std::bad_any_cast`
- Safer to use pointer-based `any_cast<T>(&any)` when unsure
- `reset()` clears the value
- `type().name()` returns the type name (implementation-defined)

============================================================================
COMPARISON – any vs variant vs void* vs union
============================================================================

| Feature              | std::any             | std::variant         | void*              | union (C-style)       |
|----------------------|----------------------|-----------------------|--------------------|------------------------|
| Type list required   | ❌ No               | ✅ Yes              | ❌ No             | ✅ Yes                |
| Type-safe access     | ✅ Yes (cast)       | ✅ Yes (visit/get)  | ❌ No             | ❌ No                 |
| Type known at compile| ❌ No               | ✅ Yes              | ❌ No             | ✅ Yes                |
| Default type         | ❌ None             | ✅ First type       | ❌ None           | ❌ None               |
| Holds ref/pointer    | ✅ Yes              | ❌ No               | ✅ Yes            | ✅ Yes                |
| Access safety        | Medium (if cast ok) | High (compile-time) | Low               | Low                   |

============================================================================
CHEAT SHEET – std::any
============================================================================

Declaration:
    any a;

Assignment:
    a = 10;
    a = string("hello");

Access:
    any_cast<int>(a);              // throws if wrong
    any_cast<int>(&a);             // pointer cast (returns nullptr if wrong)

Check:
    a.has_value();
    a.type().name();               // type info

Reset:
    a.reset();                     // clear value

Modifying:
    string* ps = any_cast<string>(&a);
    if (ps) *ps += " world";

*/

