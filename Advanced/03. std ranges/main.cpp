#include <iostream>
#include <vector>
#include <algorithm>   // for std::ranges algorithms
#include <ranges>      // for std::views
#include <numeric>     // for std::iota
#include <iterator>
using namespace std;

//
// WHY std::ranges ALGORITHMS?
//
// Problem with classic STL algorithms:
// - Require begin()/end() manually
// - Prone to mismatch errors
// - Return types are inconsistent
//
// Solution:
// - `std::ranges::` algorithms work directly on containers/ranges
// - Safer, easier to use, and support projections
// - Return structured result (in, out) → better handling
//

void ranges_copy_example() {
    cout << "=== ranges::copy (returns in-out pair) ===\n";

    vector<int> src = {1, 2, 3};
    vector<int> dst(3);

    auto result = ranges::copy(src, dst.begin()); // result has .in and .out

    cout << "Copied: ";
    for (int x : dst) cout << x << " ";
    cout << "\nNext write position: " << (result.out - dst.begin()) << endl;
}

void ranges_find_example() {
    cout << "\n=== ranges::find (container-safe) ===\n";

    vector<string> words = {"cat", "dog", "bird"};

    auto it = ranges::find(words, "dog");

    if (it != words.end())
        cout << "Found: " << *it << endl;
    else
        cout << "Not found.\n";
}

void ranges_sort_projection() {
    cout << "\n=== ranges::sort with projection ===\n";

    struct Person {
        string name;
        int age;
    };

    vector<Person> people = {
        {"Alice", 30}, {"Bob", 20}, {"Carol", 25}
    };

    // Sort by age using projection
    ranges::sort(people, {}, &Person::age);

    for (const auto& p : people)
        cout << p.name << " (" << p.age << ") ";
    cout << endl;
}

void ranges_with_views() {
    cout << "\n=== ranges::copy with filtered view ===\n";

    vector<int> nums = {1, 2, 3, 4, 5, 6};
    vector<int> evens;

    // Copy only even numbers from filtered view
    ranges::copy(
        nums | views::filter([](int x) { return x % 2 == 0; }),
        back_inserter(evens)
    );

    cout << "Evens: ";
    for (int x : evens) cout << x << " ";
    cout << endl;
}

void ranges_structured_return_example() {
    cout << "\n=== ranges::remove_copy_if return result struct ===\n";

    vector<int> src = {1, 2, 3, 4, 5};
    vector<int> dst;

    auto res = ranges::remove_copy_if(src, back_inserter(dst),
                                      [](int x) { return x % 2 == 0; });

    cout << "Removed evens, remaining: ";
    for (int x : dst) cout << x << " ";
    cout << endl;
}

int main() {
    ranges_copy_example();
    ranges_find_example();
    ranges_sort_projection();
    ranges_with_views();
    ranges_structured_return_example();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::ranges (C++20)
============================================================================

 C++20:
- Introduced `std::ranges::` algorithms as safer, more composable alternatives
- All defined in <algorithm> and <ranges>
- Work directly on containers (no .begin(), .end() required)
- Support projections (e.g., sort by member variable)
- Return structured results (e.g., `in_out_result`, `in_fun_result`, etc.)

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

O Safe:
    ranges::copy(vec, out);                // no need for vec.begin()

O Smart return:
    auto res = ranges::copy(...);          // res.in, res.out

O Projection support:
    ranges::sort(objects, {}, &Obj::id);

O Works with views:
    ranges::copy(vec | views::filter(...), out);

O All `ranges::` versions match their classic STL names:
    ranges::sort, ranges::find, ranges::transform, ranges::remove, etc.

============================================================================
CHEAT SHEET – ranges:: vs classic
============================================================================

| Classic STL                   | Modern ranges:: (C++20)              |
|-------------------------------|--------------------------------------|
| sort(vec.begin(), vec.end())  | ranges::sort(vec)                    |
| copy(a.begin(), a.end(), out) | ranges::copy(a, out)                 |
| find(a.begin(), a.end(), x)   | ranges::find(a, x)                   |
| transform(..., out, f)        | ranges::transform(input, out, f)     |
| remove_copy_if(..., pred)     | ranges::remove_copy_if(input, out, pred) |

Return Example:
    auto result = ranges::copy(a, b);
    result.in  // where read ended
    result.out // where write ended

*/

