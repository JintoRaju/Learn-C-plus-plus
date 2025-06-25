#include <iostream>
#include <memory>
#include <string>
using namespace std;

/*
================================================================================
DP_06_ADAPTER_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O When two interfaces are incompatible but need to work together
O Used to "wrap" an old/legacy class so it works with new code
O Promotes reusability by adapting existing components

O Real-World Use Cases:
- Legacy media players → modern player interface
- USB-to-ethernet adapter: converts plug shape and protocol
- Integrating old library APIs into new systems

================================================================================
CORE IDEA
--------------------------------------------------------------------------------
- You have a **target interface** your code expects
- You have an **adaptee** class with a different interface
- Adapter wraps the adaptee and makes it conform to target

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: override, unique_ptr
O C++14+: make_unique
O C++17+: optional structured bindings (not used here)
================================================================================
*/

// -----------------------------------------------------------------------------
// Step 1: Target Interface — the expected interface
// -----------------------------------------------------------------------------
class ITarget {
public:
    virtual void request() const = 0;
    virtual ~ITarget() = default;
};

// -----------------------------------------------------------------------------
// Step 2: Adaptee — the legacy/third-party class
// -----------------------------------------------------------------------------
class LegacyPrinter {
public:
    void oldPrintMethod() const {
        cout << "[LegacyPrinter] Printing using old system...\n";
    }
};

// -----------------------------------------------------------------------------
// Step 3: Adapter — bridges LegacyPrinter to ITarget
// -----------------------------------------------------------------------------
class PrinterAdapter : public ITarget {
private:
    shared_ptr<LegacyPrinter> legacyPrinter;

public:
    PrinterAdapter(shared_ptr<LegacyPrinter> lp) : legacyPrinter(lp) {}

    void request() const override {
        cout << "[Adapter] Adapting to expected interface...\n";
        legacyPrinter->oldPrintMethod(); // delegation
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- override keyword, shared_ptr

C++14:
- make_unique / make_shared available

C++20:
- Designated initializers could be used in some other variants

================================================================================
BEST PRACTICES
================================================================================
O Use Adapter when you need to integrate old classes without rewriting
O Keep Adapter thin and focused on translation only
O Use composition over inheritance (wrap adaptee inside)
O If adapting many classes, consider templated adapters

================================================================================
*/

int main() {
    // Legacy component
    shared_ptr<LegacyPrinter> legacy = make_shared<LegacyPrinter>();

    // Adapter provides new interface
    unique_ptr<ITarget> printer = make_unique<PrinterAdapter>(legacy);

    // Client only knows ITarget
    printer->request();

    return 0;
}
