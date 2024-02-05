#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

class Graph {
private:
    int numVertices;
    std::vector<std::vector<int>> adjacencyList;

public:
    Graph(int vertices) : numVertices(vertices), adjacencyList(vertices) {}

    void addEdge(int source, int destination) {
        adjacencyList[source].push_back(destination);
        // For an undirected graph, add the reverse edge as well
        adjacencyList[destination].push_back(source);
    }

    void DFS(int startNode) {
        std::vector<bool> visited(numVertices, false);
        std::stack<int> stack;

        stack.push(startNode);

        while (!stack.empty()) {
            int currentVertex = stack.top();
            stack.pop();

            if (!visited[currentVertex]) {
                std::cout << currentVertex << " ";
                visited[currentVertex] = true;
            }

            // Reverse the order of neighbors to get the desired order
            for (int i = adjacencyList[currentVertex].size() - 1; i >= 0; --i) {
                int neighbor = adjacencyList[currentVertex][i];
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                }
            }
        }
    }
};


int main() {
    Graph graph(4);

    // Adding edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);
    graph.addEdge(3, 3);

    std::cout << "DFS starting from node 2: ";
    graph.DFS(2);
    std::cout << std::endl;

    return 0;
}