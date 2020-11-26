#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

Node *newNode(int val) {
    auto *node = new Node;
    node->data = val;
    node->left = node->right = nullptr;

    return node;
}

Node *insertValToBST(Node *root, int val) {
    if (!root)
        return newNode(val);

    if (val < root->data)
        root->left = insertValToBST(root->left, val);
    else
        root->right = insertValToBST(root->right, val);

    return root;
}

Node *searchValueInBST(Node *root, int val) {
    if (!root || root->data == val)
        return root;

    // If smaller, recurse left
    if (val < root->data)
        return searchValueInBST(root->left, val);
    else
        return searchValueInBST(root->right, val);
}

void traverseInOrder(Node *root) {
    if (!root)
        return;

    traverseInOrder(root->left);
    cout << root->data << " ";
    traverseInOrder(root->right);
}

Node *smallestValueInSubtree(Node *root) {
    auto *ptr = root;

    while (ptr && ptr->left != nullptr)
        ptr = ptr->left;    // As smallest values are always to the left of a Node in BST

    return ptr;
}

Node *deleteValueFromBST(Node *root, int val) {
    if (!root)
        return root;

    // If val is smaller than curr, recurse left
    if (val < root->data)
        return deleteValueFromBST(root->left, val);
        // If val is greater, recurse right
    else if (val > root->data)
        return deleteValueFromBST(root->right, val);
    else {
        // No child or a single child
        if (!root->left) {
            auto *temp = root->right;
            delete root;
            return temp;
        }

        if (!root->right) {
            auto *temp = root->left;
            delete root;
            return temp;
        }

        // If not, then we need to find the inorder successor and replace it with that
        // Remember, in-order successor is the smallest val in right subtree
        auto *temp = smallestValueInSubtree(root->right);

        // Replace root node's data
        root->data = temp->data;

        // Delete the elem that we picked.
        root->right = deleteValueFromBST(root->right, temp->data);
    }

    return root;
}

int main(int argc, char **argv) {


    return 0;
}


