#include <iostream>

class BinarySearchTree {
    private:
        class TreeNode {
            public:
                int key;
                TreeNode* left;
                TreeNode* right;

                TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
        };

        TreeNode* root;

        TreeNode* insertRecursive(TreeNode* node, int key) {
            if (node == nullptr) {
                return new TreeNode(key);
            }

            if (key < node->key) {
                node->left = insertRecursive(node->left, key);
            } else if (key > node->key) {
                node->right = insertRecursive(node->right, key);
            }

            return node;
        }

        bool searchRecursive(TreeNode* node, int key) {
            if (node == nullptr) {
                return false;
            }

            if (key == node->key) {
                return true;
            } else if (key < node->key) {
                return searchRecursive(node->left, key);
            } else {
                return searchRecursive(node->right, key);
            }
        }

    public:
        BinarySearchTree() : root(nullptr) {}

        void insert(int key) {
            root = insertRecursive(root, key);
        }

        bool search(int key) {
            return searchRecursive(root, key);
        }
};

int main() {
    BinarySearchTree bst;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);

    std::cout << "Is 10 in BST? " << (bst.search(10) ? "Yes" : "No") << std::endl;
    std::cout << "Is 20 in BST? " << (bst.search(20) ? "Yes" : "No") << std::endl;

    return 0;
}
