#include <iostream>
#include <vector>
using namespace std;

/*
================================================================================
DSA_00_INTROANDCOMPLEXITY.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O Before learning any data structure or algorithm, we need to evaluate:
   O How fast it runs (time complexity)
   O How much memory it uses (space complexity)

O DSA helps solve problems **efficiently**, not just correctly.
O Time complexity helps us scale — avoid slow programs on large inputs.

================================================================================
TOPICS COVERED
================================================================================
1. What is Time Complexity?
2. Big-O Notation (O(1), O(n), O(n^2), etc.)
3. Space Complexity
4. Real examples in C++
================================================================================
*/


//------------------------------------------------------------------------------
// 1. O(1) — Constant time
//------------------------------------------------------------------------------
void printFirstElement(const vector<int>& arr) {
    // No matter the size of array, it accesses just one element
    cout << "[O(1)] First element is: " << arr[0] << endl;
}

//------------------------------------------------------------------------------
// 2. O(n) — Linear time
//------------------------------------------------------------------------------
void printAllElements(const vector<int>& arr) {
    cout << "[O(n)] Elements: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

//------------------------------------------------------------------------------
// 3. O(n^2) — Quadratic time
//------------------------------------------------------------------------------
void printAllPairs(const vector<int>& arr) {
    cout << "[O(n^2)] All pairs:\n";
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr.size(); ++j) {
            cout << "(" << arr[i] << "," << arr[j] << ") ";
        }
        cout << endl;
    }
}

//------------------------------------------------------------------------------
// 4. Space Complexity
//------------------------------------------------------------------------------
void copyArray(const vector<int>& input) {
    // O(n) space — creates a new vector of same size
    vector<int> copy = input;
    cout << "[O(n) Space] Copied array size: " << copy.size() << endl;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Range-based for loop introduced (used above)
- auto keyword (not used here but useful)

C++14/17:
- Minor syntax improvements

C++20:
- Concepts and ranges for advanced DSA (we will explore soon)
- Default initializer for lambdas (not needed here yet)

================================================================================
BIG-O CHEAT SHEET (COMMON COMPLEXITIES)
================================================================================
O(1)      ➜ Constant time (e.g., array[i], push_back())
O(log n)  ➜ Logarithmic (e.g., binary search)
O(n)      ➜ Linear (e.g., loop over array)
O(n log n)➜ Merge sort, quick sort
O(n^2)    ➜ Nested loops (e.g., all pairs)
O(2^n)    ➜ Recursive brute force (e.g., subsets)
O(n!)     ➜ All permutations

================================================================================
BEST PRACTICES
================================================================================
O Always analyze both time and space
O Start with brute force, then optimize using better data structures
O Know your input size: 10^5 elements = needs O(n log n) or better
O Use vector instead of raw arrays for safety and modern style
*/

int main() {
    vector<int> sample = {1, 2, 3, 4, 5};

    printFirstElement(sample);     // O(1)
    printAllElements(sample);      // O(n)
    printAllPairs(sample);         // O(n^2)
    copyArray(sample);             // O(n) space

    return 0;
}
