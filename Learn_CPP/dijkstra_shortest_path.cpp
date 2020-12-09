//
// Created by Nick on 12/9/20.
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); } while (0);

typedef pair<int, int> iPair;   // For weighted graph

class Graph {
    vector<vector<iPair>> adjList;
    int numVertices;

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
        priority_queue<iPair, vector<iPair>, greater<>> pq;     // This is a min heap basically (minimum at top)
        auto visited = new bool[numVertices];
        fill(visited, visited + numVertices, false);

        vector<int> distance(numVertices, INFINITY);            // Initially, all distances are ♾ except the src node
        distance[src] = 0;

        vector<int> tracedRoute;
        auto found = false;

        // Distance -> Idx mapping, to sort with respect to distance
        // STL pq sorts on basis of first element
        pq.push(make_pair(0, src));

        map<int, int> parentMap;    // Map of parent -> child

        // Same old beloved BFS
        while (!pq.empty()) {
            // It is a min heap, val at top has the min distance
            auto curr = pq.top().second;    // .second is the vertex idx
            if (!visited[curr])
                tracedRoute.emplace_back(curr);
            visited[curr] = true;
            pq.pop();

            if (curr == dest) {
                found = true;
                break;
            }

            for (const auto &adjVertex: adjList[curr]) {
                // Mapping of adjList is idx -> weight
                auto next = adjVertex.first;
                auto weight = adjVertex.second;

                // Now the crux of the algorithm of Dijkstra's shortest path is,
                // if D(u) + W(u, v) < D(v) then D(v) = D(u) + W(u,v)
                // Meaning, if the distance + weight of edge current <-> adjVertex node is smaller than the distance
                // of adjVertex node, we update the distance of the adjVertex node to dist + weight of curr node.
                if (!visited[next] && distance[next] > distance[curr] + weight) {   // W(a->b) == W(b->a)
                    // Update the distance
                    distance[next] = distance[curr] + weight;

                    // Push unvisited node to queue (same as BFS)
                    pq.push(make_pair(distance[next], next));

                    parentMap[next] = curr;
                }
            }
        }

        // Now we ae done and we have the shortest path from src (X) to any dest Y in distance array
        if (found) {
            print("Found the route. Shortest distance is: %i\n", distance[dest])

            // Trace the path
            print("The shortest route from %i to %i is: ", dest, src)

            int parent = dest;
            while (parent != src) {
                cout << parent << " -> ";
                parent = parentMap[parent];
            }
            cout << src << endl;
        } else {
            print("There is no route from %i to %i\n", src, dest)
        }
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

    g.shortestPath(0, 4);

    return 0;
}

