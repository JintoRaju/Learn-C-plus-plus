#include <iostream>
#include <algorithm>   // for STL algorithms
#include <vector>
#include <string>
#include <numeric>     // for accumulate
using namespace std;

//
// WHY STL ALGORITHMS?
//
// Problem:
// - Writing loops manually for every operation (search, sort, count, etc.) is error-prone.
//
// Solution:
// - STL provides 60+ algorithms in <algorithm> and <numeric> headers
// - Reusable, efficient, and highly optimized
// - Work with iterators (generic) — not tied to any one container
//

void core_examples() {
    cout << "=== Basic STL Algorithm Examples ===\n";

    vector<int> nums = {5, 1, 8, 3, 8};

    // std::sort (modifies in-place)
    sort(nums.begin(), nums.end());  // O(N log N)
    cout << "Sorted: ";
    for (int n : nums) cout << n << " ";
    cout << endl;

    // std::count
    int count8 = count(nums.begin(), nums.end(), 8);  // O(N)
    cout << "Count of 8: " << count8 << endl;

    // std::find
    auto it = find(nums.begin(), nums.end(), 3);
    if (it != nums.end()) cout << "Found 3 at position: " << distance(nums.begin(), it) << endl;

    // std::accumulate
    int total = accumulate(nums.begin(), nums.end(), 0);  // 0 is initial value
    cout << "Sum: " << total << endl;
}

void predicate_example() {
    cout << "\n=== Predicate-Based Algorithms ===\n";

    vector<int> data = {1, 2, 3, 4, 5, 6};

    // std::count_if
    int even_count = count_if(data.begin(), data.end(), [](int x) { return x % 2 == 0; });
    cout << "Even numbers: " << even_count << endl;

    // std::all_of (C++11)
    if (all_of(data.begin(), data.end(), [](int x) { return x > 0; }))
        cout << "All elements are positive.\n";

    // std::any_of (C++11)
    if (any_of(data.begin(), data.end(), [](int x) { return x > 5; }))
        cout << "At least one element > 5.\n";

    // std::none_of (C++11)
    if (none_of(data.begin(), data.end(), [](int x) { return x < 0; }))
        cout << "No negative numbers.\n";
}

int main() {
    core_examples();
    predicate_example();
    return 0;
}

/*
============================================================================
VERSION NOTES – STL Algorithms
============================================================================

C++98:
- Introduced most algorithms in <algorithm> and <numeric>
- Includes: sort, count, find, reverse, rotate, copy, etc.

C++11:
- Added lambda-friendly algorithms: all_of, any_of, none_of
- Lambdas allow inline predicates (more readable)

C++14:
- More constexpr algorithms (compiler evaluated)

C++17:
- Parallel algorithms (optional), std::reduce, execution policies
- `std::clamp()`, `std::transform_reduce`

C++20:
- Ranges-based algorithms (`std::ranges::sort`, etc.)
- Pipe-style chaining and projections
- More constexpr algorithms

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- All algorithms work on iterator ranges: [begin, end)
- Most do not modify original container (except sort, remove, etc.)
- Predicate = function that returns bool (e.g., `[](int x){ return x > 0; }`)
- Prefer STL algorithms over hand-written loops (readability + correctness)

============================================================================
CHEAT SHEET – Common STL Algorithms
============================================================================

| Name             | Purpose                       | Header         |
|------------------|-------------------------------|----------------|
| sort             | Sort elements                 | <algorithm>    |
| reverse          | Reverse elements              | <algorithm>    |
| count / count_if | Count values / with condition | <algorithm>    |
| find             | Search for value              | <algorithm>    |
| accumulate       | Sum of elements               | <numeric>      |
| all_of/any_of    | Check all/any match predicate | <algorithm>    |
| transform        | Apply function to elements    | <algorithm>    |
| remove_if        | Remove matching elements      | <algorithm>    |
| unique           | Remove duplicates (adjacent)  | <algorithm>    |

*/

