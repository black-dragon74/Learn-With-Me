//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);

typedef pair<int, int> iPair;

class Graph {
    int numVertices;
    vector<vector<iPair>> adjList;

public:
    explicit Graph(int n) {
        numVertices = n;
        adjList = vector<vector<iPair>>(n);
    }

    void addEdge(int src, int dest, int weight) {
        adjList[src].emplace_back(make_pair(dest, weight));
        adjList[dest].emplace_back(make_pair(src, weight));
    }

    // Checks cycle in an undirected graph
    bool checkCycle(int startVertex = 0) {
        vector<bool> visited(numVertices, false);
        vector<int> parent(numVertices);
        queue<int> q;

        q.push(startVertex);

        while (!q.empty()) {
            auto curr = q.front();
            if (!visited[curr])
                visited[curr] = true;
            q.pop();

            for (const auto adj: adjList[curr]) {
                auto next = adj.first;
                if (!visited[next]) {
                    parent[next] = curr;
                    q.push(next);
                } else {
                    if (next != parent[curr])
                        return true;
                }
            }
        }
        return false;
    }

    void removeEgde(int src, int dest, int weight) {
        // Our's is an undirected graph, hence we need to remove edges from both the palces
        auto srcToDest = make_pair(dest, weight);
        auto destToSrc = make_pair(src, weight);

        if (!adjList[src].empty()) {
            auto srcPos = find(adjList[src].begin(), adjList[src].end(), srcToDest);
            if (srcPos != adjList[src].end()) {
                adjList[src].erase(srcPos);
            }
        }

        if (!adjList[dest].empty()) {
            auto destPos = find(adjList[dest].begin(), adjList[dest].end(), destToSrc);
            if (destPos != adjList[dest].end()) {
                adjList[dest].erase(destPos);
            }
        }
    }

    void testKruskal() {
        // Okay so an MST will have V vertices and V-1 edges
        Graph mst(numVertices);
        int count{0};

        // Create a min heap
        priority_queue<pair<int, iPair>, vector<pair<int, iPair>>, greater<>> pq;     // Paired as {cost, {src, dest}}

        // Fill the min heap
        for (int src = 0; src < numVertices; ++src) {
            for (const auto &edge: adjList[src]) {
                pq.push(make_pair(edge.second, make_pair(src, edge.first)));
            }
        }

        // Now, while pq is not empty, choose min edge, add it as an edge, if there will be a cycle, remove it.
        while (!pq.empty() && (count / 2) != numVertices - 1) {     // An MST would only have V-1 edges
            auto curr = pq.top();
            pq.pop();

            // Extract vars for easier interpretation
            auto weight = curr.first;
            auto src = curr.second.first;
            auto dest = curr.second.second;

            // Now let's try to add this edge, we will use kind of like a knapsack approach
            // We will either take it, or we won't
            mst.addEdge(src, dest, weight);
            if (mst.checkCycle(src)) {
                print("Adding egde from %d to %d leads to cycle, skip.", src, dest);
                mst.removeEgde(src, dest, weight);
            } else {
                // We are considering this edge, let's increment the count then
                count++;
            }
        }

        // Now at this point, our MST should be really a MST
        print("Processing complete");
        print("MST has %d egdes", count / 2);   // Dividing by 2 coz our's is an undirected graph
        cout << "DFS of which is: ";
        bool *visited = new bool[numVertices];
        fill(visited, visited + numVertices, false);
        mst.dfs(0, visited);
        cout << endl;

        cout << "BFS of which is: ";
        mst.bfs();
        cout << endl;
    }

    void dfs(int start, bool *visited) {
        visited[start] = true;
        cout << start << " ";

        for (const auto &adj: adjList[start]) {
            if (!visited[adj.first])
                dfs(adj.first, visited);
        }
    }

    void bfs(int start = 0) {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        q.push(start);

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            if (!visited[curr]) {
                visited[curr] = true;
                cout << curr << " ";
            }

            for (const auto adj: adjList[curr]) {
                if (!visited[adj.first])
                    q.push(adj.first);
            }
        }
    }
};

int main() {
    Graph g(9);

    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, 8);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, 9);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(7, 0, 8);
    g.addEdge(7, 8, 7);
    g.addEdge(6, 8, 6);
    g.addEdge(8, 2, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 5, 14);

    
    g.testKruskal();


    return 0;
}

