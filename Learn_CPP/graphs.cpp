#include <bits/stdc++.h>

using namespace std;

class Graph {
private:
    int numElements;
    vector<vector<int>> adjList;
    bool *visited;

    void resetTraversal() { memset(this->visited, false, sizeof(visited)); }

public:
    explicit Graph(int size) {
        this->numElements = size;
        this->adjList = vector<vector<int>>(numElements);
        this->visited = new bool[numElements];
        resetTraversal();
    }

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    void print() {
        for (int i = 0; i < numElements; ++i) {
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

    void dfs(int startVertex = 0) {
        cout << startVertex << " ";
        visited[startVertex] = true;

        auto adjNodes = adjList[startVertex];

        for (const auto &node: adjNodes) {
            if (!visited[node])
                dfs(node);
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

    void reinit() { resetTraversal(); }
};

int main(int argc, char **argv) {
    Graph g(8);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 5);
    g.addEdge(1, 4);
    g.addEdge(2, 6);
    g.addEdge(3, 7);
    g.addEdge(4, 7);
    g.addEdge(5, 7);
    g.addEdge(6, 7);

    g.bfs();
    g.reinit();

    cout << endl;

    g.dfs();

    cout << endl;
    g.reinit();

    g.dfsIter();

    return 0;
}

