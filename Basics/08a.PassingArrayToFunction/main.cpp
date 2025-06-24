#include <iostream>
#include <array>
using namespace std;

//
// WHY THIS TOPIC?
//
// Problem:
// When we pass a C-style array to a function, it decays into a pointer.
// As a result:
//   - The function loses knowledge of array size
//   - We can't use `sizeof(arr)` inside the function
//
// Solution:
// We must either:
//   - Pass the size explicitly
//   - Use std::array (C++11+) or std::span (C++20)
//

//
// Method 1: Passing C-style array with explicit size
//
void print_array_1(int arr[], int size) {
    cout << "[print_array_1] using pointer-decayed array:\n";
    for (int i = 0; i < size; ++i) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
}

//
// Method 2: Pass with fixed known size in function signature
// Note: size must match exactly
//
void print_array_2(int (&arr)[5]) {  // reference to array of 5 ints
    cout << "[print_array_2] using array reference with fixed size:\n";
    for (int i = 0; i < 5; ++i) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
}

//
// Method 3: Use std::array<T, N> (C++11+) — preserves size
//
void print_array_3(std::array<int, 5> arr) {
    cout << "[print_array_3] using std::array (copy by value):\n";
    for (int i = 0; i < arr.size(); ++i) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
}

//
// Method 4: Use const std::array<T, N>& to avoid copying
//
void print_array_4(const std::array<int, 5>& arr) {
    cout << "[print_array_4] using const reference to std::array:\n";
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};

    // C-style arrays (decay to pointer)
    print_array_1(numbers, 5);

    // C-style array passed by reference (size must match)
    print_array_2(numbers);

    // std::array<T, N>
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    print_array_3(arr);  // by value (copy)
    print_array_4(arr);  // by reference (no copy)

    return 0;
}

/*
===========================================================================
VERSION NOTES – ARRAY PASSING AND DECAY
===========================================================================

C++98:
- Arrays decay to pointers when passed to functions
- Function signature: void f(int arr[]) === void f(int* arr)
- Size must be passed separately
- Reference-to-array syntax (int (&arr)[N]) works but is rarely used

C++11:
- Introduced std::array<T, N>
  → Keeps size info inside object
  → Allows safe copying or referencing
- Range-based for loop introduced

C++14:
- std::array got better constexpr support

C++17:
- Structured bindings allow easy unpacking from std::array

C++20:
- Introduced std::span<T>
  → Lightweight wrapper over arrays (non-owning view)
  → Can pass a portion of any array/vector without copying
  → Will be shown in separate example if needed

===========================================================================
ARRAY DECAY SUMMARY:

- When passed to functions:
    int arr[5]  → becomes int* arr (size info lost)
- To avoid decay, use:
    - `int (&arr)[5]` → reference to array of 5 ints
    - `std::array<T, N>` → modern, safer, copyable
    - `std::span<T>` → view-only, zero-overhead (C++20)

*/
