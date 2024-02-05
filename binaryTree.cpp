#include <iostream>
#include <memory>

template<typename T>
class BinarySearchTree {
    private:
        class TreeNode {
            public:
                T key;
                std::unique_ptr<TreeNode> left;
                std::unique_ptr<TreeNode> right;

                TreeNode(const T& k) : key(k), left(nullptr), right(nullptr) {}
            };

            std::unique_ptr<TreeNode> root;

            std::unique_ptr<TreeNode> insertRecursive(std::unique_ptr<TreeNode>& node, const T& key) {
                if (!node) {
                    return std::make_unique<TreeNode>(key);
                }

                if (key < node->key) {
                    node->left = insertRecursive(node->left, key);
                } else if (key > node->key) {
                    node->right = insertRecursive(node->right, key);
                }

                return std::move(node);
            }

            bool searchRecursive(const std::unique_ptr<TreeNode>& node, const T& key) const {
                if (!node) {
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

        void insert(const T& key) {
            root = insertRecursive(root, key);
        }

        bool search(const T& key) const {
            return searchRecursive(root, key);
        }
};

int main() {
    BinarySearchTree<int> bst;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);

    std::cout << "Is 10 in BST? " << (bst.search(10) ? "Yes" : "No") << std::endl;
    std::cout << "Is 20 in BST? " << (bst.search(20) ? "Yes" : "No") << std::endl;

    return 0;
}