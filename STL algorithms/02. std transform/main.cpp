#include <iostream>
#include <vector>
#include <algorithm>     // for std::transform
#include <string>
#include <cctype>        // for std::toupper
using namespace std;

//
// WHY std::transform?
//
// Problem:
// - Need to apply a function (e.g., square, uppercase, add) to every element in a container
// - Using loops is error-prone, hard to read, and less reusable
//
// Solution:
// - `std::transform` applies a function to each element in a range (or pair of ranges)
// - Can be used to generate new containers or update in-place
//

void unary_transform_example() {
    cout << "=== Unary Transform Example (1 input range) ===\n";

    vector<int> input = {1, 2, 3, 4, 5};
    vector<int> output(input.size());

    // Square each element
    transform(input.begin(), input.end(), output.begin(),
              [](int x) { return x * x; });

    cout << "Squares: ";
    for (int n : output) cout << n << " ";
    cout << endl;
}

void binary_transform_example() {
    cout << "\n=== Binary Transform Example (2 input ranges) ===\n";

    vector<int> a = {1, 2, 3};
    vector<int> b = {10, 20, 30};
    vector<int> result(a.size());

    // Add elements from a and b
    transform(a.begin(), a.end(), b.begin(), result.begin(),
              [](int x, int y) { return x + y; });

    cout << "Sum: ";
    for (int n : result) cout << n << " ";
    cout << endl;
}

void transform_string_to_uppercase() {
    cout << "\n=== Transform String to Uppercase (in-place) ===\n";

    string text = "openai gpt";

    transform(text.begin(), text.end(), text.begin(),
              [](char ch) { return toupper(ch); });

    cout << "Uppercased: " << text << endl;
}

int main() {
    unary_transform_example();
    binary_transform_example();
    transform_string_to_uppercase();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::transform
============================================================================

C++98:
- Introduced `std::transform` in <algorithm>
- Supports:
    - Unary transform: one input range → output
    - Binary transform: two input ranges → output

C++11:
- Lambdas added: cleaner function expressions inside `transform`

C++20:
- `std::ranges::transform` added (pipe-style + projections)
- Allows cleaner functional chaining
- Still backward compatible with std::transform

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Output range must be large enough (pre-allocated)
- Can transform in-place: input and output can be same
- Binary transform needs two input ranges of same size
- Works with all iterators, not just vectors
- Use with lambdas for cleaner expressions

============================================================================
CHEAT SHEET – std::transform
============================================================================

Unary transform:
    transform(begin1, end1, dest, func);

Binary transform:
    transform(begin1, end1, begin2, dest, func);

In-place:
    transform(vec.begin(), vec.end(), vec.begin(), func);

String case:
    transform(str.begin(), str.end(), str.begin(), ::toupper);

C++20 Ranges (if using):
    ranges::transform(input, output, func);
    // or
    auto new_range = input | views::transform(func);

*/

