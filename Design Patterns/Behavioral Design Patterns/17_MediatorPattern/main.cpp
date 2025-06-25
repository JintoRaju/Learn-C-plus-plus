#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
================================================================================
DP_17_MEDIATOR_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O To avoid tight coupling between objects that communicate with each other.
O Promotes **loose coupling** by making objects communicate via a **mediator object**.
O Helps manage complex object communication (e.g., chat room, air traffic control).

O Real-World Use Cases:
- Chat Room: users talk via central server (mediator)
- Air Traffic Control: planes don’t talk to each other directly
- Form fields reacting to changes in others
- GUI event coordination

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Participants don’t talk to each other directly
- Mediator handles communication logic
- Makes interactions simpler and more centralized

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: override, references, range-based for loop
================================================================================
*/

// -----------------------------------------------------------------------------
// Forward declaration
class ChatMediator;

// -----------------------------------------------------------------------------
// Participant
// -----------------------------------------------------------------------------
class User {
    string name;
    ChatMediator& mediator;

public:
    User(string name, ChatMediator& med) : name(move(name)), mediator(med) {}

    void send(const string& message) const;
    void receive(const string& message) const {
        cout << "[Receive][" << name << "] " << message << "\n";
    }

    const string& getName() const { return name; }
};

// -----------------------------------------------------------------------------
// Mediator Interface
// -----------------------------------------------------------------------------
class ChatMediator {
public:
    virtual void addUser(User* user) = 0;
    virtual void broadcast(const User* sender, const string& message) const = 0;
    virtual ~ChatMediator() = default;
};

// -----------------------------------------------------------------------------
// Concrete Mediator
// -----------------------------------------------------------------------------
class ChatRoom : public ChatMediator {
    vector<User*> users;

public:
    void addUser(User* user) override {
        users.push_back(user);
    }

    void broadcast(const User* sender, const string& message) const override {
        for (auto* user : users) {
            if (user != sender) {
                user->receive(sender->getName() + ": " + message);
            }
        }
    }
};

// Implementation of send() now that ChatMediator is defined
void User::send(const string& message) const {
    cout << "[Send][" << name << "] " << message << "\n";
    mediator.broadcast(this, message);
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- override keyword, range-based loops, move semantics for string

================================================================================
BEST PRACTICES
================================================================================
O Use Mediator when multiple objects interact in complex ways
O Reduces class interdependencies (loose coupling)
O Useful in GUI frameworks, network hubs, and coordination systems

================================================================================
*/

int main() {
    ChatRoom chatroom;

    User alice("Alice", chatroom);
    User bob("Bob", chatroom);
    User carol("Carol", chatroom);

    chatroom.addUser(&alice);
    chatroom.addUser(&bob);
    chatroom.addUser(&carol);

    alice.send("Hi everyone!");
    carol.send("Hey Alice!");
    bob.send("Let's meet at 5 PM.");

    return 0;
}
