#include <iostream>
#include <vector>
#include <algorithm>  // remove, remove_if, unique
#include <string>
using namespace std;

//
// WHY CLEANUP ALGORITHMS?
//
// Problem:
// - Need to remove unwanted or duplicate items from a container (like vector)
// - But std::vector doesn't shrink automatically on erase
//
// Solution:
// - Use `remove` and `remove_if` to *logically* remove
// - Then use container's `erase()` to *physically* remove memory
//

void remove_example() {
    cout << "=== std::remove and Erase Idiom ===\n";

    vector<int> nums = {1, 2, 3, 2, 4, 2, 5};

    // std::remove moves non-2 elements forward
    auto new_end = remove(nums.begin(), nums.end(), 2);  // doesn't shrink vector

    // Actual erase
    nums.erase(new_end, nums.end());  // now vector size is reduced

    cout << "After removing 2s: ";
    for (int n : nums) cout << n << " ";
    cout << endl;
}

void remove_if_example() {
    cout << "\n=== std::remove_if (predicate-based) ===\n";

    vector<int> nums = {1, 3, 6, 8, 10, 13};

    // Remove even numbers using lambda
    auto it = remove_if(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });
    nums.erase(it, nums.end());

    cout << "After removing evens: ";
    for (int n : nums) cout << n << " ";
    cout << endl;
}

void unique_example() {
    cout << "\n=== std::unique (removes adjacent duplicates only) ===\n";

    vector<int> nums = {1, 1, 2, 3, 3, 3, 4, 5, 5};

    // Only adjacent duplicates are removed
    auto it = unique(nums.begin(), nums.end());
    nums.erase(it, nums.end());

    cout << "After unique: ";
    for (int n : nums) cout << n << " ";
    cout << endl;
}

void erase_if_cpp20() {
    cout << "\n=== std::erase_if (C++20 only) ===\n";

    vector<string> words = {"apple", "banana", "app", "apricot"};

#if __cplusplus >= 202002L
    // Remove all words that start with "ap"
    erase_if(words, [](const string& s) {
        return s.starts_with("ap");  // C++20 std::string::starts_with
    });
#else
    // Fallback for C++17
    words.erase(remove_if(words.begin(), words.end(), [](const string& s) {
        return s.substr(0, 2) == "ap";
    }), words.end());
#endif

    cout << "After erasing words starting with 'ap': ";
    for (const auto& w : words) cout << w << " ";
    cout << endl;
}

int main() {
    remove_example();
    remove_if_example();
    unique_example();
    erase_if_cpp20();
    return 0;
}

/*
============================================================================
VERSION NOTES – Cleanup Algorithms
============================================================================

C++98:
- Introduced `std::remove`, `remove_if`, `unique`
- All of them work by moving valid items forward, do not resize container

C++11:
- Added lambda support (predicates with `remove_if` and `unique`)

C++20:
- Added `std::erase_if(container, predicate)` for common remove-if + erase pattern
- Also added `std::erase(container, value)`

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- `remove()` and `remove_if()` do NOT erase elements from container
    → They move valid elements forward, return iterator to new logical end
- You must follow with `container.erase(new_end, container.end());`
    → This is known as the **erase-remove idiom**
- `unique()` only removes *adjacent* duplicates
    → Use `sort()` before `unique()` if needed
- `std::erase_if()` in C++20 combines both steps in one call
- `std::remove_if()` is usually paired with a lambda

============================================================================
CHEAT SHEET – Cleanup Functions
============================================================================

| Algorithm         | Effect                            | Shrinks? | C++ Version |
|-------------------|------------------------------------|----------|-------------|
| remove            | Removes matching values            |  No    | C++98       |
| remove_if         | Removes values by predicate        |  No    | C++98       |
| unique            | Removes adjacent duplicates        |  No    | C++98       |
| erase_if          | Removes using predicate (one step) |  Yes   | C++20       |
| erase             | Removes matching value (C++20)     |  Yes   | C++20       |

Pattern:
    v.erase(remove(v.begin(), v.end(), val), v.end());

    v.erase(remove_if(v.begin(), v.end(), pred), v.end());

C++20:
    erase_if(v, pred);
    erase(v, val);

*/

