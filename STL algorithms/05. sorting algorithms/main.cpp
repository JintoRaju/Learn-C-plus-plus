#include <iostream>
#include <vector>
#include <algorithm>  // sort, stable_sort, partial_sort, nth_element
#include <string>
using namespace std;

//
// WHY SORTING ALGORITHMS?
//
// Problem:
// - Sorting by value, key, custom rules
// - You want speed, stability, or partial top-k results
//
// Solution:
// - STL provides fast, flexible algorithms:
//     - sort          → quick and efficient (but not stable)
//     - stable_sort   → maintains original order of equal elements
//     - partial_sort  → get top-k elements (sorted)
//     - nth_element   → find k-th largest/smallest (without full sort)
//

void std_sort_example() {
    cout << "=== std::sort (unstable but fast) ===\n";

    vector<int> data = {4, 2, 5, 3, 1};

    sort(data.begin(), data.end());  // in-place sort

    cout << "Sorted: ";
    for (int x : data) cout << x << " ";
    cout << endl;
}

void stable_sort_example() {
    cout << "\n=== std::stable_sort (preserves order of equal items) ===\n";

    struct Person {
        string name;
        int age;
    };

    vector<Person> people = {
        {"Alice", 30}, {"Bob", 25}, {"Carol", 30}, {"Dave", 25}
    };

    // Sort by age, preserving original order when age is equal
    stable_sort(people.begin(), people.end(),
                [](const Person& a, const Person& b) {
                    return a.age < b.age;
                });

    for (const auto& p : people)
        cout << p.name << " (" << p.age << ") ";
    cout << endl;
}

void partial_sort_example() {
    cout << "\n=== std::partial_sort (sort only top-k items) ===\n";

    vector<int> scores = {70, 90, 60, 100, 85};

    // Sort top 3 scores only
    partial_sort(scores.begin(), scores.begin() + 3, scores.end(), greater<int>());

    cout << "Top 3 scores: ";
    for (int i = 0; i < 3; ++i)
        cout << scores[i] << " ";
    cout << endl;
}

void nth_element_example() {
    cout << "\n=== std::nth_element (partition around nth) ===\n";

    vector<int> scores = {10, 80, 30, 60, 50, 20, 90};

    // Reorder so that the 3rd element is the one that would be in that position if fully sorted
    nth_element(scores.begin(), scores.begin() + 3, scores.end());

    cout << "After nth_element (index 3 is median-ish): ";
    for (int x : scores) cout << x << " ";
    cout << endl;

    cout << "3rd element (index 3): " << scores[3] << endl;
}

int main() {
    std_sort_example();
    stable_sort_example();
    partial_sort_example();
    nth_element_example();
    return 0;
}

/*
============================================================================
VERSION NOTES – Sorting Algorithms
============================================================================

C++98:
- Introduced `std::sort`, `std::stable_sort`, `std::partial_sort`, `std::nth_element`

C++11:
- Lambdas introduced → cleaner comparators
- `std::array` and more container compatibility

C++20:
- Added `std::ranges::sort`, `ranges::stable_sort`, etc.
- Ranges support projections and chaining (pipe syntax)
- Example: `ranges::sort(people, {}, &Person::age);`

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- `std::sort`: O(N log N), **unstable**, uses intro-sort (quick + heap + insertion)
- `std::stable_sort`: O(N log² N), **stable**, uses merge sort
- `std::partial_sort`: O(N log K), only the first K elements are sorted
- `std::nth_element`: O(N), partitions so that nth element is "correct" (but no order elsewhere)

- All are **in-place**, do not return new container
- `std::sort` usually outperforms `stable_sort` when stability isn’t needed

============================================================================
CHEAT SHEET – Sorting STL
============================================================================

| Algorithm        | Purpose                              | Stable | C++ Version |
|------------------|---------------------------------------|--------|-------------|
| std::sort        | Full sort (fast, intro-sort)          | No     | C++98       |
| std::stable_sort | Full sort (preserves order)           | Yes    | C++98       |
| std::partial_sort| Top-K sorting                         | No     | C++98       |
| std::nth_element | Partition around kth item             | No     | C++98       |

Comparators:
    sort(v.begin(), v.end(), greater<int>());
    sort(v.begin(), v.end(), [](auto a, auto b) { return a.id < b.id; });

C++20 Ranges:
    ranges::sort(container);                  // sorts whole container
    ranges::sort(data, {}, &MyType::member);  // projection (by member)

*/

