#include <iostream>
#include <memory>
#include <string>
using namespace std;

/*
================================================================================
DP_13_STRATEGY_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O To define a family of algorithms and make them interchangeable.
O Strategy lets the algorithm vary independently from the clients using it.
O Avoids long `if`/`switch` chains or duplicated logic based on behavior choice.

O Real-World Use Cases:
- Sorting: user can select merge sort, quick sort, bubble sort, etc.
- Payment systems: credit card, UPI, PayPal, etc.
- Game AI: aggressive, defensive, random strategies
- Compression: choose between ZIP, RAR, TAR at runtime

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Create a common interface for a family of behaviors (strategies).
- Pass the selected strategy to the context object.
- The context uses the strategy without knowing its concrete type.

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: override, unique_ptr, lambdas (if preferred), move semantics
O C++14+: make_unique
================================================================================
*/

// -----------------------------------------------------------------------------
// Strategy Interface
// -----------------------------------------------------------------------------
class PaymentStrategy {
public:
    virtual void pay(int amount) const = 0;
    virtual ~PaymentStrategy() = default;
};

// -----------------------------------------------------------------------------
// Concrete Strategies
// -----------------------------------------------------------------------------
class CreditCardPayment : public PaymentStrategy {
public:
    void pay(int amount) const override {
        cout << "[CreditCard] Paid ₹" << amount << " using Credit Card.\n";
    }
};

class PayPalPayment : public PaymentStrategy {
public:
    void pay(int amount) const override {
        cout << "[PayPal] Paid ₹" << amount << " using PayPal.\n";
    }
};

class UpiPayment : public PaymentStrategy {
public:
    void pay(int amount) const override {
        cout << "[UPI] Paid ₹" << amount << " using UPI.\n";
    }
};

// -----------------------------------------------------------------------------
// Context — uses a strategy
// -----------------------------------------------------------------------------
class ShoppingCart {
private:
    unique_ptr<PaymentStrategy> strategy;

public:
    void setPaymentMethod(unique_ptr<PaymentStrategy> s) {
        strategy = move(s);
    }

    void checkout(int amount) const {
        if (!strategy) {
            cout << "[Error] No payment method selected!\n";
            return;
        }
        strategy->pay(amount);
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Introduced smart pointers (unique_ptr)
- override keyword for safety
- move semantics (move(strategy))

C++14:
- make_unique (used to simplify memory allocation)

================================================================================
BEST PRACTICES
================================================================================
O Use Strategy when you want different algorithms encapsulated separately
O Allows runtime selection of behavior
O Avoids code duplication and if-else bloat
O Keep context and strategy loosely coupled
================================================================================
*/

int main() {
    ShoppingCart cart;

    // Select CreditCard payment
    cart.setPaymentMethod(make_unique<CreditCardPayment>());
    cart.checkout(1000);

    // Change to PayPal
    cart.setPaymentMethod(make_unique<PayPalPayment>());
    cart.checkout(800);

    // Change to UPI
    cart.setPaymentMethod(make_unique<UpiPayment>());
    cart.checkout(500);

    return 0;
}
