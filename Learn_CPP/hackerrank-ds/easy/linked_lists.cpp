/*
 * This is an AIO solution for all the (easy) linked list problems on Hacker-rank
 */
#include <bits/stdc++.h>

using namespace std;

/**
 * A generic singly linked list node
 * @tparam T
 */
template<typename T>
class SinglyLinkedListNode {
public:
    T data;
    SinglyLinkedListNode<T> *next;

    explicit SinglyLinkedListNode(T value) : data(value), next(nullptr) {}
};


template<typename T>
class SinglyLinkedList {
private:
    int numElements;
public:
    SinglyLinkedListNode<T> *head;

    SinglyLinkedList() : numElements(0), head(nullptr) {}

    ~SinglyLinkedList() {
        auto *ptr = head;

        while (ptr) {
            delete ptr;
            ptr = ptr->next;
        }
    }

    void print() {
        auto *ptr = head;

        while (ptr) {
            cout << ptr->data << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }

    void deleteAllNodes() {
        while (!empty())
            popBack();
    }

    void push(T elem) {
        auto *ptr = head;
        auto *tmp = new SinglyLinkedListNode<T>(elem);

        if (!ptr) {
            head = tmp;
            numElements++;
        } else {
            while (ptr->next)
                ptr = ptr->next;

            ptr->next = tmp;
            numElements++;
        }
    }

    void pushFront(T elem) {
        auto *ptr = head;
        auto *tmp = new SinglyLinkedListNode<T>(elem);

        if (!ptr) {
            push(elem);
        } else {
            tmp->next = head;
            head = tmp;
            numElements++;
        }
    }

    T getValueAtIndex(int index) {
        assert(index < numElements);

        auto *ptr = head;

        if (index == 0)
            return ptr->data;

        while (index > 0) {
            ptr = ptr->next;
            index--;
        }

        return ptr->data;
    }

    T getValueAtTailIndex(int index) {
        assert(index < numElements);
        return getValueAtIndex(numElements - index - 1);
    }

    void insertValueAtIndex(int index, T elem) {
        assert(index < numElements);

        auto *ptr = head;
        auto *tmp = new SinglyLinkedListNode<T>(elem);

        if (!ptr) {
            push(elem);
            return;
        }

        if (!index) {
            pushFront(elem);
            return;
        }

        while (index - 1 > 0) { // we wanna stop one index before the actual index to insert at
            ptr = ptr->next;
            index--;
        }

        tmp->next = ptr->next;
        ptr->next = tmp;
        numElements++;
    }

    void deleteNodeAt(int index) {
        assert(index < numElements);

        auto *ptr = head;

        if (!index) {
            head = ptr->next;
            delete ptr;
            numElements--;
            return;
        }

        while (index - 1 > 0) {
            ptr = ptr->next;
            index--;
        }

        delete ptr->next;
        ptr->next = ptr->next->next;
        numElements--;
    }

    void popFront() {
        deleteNodeAt(0);
    }

    void popBack() {
        deleteNodeAt(numElements - 1);
    }

    void printReverse() {
        auto *ptr = head;
        stack<T> myStack;

        while (ptr != nullptr) {
            myStack.push(ptr->data);
            ptr = ptr->next;
        }

        while (!myStack.empty()) {
            cout << myStack.top() << " ";
            myStack.pop();
        }

        cout << endl;
    }

    void reverse() {
        SinglyLinkedListNode<T> *prev = nullptr;
        auto *curr = head;
        SinglyLinkedListNode<T> *next = nullptr;

        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head = prev;
    }

    bool compareTo(const SinglyLinkedList<T> &otherList) {
//        auto *ptrA = head;
//        auto *ptrB = otherList.head;
//        auto countA = 0;
//        auto countB = 0;
//
//        while (ptrA) {
//            ptrA = ptrA->next;
//            countA++;
//        }
//
//        while (ptrB) {
//            ptrB = ptrB->next;
//            countB++;
//        }
//
//        if (countA != countB)
//            return false;
//
//        // Otherwise, compare each value
//        ptrA = head;
//        ptrB = otherList.head;
//        while (ptrA) {
//            if (ptrA->data != ptrB->data)
//                return false;
//
//            ptrA = ptrA->next;
//            ptrB = ptrB->next;
//        }
//
//        return true;

        auto *ptrA = head;
        auto *ptrB = otherList.head;

        while (ptrA && ptrB) {
            if (ptrA->data != ptrB->data)
                return false;

            ptrA = ptrA->next;
            ptrB = ptrB->next;
        }

        return (!ptrA && !ptrB);
    }

    void sortedMergeWith(SinglyLinkedList<T> &otherList) {
        auto *ptrA = head;
        auto *ptrB = otherList.head;
        vector<T> tempStore;

        while (ptrA) {
            tempStore.emplace_back(ptrA->data);
            ptrA = ptrA->next;
        }

        while (ptrB) {
            tempStore.emplace_back(ptrB->data);
            ptrB = ptrB->next;
        }

        sort(tempStore.begin(), tempStore.end());

        while (numElements)
            popBack();

        for (const auto &d: tempStore) {
            push(d);
        }
    }

    int size() { return numElements; }

    bool empty() { return numElements == 0; };
};

int binarySearch(const vector<int> &arr, int x) {
    int lb = 0;
    int rb = static_cast<int>(arr.size() - 1);

    while (lb <= rb) {
        int mid = lb + (rb - lb) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] < x)
            lb = mid + 1;
        else
            rb = mid -1;
    }

    return -1;
}

int main(int argc, char **argv) {
    auto myList = SinglyLinkedList<int>();



//    int arr[] = {2, 3, 4, 10, 40};
//    int x = 40;
//    int n = sizeof(arr) / sizeof(arr[0]);
//    int result = binarySearch(arr, 0, n - 1, x);
//    (result == -1) ? cout << "Element is not present in array"
//                   : cout << "Element is present at index " << result;


//    myList.print();
//    myList.insertValueAtIndex(1, 74);
//    assert(myList.getValueAtIndex(1) == 74);
//
//    myList.insertValueAtIndex(5, 75);
//    assert(myList.getValueAtIndex(5) == 75);
//
//    myList.insertValueAtIndex(10, 76);
//    assert(myList.getValueAtIndex(10) == 76);


    return 0;
}
