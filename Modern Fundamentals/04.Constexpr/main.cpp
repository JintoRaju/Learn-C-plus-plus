#include <iostream>
#include <array>
using namespace std;

//
// WHY DO WE NEED constexpr, consteval, constinit?
//
// Problem:
// Sometimes we want to compute values at **compile time** instead of runtime:
//   - For performance
//   - For static array sizes
//   - For template parameters
//
// Solution:
// - C++11 introduced `constexpr` to allow constant evaluation of functions and variables.
// - C++20 adds:
//   - `consteval`: **must** be evaluated at compile time (stricter than `constexpr`)
//   - `constinit`: for initializing global/static vars at compile time (but allows mutation later)
//

/* ------------------- C++11: constexpr functions ------------------- */
// A constexpr function can be used in both compile-time and runtime contexts

constexpr int square(int x) {
    return x * x;
}

/* ------------------- C++20: consteval function ------------------- */
// consteval: **must** be evaluated at compile time

consteval int cube(int x) {
    return x * x * x;
}

/* ------------------- C++20: constinit variable ------------------- */
// constinit ensures variable is initialized at compile time,
// but unlike constexpr, it can be modified later

constinit int global_counter = 0; // must be initialized with a constant expression

int main() {
    // ----------------- C++11: constexpr variable -----------------
    constexpr int size = 5;

    // Can use it in compile-time context: array size
    array<int, square(size)> myArray;

    cout << "myArray size = " << myArray.size() << endl;

    // ----------------- Runtime use of constexpr function -----------------
    int n;
    cout << "Enter a number to square: ";
    cin >> n;

    cout << "square(" << n << ") = " << square(n) << endl;

    // ----------------- C++20: consteval function usage -----------------

    // cube(3) is known at compile time
    constexpr int c = cube(3);
    cout << "cube(3) = " << c << endl;

    // int x = 4;
    // int result = cube(x); //  Error: consteval function cannot be used at runtime

    // ----------------- C++20: constinit use -----------------

    global_counter += 1;  // allowed: constinit is not const
    cout << "global_counter = " << global_counter << endl;

    return 0;
}

/*
----------------------------------------------------------------
VERSION HISTORY – constexpr, consteval, constinit
----------------------------------------------------------------

C++11:
- Introduced `constexpr`:
  - Allowed defining compile-time functions and variables
  - Functions had to contain only a single return statement (very restricted)

C++14:
- Relaxed `constexpr` rules:
  - Allowed if-else, loops, multiple statements inside constexpr functions

C++17:
- `constexpr` usable with more standard library types like `std::string_view`
- Enabled compile-time logic with more powerful syntax

C++20:
- Added `consteval`: must be evaluated at compile time
- Added `constinit`: guarantees compile-time initialization, but variable can be mutable
- `constinit` avoids static initialization order issues (used in global/static vars)

*/
