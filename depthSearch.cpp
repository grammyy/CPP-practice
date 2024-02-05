#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

class Graph {
    private:
        std::size_t numVertices;
        std::vector<std::vector<std::size_t>> adjacencyList;

    public:
        Graph(std::size_t vertices) : numVertices(vertices), adjacencyList(vertices) {}

        void addEdge(std::size_t source, std::size_t destination) {
            adjacencyList[source].push_back(destination);
            adjacencyList[destination].push_back(source);
        }

        void DFS(std::size_t startNode) {
            std::vector<bool> visited(numVertices, false);
            std::stack<std::size_t> stack;

            stack.push(startNode);

            while (!stack.empty()) {
                std::size_t currentVertex = stack.top();

                stack.pop();

                if (!visited[currentVertex]) {
                    std::cout << currentVertex << " ";
                    visited[currentVertex] = true;

                    for (auto it = adjacencyList[currentVertex].rbegin(); it != adjacencyList[currentVertex].rend(); ++it) {
                        std::size_t neighbor = *it;
                        if (!visited[neighbor]) {
                            stack.push(neighbor);
                        }
                    }
                }
            }
        }
};

int main() {
    Graph graph(4);

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