#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <iterator>
#include <type_traits> // For iterator_category introspection (type traits)

using namespace std;

//
// WHY ITERATORS?
//
// Problem:
// - You need a generic way to traverse containers (e.g., vector, list, set)
// - Loops and indices don't work for all containers (e.g., singly-linked lists)
//
// Solution:
// - Iterators are generalized pointers
// - STL algorithms (sort, find, transform) use them to work with any container
//

// Helper function to print iterator category
template <typename Iter>
void print_category(const Iter& it) {
    using Cat = typename iterator_traits<Iter>::iterator_category;

    cout << "Iterator category: ";
    if constexpr (is_same_v<Cat, input_iterator_tag>)         cout << "Input\n";
    else if constexpr (is_same_v<Cat, output_iterator_tag>)   cout << "Output\n";
    else if constexpr (is_same_v<Cat, forward_iterator_tag>)  cout << "Forward\n";
    else if constexpr (is_same_v<Cat, bidirectional_iterator_tag>) cout << "Bidirectional\n";
    else if constexpr (is_same_v<Cat, random_access_iterator_tag>) cout << "Random Access\n";
    else cout << "Unknown\n";
}

void demo_iterators() {
    cout << "=== Iterator Category Examples ===\n";

    vector<int> vec = {1, 2, 3};
    list<int> lst = {4, 5, 6};
    forward_list<int> flst = {7, 8, 9};

    // Test iterator category detection
    print_category(vec.begin());   // random-access
    print_category(lst.begin());   // bidirectional
    print_category(flst.begin());  // forward

    // Access via iterator (vector)
    auto vit = vec.begin();
    cout << "vec[1] using iterator: " << *(vit + 1) << endl;  // only valid for random-access

    // Access via iterator (list)
    auto lit = lst.begin();
    ++lit;  // move to 2nd element
    cout << "list[1] using iterator: " << *lit << endl;

    // Forward list does NOT support -- (no bidirectional)
    auto flit = flst.begin();
    ++flit;
    cout << "forward_list[1] using iterator: " << *flit << endl;
}

int main() {
    demo_iterators();
    return 0;
}

/*
============================================================================
VERSION NOTES – STL Iterators
============================================================================

 C++98:
- Introduced `iterator_traits`, iterator categories:
  input, output, forward, bidirectional, random-access

 C++11:
- `auto` simplifies iterator declarations
- Range-based for loops (`for (auto x : container)`) introduced
- Lambdas enable easier use with algorithms

 C++17:
- `std::data()`, `std::size()` helpers added
- STL algorithms can deduce iterator types better

 C++20:
- Iterators + ranges: views work with iterators automatically
- Concepts like `std::input_iterator`, `std::ranges::range` added
- `contiguous_iterator_tag` added to describe raw array-style memory (e.g., vector)

============================================================================
CHEAT SHEET – Iterator Categories
============================================================================

| Category             | Features                       | Examples                  |
|----------------------|--------------------------------|---------------------------|
| input_iterator       | Read-only, single-pass         | `istream_iterator`        |
| output_iterator      | Write-only, single-pass        | `ostream_iterator`        |
| forward_iterator     | Read/write, multi-pass         | `forward_list::iterator`  |
| bidirectional        | + backward (`--`)              | `list::iterator`, `set`   |
| random_access        | + arithmetic (`+`, `-`, `[]`)  | `vector::iterator`, `deque`
| contiguous (C++20)   | Raw memory contiguous access   | `vector`, `array`, C-arrays

============================================================================
TIPS
============================================================================

- Most STL algorithms require at least forward iterators
- `sort()` needs random-access iterators → won't work on `list`, `forward_list`
- Use `iterator_traits` to introspect iterator category at compile time

*/

