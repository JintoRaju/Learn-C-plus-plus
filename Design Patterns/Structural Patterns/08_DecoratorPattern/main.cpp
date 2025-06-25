#include <iostream>
#include <memory>
#include <string>
using namespace std;

/*
================================================================================
DP_08_DECORATOR_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O To add responsibilities/behaviors to individual objects dynamically
O When subclassing for every variation leads to class explosion
O Avoids modifying original classes (Open/Closed Principle)

O Real-World Use Cases:
- UI components: Scrollbar, border, shadow decorators
- I/O Streams: std::istream → buffered → zipped → encrypted
- Logging: wrap original object to add logging/tracing

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Wrap a concrete object with a series of decorators
- Each decorator has the same interface as the base component
- Forward requests and optionally add new behavior

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: `override`, `unique_ptr`, `move semantics`
O C++14+: `make_unique`, `std::move`
================================================================================
*/

// -----------------------------------------------------------------------------
// Component Interface
// -----------------------------------------------------------------------------
class Notifier {
public:
    virtual void send(const string& msg) const = 0;
    virtual ~Notifier() = default;
};

// -----------------------------------------------------------------------------
// Concrete Component
// -----------------------------------------------------------------------------
class EmailNotifier : public Notifier {
public:
    void send(const string& msg) const override {
        cout << "[Email] Sending: " << msg << "\n";
    }
};

// -----------------------------------------------------------------------------
// Base Decorator (wraps another Notifier)
// -----------------------------------------------------------------------------
class NotifierDecorator : public Notifier {
protected:
    unique_ptr<Notifier> wrappee;

public:
    NotifierDecorator(unique_ptr<Notifier> base) : wrappee(move(base)) {}

    void send(const string& msg) const override {
        wrappee->send(msg);  // delegate to base
    }
};

// -----------------------------------------------------------------------------
// Concrete Decorators
// -----------------------------------------------------------------------------
class SMSDecorator : public NotifierDecorator {
public:
    SMSDecorator(unique_ptr<Notifier> base) : NotifierDecorator(move(base)) {}

    void send(const string& msg) const override {
        wrappee->send(msg);  // delegate to original
        cout << "[SMS] Sending: " << msg << "\n";
    }
};

class SlackDecorator : public NotifierDecorator {
public:
    SlackDecorator(unique_ptr<Notifier> base) : NotifierDecorator(move(base)) {}

    void send(const string& msg) const override {
        wrappee->send(msg);  // delegate to original
        cout << "[Slack] Sending: " << msg << "\n";
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- `override`, smart pointers, move semantics

C++14:
- `make_unique` for simpler memory handling

================================================================================
BEST PRACTICES
================================================================================
O Prefer composition over inheritance
O Use decorators for flexible extension without changing existing code
O Avoid deep decorator chains that become hard to debug
O Can be recursive and dynamic — e.g., log+encrypt+compress

================================================================================
*/

int main() {
    // Start with Email
    unique_ptr<Notifier> notifier = make_unique<EmailNotifier>();

    // Decorate with SMS
    notifier = make_unique<SMSDecorator>(move(notifier));

    // Decorate with Slack
    notifier = make_unique<SlackDecorator>(move(notifier));

    notifier->send("System Alert: High CPU Usage");

    return 0;
}
