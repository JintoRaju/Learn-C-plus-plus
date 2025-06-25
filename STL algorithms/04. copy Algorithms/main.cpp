#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // copy, copy_if, copy_n, copy_backward
using namespace std;

//
// WHY copy ALGORITHMS?
//
// Problem:
// - You want to copy part or all of a container into another
// - Want to copy *conditionally*, or *to a different place*
// - Manual loops are tedious and error-prone
//
// Solution:
// - Use `std::copy`, `std::copy_if`, `std::copy_n`, `std::copy_backward`
// - Each solves a specific need efficiently and safely
//

void simple_copy_example() {
    cout << "=== std::copy Example ===\n";

    vector<int> src = {1, 2, 3, 4, 5};
    vector<int> dest(5);  // must be pre-sized

    copy(src.begin(), src.end(), dest.begin());

    cout << "Copied: ";
    for (int n : dest) cout << n << " ";
    cout << endl;
}

void conditional_copy_example() {
    cout << "\n=== std::copy_if Example (C++11) ===\n";

    vector<int> src = {1, 2, 3, 4, 5, 6};
    vector<int> evens;

    // Reserve or use back_inserter to auto-expand
    copy_if(src.begin(), src.end(), back_inserter(evens),
            [](int x) { return x % 2 == 0; });

    cout << "Even numbers: ";
    for (int x : evens) cout << x << " ";
    cout << endl;
}

void copy_n_example() {
    cout << "\n=== std::copy_n Example (C++11) ===\n";

    vector<string> src = {"one", "two", "three", "four"};
    vector<string> first_two(2);

    copy_n(src.begin(), 2, first_two.begin());

    cout << "First two: ";
    for (const auto& s : first_two) cout << s << " ";
    cout << endl;
}

void copy_backward_example() {
    cout << "\n=== std::copy_backward Example ===\n";

    vector<int> src = {10, 20, 30};
    vector<int> dest(5, 0);  // initialized with 0s

    // Copy to the last 3 slots
    copy_backward(src.begin(), src.end(), dest.end());

    cout << "Copy backward: ";
    for (int x : dest) cout << x << " ";
    cout << endl;
}

int main() {
    simple_copy_example();
    conditional_copy_example();
    copy_n_example();
    copy_backward_example();
    return 0;
}

/*
============================================================================
VERSION NOTES – Copy Algorithms
============================================================================

C++98:
- std::copy
- std::copy_backward

C++11:
- Added `std::copy_if` and `std::copy_n`
- Also added `back_inserter()` and lambda support

C++20:
- Added `std::ranges::copy`, `ranges::copy_if`, etc.
- Works with projections, pipe style (views::filter | views::transform)

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- `copy()` requires output range to be pre-sized
    ➜ Use `back_inserter()` to grow automatically (especially with `vector`)
- `copy_if()` skips items based on condition
    ➜ Needs inserter like
