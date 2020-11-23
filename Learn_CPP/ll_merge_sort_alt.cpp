/*
 * Created by Nick aka black-dragon74 on 24-11-2020
 *
 * Sorting a LL is quite a pain right? And you can only use merge sort, that further adds to the complexity.
 * So, here I try to sort LL in a new way, kind of how you would merge sort an array.
 * Guess what? Sorting an LL seems pretty easy when you apply those same principles here.
 * This approach gets rid of scary tail and dummy nodes that you have to use when you look for the ways to sort
 * a linked list on the internet. Also, no recusrive approach to merge two sorted LL.
 *
 * Time complexity of this approach: O(nLogn)
 */
#include <bits/stdc++.h>

using namespace std;

class Node {
public:
    int data;
    Node *next;
};

void print(const Node *ref) {
    auto *rCopy = ref;
    while (rCopy) {
        cout << rCopy->data << " ";
        rCopy = rCopy->next;
    }
    cout << endl;
}

void push(Node **head, int value) {
    Node *n = new Node();
    n->data = value;
    n->next = nullptr;

    auto *ptr = *head;
    if (!ptr) {
        *head = n;
        return;
    }

    while (ptr->next) {
        ptr = ptr->next;
    }

    ptr->next = n;
}

void split(Node *head, Node **refA, Node **refB) {
    auto slowPtr = head;
    auto ptr = head->next;

    while (ptr) {
        ptr = ptr->next;
        if (ptr) {
            ptr = ptr->next;
            slowPtr = slowPtr->next;
        }
    }

    *refB = slowPtr->next;
    slowPtr->next = nullptr;
    *refA = head;
}

Node *mergeTwoLL(Node *nodeA, Node *nodeB) {
    Node *mergedLL{nullptr};    // LL equiv of B[UB + 1]

    if (!nodeA)
        return nodeB;
    else if (!nodeB)
        return nodeA;

    while (nodeA && nodeB) {
        if (nodeA->data <= nodeB->data) {
            push(&mergedLL, nodeA->data);
            nodeA = nodeA->next;
        } else {
            push(&mergedLL, nodeB->data);
            nodeB = nodeB->next;
        }
    }

    // Check for leftovers
    if (!nodeA) {   // It is exhausted
        while (nodeB) {
            push(&mergedLL, nodeB->data);
            nodeB = nodeB->next;
        }
    } else {    // NodeB is exhausted
        while (nodeA) {
            push(&mergedLL, nodeA->data);
            nodeA = nodeA->next;
        }
    }

    return mergedLL;
}

void mergeSort(Node **head) {
    Node *ptr = *head;
    Node *nodeA;
    Node *nodeB;

    if (!ptr || !ptr->next)     // LL Equivalent of lb < rb check, base case for recursion
        return;                 // As there should be more than one node for split and merge

    split(ptr, &nodeA, &nodeB); // LL Equivalent of finding mid
    mergeSort(&nodeA);  // On left part
    mergeSort(&nodeB);  // On right part
    *head = mergeTwoLL(nodeA, nodeB);   // Merge
}

int main() {
    Node *myList{nullptr};

    push(&myList, 34);
    push(&myList, 132);
    push(&myList, 8);
    push(&myList, 12);
    push(&myList, 20);
    push(&myList, 194);
    push(&myList, 999);

    print(myList);  // Prints: 34 132 8 12 20 194 999

    mergeSort(&myList);

    assert(myList->data == 8);  // Assertion to check

    print(myList); // Prints: 8 12 20 34 132 194 999


    return 0;
}

