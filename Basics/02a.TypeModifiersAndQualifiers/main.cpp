#include <iostream>
#include <limits>
using namespace std;

//
// ===================================================================
// PART 1: TYPE MODIFIERS
// ===================================================================
//
// WHY DO WE NEED TYPE MODIFIERS?
//
// Problem:
// The built-in `int` type has fixed size and signed behavior. But in real-world systems:
//
// - Sometimes we need to save space (e.g., sensors, embedded) → use `short`
// - Sometimes we need large values (e.g., IDs, time, file sizes) → use `long long`
// - Sometimes we only need positive numbers → use `unsigned`
//
// Solution:
// Use modifiers to **customize the width and sign** of basic types.
//
// These modifiers do not change syntax or behavior — they only adjust range/storage.
//

void type_modifiers_demo() {
    cout << "=== Type Modifiers ===\n";

    signed int a = -10;      // signed = default for int (optional to write)
    unsigned int b = 10;     // unsigned = no negative range

    cout << "signed int a = " << a << endl;
    cout << "unsigned int b = " << b << endl;

    // Demonstrate unsigned underflow:
    unsigned int c = 0;
    c = c - 1;  // wraps around to max value (due to underflow)
    cout << "unsigned underflow (0 - 1): c = " << c << endl;

    // Width modifiers:
    short s = 100;                     // small, typically 2 bytes
    long l = 100000L;                  // large, typically 4 or 8 bytes
    long long ll = 10000000000LL;      // very large, 8 bytes (standard since C++11)

    cout << "short = " << s << endl;
    cout << "long = " << l << endl;
    cout << "long long = " << ll << endl;

    // Show actual min/max range of each type
    cout << "\n--- Type Ranges ---\n";
    cout << "int: " << numeric_limits<int>::min() << " to " << numeric_limits<int>::max() << endl;
    cout << "unsigned int: 0 to " << numeric_limits<unsigned int>::max() << endl;
    cout << "short: " << numeric_limits<short>::min() << " to " << numeric_limits<short>::max() << endl;
    cout << "long long: " << numeric_limits<long long>::min() << " to " << numeric_limits<long long>::max() << endl;
}

//
// ===================================================================
// PART 2: TYPE QUALIFIERS
// ===================================================================
//
// WHY DO WE NEED TYPE QUALIFIERS?
//
// Problem:
// Sometimes we want to change how a variable behaves, not its size:
// - Prevent modification (`const`)
// - Allow modification inside `const` objects (`mutable`)
// - Prevent optimizations for memory-mapped variables (`volatile`)
// - Evaluate things at compile time (`constexpr`, `consteval`, `constinit`)
//
// Solution:
// Use **type qualifiers** to inform the compiler how the variable should behave.
//

// 1. const → read-only after initialization
void const_example() {
    const int x = 10;
    // x = 20; //  error: x is const
    cout << "[const] x = " << x << endl;
}

// 2. volatile → avoid compiler optimizations (for hardware/multithread use)
void volatile_example() {
    volatile int flag = 1; // compiler re-reads every time
    cout << "[volatile] flag = " << flag << endl;
}

// 3. mutable → allow mutation even in const objects
class MyClass {
public:
    int normal = 1;
    mutable int debug_counter = 0;

    void doSomething() const {
        // normal++; //  error: normal is not mutable
        debug_counter++; //  allowed
        cout << "[mutable] debug_counter = " << debug_counter << endl;
    }
};

// 4. constexpr → compile-time evaluated (C++11+)
constexpr int square(int x) {
    return x * x;
}

// 5. consteval → must be compile-time evaluated (C++20)
consteval int cube(int x) {
    return x * x * x;
}

// 6. constinit → compile-time initialization, but mutable (C++20)
constinit int global_value = 5;

void type_qualifiers_demo() {
    cout << "\n=== Type Qualifiers ===\n";

    const_example();
    volatile_example();

    const MyClass obj;
    obj.doSomething();  // modifies mutable member

    constexpr int result = square(4); // evaluated at compile time
    cout << "[constexpr] square(4) = " << result << endl;

    constexpr int val = cube(3);     // must be constexpr input
    cout << "[consteval] cube(3) = " << val << endl;

    global_value += 10; // constinit is not const
    cout << "[constinit] global_value = " << global_value << endl;
}

int main() {
    type_modifiers_demo();
    type_qualifiers_demo();
    return 0;
}

/*
===========================================================================
VERSION NOTES – TYPE MODIFIERS
===========================================================================

C++98:
- signed, unsigned, short, long available
- long long existed in some compilers (not standard)

C++11:
- long long standardized (guaranteed 64-bit on all systems)
- std::numeric_limits<T> for safe min/max usage

C++14/17/20:
- No new size/sign modifiers added
- Still commonly used with templates and traits

===========================================================================

VERSION NOTES – TYPE QUALIFIERS
===========================================================================

C++98:
- const: read-only after init
- volatile: prevents compiler from optimizing memory access
- mutable: allows modification inside const-qualified object

C++11:
- constexpr: compile-time evaluated functions and vars (limited rules)

C++14:
- constexpr functions allowed multiple statements, loops, conditionals

C++20:
- consteval: forces compile-time execution
- constinit: guarantees static/global init at compile time but mutable

===========================================================================

*/

