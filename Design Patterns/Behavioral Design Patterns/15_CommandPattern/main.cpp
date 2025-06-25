#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

/*
================================================================================
DP_15_COMMAND_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O To encapsulate a request as an object.
O Allows us to:
   - Queue commands
   - Log commands
   - Implement undo/redo
O Decouples the object invoking the command from the object that performs it.

O Real-World Use Cases:
- GUI buttons: each button maps to a command object
- Undo/Redo in text editors
- Macro recording systems (e.g., IDE actions)
- Job scheduling/queuing systems

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Command interface defines execute()
- ConcreteCommand binds a receiver and an action
- Invoker triggers commands without knowing internal logic
- Receiver performs the actual work

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: smart pointers, override, lambdas (if extended)
O C++14+: make_unique
================================================================================
*/

// -----------------------------------------------------------------------------
// Receiver — The actual worker
// -----------------------------------------------------------------------------
class Light {
public:
    void turnOn() {
        cout << "[Light] 💡 turned ON.\n";
    }

    void turnOff() {
        cout << "[Light] ❌ turned OFF.\n";
    }
};

// -----------------------------------------------------------------------------
// Command Interface
// -----------------------------------------------------------------------------
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

// -----------------------------------------------------------------------------
// Concrete Commands
// -----------------------------------------------------------------------------
class TurnOnCommand : public Command {
    Light& light;

public:
    TurnOnCommand(Light& l) : light(l) {}
    void execute() override {
        light.turnOn();
    }
};

class TurnOffCommand : public Command {
    Light& light;

public:
    TurnOffCommand(Light& l) : light(l) {}
    void execute() override {
        light.turnOff();
    }
};

// -----------------------------------------------------------------------------
// Invoker — Button or scheduler
// -----------------------------------------------------------------------------
class RemoteControl {
    vector<unique_ptr<Command>> history;

public:
    void pressButton(unique_ptr<Command> cmd) {
        cmd->execute();
        history.push_back(move(cmd)); // store command if needed for undo/log
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- unique_ptr, override keyword, range-based loop

C++14:
- make_unique to simplify command creation

================================================================================
BEST PRACTICES
================================================================================
O Use Command when you need undo, queuing, or decoupled UI
O Keep command objects light — encapsulate receiver + action
O Commands are often stateless; log only if necessary
O Group macro commands using Composite pattern if needed

================================================================================
*/

int main() {
    Light roomLight;
    RemoteControl remote;

    // Each button press is a command
    remote.pressButton(make_unique<TurnOnCommand>(roomLight));
    remote.pressButton(make_unique<TurnOffCommand>(roomLight));

    return 0;
}
