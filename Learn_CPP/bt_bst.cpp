#include <bits/stdc++.h>

using namespace std;

typedef vector<int> iv;
typedef unordered_map<int, int> im;

// BInary tree
struct Node {
    int data;
    Node *left, *right;
};

Node *createNewNode(int val) {
    auto *node = new Node;
    node->data = val;
    node->left = node->right = nullptr;

    return node;
}

Node *createBT() {
    int x;
    cout << "Enter value for node: ";
    cin >> x;

    if (x == -1)
        return nullptr;

    auto *node = createNewNode(x);
    cout << "Creating left of " << x << endl;
    node->left = createBT();

    cout << "Creating right of " << x << endl;
    node->right = createBT();

    return node;
}

void inOrderTraverse(Node *root) {
    if (!root)
        return;

    inOrderTraverse(root->left);
    cout << root->data << " ";
    inOrderTraverse(root->right);
}

void preOrderTraverse(Node *root) {
    if (!root)
        return;

    cout << root->data << " ";
    preOrderTraverse(root->left);
    preOrderTraverse(root->right);
}

void postOrderTraverse(Node *root) {
    if (!root)
        return;

    postOrderTraverse(root->left);
    postOrderTraverse(root->right);
    cout << root->data << " ";
}

void printBST(Node *root) {
    cout << "In order: ";
    inOrderTraverse(root);
    cout << endl;

    cout << "Pre order: ";
    preOrderTraverse(root);
    cout << endl;

    cout << "Post order: ";
    postOrderTraverse(root);
    cout << endl;
}

Node *processBTFromInAndPreOrder(int lb, int ub, const iv &preOrder, int &pIndex, im &map) {
    if (lb > ub)
        return nullptr;

    auto *root = createNewNode(preOrder[pIndex++]);

    auto index = map[root->data];

    // All to left of index are a part of left subtree
    root->left = processBTFromInAndPreOrder(lb, index - 1, preOrder, pIndex, map);

    // All to the right of index are a part of right subtree
    root->right = processBTFromInAndPreOrder(index + 1, ub, preOrder, pIndex, map);

    return root;
}

Node *createBTFromInAndPreOrder(const iv &inOrder, const iv &preOrder) {
    auto size = static_cast<int>(inOrder.size());
    im inOrderIndexMap;

    for (int i = 0; i < size; ++i) {
        inOrderIndexMap[inOrder[i]] = i;
    }

    auto pIndex = 0;

    return processBTFromInAndPreOrder(0, size - 1, preOrder, pIndex, inOrderIndexMap);

}

Node *processBTFromInAndPostOrder(int lb, int ub, const iv &postOrder, int &pIndex, im &map) {
    if (lb > ub)
        return nullptr;

    auto *root = createNewNode(postOrder[pIndex--]);

    auto index = map[root->data];

    // All to the right of index are a part of right subtree
    root->right = processBTFromInAndPostOrder(index + 1, ub, postOrder, pIndex, map);

    // All to left of index are a part of left subtree
    root->left = processBTFromInAndPostOrder(lb, index - 1, postOrder, pIndex, map);

    return root;
}

Node *createBTFromInAndPostOrder(const iv &inOrder, const iv &postOrder) {
    auto size = static_cast<int>(inOrder.size());
    im inOrderIndexMap;

    for (int i = 0; i < size; ++i) {
        inOrderIndexMap[inOrder[i]] = i;
    }

    auto pIndex = size - 1;

    return processBTFromInAndPostOrder(0, size - 1, postOrder, pIndex, inOrderIndexMap);

}

Node *smallestValueInSubtreeOfBST(Node *root) {
    if (!root || !root->left)
        return root;

    return smallestValueInSubtreeOfBST(root->left);
}

Node *insertValueInBST(int val, Node *root) {
    if (!root)
        return createNewNode(val);

    if (val < root->data)
        root->left = insertValueInBST(val, root->left);
    else
        root->right = insertValueInBST(val, root->right);

    return root;
}

Node *searchValueInBST(int val, Node *root) {
    if (!root || root->data == val)
        return root;

    if (val < root->data)
        return searchValueInBST(val, root->left);
    else
        return searchValueInBST(val, root->right);
}

Node *deleteValueFromBST(int val, Node *root) {
    if (!root)
        return root;

    if (val < root->data)
        root->left = deleteValueFromBST(val, root->left);
    else if (val > root->data)
        root->right = deleteValueFromBST(val, root->right);
    else {
        if (!root->left || !root->right) {
            auto *temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }

            delete temp;
        } else {
            auto *temp = smallestValueInSubtreeOfBST(root->right);  // in ordr succ = min in right ST
            root->data = temp->data;
            root->right = deleteValueFromBST(temp->data, root->right);  // Delete chosen node and update right ST
        }
    }

    return root;
}

int main(int argc, char **argv) {
    vector<int> io = {20, 30, 40, 50, 60, 70, 80};
    vector<int> preo = {50, 30, 20, 40, 70, 60, 80};
    vector<int> po = {20, 40, 30, 60, 80, 70, 50};

    Node *root{nullptr};
    root = createBTFromInAndPreOrder(io, preo);

//    root = insertValueInBST(50, root);
//    root = insertValueInBST(30, root);
//    root = insertValueInBST(20, root);
//    root = insertValueInBST(40, root);
//    root = insertValueInBST(70, root);
//    root = insertValueInBST(60, root);
//    root = insertValueInBST(80, root);

    cout << "Inorder traversal of the given tree \n";
    printBST(root);

    cout << "\nDelete 20\n";
    root = deleteValueFromBST(20, root);
    cout << "Traversal of the modified tree \n";
    printBST(root);

    cout << "\nDelete 30\n";
    root = deleteValueFromBST(30, root);
    cout << "Traversal of the modified tree \n";
    printBST(root);

    cout << "\nDelete 50\n";
    root = deleteValueFromBST(50, root);
    cout << "Traversal of the modified tree \n";
    printBST(root);

    return 0;
}

