#include <memory>
#include <stdexcept>
using namespace std;

class AVLTreeNode {
public:
    unique_ptr<AVLTreeNode> left;
    unique_ptr<AVLTreeNode> right;
    int value;
    int balance;

    AVLTreeNode(int v)
        : left(nullptr), right(nullptr), value(v), balance(0) {}

    void setLeft(int v) {
        left.reset(new AVLTreeNode(v));
    }

    void setRight(int v) {
        right.reset(new AVLTreeNode(v));
    }
};

class AVLTree {
private:
    int insert(unique_ptr<AVLTreeNode>& parent, unique_ptr<AVLTreeNode>& node, int v);
    int remove(unique_ptr<AVLTreeNode>& parent, unique_ptr<AVLTreeNode>& node, int v);
    void replace(unique_ptr<AVLTreeNode>& parent, unique_ptr<AVLTreeNode>& oldNode, unique_ptr<AVLTreeNode>& newNode);
    int achiveBalance(unique_ptr<AVLTreeNode>& parent, unique_ptr<AVLTreeNode>& node, int leftHeightDiff, int rightHeightDiff);

public:
    unique_ptr<AVLTreeNode> root;
    unique_ptr<AVLTreeNode> _null;

    AVLTree()
        : root(nullptr), _null(nullptr) {}

    void insert(int v);
    void remove(int v);
};


void AVLTree::insert(int v) {
    if (root == nullptr) {
        root.reset(new AVLTreeNode(v));
        return;
    }
    insert(_null, root, v);
}

int AVLTree::insert(unique_ptr<AVLTreeNode>& parent, unique_ptr<AVLTreeNode>& node, int v) {
    int diff = 0;
    if (v <= node->value) {
        if (node->left == nullptr) {
            node->setLeft(v);
            diff = 1;
        } else {
            diff = insert(node, node->left, v);
        }
        return achiveBalance(parent, node, diff, 0);
    } else {
        if (node->right == nullptr) {
            node->setRight(v);
            diff = 1;
        } else {
            diff = insert(node, node->right, v);
        }
        return achiveBalance(parent, node, 0, diff);
    }
}

void AVLTree::remove(int v) {
    remove (_null, root, v);
}

int AVLTree::remove(unique_ptr<AVLTreeNode>& parent, unique_ptr<AVLTreeNode>& node, int v) {
    if (node == nullptr) {
        return 0;
    }

    if (v < node->value) {
        int diff = remove(node, node->left, v);
        return achiveBalance(parent, node, diff, 0);
    } else if (v > node->value) {
        int diff = remove(node, node->right, v);
        return achiveBalance(parent, node, 0, diff);
    } else {
        // size--;
        if (node->left != nullptr) {
            int diff = findMaxAndRemove(node, node->left, node);
            return achiveBalance(parent, node, diff, 0);
        } else if (node->right != nullptr) {
            int diff = findMinAndRemove(node, node->right, node);
            return achiveBalance(parent, node, 0, diff);
        } else {
            replace(parent, node, _null);
            return -1;
        }
    }
}

void AVLTree::replace(unique_ptr<AVLTreeNode>& parent, unique_ptr<AVLTreeNode>& oldNode, unique_ptr<AVLTreeNode>& newNode) {
    if (parent == nullptr) {
        root.reset(oldNode.get());
        return;
    }
    if (parent->left == oldNode) {
        parent->left.reset(newNode.get());
    } else if (parent->right == oldNode) {
        parent->right.reset(newNode.get());
    } else {
        throw invalid_argument("Not found child node");
    }
}

int AVLTree::achiveBalance(unique_ptr<AVLTreeNode>& parent, unique_ptr<AVLTreeNode>& node, int leftHeightDiff, int rightHeightDiff) {
    if (leftHeightDiff == 0 && rightHeightDiff == 0) {
        return 0;
    }

    int heightDiff = 0;
    if ((leftHeightDiff > 0 && node->balance <= 0)
        || (rightHeightDiff > 0 && node->balance >= 0)) {
        heightDiff++;
    }
    if ((leftHeightDiff < 0 && node->balance < 0)
        || (rightHeightDiff < 0 && node->balance > 0)) {
        heightDiff--;
    }
    node->addBalance(-leftHeightDiff + rightHeightDiff);

    if (node->balance == -2) {
        if (node->left->balance != 0) {
            heightDiff--;
        }
        if (node->left->balance == 1) {
            replace(node, node->left, rotateLeft(node->left));
        }
        replace(parent, node, rotateRight(node));
    } else if (node->balance == 2) {
        if (node->right->balance != 0) {
            heightDiff--;
        }
        if (node->right->balance == -1) {
            replace(node, node->right, rotateRight(node->right));
        }
        replace(parent, node, rotateLeft(node));
    }
    return heightDiff;
}
