# Let's break it down:

## Table of contents:
* [Binary Tree Search](https://github.com/grammyy/CPP-practice?tab=readme-ov-file#binary-tree-search)

## Binary Tree Search
```
C:\Users\grammy\Documents\GitHub\CPP-practice>binaryTree.exe 
Is 10 in BST? Yes
Is 20 in BST? No
```
***
* The BinarySearchTree class has a private nested class called TreeNode. Each TreeNode has an integer key, and pointers to its left and right child nodes (subtrees).
* The BinarySearchTree class has a private member variable root that points to the root of the BST.
```
BinarySearchTree
└── Private Members
    └── TreeNode
        ├── key: int
        ├── left: TreeNode*
        └── right: TreeNode*
```
### Public interface
* The public interface of the BinarySearchTree class includes a default constructor, an insert method to insert a key into the BST, and a search method to check if a key exists in the BST.
```
└── Public Methods
    └── BinarySearchTree(): Constructor, initializes root to null
    └── insert(key: int): void
        └── Calls private insertRecursive method with root and key
    └── search(key: int): bool
        └── Calls private searchRecursive method with root and key
```

## Private Methods
* insertRecursive Method:
```
└── Private Methods
    └── insertRecursive(node: TreeNode*, key: int): TreeNode*
        ├── If node is null
        │   └── Create new TreeNode(key)
        ├── If key < node->key
        │   └── Recursively call insertRecursive on left subtree
        ├── If key > node->key
        │   └── Recursively call insertRecursive on right subtree
        └── Return modified node

    └── searchRecursive(node: TreeNode*, key: int): bool
        ├── If node is null
        │   └── Return false
        ├── If key == node->key
        │   └── Return true
        ├── If key < node->key
        │   └── Recursively call searchRecursive on left subtree
        └── If key > node->key
            └── Recursively call searchRecursive on right subtree
```
  * The insertRecursive method is a private helper function for inserting a new key into the BST in a recursive manner.
  * It takes a TreeNode* node and an integer key as parameters.
  * If the node is null, it creates a new TreeNode with the given key and returns it.
  * If the key is less than the current node's key, it recursively calls insertRecursive on the left subtree.
  * If the key is greater, it recursively calls insertRecursive on the right subtree.
  * Finally, it returns the modified node.
* searchRecursive Method:
  * The searchRecursive method is a private helper function for searching a key in the BST in a recursive manner.
  *  It takes a TreeNode* node and an integer key as parameters.
  * If the node is null, it means the key is not found, and it returns false.
  * If the key is equal to the current node's key, it returns true.
  * If the key is less than the current node's key, it recursively calls searchRecursive on the left subtree.
  * If the key is greater, it recursively calls searchRecursive on the right subtree.
 
## Depth Search
```
C:\Users\grammy\Documents\GitHub\CPP-practice>depthSearch.exe
DFS starting from node 2: 2 0 1 3
```
***
``` 
0 ---- 1 ← Example visualized graph
|      |
2 ---- 3
```

* The Graph class has private members: numVertices (number of vertices) and adjacencyList (a vector of vectors representing the adjacency list).
* The constructor initializes the number of vertices and the adjacency list with an empty vector for each vertex.

```
Graph
└── Private Members
    ├── numVertices: int
    └── adjacencyList: vector<vector<int>>
```

### Graph Methods

* addEdge Method:
  * The addEdge method adds an edge between two vertices in the graph.
  * It takes the source and destination vertices as parameters.
  * It adds the destination to the adjacency list of the source, and for an undirected graph, it adds the reverse edge as well.
* DFS Method:
  * The DFS method performs a depth-first search traversal starting from a specified node.
  * It uses a stack to keep track of the vertices to be visited.
  * It initializes a boolean vector visited to keep track of visited vertices and sets all values to false.
  * It starts with the specified startNode by pushing it onto the stack.
  * In the DFS loop, it pops a vertex from the stack, checks if it's visited, prints it if not, marks it as visited, and then pushes its unvisited neighbors onto the stack.

```
└── Public Methods
    ├── Graph(vertices: int): Constructor, initializes numVertices and adjacencyList
    ├── addEdge(source: int, destination: int): void
        └── Adds an edge between source and destination vertices in the adjacencyList
    ├── DFS(startNode: int): void
        └── Performs Depth-First Search starting from the given startNode
            ├── Initialize visited array with false values
            ├── Initialize stack for DFS traversal
            ├── Push startNode onto the stack
            └── stack handled while its not empty
```

## Smart Pointer

## ThreadPool

## Thread Queue
