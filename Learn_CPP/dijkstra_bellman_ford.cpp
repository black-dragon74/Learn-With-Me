//
// Created by Nick on 12/9/20.
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); } while (0);
#define eol cout << endl;

typedef pair<int, int> iPair;   // For weighted graph

class Graph {
private:
    vector<vector<iPair>> adjList;
    int numVertices;

    void getBridges(int curr, bool *visited, int *disc, int *low, int *parent) {
        static int time{0};
        visited[curr] = true;

        disc[curr] = low[curr] = ++time;

        for (const auto &adjVertex: adjList[curr]) {
            auto next = adjVertex.first;
            if (!visited[next]) {
                parent[next] = curr;

                getBridges(next, visited, disc, low, parent);

                low[curr] = min(low[curr], low[next]);

                if (low[next] > disc[curr]) {
                    cout << curr << " -> " << next << " is a bridge.";
                    eol
                }
            }

            if (next != parent[curr]) {
                low[curr] = min(low[curr], disc[next]);
            }
        }
    }

    void _dfs(int start, bool *visited) {
        visited[start] = true;
        print("%d ", start);

        for (const auto &adj: adjList[start]) {
            if (!visited[adj.first])
                _dfs(adj.first, visited);
        }
    }

public:
    explicit Graph(int n) {
        numVertices = n;
        adjList = vector<vector<iPair>>(numVertices);
    }

    void addEdge(int src, int dest, int weight) {
        adjList[src].emplace_back(make_pair(dest, weight));
        adjList[dest].emplace_back(make_pair(src, weight));
    }

    void shortestPath(int src, int dest) {
        if (src >= numVertices)
            throw invalid_argument("Invalid source vertex.");

        priority_queue<iPair, vector<iPair>, greater<>> pq;     // This is a min heap basically (minimum at top)
        auto visited = new bool[numVertices];
        fill(visited, visited + numVertices, false);

        vector<int> distance(numVertices, INFINITY);            // Initially, all distances are ♾ except the src node
        distance[src] = 0;

        auto found = false;

        // Distance -> Idx mapping, to sort with respect to distance
        // STL pq sorts on basis of first element
        pq.push(make_pair(0, src));

        vector<int> parent(numVertices);

        // Same old beloved BFS
        while (!pq.empty()) {
            // It is a min heap, val at top has the min distance
            auto curr = pq.top().second;    // .second is the vertex idx
            visited[curr] = true;
            pq.pop();

            if (curr == dest) {
                found = true;
                break;
            } else {
                cout << curr << " not the dest";
                eol
            }

            for (const auto &adjVertex: adjList[curr]) {
                // Mapping of adjList is idx -> weight
                auto next = adjVertex.first;
                auto weight = adjVertex.second;

                // Now the crux of the algorithm of Dijkstra's shortest path is,
                // if D(u) + W(u, v) < D(v) then D(v) = D(u) + W(u,v)
                // Meaning, if the distance + weight of edge current <-> adjVertex node is smaller than the distance
                // of adjVertex node, we update the distance of the adjVertex node to dist + weight of curr node.
                if (!visited[next] and distance[next] > distance[curr] + weight) {   // W(a->b) == W(b->a)
                    // Update the distance
                    distance[next] = distance[curr] + weight;

                    // Push unvisited node to queue (same as BFS)
                    pq.push(make_pair(distance[next], next));

                    parent[next] = curr;
                }
            }
        }

        // Now we ae done and we have the shortest path from src (X) to any dest Y in distance array
        if (found) {
            print("Found the route. Weight encountered is: %i\n", distance[dest])

            // Trace the path
            print("The shortest traced route from %i to %i is: ", src, dest)
            vector<int> path;
            auto curr = dest;

            while (curr != src) {
                path.emplace_back(curr);
                curr = parent[curr];
            }
            path.emplace_back(src);
            reverse(path.begin(), path.end());

            for (int i = 0; i < path.size(); ++i) {
                cout << path[i];

                if (i != path.size() - 1)
                    cout << " -> ";
                else
                    cout << endl;
            }
        } else {
            print("There is no route from %i to %i. Houston, are we lost?\n", src, dest)
        }
    }

    void bfs(int sourceVertex = 0) {
        vector<bool> visited(numVertices, false);

        queue<int> q;
        q.push(sourceVertex);

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            if (!visited[curr]) {
                visited[curr] = true;
                cout << curr << " ";
            }

            for (const auto &a: adjList[curr]) {
                if (!visited[a.first])
                    q.push(a.first);
            }
        }
        eol
    }

    void findBridges() {
        auto *visited = new bool[numVertices];
        fill(visited, visited + numVertices, false);
        auto *disc = new int[numVertices];
        auto *low = new int[numVertices];
        auto *parent = new int[numVertices];

        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i])
                getBridges(i, visited, disc, low, parent);
        }
    }

    void dijkstra(int src, int dest) {
        auto *visited = new bool[numVertices];
        fill(visited, visited + numVertices, false);
        priority_queue<iPair, vector<iPair>, greater<>> pq;

        vector<int> distance(numVertices, INFINITY);
        distance[src] = 0;

        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            auto curr = pq.top().second;
            pq.pop();

            visited[curr] = true;
            for (const auto &adjVertex: adjList[curr]) {
                auto next = adjVertex.first;
                auto weight = adjVertex.second;
                if (!visited[next] && distance[next] > distance[curr] + weight) {
                    // Update the distance
                    distance[next] = distance[curr] + weight;

                    // Push the new one one the stack
                    pq.push(make_pair(distance[next], next));
                }
            }
        }

        print("DKSTRA: Shortest distance from %i to %i is: %i", src, dest, distance[dest])
        eol
    }

    void bellmanFord(int src, int dest) {
        vector<int> distance(numVertices, INT_MAX);
        distance[src] = 0;

        // Relax till n-1 (BF rule)
        for (int i = 0; i < numVertices - 1; ++i) {
            for (int curr = 0; curr < numVertices; ++curr) {
                for (const auto &adjVertex: adjList[curr]) {
                    auto next = adjVertex.first;
                    auto weight = adjVertex.second;

                    if (distance[curr] != INT_MAX && distance[next] > distance[curr] + weight) {
                        distance[next] = distance[curr] + weight;
                    }
                }
            }
        }

        // This algo doesn't work for -ve cycles, take care of that
        // The code below might seem confusing at first but really isn't.
        // The bellman ford algo says, that the distance of a vertex will change only upto n-1 times.
        // After that, you can do as many checks you want, the value will never change.
        // So we can say that the value of D(v) will always be <= distance(u) + weight(u,v) after n-1 relaxations
        // If the above condition is false, the value has changed. This can only happen in case of -ve weight cycle.
        for (int curr = 0; curr < numVertices; ++curr) {
            for (const auto &adj: adjList[curr]) {
                auto next = adj.first;
                auto weight = adj.second;

                if (distance[curr] != INT_MAX && distance[next] > distance[curr] + weight) {
                    print("Graph has a negative weight cycle. Abort.\n")
                    exit(1);
                }
            }
        }

        print("BLMNFRD: Shortest distance from %i to %i is: %i", src, dest, distance[dest])
        eol
    }

    void dfs(int start = 0) {
        auto *visited = new bool[numVertices];
        fill(visited, visited + numVertices, false);

        _dfs(start, visited);
        eol
    }
};

int main() {
    Graph g(9);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    print("BFS of graph is: ")
    g.bfs();

    print("DFS of graph is: ")
    g.dfs();

    g.dijkstra(0, 4);

    g.bellmanFord(0, 4);    //21

    return 0;
}

