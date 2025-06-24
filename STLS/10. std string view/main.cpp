#include <iostream>
#include <string>
#include <string_view>  // C++17 header
using namespace std;

//
// WHY std::string_view?
//
// Problem:
// - std::string makes a full copy of the text → expensive for large/literal strings
// - Many APIs just need to read, not modify or own the string
//
// Solution:
// - std::string_view is a lightweight, non-owning **view** over string data:
//     - No memory allocation
//     - No copy
//     - Can view substrings without creating new objects
//

void basic_string_view() {
    cout << "=== std::string_view Basics ===\n";

    string_view sv = "Hello, World!";  // views literal — no copy

    cout << "Content: " << sv << endl;
    cout << "Length: " << sv.length() << endl;
    cout << "First char: " << sv.front() << ", Last char: " << sv.back() << endl;
}

void substring_view() {
    cout << "\n=== Substring View (No Copy) ===\n";

    string full = "C++20 is modern";
    string_view view(full);  // views entire string

    string_view sub = view.substr(5, 2);  // view "20"
    cout << "Substring view: " << sub << endl;

    // trim front/back (no actual data modified)
    view.remove_prefix(4);  // trims "C++ "
    view.remove_suffix(7);  // trims "modern"
    cout << "After trim: " << view << endl;
}

void use_string_view_in_function(string_view sv) {
    cout << "Inside function: " << sv << ", length = " << sv.length() << endl;
}

void function_example() {
    cout << "\n=== Passing string_view to Functions ===\n";

    use_string_view_in_function("temporary literal");  // very efficient
    string str = "Hello again";
    use_string_view_in_function(str);  // implicit conversion
}

void lifetime_issue() {
    cout << "\n=== ⚠️ Lifetime Pitfall ===\n";

    string_view sv;
    {
        string temp = "temporary";
        sv = temp;  //  sv points to temp's data
    }  // temp is destroyed here

    // cout << sv << endl;  //  UNDEFINED BEHAVIOR if uncommented
    cout << "(lifetime problem: sv points to destroyed string)\n";
}

int main() {
    basic_string_view();
    substring_view();
    function_example();
    lifetime_issue();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::string_view
============================================================================

C++17:
- Introduced std::string_view and std::wstring_view
- Non-owning view: works with literals, strings, char arrays
- Trimming via remove_prefix(), remove_suffix()
- Does NOT own or manage memory

C++20:
- Fully constexpr compatible
- Better integration with ranges and spans
- Operator==, operator<=> for comparison (C++20 spaceship)

============================================================================
COMPARISON – string vs string_view
============================================================================

| Feature               | std::string         | std::string_view      |
|-----------------------|---------------------|------------------------|
| Owns data             |  Yes              |  No                 |
| Memory allocation     |  Yes (heap)       |  No                 |
| Null-terminated       |  Yes              |  Not guaranteed     |
| Efficient slicing     |  No               |  Yes (no copy)      |
| Safe to return/store  |  Yes              |  Be cautious        |
| Modifiable            |  Yes              |  Read-only          |
| Works with literals   |  Yes              |  Yes (fast!)        |

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- `std::string_view` does **not null-terminate** the view (but works with C-style strings if given)
- Use `.data()` to access underlying `const char*`
- Use `.substr()`, `.starts_with()`, `.ends_with()` in C++20
- `.remove_prefix(n)` / `.remove_suffix(n)` trims the view without changing the original data
-  Lifetime danger: don't keep views to temporary/local strings

============================================================================
CHEAT SHEET – std::string_view
============================================================================

Declaration:
    string_view sv = "text";
    string_view sv = some_std_string;

Access:
    sv.size(), sv.length(), sv.empty()
    sv.front(), sv.back()
    sv.substr(start, count)
    sv.data() → const char*

Trimming (in-place, modifies view only):
    sv.remove_prefix(n);
    sv.remove_suffix(n);

Comparison:
    sv1 == sv2
    sv.starts_with("prefix")   // C++20
    sv.ends_with("suffix")     // C++20

Function parameters:
    void f(string_view sv);   // accept literals, string, etc.

Caution:
    Don't return `string_view` to a local/temporary string!
    Use `std::string` if ownership/lifetime must be preserved.

*/

