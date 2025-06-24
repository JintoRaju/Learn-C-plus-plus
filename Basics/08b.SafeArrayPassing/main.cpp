#include <iostream>
#include <span>     // Required for std::span (C++20)
#include <array>
#include <vector>
using namespace std;

//
// WHY THIS DEMO?
//
// Problem:
// - `sizeof(arr)` outside a function gives total size in bytes
// - Inside a function (when passed as parameter), the array decays to a pointer
// - So `sizeof(arr)` inside gives pointer size, not array size
//
// Let's demonstrate this clearly.
//

// Function taking array as a parameter (decays to pointer)
void size_demo_decay(int arr[]) {
    std::cout << "[Inside function] sizeof(arr) = " << sizeof(arr) << " bytes (pointer size)" << endl;
}

// Function taking reference to array (no decay)
void size_demo_reference(int (&arr)[5]) {
    std::cout << "[Inside function with reference] sizeof(arr) = " << sizeof(arr) << " bytes (true array size)" << endl;
}



/*
===========================================================================
EXPLANATION: WHY SIZEOF RETURNS DIFFERENT VALUES
===========================================================================

C++ arrays decay to pointers when passed to a function:
    int arr[5] → becomes int* arr

So:
    - Outside function: sizeof(arr) = 5 × sizeof(int) = 20 bytes (on 64-bit)
    - Inside function (int arr[]): sizeof(arr) = sizeof(int*) = 8 bytes (on 64-bit)

To prevent decay:
    - Use int (&arr)[N] → reference to full array (no size loss)


*/


/*

WHY USE std::span?

Problem:
- C-style arrays decay to pointers → lose size info
- std::array and std::vector can’t be used interchangeably

Solution (C++20):
- std::span<T> is a **lightweight, non-owning view**
- Can refer to:
    - array T[N]
    - std::array<T, N>
    - std::vector<T>
    - Any contiguous block of T
*/




void print_span(std::span<int> s) {
    std::cout << "[std::span] size = " << s.size() << endl;
    for (int value : s) {
        cout << value << " ";
    }
    std::cout << endl;
}

int main() {


    int arr[5] = {10, 20, 30, 40, 50};

    cout << "=== sizeof on Array (Outside Function) ===\n";
    cout << "[Outside] sizeof(arr) = " << sizeof(arr) << " bytes" << endl;
    cout << "[Outside] sizeof(arr[0]) = " << sizeof(arr[0]) << " bytes" << endl;
    cout << "[Outside] Number of elements = " << sizeof(arr) / sizeof(arr[0]) << endl;

    cout << "\n=== sizeof Inside Function (Decay to Pointer) ===\n";
    size_demo_decay(arr); // arr decays to int*

    cout << "\n=== sizeof Inside Function (Reference to Array) ===\n";
    size_demo_reference(arr); // arr remains full array inside function


    cout << "=== Using std::span with C-style array ===\n";
    int c_arr[5] = {1, 2, 3, 4, 5};
    print_span(c_arr);  // std::span can take C-style array

    cout << "\n=== Using std::span with std::array ===\n";
    std::array<int, 5> a_arr = {10, 20, 30, 40, 50};
    print_span(a_arr);  // std::array has contiguous storage

    cout << "\n=== Using std::span with std::vector ===\n";
    std::vector<int> v_arr = {100, 200, 300, 400};
    print_span(v_arr);  // works perfectly — no copy

    cout << "\n=== Slicing a span ===\n";
    std::span<int> full_span = v_arr;
    std::span<int> sub_span = full_span.subspan(1, 2);  // from index 1, length 2

    cout << "Subspan (slice of vector): ";
    for (int val : sub_span) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
===========================================================================
VERSION NOTES – std::span
===========================================================================

C++98 to C++17:
- No `std::span` available
- Required passing arrays with size explicitly
- `std::vector` or `std::array` used for safe structures
- No way to write a unified function for both

C++20:
- Introduced std::span<T>
  → Non-owning, cheap wrapper for array-like data
  → Preserves size info
  → Can be sliced with .subspan(start, count)
  → Works with: T[N], std::array, std::vector, etc.

C++23+:
- `std::span` is widely used in ranges, views, algorithms

===========================================================================
SUMMARY:
- std::span<T> lets you pass **any contiguous range** without copying
- No need to pass size separately
- Always use const std::span<T> in read-only APIs
- span doesn’t own the data — be careful not to return it from a function if original array goes out of scope
*/