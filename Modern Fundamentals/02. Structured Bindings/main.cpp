#include <iostream>
#include <vector>
#include <tuple>
#include <map>
using namespace std;

//
// WHY DO WE NEED STRUCTURED BINDINGS?
//
// Problem:
// In older C++, extracting values from `pair`, `tuple`, or `struct` required verbose and repetitive code.
// For example: `p.first`, `p.second`, `get<0>(t)`, or manually unpacking into separate variables.
//
// Solution:
// C++17 introduced **structured bindings** which allow us to unpack objects into individual named variables in one line.
//
// Benefit:
// Code becomes shorter, cleaner, and more readable.
//

int main() {
    // ----------- Unpacking a std::pair -----------
    pair<int, string> p = {101, "Apple"};

    // C++17 structured binding syntax
    auto [code, label] = p; // `code` becomes int, `label` becomes string
    cout << "Pair: code = " << code << ", label = " << label << endl;

    // ----------- Unpacking a std::tuple -----------
    tuple<int, double, string> t = {1, 2.5, "Tuple"};

    // Structured binding with a 3-element tuple
    auto [a, b, c] = t;
    cout << "Tuple: a = " << a << ", b = " << b << ", c = " << c << endl;

    // ----------- Structured binding in loop with map -----------
    map<string, int> fruits = {
        {"apple", 10},
        {"banana", 20},
        {"cherry", 30}
    };

    // Previously: for (auto it = fruits.begin(); it != fruits.end(); ++it)
    // Now:
    for (const auto& [key, value] : fruits) { // key is string, value is int
        cout << "Fruit: " << key << ", Quantity: " << value << endl;
    }

    // ----------- Unpacking a struct -----------

    struct Person {
        int id;
        string name;
    };

    Person person = {1, "Jose"};

    // C++17: Only works if struct members are public and NOT inherited/virtual
    auto [personId, personName] = person;
    cout << "Person: ID = " << personId << ", Name = " << personName << endl;

    // ----------- Unpacking an array -----------
    int arr[] = {10, 20, 30};

    auto [x, y, z] = arr;  // Only works with arrays of known size
    cout << "Array values: x = " << x << ", y = " << y << ", z = " << z << endl;

    return 0;
}

/*
-----------------------------------------------------------
VERSION HISTORY – STRUCTURED BINDINGS
-----------------------------------------------------------

C++98 to C++14:
- No support for unpacking objects directly.
- Required manual access: obj.first, obj.second, std::get<0>(tuple)

C++17:
- Introduced structured bindings using `auto [a, b] = ...`
- Works with:
    1. `std::pair`, `std::tuple`
    2. Arrays (known size)
    3. User-defined structs (non-virtual, public members only)
- Improves readability in loops and destructuring scenarios

C++20:
- Structured bindings are still the same, but used more often with:
    - Ranges (`std::ranges::views::zip`)
    - Concepts + generic code
- Can be used with `const`, `&`, `&&` like:
    - `const auto& [a, b] = pair_obj;`
    - `auto&& [a, b] = some_func();`

*/
