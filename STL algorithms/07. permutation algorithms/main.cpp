#include <iostream>
#include <vector>
#include <algorithm>  // next_permutation, prev_permutation, is_permutation
using namespace std;

//
// WHY PERMUTATION ALGORITHMS?
//
// Problem:
// - You want to generate all possible arrangements of elements
// - Or check if two sequences are just different permutations
//
// Solution:
// - Use `std::next_permutation` and `std::prev_permutation` to walk through permutations
// - Use `std::is_permutation` to check if two containers have same elements (in any order)
//

void next_perm_example() {
    cout << "=== std::next_permutation (lexicographic order) ===\n";

    vector<int> nums = {1, 2, 3};

    // Must be sorted initially to generate all permutations
    int count = 1;
    do {
        cout << "Perm " << count++ << ": ";
        for (int n : nums) cout << n << " ";
        cout << endl;
    } while (next_permutation(nums.begin(), nums.end()));
}

void prev_perm_example() {
    cout << "\n=== std::prev_permutation (reverse lexicographic) ===\n";

    vector<int> nums = {3, 2, 1};  // highest order

    int count = 1;
    do {
        cout << "Perm " << count++ << ": ";
        for (int n : nums) cout << n << " ";
        cout << endl;
    } while (prev_permutation(nums.begin(), nums.end()));
}

void is_perm_example() {
    cout << "\n=== std::is_permutation (check rearranged equality) ===\n";

    vector<int> a = {1, 2, 3, 4};
    vector<int> b = {4, 3, 2, 1};
    vector<int> c = {1, 2, 2, 4};

    cout << "a and b: ";
    cout << (is_permutation(a.begin(), a.end(), b.begin()) ? "Yes" : "No") << endl;

    cout << "a and c: ";
    cout << (is_permutation(a.begin(), a.end(), c.begin()) ? "Yes" : "No") << endl;
}

int main() {
    next_perm_example();
    prev_perm_example();
    is_perm_example();
    return 0;
}

/*
============================================================================
VERSION NOTES – Permutation Algorithms
============================================================================

C++98:
- `std::next_permutation` and `std::prev_permutation`
- `std::is_permutation` was not available

C++11:
- `std::is_permutation` added
- Lambdas now allowed for custom comparisons in permutations

C++20:
- `std::ranges::next_permutation` (in <algorithm> but with ranges)
- Supports projections and cleaner chaining

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- `next_permutation` and `prev_permutation` reorder elements in-place
- They return `false` when no more permutations remain
    ➜ After last one, sequence is reset to first (or last, respectively)
- Sequence should be **sorted** to generate all permutations in order
- `is_permutation()` checks multiset equality — not ordering
    ➜ Duplicate handling matters!

============================================================================
CHEAT SHEET – Permutations
============================================================================

| Algorithm             | Description                           | Returns | C++ Version |
|-----------------------|---------------------------------------|---------|-------------|
| next_permutation      | Moves to next lexicographical order   | bool    | C++98       |
| prev_permutation      | Moves to previous lex order           | bool    | C++98       |
| is_permutation        | True if two ranges are permutations   | bool    | C++11       |

Examples:
    sort(v.begin(), v.end());
    do {
        // use v
    } while (next_permutation(v.begin(), v.end()));

    if (is_permutation(a.begin(), a.end(), b.begin()))
        cout << "Same elements";

C++20:
    ranges::next_permutation(v);
    ranges::is_permutation(v, w);

*/

