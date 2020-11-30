#include <bits/stdc++.h>

using namespace std;

int verbose = 1;
#define V(x) if (!verbose); else x;

enum Color {
    kcRed,
    kcBlack,
};

#define RED kcRed
#define BLACK kcBlack

struct Node {
    int data;
    Node *left, *right, *parent;
    Color color;

    explicit Node(int val) {
        data = val;
        left = right = parent = nullptr;
        color = kcRed;  // By default, inserted nodes are red, right?
    }

    bool isLeftChild() {
        return this == this->parent->left;
    }

    bool isRightChild() {
        return !isLeftChild();
    }

    [[nodiscard]]
    bool hasRedChild() const {
        return (left && left->color == kcRed) || (right && right->color == kcRed);
    }

    Node *getSibling() {
        return isLeftChild() ? parent->right : parent->left;
    }

    [[nodiscard]]
    Node *getGrandParent() const {
        return parent->parent;
    }

    [[nodiscard]]
    Node *getUncle() const {
        return parent->getSibling();
    }
};

class RedBlackTree {
private:
    Node *root;

    void fixDoubleRed(Node *&);

    void fixDoubleBlack(Node *&);

    void p_in_order(Node *x) {
        if (!x) {
            return;
        }

        p_in_order(x->left);
        cout << x->data << " ";
        p_in_order(x->right);
    }

    static void p_level_order(Node *x) {
        if (!x) {
            cout << "Empty tree.\n";
            return;
        }

        queue<Node *> q;
        q.push(x);

        while (!q.empty()) {
            auto *temp = q.front();
            cout << temp->data << " ";
            q.pop();

            if (temp->left)
                q.push(temp->left);

            if (temp->right)
                q.push(temp->right);
        }
    }

    static void swapColor(Node *n1, Node *n2) {
        swap(n1->color, n2->color);
    }

    static void swapValue(Node *n1, Node *n2) {
        swap(n1->data, n2->data);
    }

public:

    RedBlackTree() : root(nullptr) {}

    void rotateLeft(Node *&);

    void rotateRight(Node *&);

    Node *search(const int &);

    void insert(const int &);

    void deleteNodeWithValue(const int &);

    void deleteNode(Node *);

    void inOrder() {
        p_in_order(root);
        cout << endl;
    }

    void levelOrder() {
        p_level_order(root);
        cout << endl;
    }
};

Node *BSTInsert(Node *root, Node *newNodePtr) {
    if (!root)
        return newNodePtr;

    if (newNodePtr->data < root->data) {
        root->left = BSTInsert(root->left, newNodePtr);
        root->left->parent = root;
    } else {
        root->right = BSTInsert(root->right, newNodePtr);
        root->right->parent = root;
    }

    return root;
}

Node *successorNodeInSubtree(Node *node) {
    if (!node || !node->left)
        return node;

    return successorNodeInSubtree(node->left);
}

Node *BSTReplacementNode(Node *node) {
    // IF two children, return inorder successor
    if (node->left && node->right)
        return successorNodeInSubtree(node->right);

    // If leaf, return null
    if (!node->left && !node->right)
        return nullptr;

    // IF single child, return that child
    if (node->left)
        return node->left;
    else
        return node->right;
}

Node *search(Node *node, const int &val) {
    if (!node || node->data == val)
        return node;

    if (val < node->data)
        return search(node->left, val);
    else
        return search(node->right, val);
}

Node *RedBlackTree::search(const int &val) {
    return ::search(root, val);
}

void RedBlackTree::deleteNode(Node *nodeToDelete) {
    Node *replacementNode = BSTReplacementNode(nodeToDelete);

    // True when replacementNode and nodeToDelete are both black
    bool uvBlack = ((replacementNode == nullptr || replacementNode->color == kcBlack) &&
                    (nodeToDelete->color == kcBlack));
    Node *parent = nodeToDelete->parent;

    if (replacementNode == nullptr) {
        // replacementNode is NULL therefore nodeToDelete is leaf
        if (nodeToDelete == root) {
            // nodeToDelete is root, making root null
            root = nullptr;
        } else {
            if (uvBlack) {
                // replacementNode and nodeToDelete both black
                // nodeToDelete is leaf, fix double black at nodeToDelete
                fixDoubleBlack(nodeToDelete);
            } else {
                // replacementNode or nodeToDelete is red
                if (nodeToDelete->getSibling() != nullptr)
                    // sibling is not null, make it red"
                    nodeToDelete->getSibling()->color = kcRed;
            }

            // delete nodeToDelete from the tree
            if (nodeToDelete->isLeftChild()) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
        delete nodeToDelete;
        return;
    }

    if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
        // nodeToDelete has 1 child
        if (nodeToDelete == root) {
            // nodeToDelete is root, assign the value of replacementNode to nodeToDelete, and delete replacementNode
            nodeToDelete->data = replacementNode->data;
            nodeToDelete->left = nodeToDelete->right = nullptr;
            delete replacementNode;
        } else {
            // Detach nodeToDelete from tree and move replacementNode up
            if (nodeToDelete->isLeftChild()) {
                parent->left = replacementNode;
            } else {
                parent->right = replacementNode;
            }
            delete nodeToDelete;
            replacementNode->parent = parent;
            if (uvBlack) {
                // replacementNode and nodeToDelete both black, fix double black at replacementNode
                fixDoubleBlack(replacementNode);
            } else {
                // replacementNode or nodeToDelete red, color replacementNode black
                replacementNode->color = kcBlack;
            }
        }
        return;
    }

    // nodeToDelete has 2 children, swap values with successor and recurse
    swapValue(replacementNode, nodeToDelete);
    deleteNode(replacementNode);
}

void RedBlackTree::rotateLeft(Node *&prevNode) {
    auto *newNode = prevNode->right;
    prevNode->right = newNode->left;

    // If previous node has a child to it's right (which is now the left child of new node)
    // Update it's parent to be the previous node. It had newNode as it's parent before
    if (prevNode->right)
        prevNode->right->parent = prevNode;

    // New node's parent will obv be the previous node's parent
    newNode->parent = prevNode->parent;

    if (!newNode->parent)                          // If new node has no parent, it means it is the root node.
        root = newNode;
    else if (prevNode->isLeftChild())              // If prevNode was on left, update it's parent left to the new node
        prevNode->parent->left = newNode;
    else                                           // It was a right child, update the right child to be the new node
        prevNode->parent->right = newNode;

    // Rotate
    newNode->left = prevNode;

    // Now, the new node is the parent of the previous node
    prevNode->parent = newNode;
}

void RedBlackTree::rotateRight(Node *&prevNode) {
    auto *newNode = prevNode->left;                 // Self explanatory
    prevNode->left = newNode->right;                // Self explanatory

    // If prevNode has a child to it's left (we assigned it's left to be newNode's right)
    // We need to change the parent from newNode to the prevNode, self explanatory, right?
    if (prevNode->left)
        prevNode->left->parent = prevNode;

    // OFC, new node's parent will be prevNode's parent as it took it's place.
    newNode->parent = prevNode->parent;

    if (!newNode->parent)                           // If It has no parent, it means, it is the root node.
        root = newNode;
    else if (prevNode->isLeftChild())               // If it was the left child, tell it's parent that left has changed
        prevNode->parent->left = newNode;
    else
        prevNode->parent->right = newNode;          // If was a right child, the place is now taken by newNode.

    newNode->right = prevNode;                      // Self explanatory

    prevNode->parent = newNode;                     // newNode is now the parent node of the prevNode
}

void RedBlackTree::fixDoubleRed(Node *&node) {
    // 1. If node is root, color black and exit
    if (root == node) {
        node->color = kcBlack;
        return;
    }

    // 2. If parent of new node is black, return.
    if (node->parent->color == kcBlack)
        return;

    // 3. If parent of new node is red, check color of it's uncle.
    auto *grandParent = node->getGrandParent();
    auto *parent = node->parent;
    auto *uncle = node->getUncle();
    // if (parent->color == kcRed) is not needed as if it was black, the statement would've returned
    // 3.1 If uncle is red, recolor and then recurse on grandparent
    if (uncle && uncle->color == kcRed) {
        parent->color = kcBlack;
        uncle->color = kcBlack;
        grandParent->color = kcRed;
        fixDoubleRed(grandParent);
    } else {
        // 3.2, If color is black or null then rotate and recolor
        if (parent->isLeftChild()) {
            if (node->isLeftChild()) {
                // Left left
                swapColor(parent, grandParent);
            } else {
                // Left right
                rotateLeft(parent);
                swapColor(node, grandParent);
            }
            rotateRight(grandParent);
        } else {
            if (node->isRightChild()) {
                // Right right
                swapColor(parent, grandParent);
            } else {
                // Right left
                rotateRight(parent);
                swapColor(node, grandParent);
            }
            rotateLeft(grandParent);
        }
    }
}

void RedBlackTree::fixDoubleBlack(Node *&node) {
    if (node == root)
        return;

    auto *sibling = node->getSibling(), *parent = node->parent;
    if (!sibling) {
        // No sibling, push double black up
        fixDoubleBlack(parent);
    } else {
        if (sibling->color == RED) {
            // Sibling is red
            parent->color = RED;
            sibling->color = BLACK;

            if (sibling->isLeftChild()) {
                // Left left
                rotateRight(parent);
            } else {
                // Right right
                rotateLeft(parent);
            }
            fixDoubleBlack(node);
        } else {
            // Sibling is black
            if (sibling->hasRedChild()) {
                if (sibling->left && sibling->left->color == RED) {
                    if (sibling->isLeftChild()) {
                        // Left left
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rotateRight(parent);
                    } else {
                        // Right left
                        sibling->left->color = parent->color;
                        rotateRight(sibling);
                        rotateLeft(parent);
                    }
                } else {
                    if (sibling->isLeftChild()) {
                        // Left Right
                        sibling->right->color = parent->color;
                        rotateLeft(sibling);
                        rotateRight(parent);
                    } else {
                        // Right right
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        rotateLeft(parent);
                    }
                }
                parent->color = BLACK;
            } else {
                // 2 black children
                sibling->color = RED;
                if (parent->color == BLACK) {
                    fixDoubleBlack(parent);
                } else {
                    parent->color = BLACK;
                }
            }
        }
    }
}

void RedBlackTree::insert(const int &val) {
    auto *newNode = new Node(val);

    root = BSTInsert(root, newNode);

    fixDoubleRed(newNode);
}

void RedBlackTree::deleteNodeWithValue(const int &val) {
    if (!root)
        return;

    auto *nodeToDelete = search(val);

    if (!nodeToDelete)
        return;

    deleteNode(nodeToDelete);
}

int main() {
    RedBlackTree tree;

    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);

    tree.inOrder();
    tree.levelOrder();
    cout << endl;

    tree.deleteNodeWithValue(18);
    tree.deleteNodeWithValue(11);
    tree.deleteNodeWithValue(3);
    tree.deleteNodeWithValue(10);
    tree.deleteNodeWithValue(22);

    tree.inOrder();
    tree.levelOrder();

//    do {
//        int x;
//        cin >> x;
//
//        if (x == -1)
//            break;
//
//        tree.insert(x);
//
//    } while (true);

//    tree.inOrder();     // 1 2 3 4 5 6 7
//    tree.levelOrder();  // 6 4 7 2 5 1 3

    return 0;
}

