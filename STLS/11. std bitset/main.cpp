#include <iostream>
#include <bitset>
#include <string>
using namespace std;

//
// WHY std::bitset?
//
// Problem:
// - Using `int` for flags is unsafe (easy to overflow, difficult to visualize)
// - `vector<bool>` is dynamic but inefficient for tight-packed bits
//
// Solution:
// - `std::bitset<N>`: Fixed-size bitfield with:
//     - Easy access to individual bits
//     - Bitwise operations (AND, OR, XOR, shifts)
//     - Conversion to/from binary strings
//     - Fast, compact, and visual
//

void basic_bitset_usage() {
    cout << "=== std::bitset Basics ===\n";

    bitset<8> b1;             // default all 0s
    bitset<8> b2(42);         // decimal 42 → binary 00101010
    bitset<8> b3(string("1101")); // right-aligned → 00001101

    cout << "b1: " << b1 << endl;
    cout << "b2: " << b2 << endl;
    cout << "b3: " << b3 << endl;
}

void bit_operations() {
    cout << "\n=== Bit Manipulation ===\n";

    bitset<8> bits("00101101");

    bits.set(0);          // set bit 0 to 1
    bits.reset(3);        // set bit 3 to 0
    bits.flip(1);         // flip bit 1

    cout << "Modified bits: " << bits << endl;

    cout << "Bit 2 is: " << bits.test(2) << endl;     // true/false
    cout << "Any set? " << bits.any() << endl;
    cout << "None set? " << bits.none() << endl;
    cout << "Number of 1s: " << bits.count() << endl;
}

void binary_logic() {
    cout << "\n=== Binary Logic Operations ===\n";

    bitset<8> a(string("10101010"));
    bitset<8> b(string("11001100"));

    bitset<8> anded = a & b;
    bitset<8> ored  = a | b;
    bitset<8> xored = a ^ b;
    bitset<8> not_a = ~a;

    cout << "a & b : " << anded << endl;
    cout << "a | b : " << ored  << endl;
    cout << "a ^ b : " << xored << endl;
    cout << "~a    : " << not_a << endl;
}

void shifts_and_conversion() {
    cout << "\n=== Bit Shifts and Conversions ===\n";

    bitset<8> bits("00010001");

    cout << "Original: " << bits << endl;
    cout << "Shift left 2: " << (bits << 2) << endl;
    cout << "Shift right 3: " << (bits >> 3) << endl;

    unsigned long val = bits.to_ulong(); // convert to number
    cout << "As number: " << val << endl;

    string bin_str = bits.to_string();
    cout << "As binary string: " << bin_str << endl;
}

int main() {
    basic_bitset_usage();
    bit_operations();
    binary_logic();
    shifts_and_conversion();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::bitset
============================================================================

C++98:
- Introduced std::bitset<N> in STL
- Supports fixed-length bit storage
- Access: set(), reset(), flip(), test(), count()
- Logic: &, |, ^, ~, <<, >>

C++11:
- Improved performance and compatibility
- Bitwise ops on const objects more consistent

C++14:
- Minor constexpr enhancements

C++17:
- Better interoperability with other STL containers

C++20:
- Fully usable in constexpr contexts
- Integration with other constexpr logic and meta-programming

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Length `N` is a compile-time constant → cannot resize
- Operates on internal array of words (efficient)
- `.test(i)` safely checks bit i, returns bool
- `.set(i)`, `.reset(i)`, `.flip(i)` allow modifying individual bits
- `.to_string()` returns full binary with leading 0s
- `.to_ulong()` / `.to_ullong()` convert to numbers
- Throws `std::overflow_error` if `.to_ulong()` overflows

============================================================================
COMPARISON – bitset vs vector<bool> vs int
============================================================================

| Feature               | bitset<N>        | vector<bool>      | int / uint        |
|-----------------------|------------------|--------------------|-------------------|
| Fixed-size            |  Yes (compile) |  Dynamic         |  Dynamic bits   |
| Random access         |  Yes           |  Yes (proxy)     |  Manual mask    |
| Resizable             |  No            |  Yes             |  No             |
| Bitwise operators     |  Yes           |  Limited         |  Yes            |
| Memory efficient      |  Yes           |  Mixed           |  (compact)      |
| String conversion     |  Yes           |  No              |  No             |

============================================================================
CHEAT SHEET – std::bitset
============================================================================

Declaration:
    bitset<8> b;                  // all 0s
    bitset<8> b(42);              // from integer
    bitset<8> b("1101");          // from string

Operations:
    b.set(i);                     // set bit i to 1
    b.reset(i);                   // set bit i to 0
    b.flip(i);                    // toggle bit i
    b.test(i);                    // check bit i

Checks:
    b.any(), b.none(), b.count()

Logic:
    b1 & b2, b1 | b2, b1 ^ b2, ~b1

Shift:
    b << n, b >> n

Conversion:
    b.to_string(), b.to_ulong(), b.to_ullong()

*/

