/*
 * Created by Nick aka black-dragon74 on 26-11-2020
 *
 * Contains all the basic operations of a binary tree
 */
#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

enum TraverseMode {
    kTraverseInOrder,
    kTraversePreOrder,
    kTraversePostOrder
};

Node *createNewNode(int val) {
    auto node = new Node();
    node->data = val;
    node->left = node->right = nullptr;

    return node;
}

Node *createBinaryTreeNode() {
    Node *node{nullptr};
    int x;
    fprintf(stdout, "Enter the value for node (-1 for empty node): ");
    cin >> x;

    // Base case, if user enter it, well we don't create a node
    if (x == -1)
        return node;

    // Otherwise, we create node and then recursively fill it's left and right
    // We will call createBinaryTreeNode as we really have to create a whole new node
    // The new node will also have left and right, correct?
    node = createNewNode(x);
    fprintf(stdout, "Creating left node of %d.\n", x);
    node->left = createBinaryTreeNode();
    fprintf(stdout, "Creating right node of %d.\n", x);
    node->right = createBinaryTreeNode();

    return node;
}

void inOrderTraverse(Node *root) {
    if (root) {
        inOrderTraverse(root->left);
        cout << root->data << " ";
        inOrderTraverse(root->right);
    }
}

void preOrderTraverse(Node *root) {
    if (root) {
        cout << root->data << " ";
        preOrderTraverse(root->left);
        preOrderTraverse(root->right);
    }
}

void postOrderTraverse(Node *root) {
    if (root) {
        postOrderTraverse(root->left);
        postOrderTraverse(root->right);
        cout << root->data << " ";
    }
}

void traverseBinaryTree(Node *root, TraverseMode predicate) {
    switch (predicate) {
        case kTraverseInOrder:
            inOrderTraverse(root);
            break;
        case kTraversePreOrder:
            preOrderTraverse(root);
            break;
        case kTraversePostOrder:
            postOrderTraverse(root);
            break;
    }
}

Node *processBTFromInPreOrder(int lb, int ub, const vector<int> &preOrder, int &preOrderIndex,
                              unordered_map<int, int> &indexMap) {

    // Base case
    if (lb > ub)
        return nullptr;

    // Step 1, Next unprocessed elem in pre-order is the root
    Node *root = createNewNode(preOrder[preOrderIndex++]);

    // Step2, locate this root elem in in-order
    auto indexOfRoot = indexMap[root->data];

    // Now all the value to the left of `indexOfRoot` go to left subtree
    root->left = processBTFromInPreOrder(lb, indexOfRoot - 1, preOrder, preOrderIndex, indexMap);

    // And all the value to the right of `indexOfRoot` go to right subtree
    root->right = processBTFromInPreOrder(indexOfRoot + 1, ub, preOrder, preOrderIndex, indexMap);

    return root;
}

Node *createBTFromInPreOrder(const vector<int> &inOrder, const vector<int> &preOrder) {
    auto size = static_cast<int>(inOrder.size()) - 1;
    auto preOrderIndex = 0;

    unordered_map<int, int> inOrderIndexMap;
    for (int i = 0; i <= size; ++i) {
        inOrderIndexMap[inOrder[i]] = i;
    }

    return processBTFromInPreOrder(0, size, preOrder, preOrderIndex, inOrderIndexMap);
}

Node *processBTFromInPostOrder(int lb, int ub, const vector<int> &postOrder, int &postOrderIndex,
                               unordered_map<int, int> &indexMap) {

    if (lb > ub)
        return nullptr;

    Node *root = createNewNode(postOrder[postOrderIndex--]);

    auto indexOfRoot = indexMap[root->data];

    root->right = processBTFromInPostOrder(indexOfRoot + 1, ub, postOrder, postOrderIndex, indexMap);
    root->left = processBTFromInPostOrder(lb, indexOfRoot - 1, postOrder, postOrderIndex, indexMap);

    return root;
}

Node *createBTFromInPostOrder(const vector<int> &inOrder, const vector<int> &postOrder) {
    auto size = static_cast<int>(inOrder.size()) - 1;
    unordered_map<int, int> inOrderIndexMap;

    for (int i = 0; i <= size; ++i) {
        inOrderIndexMap[inOrder[i]] = i;
    }

    return processBTFromInPostOrder(0, size, postOrder, size, inOrderIndexMap);
}

Node *
processBTFromPrePostOrder(int lb, int ub, const vector<int> &preOrder, int &startIndex, unordered_map<int, int> &map) {

    auto *root = createNewNode(preOrder[startIndex++]);

    if (startIndex == preOrder.size())
        return root;

    auto nextIndex = map[preOrder[startIndex]];

    if (lb <= nextIndex && nextIndex + 1 <= ub - 1) {
        root->left = processBTFromPrePostOrder(lb, nextIndex, preOrder, startIndex, map);
        root->right = processBTFromPrePostOrder(nextIndex + 1, ub - 1, preOrder, startIndex, map);
    }

    return root;
}

Node *createBTFromPrePostOrder(const vector<int> &preOrder, const vector<int> &postOrder) {
    auto size = static_cast<int>(preOrder.size()) - 1;
    auto strtIndex = 0;
    unordered_map<int, int> postOrderIndexMap;

    for (int i = 0; i <= size; ++i) {
        postOrderIndexMap[postOrder[i]] = i;
    }

    return processBTFromPrePostOrder(0, size, preOrder, strtIndex, postOrderIndexMap);
}

int main(int argc, char **argv) {
//    vector<int> inTrav = {4, 2, 5, 1, 8, 6, 9, 3, 7};
//    vector<int> preTrav = {1, 2, 4, 5, 3, 6, 8, 9, 7};
//    vector<int> posTrav = {4, 5, 2, 8, 9, 6, 7, 3, 1};

    auto *a = createBinaryTreeNode();

    fprintf(stdout, "In order\n");
    traverseBinaryTree(a, kTraverseInOrder);
    cout << endl;

    fprintf(stdout, "Pre order\n");
    traverseBinaryTree(a, kTraversePreOrder);
    cout << endl;

    fprintf(stdout, "Post order\n");
    traverseBinaryTree(a, kTraversePostOrder);
    cout << endl;

    return 0;
}

