#include <iostream>
#include <stdexcept>
#include <memory>
using namespace std;

template<typename T>
class TreeNode {
public:
    T value;
    unique_ptr<TreeNode<T>> left, right;

    TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

template<typename T>
class Tree {
private:
    bool contains(const unique_ptr<TreeNode<T>>& node, T v) {
        if (node == nullptr) {
            return false;
        }
        if (node->value == v) {
            return true;
        }

        if (node->value > v) {
            return contains(node->left, v);
        } else {
            return contains(node->right, v);
        }
    }

public:
    unique_ptr<TreeNode<T>> root;

    Tree() : root(nullptr) {}

    void replace(TreeNode<T> parent, TreeNode<T> oldNode, TreeNode<T> newNode) {
        if (parent == nullptr) {
            root = newNode;
            return;
        }

        if (parent.left == oldNode) {
            parent.left.reset(newNode);
        } else if (parent.right == oldNode) {
            parent.right.reset(newNode);
        } else {
            throw new invalid_argument("oldNode is not found");
        }
    }

    bool contains(T v) {
        return contains(root, v);
    }

    void insert(T v) {
        if (root == nullptr) {
            root.reset(new TreeNode<T>(v));
            return;
        }

        auto node = root.get();
        while (true) {
            if (node->value >= v) {
                if (node->left != nullptr) {
                    node = node->left.get();
                } else {
                    node->left.reset(new TreeNode<T>(v));
                    return;
                }
            } else {
                if (node->right != nullptr) {
                    node = node->right.get();;
                } else {
                    node->right.reset(new TreeNode<T>(v));
                    return;
                }
            }
        }
    }
};


int main() {
    Tree<int> tree;

    tree.insert(6);
    tree.insert(1);
    tree.insert(8);
    tree.insert(3);
    tree.insert(9);

    for (int i = 0; i < 10; i++) {
        if (tree.contains(i)) {
            cout << "Tree contains " << i << endl;
        }
    }
}
