#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
#include <memory> // for move capture
#include <utility> // for std::move
using namespace std;

//
// FUNCTION-LEVEL MODERN C++ (C++11–C++20)
// ----------------------------------------
// This file demonstrates all major function-level features:
// - Lambda functions (with all capture types)
// - std::function
// - std::bind
// - Mutable lambdas
// - Move captures
// - Lambdas in STL algorithms
// - Immediately invoked lambdas (IIFE)
// - Comparison: Lambdas vs function pointers vs std::function
//
// All explanations are inline, deeply commented, and version-noted.
//

int main() {

    // 1. Basic Lambda Function — Introduced in C++11
    // ------------------------------------------------
    // Motivation: Small, inline, unnamed functions useful for callbacks and algorithms
    auto add = [](int a, int b) { return a + b; }; // lambda expression
    cout << "Lambda add(3, 5) = " << add(3, 5) << "\n";

    // Syntax: [capture-list](parameters) -> return-type { body }
    // - capture-list []: What to bring from outer scope
    // - return type is usually inferred; explicit `-> type` is optional


    // 2. Lambda Captures — C++11
    // ----------------------------
    int x = 10, y = 20;

    auto by_val = [x]() { cout << "Captured by value (x): " << x << "\n"; };
    auto by_ref = [&y]() { cout << "Captured by reference (y): " << y << "\n"; };

    by_val(); // captures a copy of x at the moment of lambda definition
    by_ref(); // accesses live reference of y — changes to y will be seen

    // Notes:
    // - Default capture by value: [=]
    // - Default capture by reference: [&]
    // - Mixed capture: [x, &y]


    // 3. Capturing by Move — Introduced in C++14
    // -------------------------------------------
    // Motivation: When capturing movable-only types (e.g., unique_ptr), normal capture fails
    auto ptr = make_unique<int>(99);

    auto move_capture = [p = move(ptr)]() {
        cout << "Captured unique_ptr by move: *p = " << *p << "\n";
    };
    move_capture();

    // Note:
    // - After move, `ptr` is nullptr; move-capture allows transferring ownership into lambda


    // 4. Generic Lambdas — Introduced in C++14
    // ------------------------------------------
    // Motivation: Lambdas should be able to take any type, like function templates
    auto square = [](auto val) { return val * val; }; // val: deduced at runtime

    cout << "Generic lambda square(4): " << square(4) << ", square(2.5): " << square(2.5) << "\n";

    // Note: Before C++14, we had to write templates or overloads


    // 5. std::function — Type-erased function wrapper (C++11)
    // --------------------------------------------------------
    // Motivation: Needed to store lambdas or function pointers in containers, variables, etc.
    std::function<int(int, int)> sum_func = [](int a, int b) { return a + b; };

    cout << "std::function result: sum_func(10, 20) = " << sum_func(10, 20) << "\n";

    // Notes:
    // - Adds runtime overhead due to type-erasure (heap allocation, virtual calls)
    // - Use only when needed (e.g., passing as a callback to APIs, storing heterogeneous callables)


    // 6. std::bind — Partial Function Application (C++11)
    // -----------------------------------------------------
    // Motivation: Create functions with fixed arguments (also known as currying/partial binding)
    auto multiply = [](int a, int b) { return a * b; };

    auto double_func = bind(multiply, 2, placeholders::_1); // fixes a=2, keeps b as input

    cout << "std::bind result: double_func(8) = " << double_func(8) << "\n";

    // Notes:
    // - Use placeholders::_1, _2 for argument positions
    // - Replaced by lambdas in most modern code for clarity
    // - std::bind has edge cases with reference binding


    // 7. Lambdas in Algorithms — Works from C++11, but enhanced by C++20 (ranges)
    // ---------------------------------------------------------------------------
    vector<int> vec = {1, 2, 3, 4, 5};

    cout << "Before transform: ";
    for (int v : vec) cout << v << " ";

    ranges::transform(vec, vec.begin(), [](int v) { return v * 2; });

    cout << "\nAfter transform (×2): ";
    for (int v : vec) cout << v << " ";
    cout << "\n";

    // Notes:
    // - Lambdas are widely used in STL algorithms
    // - `ranges::transform` (C++20) avoids passing iterators explicitly


    // 8. Mutable Lambdas — C++11
    // ----------------------------
    int counter = 0;

    auto inc = [counter]() mutable {
        counter++;
        cout << "Inside mutable lambda: counter = " << counter << "\n";
    };

    inc();
    cout << "Outside lambda: counter = " << counter << " (original unchanged)\n";

    // Notes:
    // - Captures by value are const by default
    // - mutable allows changing captured-by-value inside lambda


    // 9. Immediately Invoked Lambdas (IIFE) — C++11
    // -----------------------------------------------
    // Motivation: Do quick computations or scope management
    int sum = [](int a, int b) {
        return a + b;
    }(3, 4);

    cout << "IIFE result: sum = " << sum << "\n";

    // Note:
    // - Similar to JavaScript IIFE
    // - Useful for on-the-spot initialization


    // 10. Function Pointers vs Lambda vs std::function
    // --------------------------------------------------
    // Function pointer (C-style)
    int (*func_ptr)(int, int) = [](int a, int b) { return a - b; };
    cout << "Function pointer call: func_ptr(7, 2) = " << func_ptr(7, 2) << "\n";

    // std::function (type-erased)
    std::function<void()> greet = []() {
        cout << "Hello from std::function!\n";
    };
    greet();

    // Notes:
    // - Lambda can be converted to function pointer if it doesn't capture
    // - Use std::function for storage/flexibility; avoid for hot paths due to overhead

    return 0;
}

/*
============================================================================
VERSION NOTES
============================================================================

✅ C++11:
- Lambdas introduced
- std::function and std::bind available
- Mutable lambdas
- Function pointer compatibility

✅ C++14:
- Generic lambdas (auto parameters)
- Init-capture syntax (move-capture by `[x = move(...)`])

✅ C++17:
- constexpr lambdas (minor enhancement)
- Deductions more refined

✅ C++20:
- Lambdas used with ranges
- Template lambdas + constraints
- Safer conversions to function pointers
- Lambdas in unevaluated contexts

============================================================================
TINY EDGE NOTES
============================================================================

- Lambdas with captures cannot convert to function pointer
- std::function may allocate memory → avoid in performance-critical code
- std::bind is less readable — prefer lambdas
- Capturing by move is useful for smart pointers, large objects
- Mutable lambdas are often misunderstood — value copy is not mutated outside

============================================================================
CHEAT SHEET: FUNCTION-LEVEL MODERN C++
============================================================================

| Feature               | Syntax / Note                                     |
|----------------------|---------------------------------------------------|
| Lambda               | `[](int x){ return x*x; }`                        |
| Capture by value     | `[x]`                                             |
| Capture by ref       | `[&x]`                                            |
| Capture all value    | `[=]`                                             |
| Capture all ref      | `[&]`                                             |
| Move capture (C++14) | `[p = move(ptr)]`                                 |
| Generic lambda       | `[](auto x){ return x + 1; }`                     |
| Mutable              | `[]() mutable { val++; }`                         |
| std::function        | `std::function<int(int)>`                         |
| std::bind            | `bind(func, 2, _1)`                               |
| IIFE                 | `[](int a){ return a*2; }(10)`                    |

*/
