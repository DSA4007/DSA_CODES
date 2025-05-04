#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjMatrix;
    vector<bool> visited;

    void dfsUtil(int v) {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < vertices; ++i) {
            if (adjMatrix[v][i] && !visited[i]) {
                dfsUtil(i);
            }
        }
    }

public:
    Graph(int v) : vertices(v) {
        adjMatrix.resize(vertices, vector<int>(vertices, 0));
        visited.resize(vertices, false);
    }

    void addEdge(int u, int v) {
        if (u >= vertices || v >= vertices) {
            cout << "Invalid edge!\n";
            return;
        }
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;  // Undirected graph
    }

    void displayMatrix() const {
        cout << "Adjacency Matrix:\n";
        for (const auto& row : adjMatrix) {
            for (int val : row)
                cout << val << " ";
            cout << "\n";
        }
    }

    void DFS(int start) {
        fill(visited.begin(), visited.end(), false);
        cout << "DFS Traversal starting from vertex " << start << ": ";
        dfsUtil(start);
        cout << "\n";
    }

    void BFS(int start) {
        fill(visited.begin(), visited.end(), false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal starting from vertex " << start << ": ";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int i = 0; i < vertices; ++i) {
                if (adjMatrix[v][i] && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        cout << "\n";
    }
};

int main() {
    int v, e;
    cout << "Enter number of vertices: ";
    cin >> v;
    Graph g(v);

    cout << "Enter number of edges: ";
    cin >> e;
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < e; ++i) {
        int u, w;
        cin >> u >> w;
        g.addEdge(u, w);
    }

    int choice, start;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display Adjacency Matrix\n";
        cout << "2. DFS Traversal\n";
        cout << "3. BFS Traversal\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.displayMatrix();
                break;
            case 2:
                cout << "Enter starting vertex for DFS: ";
                cin >> start;
                g.DFS(start);
                break;
            case 3:
                cout << "Enter starting vertex for BFS: ";
                cin >> start;
                g.BFS(start);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
