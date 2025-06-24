#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

//
// WHY std::array?
//
// Problem:
// - C-style arrays don't carry size info, are not copyable or assignable directly
// - Not compatible with STL algorithms (e.g., sort(), begin(), end())
//
// Solution:
// - std::array<T, N> is a fixed-size container:
//     - Safer than raw arrays (size is known at compile-time)
//     - Compatible with STL
//     - Supports assignment, copy, iterators, algorithms
//

void array_basics() {
    cout << "=== std::array Basics ===\n";

    array<int, 5> arr = {10, 20, 30, 40, 50};

    cout << "Using index: ";
    for (size_t i = 0; i < arr.size(); ++i)
        cout << arr[i] << " ";
    cout << endl;

    cout << "Using range-based loop: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Modifiable front/back access
    arr.front() = 1;
    arr.back() = 99;

    cout << "After front/back modification: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

void array_algorithms() {
    cout << "\n=== STL Algorithms on std::array ===\n";

    array<int, 6> arr = {5, 2, 1, 4, 6, 3};

    sort(arr.begin(), arr.end());  // works just like vector

    for (int x : arr) cout << x << " ";
    cout << endl;

    reverse(arr.begin(), arr.end());
    cout << "After reverse: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    cout << "Find 4: ";
    auto it = find(arr.begin(), arr.end(), 4);
    if (it != arr.end())
        cout << "Found at position " << distance(arr.begin(), it) << endl;
    else
        cout << "Not found\n";
}

void array_comparison_and_copy() {
    cout << "\n=== Copy and Comparison ===\n";

    array<int, 3> a1 = {1, 2, 3};
    array<int, 3> a2 = {1, 2, 3};
    array<int, 3> a3 = a1;   // full copy

    cout << "a1 == a2? " << boolalpha << (a1 == a2) << endl;

    a3[0] = 9;
    cout << "After modifying a3: ";
    for (int x : a3) cout << x << " ";
    cout << endl;
}

void array_edge_cases() {
    cout << "\n=== Edge Cases and Limitations ===\n";

    array<int, 0> empty_array; // valid! but size is 0

    cout << "Empty array size: " << empty_array.size() << endl;

    // array<int, N> is value-semantic: copying = copy all elements
    array<string, 2> str_arr = {"hello", "world"};
    array<string, 2> copy_arr = str_arr;

    cout << "String copy test: ";
    for (auto& s : copy_arr) cout << s << " ";
    cout << endl;
}

int main() {
    array_basics();
    array_algorithms();
    array_comparison_and_copy();
    array_edge_cases();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::array
============================================================================

C++11:
- Introduced std::array<T, N>
- Zero-overhead wrapper around C-style arrays
- Copyable, assignable, usable with STL
- Supports: .size(), .begin(), .end(), .front(), .back(), .fill(), etc.

C++14:
- More constexpr support
- Minor allocator improvements

C++17:
- .data() becomes constexpr-compatible
- Structured bindings now work: auto [a, b, c] = my_array;

C++20:
- Usable in constexpr contexts more broadly
- Fully works with ranges library

============================================================================
COMPARISON – std::array vs vector vs C-array
============================================================================

| Feature               | C-style array    | std::array        | std::vector       |
|-----------------------|------------------|-------------------|-------------------|
| Fixed-size            |  Yes           |  Yes            |  (dynamic)      |
| STL-compatible        |  No            |  Yes            |  Yes            |
| Copyable/Assignable   |  Error         |  Yes            |  Yes            |
| .size(), .front(), etc|  No            |  Yes            |  Yes            |
| Iterators             |  No            |  Yes            |  Yes            |
| Memory layout         | Contiguous       | Contiguous        | Contiguous        |
| Compile-time size     |  Yes           |  Yes            |  No             |

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Size is part of type: array<int, 3> ≠ array<int, 4>
- Cannot resize — fixed at compile time
- Passed by value = entire array copied (not like pointer!)
- Best when size is known and doesn't change
- Works great in embedded / performance-critical code
- You can use std::get<N>(arr) for tuple-style access

============================================================================
CHEAT SHEET – std::array
============================================================================

Declaration:
    array<T, N> arr = {a, b, c};

Access:
    arr[i], arr.at(i), arr.front(), arr.back(), arr.data()

STL compatibility:
    begin(arr), end(arr)
    sort(arr.begin(), arr.end()), find(...), reverse(...)

Assignment & comparison:
    arr2 = arr1;
    arr1 == arr2;

Filling:
    arr.fill(value);

Iteration:
    for (int x : arr)
    for (auto it = arr.begin(); it != arr.end(); ++it)

*/

