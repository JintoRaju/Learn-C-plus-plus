#include <iostream>
#include <memory>
using namespace std;

/*
================================================================================
DP_03_ABSTRACT_FACTORY.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O Factory Method lets you create one product at a time.
O Abstract Factory groups multiple related products into one family.

O Example Use Cases:
- Cross-platform GUI: WindowsFactory, MacFactory create Button + Checkbox
- Game engine themes: OrcFactory, ElfFactory create Sword + Shield
- OS Abstractions: UIFactory creates menus, dialogs for Linux/Windows/Mac

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Create interfaces for multiple product types
- Provide concrete factories that produce variants of those products

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: override, smart pointers
O C++14: make_unique
O C++17+: class templates (optional)
================================================================================
*/

// -----------------------------------------------------------------------------
// Step 1: Product Interfaces
// -----------------------------------------------------------------------------
class Button {
public:
    virtual void render() const = 0;
    virtual ~Button() = default;
};

class Checkbox {
public:
    virtual void render() const = 0;
    virtual ~Checkbox() = default;
};

// -----------------------------------------------------------------------------
// Step 2: Concrete Products — Windows
// -----------------------------------------------------------------------------
class WindowsButton : public Button {
public:
    void render() const override {
        cout << "Rendering Windows-style Button\n";
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() const override {
        cout << "Rendering Windows-style Checkbox\n";
    }
};

// -----------------------------------------------------------------------------
// Step 3: Concrete Products — Mac
// -----------------------------------------------------------------------------
class MacButton : public Button {
public:
    void render() const override {
        cout << "Rendering Mac-style Button\n";
    }
};

class MacCheckbox : public Checkbox {
public:
    void render() const override {
        cout << "Rendering Mac-style Checkbox\n";
    }
};

// -----------------------------------------------------------------------------
// Step 4: Abstract Factory Interface
// -----------------------------------------------------------------------------
class GUIFactory {
public:
    virtual unique_ptr<Button> createButton() const = 0;
    virtual unique_ptr<Checkbox> createCheckbox() const = 0;
    virtual ~GUIFactory() = default;
};

// -----------------------------------------------------------------------------
// Step 5: Concrete Factories
// -----------------------------------------------------------------------------
class WindowsFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() const override {
        return make_unique<WindowsButton>();
    }
    unique_ptr<Checkbox> createCheckbox() const override {
        return make_unique<WindowsCheckbox>();
    }
};

class MacFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() const override {
        return make_unique<MacButton>();
    }
    unique_ptr<Checkbox> createCheckbox() const override {
        return make_unique<MacCheckbox>();
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- override keyword, smart pointers

C++14:
- make_unique, defaulted destructors

================================================================================
BEST PRACTICES
================================================================================
O Use when objects must be used together consistently
O Avoid exposing concrete classes to client
O Keeps the code open for extension but closed for modification

================================================================================
*/

void renderUI(const GUIFactory& factory) {
    auto btn = factory.createButton();
    auto chk = factory.createCheckbox();
    btn->render();
    chk->render();
}

int main() {
    cout << "[Using Windows Factory]\n";
    WindowsFactory winFactory;
    renderUI(winFactory);

    cout << "\n[Using Mac Factory]\n";
    MacFactory macFactory;
    renderUI(macFactory);

    return 0;
}
