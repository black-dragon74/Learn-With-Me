#include <bits/stdc++.h>

int debug = 1;
#define DBG(x) if (!debug); else { printf("DBG: "); x; };

using namespace std;

// AVL Tree structure
struct Node {
    int data;
    Node *left, *right;
    int height;
};

int getHeight(Node *N) {
    if (!N)
        return 0;

    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node *newNode(int val) {
    auto *node = new Node;
    node->data = val;
    node->left = node->right = nullptr;
    node->height = 1;

    return node;
}

Node *rightRotate(Node *prevRoot) {
    auto *newRoot = prevRoot->left;
    auto *cNode = newRoot->right;

    // Rotate
    newRoot->right = prevRoot;
    prevRoot->left = cNode;

    // Recalculate heights
    prevRoot->height = max(getHeight(prevRoot->left), getHeight(prevRoot->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    // Return rotated new node, now rooted at `newRoot`
    return newRoot;
}

Node *leftRotate(Node *prevRoot) {
    auto *newRoot = prevRoot->right;
    auto *cNode = newRoot->left;

    // Rotate
    newRoot->left = prevRoot;
    prevRoot->right = cNode;

    // Recalculate heights
    prevRoot->height = max(getHeight(prevRoot->left), getHeight(prevRoot->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    // Return rotated new node, rooted at `newRoot`
    return newRoot;
}

int getBalanceFactor(Node *root) {

    if (!root)
        return 0;

    // Difference of height of left subtree and right subtree
    return getHeight(root->left) - getHeight(root->right);
}

Node *rebalanceIfNeededPD(Node *node) {
    auto balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        // One thing is sure that it is caused due to one left insertion
        // Now we need to find the type of other insertion
        if (getBalanceFactor(node->left) >= 0) {
            DBG(printf("LL PD\n"))
            // LL case, right rotation is needed
            return rightRotate(node);
        } else {
            // LR rotation is needed
            DBG(printf("LR PD\n"))
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (balanceFactor < -1) {
        // Right is for sure
        if (getBalanceFactor(node->right) <= 0) {
            // RR
            DBG(printf("RR PD\n"))
            return rightRotate(node);
        } else {
            // RL
            DBG(printf("RL PD\n"))
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

/**
 * After insertion, we compare and determine the unbalance factor based on the inserted value.
 * If value was inserted to the left and BF of the current node > 1, LL else LR
 * If value was inserted to the right and BF of current node < -1, RR else RL
 *
 * @brief Rebalances a node post insertion.
 * @param val The value that was inserted
 * @param node The unbalanced node
 * @return The new node pointer with balanced sub trees
 */
Node *rebalanceIfNeededPI(const int &val, Node *node) {
    // First, get the balance factor
    auto balanceFactor = getBalanceFactor(node);

    // Now we check for the unbalance
    if (balanceFactor > 1) {    // One imbalance is on left, that's for sure
        // Now check if it is another left or right
        if (val < node->left->data) {
            // It is inserted on left for sure, which makes it LL case
            // One right rotation will balance it.
            DBG(printf("LL PI %d\n", val))
            return rightRotate(node);
        }

        if (val > node->left->data) {
            // Greater values go to the right, LR case it is
            // One left and one right rotation ought to balance this
            DBG(printf("LR PI %d\n", val))
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    } else if (balanceFactor < -1) {    // One imbalance is on the right for sure
        // Now we check if another imbalance is on left or right
        if (val > node->right->data) {
            // Larger vals are always inserted on the right of a node in BST, RR case
            // One left rotation is needed
            DBG(printf("RR PI %d\n", val))
            return leftRotate(node);
        }
        if (val < node->right->data) {
            // Smaller values are always inserted to the left, it makes it RL case
            // One right and one left rotation is needed
            DBG(printf("RL PI %d\n", val))
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    // Otherwise, it is a good lil balanced node, return it untouched.
    return node;
}

Node *insertValueInAVLTree(int val, Node *root) {
    // First case, there is no node, i.e. root node is null
    if (!root)
        return newNode(val);

    // Second case, val is less, insert in left ST
    if (val < root->data)
        root->left = insertValueInAVLTree(val, root->left);
    else if (val > root->data)
        root->right = insertValueInAVLTree(val, root->right);
    else
        return root;    // Fffff duplicates not allowed

    // Update the height of the node, 1 insert happened means val + 1
    // Also, height is the longest path from N to leaf node, hence we use max, the longest path will be selected
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // Now, it is possible that the tree is not AVL, take care of that
    return rebalanceIfNeededPI(val, root);
}

Node *minValueinSubtreeOf(Node *node) {
    if (!node || !node->left)
        return node;

    // AVL is a BST, min will lie in the farthest left
    return minValueinSubtreeOf(node->left);
}

Node *deleteValueFromAVLTree(int val, Node *root) {
    if (!root)
        return root;

    if (val < root->data)
        root->left = deleteValueFromAVLTree(val, root->left);
    else if (val > root->data)
        root->right = deleteValueFromAVLTree(val, root->right);
    else {
        // This is the node, delete, update height and then rebalance if needed
        // Case 1, 0 or no child case
        if (!root->left || !root->right) {
            auto *temp = root->left ? root->left : root->right;

            if (!temp) {
                // No child is there, just delete it
                temp = root;
                root = nullptr;
            } else {
                // There is one child, it becomes the parent
                *root = *temp;
            }

            delete temp;
        } else {
            // Fucker has 2 children, get the inorder successor
            auto *temp = minValueinSubtreeOf(root->right);

            root->data = temp->data;

            root->right = deleteValueFromAVLTree(temp->data, root->right);
        }
    }

    // Now that we have deleted, update the height, but if node had no child, we just deleted it
    if (!root)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Rebalance if needed
    return rebalanceIfNeededPD(root);
}

void preOrder(Node *node) {
    if (!node)
        return;

    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void getLeaves(Node *root) {
    if (!root)
        return;

    // Leaf has no child
    if (!root->left && !root->right) {
        cout << "Leaf: " << root->data << endl;
        DBG(printf("eight leaf: %d\n", root->height))
        return;
    }

    // Else, recurse left and right
    getLeaves(root->left);
    getLeaves(root->right);
}

Node *searchValueInAVL(int val, Node *root) {
    if (!root || root->data == val)
        return root;

    if (val < root->data)
        return searchValueInAVL(val, root->left);
    else
        return searchValueInAVL(val, root->right);
}

int main(int argc, char **argv) {

    Node *root{nullptr};

    root = insertValueInAVLTree(9, root);
    root = insertValueInAVLTree(5, root);
    root = insertValueInAVLTree(10, root);
    root = insertValueInAVLTree(0, root);
    root = insertValueInAVLTree(6, root);
    root = insertValueInAVLTree(11, root);
    root = insertValueInAVLTree(1, root);
    root = insertValueInAVLTree(2, root);

    root = deleteValueFromAVLTree(10, root);

    cout << "PreOrder: ";   // PreOrder: 5 1 0 2 9 6 11
    preOrder(root);
    cout << endl;

    getLeaves(root);

    return 0;
}


