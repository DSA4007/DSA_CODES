#include <iostream>
#include <vector>
#include <queue>

class Graph {
private:
    int vertices;
    std::vector<std::vector<int>> adjMatrix;
    std::vector<bool> visited;

    void dfsUtil(int v) {
        visited[v] = true;
        std::cout << v << " ";

        for (int i = 0; i < vertices; ++i) {
            if (adjMatrix[v][i] && !visited[i]) {
                dfsUtil(i);
            }
        }
    }

public:
    Graph(int v) : vertices(v) {
        adjMatrix.resize(vertices, std::vector<int>(vertices, 0));
        visited.resize(vertices, false);
    }

    void addEdge(int u, int v) {
        if (u >= vertices || v >= vertices) {
            std::cout << "Invalid edge!\n";
            return;
        }
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;  // Undirected graph
    }

    void displayMatrix() const {
        std::cout << "Adjacency Matrix:\n";
        for (const auto& row : adjMatrix) {
            for (int val : row)
                std::cout << val << " ";
            std::cout << "\n";
        }
    }

    void DFS(int start) {
        std::fill(visited.begin(), visited.end(), false);
        std::cout << "DFS Traversal starting from vertex " << start << ": ";
        dfsUtil(start);
        std::cout << "\n";
    }

    void BFS(int start) {
        std::fill(visited.begin(), visited.end(), false);
        std::queue<int> q;
        visited[start] = true;
        q.push(start);

        std::cout << "BFS Traversal starting from vertex " << start << ": ";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            std::cout << v << " ";

            for (int i = 0; i < vertices; ++i) {
                if (adjMatrix[v][i] && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        std::cout << "\n";
    }
};

int main() {
    int v, e;
    std::cout << "Enter number of vertices: ";
    std::cin >> v;
    Graph g(v);

    std::cout << "Enter number of edges: ";
    std::cin >> e;
    std::cout << "Enter edges (u v):\n";
    for (int i = 0; i < e; ++i) {
        int u, w;
        std::cin >> u >> w;
        g.addEdge(u, w);
    }

    int choice, start;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Display Adjacency Matrix\n";
        std::cout << "2. DFS Traversal\n";
        std::cout << "3. BFS Traversal\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                g.displayMatrix();
                break;
            case 2:
                std::cout << "Enter starting vertex for DFS: ";
                std::cin >> start;
                g.DFS(start);
                break;
            case 3:
                std::cout << "Enter starting vertex for BFS: ";
                std::cin >> start;
                g.BFS(start);
                break;
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
