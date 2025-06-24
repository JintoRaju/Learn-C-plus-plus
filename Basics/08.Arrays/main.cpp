#include <iostream>
#include <array>  // For std::array (C++11+)
using namespace std;

//
// WHY DO WE NEED ARRAYS?
//
// Problem:
// When we need to store multiple related values (like marks, temperatures, IDs),
// declaring many separate variables is inefficient.
//
// Solution:
// Arrays allow us to:
//  - Store multiple values of the same type under one name
//  - Use indexed access
//  - Loop through items easily
//  - Reduce code size and errors
//
// Types:
//  - C-style fixed-size array: int arr[5];
//  - std::array<T, N>: safer, better (C++11+)
//  - dynamic arrays (vector): we’ll cover later
//

void c_style_array_demo() {
    cout << "=== C-style Fixed Arrays ===\n";

    int nums[5];  // uninitialized, contains garbage values

    // safer to zero-initialize
    int zeros[5] = {};  // all values = 0
    int values[5] = {1, 2};  // rest are 0

    for (int i = 0; i < 5; ++i) {
        cout << "values[" << i << "] = " << values[i] << endl;
    }

    // accessing out-of-bounds = undefined behavior
    // values[10] = 100; // ❌ DO NOT DO THIS (no bounds checking)
}

void array_looping_and_modification() {
    cout << "\n=== Looping and Modification ===\n";

    int scores[4] = {60, 70, 80, 90};

    // modify using normal for loop
    for (int i = 0; i < 4; ++i) {
        scores[i] += 5;
    }

    // print using range-based for loop (C++11+)
    for (int s : scores) {
        cout << s << " ";
    }
    cout << endl;
}

void multidimensional_array_demo() {
    cout << "\n=== Multidimensional Arrays ===\n";

    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 3; ++col) {
            cout << "matrix[" << row << "][" << col << "] = " << matrix[row][col] << endl;
        }
    }
}

void std_array_demo() {
    cout << "\n=== std::array (C++11+) ===\n";

    std::array<int, 5> arr = {10, 20, 30, 40, 50};

    // safer: knows its size, supports .at(), can be passed by value
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    // bounds-checked access (throws on error)
    try {
        cout << "arr.at(2) = " << arr.at(2) << endl;
        // cout << "arr.at(10) = " << arr.at(10) << endl; // throws std::out_of_range
    } catch (const out_of_range& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

int main() {
    c_style_array_demo();
    array_looping_and_modification();
    multidimensional_array_demo();
    std_array_demo();
    return 0;
}

/*
====================================================================
VERSION NOTES – ARRAYS
====================================================================

C++98:
- Supports fixed-size arrays (T arr[N]) with stack allocation
- No automatic bounds checking
- Multidimensional arrays fully supported
- Initialization: int arr[5] = {1,2}; → rest zero-filled

C++11:
- Introduced std::array<T, N> in <array> header
    - Fixed size, stack-allocated, safer than C-style
    - Supports .size(), .at(), iterators
- Range-based for loop: for (auto x : arr) {...}

C++14:
- Minor improvements: deduced return types work with std::array

C++17:
- Structured bindings work with std::array: `auto [a, b] = arr;` (if N == 2)

C++20:
- constexpr std::array usable in compile-time contexts
- Improved range loop support with concepts and views (in `ranges`)

====================================================================
NOTES:
- C-style arrays decay to pointers when passed to functions
- std::array<T, N> maintains size and does not decay
- Prefer std::array<T, N> unless you are working with C APIs
*/
