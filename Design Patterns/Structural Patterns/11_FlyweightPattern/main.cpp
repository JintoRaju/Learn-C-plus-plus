#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
using namespace std;

/*
================================================================================
DP_11_FLYWEIGHT_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O To efficiently support a large number of fine-grained objects
O Reduce memory by sharing common state among multiple objects
O Used when object creation is costly or uses redundant data

O Real-World Use Cases:
- Game engines: thousands of trees, bullets, NPCs with shared models/textures
- Text rendering: sharing font glyphs
- Document editors: repeated characters/objects

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Separate object state into:
  • Intrinsic state — shared & immutable (e.g., shape, font)
  • Extrinsic state — passed from client (e.g., position, user input)
- Use a factory to manage/reuse intrinsic state objects

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: unordered_map, smart pointers, lambdas
O C++14+: make_unique
================================================================================
*/

// -----------------------------------------------------------------------------
// Intrinsic shared object
// -----------------------------------------------------------------------------
class TreeModel {
    string texture;
    string mesh;

public:
    TreeModel(string tex, string m) : texture(move(tex)), mesh(move(m)) {}

    void draw(int x, int y) const {
        cout << "[TreeModel] Drawing at (" << x << "," << y << ") with texture: "
             << texture << " and mesh: " << mesh << "\n";
    }
};

// -----------------------------------------------------------------------------
// Flyweight Factory
// -----------------------------------------------------------------------------
class TreeFactory {
    unordered_map<string, shared_ptr<TreeModel>> modelCache;

public:
    shared_ptr<TreeModel> getTreeModel(const string& type) {
        if (modelCache.count(type)) {
            return modelCache[type];
        }

        // Simulate creating heavy texture/mesh
        if (type == "Pine") {
            modelCache[type] = make_shared<TreeModel>("pine_texture.png", "pine_mesh.obj");
        } else if (type == "Oak") {
            modelCache[type] = make_shared<TreeModel>("oak_texture.jpg", "oak_mesh.obj");
        } else {
            modelCache[type] = make_shared<TreeModel>("default.png", "generic.obj");
        }

        return modelCache[type];
    }
};

// -----------------------------------------------------------------------------
// Context: Has extrinsic state (position), uses shared TreeModel
// -----------------------------------------------------------------------------
class Tree {
    int x, y; // Extrinsic state
    shared_ptr<TreeModel> model;

public:
    Tree(int x_, int y_, shared_ptr<TreeModel> m) : x(x_), y(y_), model(move(m)) {}

    void draw() const {
        model->draw(x, y);
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- shared_ptr, unordered_map, range-based loop

C++14:
- make_unique / make_shared

================================================================================
BEST PRACTICES
================================================================================
O Use Flyweight when many objects share data (e.g., thousands of repeated objects)
O Separate shared (intrinsic) and unique (extrinsic) state clearly
O Use factory to avoid duplication
O Avoid premature optimization — only apply when memory or perf is an issue

================================================================================
*/

int main() {
    TreeFactory factory;

    vector<Tree> forest;
    for (int i = 0; i < 5; ++i) {
        forest.emplace_back(i * 10, i * 5, factory.getTreeModel("Pine"));
        forest.emplace_back(i * 12, i * 7, factory.getTreeModel("Oak"));
    }

    for (const auto& tree : forest) {
        tree.draw();
    }

    return 0;
}
