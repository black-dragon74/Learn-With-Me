#include <bits/stdc++.h>

using namespace std;
map<char, int> mMap;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjList;
    bool *visited;

    void findBridge(int startVertex, bool *vis, int *discoveredAt, int *low, int *parent) {
        // Mark as visited
        vis[startVertex] = true;

        // To keep a track of discovery time
        static int time{0};

        // Update the time
        discoveredAt[startVertex] = low[startVertex] = ++time;

        // Get current vertices
        auto adjVertices = adjList[startVertex];

        for (const auto &adjVertex: adjVertices) {
            if (!vis[adjVertex]) {
                // Parent adjVertex is obv the startVertex
                parent[adjVertex] = startVertex;

                // Recurse over adjVertex
                findBridge(adjVertex, vis, discoveredAt, low, parent);

                // Update the low discovery value
                // Now you might wonder how are we updating the low val for every adj vertex
                // Well, coz we are iterating over each adj vertex and to find min would not be viable in recursion
                // So, we really change the min value only when we find a minVal lower than the current one
                low[startVertex] = min(low[startVertex], low[adjVertex]);

                // Check if it is a bridge
                // It is a bridge when the value of adjVertex is greater than the parent (startVertex) and there
                // are no adj nodes that have a lower value than its parent.
                if (low[adjVertex] > low[startVertex]) {
                    // bridge is found
                    cout << startVertex << " -> " << adjVertex << " is a bridge.\n";
                }
            }

            // If adjVertex is not the parent of the startVertex
            // Update the low of start vertex
            if (adjVertex != parent[startVertex])
                low[startVertex] = min(low[startVertex], discoveredAt[adjVertex]);
        }
    }

public:
    explicit Graph(int size) {
        this->numVertices = size;
        this->adjList = vector<vector<int>>(numVertices);
        this->visited = new bool[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            this->visited[i] = false;
        }
    }

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    void print() {
        for (int i = 0; i < numVertices; ++i) {
            cout << "Vertex " << i << " |-";
            for (const auto &a: adjList[i])
                cout << "-> " << a << " ";
            cout << endl;
        }
    }

    bool isThereAnEdgeFrom(int src, int dest) {
        return any_of(
                adjList[src].begin(),
                adjList[src].end(),
                [dest](int curr) { return curr == dest; }
        );
    }

    void bfs(int startVertex = 0) {
        queue<int> myQ;
        myQ.push(startVertex);

        while (!myQ.empty()) {
            startVertex = myQ.front();
            myQ.pop();

            if (!visited[startVertex]) {
                cout << startVertex << " ";
                visited[startVertex] = true;
            }

            for (const auto adj: adjList[startVertex]) {
                if (!visited[adj]) {
                    myQ.push(adj);
                }
            }
        }
    }

    void dfs(int startVertex = 0, bool print = true) {
        if (print)
            cout << startVertex << " ";

        visited[startVertex] = true;

        auto adjNodes = adjList[startVertex];

        for (const auto &node: adjNodes) {
            if (!visited[node])
                dfs(node, print);
        }
    }

    void dfsIter(int startVertex = 0) {
        stack<int> myS;
        myS.push(startVertex);

        while (!myS.empty()) {
            startVertex = myS.top();
            myS.pop();

            if (!visited[startVertex]) {
                cout << startVertex << " ";
                visited[startVertex] = true;
            }

            for (auto &a: adjList[startVertex])
                if (!visited[a])
                    myS.push(a);
        }
        cout << endl;
    }

    void printAdjVerticesOf(int vertex) {
        auto connectedNodes = adjList[vertex];
        cout << "Adj. vertices of " << vertex << " are: ";
        for (const auto &node: connectedNodes) {
            cout << node << ", ";
        }
        cout << endl;
    }

    void reinit() {
        for (int i = 0; i < numVertices; ++i) {
            visited[i] = false;
        }
    }

    void getBridges() {
        bool *vis = new bool[numVertices];
        int *discoveredAt = new int[numVertices];
        int *low = new int[numVertices];
        int *parent = new int[numVertices];

        for (int i = 0; i < numVertices; ++i)
            parent[i] = 0, vis[i] = false;

        for (int i = 0; i < numVertices; ++i)
            if (!visited[i])
                findBridge(i, vis, discoveredAt, low, parent);
    }

    int countConnectedComponents() {
        auto *vis = new bool[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            vis[i] = false;
        }

        function<void(int)> internalDFS = [vis, this, &internalDFS](int node) {
            vis[node] = true;

            for (const auto &a: adjList[node]) {
                if (!vis[a])
                    internalDFS(a);
            }
        };

        int count{0};
        for (int i = 0; i < numVertices; ++i) {
            if (!vis[i]) {
                internalDFS(i);
                count++;
            }
        }

        return count;
    }
    
    bool cycleInUndirectedGraph(int node = 0) {
            vector<bool> visited(numVertices, false);
            vector<int> parent(numVertices, -1);

            deque<int> q;
            q.push_back(node);

            while (!q.empty()) {
                auto curr = q.front();
                q.pop_front();

                visited[curr] = true;

                for (const auto &next: adjList[curr]) {
                    if (!visited[next]) {
                        parent[next] = curr;
                        q.push_back(next);
                    } else {
                        if (next != parent[curr]) {
                            fprintf(stdout, "Cycle: %d isn't parent of %d. Detected at: %d\n", parent[curr], next, curr);
                            return true;
                        }
                    }
                }
            }
            for (int i = 0; i < numVertices; ++i) {
                fprintf(stdout, "Parent of %d is %d\n", i, parent[i]);
            }
            return false;
        }

        bool cycleInDirectedGraph(int node = 0) {
            vector<bool> visited = vector<bool>(numVertices, false);
            vector<int> parent = vector<int>(numVertices, -1);

            queue<int> q;
            q.push(node);

            while (!q.empty()) {
                auto curr = q.front();
                q.pop();
                visited[curr] = true;

                for (const auto &next: adjList[curr]) {
                    if (!visited[next])
                        q.push(next);
                    else {
                        fprintf(stdout, "Cycle to %d. Detected at: %d\n", next, curr);
                        return true;
                    }
                }
            }
            return false;
        }
};

int main() {
    auto start = 'a';
    auto startI = 1;

    while (start <= 'z') {
        mMap[start] = startI;
        start++, startI++;
    }

    Graph g1(5);    // We have values upto `o`

    g1.addEdge(1, 0);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);

    g1.getBridges();

    g1.bfs();
    cout << endl;
    g1.reinit();

    g1.dfsIter();
    g1.reinit();

    cout << "Num of connected components: " << g1.countConnectedComponents() << endl;

    return 0;
}

