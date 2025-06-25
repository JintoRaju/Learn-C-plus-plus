#include <iostream>
#include <vector>
#include <algorithm>  // for set algorithms
using namespace std;

//
// WHY SET ALGORITHMS?
//
// Problem:
// - You want to find elements:
//     - Common to two sets
//     - Only in one, not in other
//     - Appearing in either, but not both
//
// Solution:
// - STL provides `set_union`, `set_intersection`, etc.
// - Work with sorted ranges (input MUST be sorted)
// - Output to any container using back_inserter
//

void show(const vector<int>& v, const string& label) {
    cout << label << ": ";
    for (int n : v) cout << n << " ";
    cout << endl;
}

void run_set_algorithms() {
    vector<int> A = {1, 2, 4, 5, 6};
    vector<int> B = {2, 3, 5, 7};

    vector<int> result;

    //
    // 1. Union – all unique elements from both (like SQL UNION)
    //
    result.clear();
    set_union(A.begin(), A.end(), B.begin(), B.end(), back_inserter(result));
    show(result, "Union");

    //
    // 2. Intersection – only common elements
    //
    result.clear();
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(result));
    show(result, "Intersection");

    //
    // 3. Difference – A - B (in A but not in B)
    //
    result.clear();
    set_difference(A.begin(), A.end(), B.begin(), B.end(), back_inserter(result));
    show(result, "A - B (Difference)");

    //
    // 4. Symmetric Difference – elements in A or B but not both
    //
    result.clear();
    set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(), back_inserter(result));
    show(result, "Symmetric Difference");
}

int main() {
    cout << "=== Set Algorithms ===\n";
    run_set_algorithms();
    return 0;
}

/*
============================================================================
VERSION NOTES – Set Algorithms
============================================================================

C++98:
- All 4 set algorithms introduced in <algorithm>
  - set_union
  - set_intersection
  - set_difference
  - set_symmetric_difference

C++20:
- Ranges-based versions added:
  - ranges::set_union()
  - ranges::set_difference(), etc.
  - Allow projections, pipe syntax
  - Also support comparators and `views`

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- (Yes) Inputs **must be sorted** for correct results!
  - If not sorted, output will be incorrect.
  - Use `std::sort()` beforehand if needed.

- Output is written via output iterator (e.g., `back_inserter`)
- Duplicate elements are preserved per set rules

- You can use custom comparators (like case-insensitive, struct compare)
- All functions work with any sorted ranges (e.g., `vector`, `set`, `array`)

============================================================================
CHEAT SHEET – STL Set Algorithms
============================================================================

| Algorithm                 | Description                      | Output Contains              |
|---------------------------|----------------------------------|------------------------------|
| set_union                 | Elements in A ∪ B                | All from A or B              |
| set_intersection          | Elements in A ∩ B                | Common to both               |
| set_difference            | Elements in A - B                | Only in A                    |
| set_symmetric_difference  | Elements in A ⊕ B                | In A or B but not both       |

Pattern:
    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(out));

    // For structs:
    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(out), comparator);

C++20:
    ranges::set_union(a, b, back_inserter(out));
    ranges::set_difference(a, b, out_it);

*/

