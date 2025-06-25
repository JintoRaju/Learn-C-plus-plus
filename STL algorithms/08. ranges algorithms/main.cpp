#include <iostream>
#include <vector>
#include <algorithm>   // for ranges:: algorithms
#include <ranges>      // for views and ranges
#include <string>
#include <cctype>      // for std::toupper
using namespace std;

//
// WHY STL RANGES (C++20)?
//
// Problem with classic STL algorithms:
// - Require manual passing of begin/end iterators
// - Cannot chain operations cleanly
// - Unsafe if begin/end mismatched
//
// Solution – ranges-based algorithms:
// - Safer: work directly on containers (no need for begin/end)
// - Cleaner: support projections, pipe syntax, and views
// - Functional: can chain filters, transforms, etc.
//
// All new algorithms live in `std::ranges`
// Views come from `std::views`
//

void ranges_sort_and_projection() {
    cout << "=== ranges::sort with projection ===\n";

    struct User {
        string name;
        int id;
    };

    vector<User> users = {{"alice", 3}, {"bob", 1}, {"carol", 2}};

    // Sort by id using projection
    ranges::sort(users, {}, &User::id);  // 3rd param is "projection"

    for (const auto& u : users)
        cout << u.name << " (" << u.id << ") ";
    cout << endl;
}

void ranges_transform_view_chain() {
    cout << "\n=== views::filter | views::transform | range-based loop ===\n";

    vector<int> nums = {1, 2, 3, 4, 5, 6};

    // Filter even, then square
    auto result = nums 
                | views::filter([](int x) { return x % 2 == 0; })
                | views::transform([](int x) { return x * x; });

    cout << "Even squares: ";
    for (int x : result) cout << x << " ";
    cout << endl;
}

void ranges_copy() {
    cout << "\n=== ranges::copy (container-only, safer) ===\n";

    vector<int> src = {10, 20, 30};
    vector<int> dest(3);

    ranges::copy(src, dest.begin());

    cout << "Copied: ";
    for (int x : dest) cout << x << " ";
    cout << endl;
}

void ranges_foreach_loop() {
    cout << "\n=== Ranges + range-based for loop ===\n";

    string text = "Hello World";

    auto uppercase = text 
                   | views::transform([](char c) { return toupper(c); });

    for (char ch : uppercase) cout << ch;
    cout << endl;
}

int main() {
    ranges_sort_and_projection();
    ranges_transform_view_chain();
    ranges_copy();
    ranges_foreach_loop();
    return 0;
}

/*
============================================================================
VERSION NOTES – Ranges Algorithms
============================================================================

✅ C++20:
- Introduced `std::ranges::sort`, `ranges::copy`, etc.
- Works directly on containers (no begin/end needed)
- All under `<algorithm>` and `<ranges>` headers

Classic:
    sort(vec.begin(), vec.end());

C++20:
    ranges::sort(vec);                      // cleaner and safer
    ranges::sort(vec, {}, &T::member);      // projection

C++20 Views:
    views::filter, views::transform, views::take, views::drop, etc.

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- All `ranges::` algorithms return result objects, not bools (e.g., copy result = {in, out})
- Views are lazy-evaluated (efficient!)
- You can chain views using `|` pipe operator
- Projections let you sort by a member or transform inside the algorithm call

- Views don't create new containers — just wrappers
- Combine views for powerful range expressions (filter, transform, take, etc.)

============================================================================
CHEAT SHEET – Ranges vs Classic
============================================================================

| Classic Syntax                 | Ranges Syntax (C++20)               |
|-------------------------------|-------------------------------------|
| sort(v.begin(), v.end())      | ranges::sort(v)                     |
| copy(a.begin(), a.end(), out) | ranges::copy(a, out)                |
| transform(a.begin(), a.end()) | views::transform([](x){...})       |
| for (auto x : container)      | for (auto x : container | view)    |

Pipe example:
    auto result = vec 
                | views::filter([](x){...})
                | views::transform([](x){...})
                | views::take(5);

Iterate:
    for (int x : result) { ... }

*/

