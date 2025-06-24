#include <iostream>
#include <tuple>     // for std::tuple
#include <string>
using namespace std;

//
// WHY std::tuple?
//
// Problem:
// - `std::pair` supports only 2 values
// - Need to return or group 3+ heterogeneous values (e.g., name, age, salary)
//
// Solution:
// - `std::tuple<T1, T2, ..., Tn>` stores fixed-size heterogeneous data
// - Can access values using `std::get<index>()`
// - Common in advanced STL and functional programming
//

tuple<string, int, double> get_employee_data() {
    string name = "Alice";
    int age = 30;
    double salary = 75432.5;
    return make_tuple(name, age, salary);  // safe type inference
}

void basic_tuple_usage() {
    cout << "=== Basic std::tuple Usage ===\n";

    tuple<string, int, double> emp = get_employee_data();

    // Access using get<index>
    cout << "Name: "   << get<0>(emp) << endl;
    cout << "Age: "    << get<1>(emp) << endl;
    cout << "Salary: " << get<2>(emp) << endl;
}

void structured_binding_and_tie() {
    cout << "\n=== Structured Bindings and std::tie ===\n";

    auto emp = get_employee_data();

    // Structured binding (C++17)
    auto [name, age, salary] = emp;
    cout << "Unpacked → " << name << ", " << age << ", " << salary << endl;

    // Using std::tie for comparison
    tuple<int, int, int> a = {1, 2, 3};
    tuple<int, int, int> b = {1, 2, 4};

    if (a < b)
        cout << "Tuple a is less than b (lexicographically)\n";

    // Ignore values using std::ignore
    int x, y;
    tie(x, y, ignore) = a;
    cout << "Only x and y: " << x << ", " << y << endl;
}

void nested_tuples_and_returning_multiple_values() {
    cout << "\n=== Nested Tuples and Return Pattern ===\n";

    tuple<string, tuple<int, double>> t = {"Bob", {40, 50000.0}};

    auto [ename, inner] = t;
    cout << "Name: " << ename << endl;
    cout << "Age: " << get<0>(inner) << ", Salary: " << get<1>(inner) << endl;
}

int main() {
    basic_tuple_usage();
    structured_binding_and_tie();
    nested_tuples_and_returning_multiple_values();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::tuple
============================================================================

C++11:
- Introduced `std::tuple`
- Supports `std::get<N>`, `std::make_tuple()`, `std::tie()`
- Comparison operators: lexicographical (<, ==, etc.)

C++14:
- `std::get<T>` overload added (only if T appears once)

C++17:
- Structured bindings support: `auto [a, b, c] = t`
- `std::apply()` – invoke function with tuple as argument list

C++20:
- `constexpr` support for all tuple operations
- Tuple concatenation: `std::tuple_cat`

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Access with `std::get<index>(tuple)` (index must be constant at compile time)
- Size can be queried using `std::tuple_size<decltype(t)>::value`
- Types can be queried via `std::tuple_element<N, T>::type`
- `std::make_tuple(a, b, c)` infers types
- `std::tie(a, b, c)` allows unpacking or comparisons
- `std::ignore` is used when you want to skip an element

============================================================================
COMPARISON – pair vs tuple vs struct
============================================================================

| Feature        | std::pair         | std::tuple             | struct                 |
|----------------|-------------------|-------------------------|-------------------------|
| Value count    | 2                 | Any fixed number        | Any fixed number        |
| Access         | .first/.second    | std::get<N>(), bindings | Named members           |
| Comparison     |  Built-in       |  Built-in             |  If overloaded        |
| Type safety    | Moderate          | High (full heterogeneity)| Highest (by name/type)  |
| Use case       | Simple key-value  | Multi-value grouping    | Designed, documented    |

============================================================================
CHEAT SHEET – std::tuple
============================================================================

Declaration:
    tuple<string, int, double> t;
    auto t2 = make_tuple("Alice", 25, 35000.0);

Access:
    get<0>(t);      // by index
    get<T>(t);      // if T appears only once (C++14+)

Unpack:
    auto [a, b, c] = t;  // C++17 structured bindings
    tie(x, y, z) = t;

Ignore:
    tie(x, ignore, z) = t;

Comparison:
    if (a < b) ...  // lexicographic

Nested:
    tuple<int, tuple<int, int>> nested;

Size/type:
    tuple_size<decltype(t)>::value;
    tuple_element<1, decltype(t)>::type;

*/

