#include <iostream>
#include <memory>
#include <string>
using namespace std;

/*
================================================================================
DP_16_CHAIN_OF_RESPONSIBILITY.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O To decouple sender and receiver of a request.
O Allows more than one object a chance to handle the request.
O Avoids tight coupling between sender and specific handler classes.

O Real-World Use Cases:
- Event bubbling in GUI frameworks
- Logging systems: ERROR → File → Console → Email, etc.
- Access control: user → manager → admin
- Tech support: tiered escalation

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Each handler processes request or forwards it to next handler.
- Handler holds a reference to the next handler in the chain.

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: smart pointers, override, move semantics
O C++14+: make_unique
================================================================================
*/

// -----------------------------------------------------------------------------
// Request Struct (can be expanded to include type, level, etc.)
// -----------------------------------------------------------------------------
struct Request {
    string message;
    int level; // 1 = low, 2 = medium, 3 = high
};

// -----------------------------------------------------------------------------
// Handler Interface
// -----------------------------------------------------------------------------
class Handler {
protected:
    unique_ptr<Handler> next;

public:
    void setNext(unique_ptr<Handler> n) {
        next = move(n);
    }

    virtual void handle(const Request& req) {
        if (next)
            next->handle(req);
        else
            cout << "[Handler] No handler available for: " << req.message << "\n";
    }

    virtual ~Handler() = default;
};

// -----------------------------------------------------------------------------
// Concrete Handlers
// -----------------------------------------------------------------------------
class BasicSupport : public Handler {
public:
    void handle(const Request& req) override {
        if (req.level == 1) {
            cout << "[BasicSupport] Handled request: " << req.message << "\n";
        } else {
            cout << "[BasicSupport] Can't handle. Forwarding...\n";
            Handler::handle(req);
        }
    }
};

class AdvancedSupport : public Handler {
public:
    void handle(const Request& req) override {
        if (req.level == 2) {
            cout << "[AdvancedSupport] Handled request: " << req.message << "\n";
        } else {
            cout << "[AdvancedSupport] Can't handle. Forwarding...\n";
            Handler::handle(req);
        }
    }
};

class AdminSupport : public Handler {
public:
    void handle(const Request& req) override {
        if (req.level == 3) {
            cout << "[AdminSupport] Handled request: " << req.message << "\n";
        } else {
            cout << "[AdminSupport] Can't handle. End of chain.\n";
            Handler::handle(req);
        }
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- override keyword, move semantics, unique_ptr

C++14:
- make_unique for building the chain

================================================================================
BEST PRACTICES
================================================================================
O Use Chain of Responsibility when multiple objects can handle a request
O Good for dynamic, flexible, or hierarchical processing
O Each handler should only process what it understands
O Carefully terminate the chain if no handler matches

================================================================================
*/

int main() {
    // Build the chain: Basic → Advanced → Admin
    auto basic = make_unique<BasicSupport>();
    auto advanced = make_unique<AdvancedSupport>();
    auto admin = make_unique<AdminSupport>();

    advanced->setNext(move(admin));
    basic->setNext(move(advanced));

    // Send various requests
    basic->handle({ "Password reset", 1 });
    basic->handle({ "Software install", 2 });
    basic->handle({ "Server down!", 3 });
    basic->handle({ "Unreachable issue", 4 });

    return 0;
}
