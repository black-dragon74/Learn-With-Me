#include <bits/stdc++.h>

using namespace std;

int verbose = 1;
#define V(x) if (!verbose); else x;

enum Color {
    kcRed,
    kcBlack,
};

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

    void insertionDidFinish(Node *&);

    void p_in_order(Node *x) {
        if (!x) {
            cout << "Empty tree.\n";
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

public:

    RedBlackTree() : root(nullptr) {}

    void rotateLeft(Node *&);

    void rotateRight(Node *&);

    void insert(const int &);

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

void RedBlackTree::insertionDidFinish(Node *&node) {
    Node *parentPtr{nullptr};
    Node *grandParentPtr{nullptr};

    while ((node != root) && (node->color != kcBlack) && (node->parent->color == kcRed)) {
        parentPtr = node->parent;
        grandParentPtr = node->getGrandParent();

        // Case A, parent of node is left child of node's grandparent
        if (parentPtr->isLeftChild()) {
            auto *unclePtr = node->getUncle();

            // Case A.1, check uncle's color, if red, recolor
            if (unclePtr && unclePtr->color == kcRed) {
                V(printf("A.1\n"))
                grandParentPtr->color = kcRed;
                parentPtr->color = kcBlack;
                unclePtr->color = kcBlack;
                node = grandParentPtr;
            } else {
                // Case A.2, node is right child, left rotation is required
                if (node->isRightChild()) {
                    V(printf("A.2\n"))
                    rotateLeft(parentPtr);
                    node = parentPtr;
                    parentPtr = node->parent;
                }

                // Case A.3, node is left child, right rotation required
                V(printf("A.3\n"))
                rotateRight(grandParentPtr);
                swap(parentPtr->color, grandParentPtr->color);
                node = parentPtr;
            }
        }

            // Case B, parent of node is right child of node's grandparent
        else {
            auto *unclePtr = node->getUncle();

            // Case B.1, uncle is red, only recolor required
            if (unclePtr && unclePtr->color == kcRed) {
                V(printf("B.1\n"))
                grandParentPtr->color = kcRed;
                parentPtr->color = kcBlack;
                unclePtr->color = kcBlack;
                node = grandParentPtr;
            } else {
                // Case B.2, node is left child, right rotation is required
                if (node->isLeftChild()) {
                    V(printf("B.2\n"))
                    rotateRight(parentPtr);
                    node = parentPtr;
                    parentPtr = node->parent;
                }

                // Case B.3, node is right child, left rotation is required
                V(printf("B.3\n"))
                rotateLeft(grandParentPtr);
                swap(parentPtr->color, grandParentPtr->color);
                node = parentPtr;
            }
        }
    }

    root->color = kcBlack;
}

void RedBlackTree::insert(const int &val) {
    auto *newNode = new Node(val);

    root = BSTInsert(root, newNode);

    insertionDidFinish(newNode);
}

int main() {
    RedBlackTree tree;

//    tree.insert(7);
//    tree.insert(6);
//    tree.insert(5);
//    tree.insert(4);
//    tree.insert(3);
//    tree.insert(2);
//    tree.insert(1);

    tree.inOrder();     // 1 2 3 4 5 6 7
    tree.levelOrder();  // 6 4 7 2 5 1 3

    return 0;
}

