#include <iostream>
#include <memory>
#include <string>
using namespace std;

/*
================================================================================
DP_18_STATE_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O To allow an object to alter its behavior when its internal state changes.
O Removes complex if-else or switch statements that depend on state.
O Encapsulates state-specific behavior in separate classes.

O Real-World Use Cases:
- Finite State Machines (FSM): doors (open/closed), media players (play/pause/stop)
- Network connection states: disconnected, connecting, connected
- Traffic lights, game states, TCP/IP protocols

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Context holds a state object
- The state object handles behavior
- When state changes, we swap in a new state object

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: smart pointers, override, nullptr, move semantics
O C++14+: make_unique
================================================================================
*/

// -----------------------------------------------------------------------------
// Forward Declaration
class State;
class Context;

// -----------------------------------------------------------------------------
// State Interface
// -----------------------------------------------------------------------------
class State {
public:
    virtual void handle(Context& ctx) = 0;
    virtual string name() const = 0;
    virtual ~State() = default;
};

// -----------------------------------------------------------------------------
// Context
// -----------------------------------------------------------------------------
class Context {
    unique_ptr<State> currentState;

public:
    Context(unique_ptr<State> initialState) : currentState(move(initialState)) {}

    void setState(unique_ptr<State> newState) {
        currentState = move(newState);
    }

    void request(); // delegates to state

    string getStateName() const {
        return currentState ? currentState->name() : "None";
    }
};

// -----------------------------------------------------------------------------
// Concrete States
// -----------------------------------------------------------------------------
class LockedState : public State {
public:
    void handle(Context& ctx) override;
    string name() const override { return "Locked"; }
};

class UnlockedState : public State {
public:
    void handle(Context& ctx) override;
    string name() const override { return "Unlocked"; }
};

// Implement state transitions
void LockedState::handle(Context& ctx) {
    cout << "[LockedState] Received input → Unlocking...\n";
    ctx.setState(make_unique<UnlockedState>());
}

void UnlockedState::handle(Context& ctx) {
    cout << "[UnlockedState] Received input → Locking...\n";
    ctx.setState(make_unique<LockedState>());
}

void Context::request() {
    if (currentState)
        currentState->handle(*this);
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- override, smart pointers, nullptr, move semantics

C++14:
- make_unique used for cleaner syntax

================================================================================
BEST PRACTICES
================================================================================
O Use State when object behavior should vary based on internal state
O Avoids massive switch/case or if-else chains
O Encapsulates each state’s behavior into separate class
O Context delegates work to state

================================================================================
*/

int main() {
    Context door(make_unique<LockedState>());

    cout << "Initial Door State: " << door.getStateName() << "\n";

    // Toggle state a few times
    door.request(); // Unlock
    cout << "Current State: " << door.getStateName() << "\n";

    door.request(); // Lock again
    cout << "Current State: " << door.getStateName() << "\n";

    door.request(); // Unlock again
    cout << "Current State: " << door.getStateName() << "\n";

    return 0;
}
