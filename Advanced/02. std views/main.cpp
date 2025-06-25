#include <iostream>
#include <vector>
#include <string>
#include <ranges>      // For std::views
#include <algorithm>   // For std::ranges:: algorithms
#include <numeric>     // For std::iota
using namespace std;

//
// WHY std::views?
//
// Problem:
// - Classic STL algorithms copy/modify data
// - Complex transformations require extra containers and loops
//
// Solution:
// - `views` are **non-owning**, **lazy**, and **composable**
// - They produce data on-the-fly, with clean pipe syntax
//

void filter_and_transform() {
    cout << "=== views::filter | views::transform ===\n";

    vector<int> nums = {1, 2, 3, 4, 5, 6};

    auto evens_squared = nums
                       | views::filter([](int x) { return x % 2 == 0; })
                       | views::transform([](int x) { return x * x; });

    cout << "Even squares: ";
    for (int x : evens_squared) cout << x << " ";
    cout << endl;
}

void take_and_drop() {
    cout << "\n=== views::take | views::drop ===\n";

    vector<int> nums(10);
    iota(nums.begin(), nums.end(), 1);  // 1 to 10

    auto taken = nums | views::take(5);   // First 5 elements
    auto dropped = nums | views::drop(5); // Skip first 5

    cout << "First 5: ";
    for (int x : taken) cout << x << " ";
    cout << "\nLast 5: ";
    for (int x : dropped) cout << x << " ";
    cout << endl;
}

void reverse_and_iota() {
    cout << "\n=== views::iota | views::reverse ===\n";

    auto r = views::iota(1, 11)       // 1 to 10
           | views::reverse;         // reverse order

    for (int x : r) cout << x << " ";
    cout << endl;
}

void split_string() {
    cout << "\n=== views::split (split by space) ===\n";

    string text = "The quick brown fox";
    auto words = text | views::split(' ');

    for (auto&& word : words) {
        for (char c : word)
            cout << c;
        cout << "\n";
    }
}

void combine_views() {
    cout << "\n=== Combined views (filter + transform + take) ===\n";

    vector<int> data(20);
    iota(data.begin(), data.end(), 1); // 1 to 20

    auto result = data
                | views::filter([](int x) { return x % 2 != 0; })      // odd
                | views::transform([](int x) { return x * 10; })      // scale
                | views::take(5);                                     // limit

    for (int x : result) cout << x << " ";
    cout << endl;
}

int main() {
    filter_and_transform();
    take_and_drop();
    reverse_and_iota();
    split_string();
    combine_views();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::views
============================================================================

(Yes) C++20:
- Introduced <ranges> header
- Added `std::views` namespace (lazy range adapters)
- Works with ranges:: algorithms (also from <algorithm>)

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Views are **lazy** and **non-owning**
    ➜ They reference original data, no copy unless explicitly made
- Chained using `|` pipe syntax
- Can be used in range-for loops or ranges:: algorithms
- Efficient: no extra memory, only computed when accessed
- Must include `<ranges>` and use `std::views::` prefix

Commonly Used Views:
| View              | Purpose                              |
|-------------------|---------------------------------------|
| views::filter     | Filter elements (by predicate)        |
| views::transform  | Apply function to each element        |
| views::take(n)    | Take first n elements                 |
| views::drop(n)    | Skip first n elements                 |
| views::iota       | Infinite or finite counting range     |
| views::reverse    | Reverse view (not in-place)           |
| views::split      | Split string or range into subranges  |

 `views::split` returns nested views — loop needs `for (auto&& part : view)`

============================================================================
CHEAT SHEET – Views Examples
============================================================================

auto result = vec
            | views::filter([](x) { return x > 5; })
            | views::transform([](x) { return x * 2; })
            | views::take(3);

views::iota(1, 10)       // 1 to 9
views::iota(0)           // Infinite counting

std::ranges::copy(view, ostream_iterator<int>(cout, " "));

*/

