#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

/*
================================================================================
DSA_09_GRAPH_BASICS.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O Graphs model real-world systems: networks, maps, dependencies, social media
O Used in:
   O Pathfinding (Google Maps, Dijkstra’s)
   O Cycle detection (deadlocks, dependencies)
   O Connectivity checks (network design)
   O Web crawling, build systems, etc.

================================================================================
TOPICS COVERED
================================================================================
1. Graph representation (Adjacency List)
2. Breadth-First Search (BFS)
3. Depth-First Search (DFS)
4. Handling Disconnected Components
================================================================================
*/

//------------------------------------------------------------------------------
// 1. GRAPH REPRESENTATION USING ADJACENCY LIST
//------------------------------------------------------------------------------
class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // For undirected graph
    }

    //----------------------------------------------------------------------    
    // 2. BFS (Breadth-First Search)
    //----------------------------------------------------------------------
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "[BFS from node " << start << "]: ";
        while (!q.empty()) {
            int node = q.front(); q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "\n";
    }

    //----------------------------------------------------------------------    
    // 3. DFS (Depth-First Search) — Recursive
    //----------------------------------------------------------------------
    void DFSUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor])
                DFSUtil(neighbor, visited);
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "[DFS from node " << start << "]: ";
        DFSUtil(start, visited);
        cout << "\n";
    }

    //----------------------------------------------------------------------    
    // 4. DFS FOR DISCONNECTED GRAPHS
    //----------------------------------------------------------------------
    void DFSDisconnected() {
        vector<bool> visited(V, false);
        cout << "[DFS for all disconnected components]: ";
        for (int i = 0; i < V; ++i) {
            if (!visited[i])
                DFSUtil(i, visited);
        }
        cout << "\n";
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
O C++98: std::vector, std::queue, std::stack available
O C++11+: range-based `for`, lambdas help with concise code
O C++20+: std::views/ranges can help traverse complex graph data (covered later)

================================================================================
TIME COMPLEXITY
================================================================================
V = vertices, E = edges

- BFS / DFS: O(V + E)
- Space: O(V) for visited + O(V+E) for adjacency list

================================================================================
BEST PRACTICES
================================================================================
O Always initialize visited[] per run
O Prefer adjacency list over matrix for sparse graphs
O Handle disconnected components if graph is not connected
O Use iterative DFS with stack to avoid stack overflow in large graphs
*/

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(5, 6); // Disconnected component

    g.BFS(0);
    g.DFS(0);
    g.DFSDisconnected();

    return 0;
}
