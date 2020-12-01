#include <bits/stdc++.h>

using namespace std;

class MaxHeap {
private:
    int *store;
    int capacity;
    int size;

    static int parent(int i) { return (i - 1) / 2; }

    static int leftChild(int i) { return (2 * i) + 1; }

    static int rightChild(int i) { return (2 * i) + 2; }

public:
    explicit MaxHeap(int cap) {
        store = new int[cap];
        capacity = cap;
        size = 0;
    }

    /**
     * Fixes heap violations at an index. It requires the subtress of the current index to already be heaps.
     * @param index The index to perform heapify at
     */
    void heapify(int index) {
        auto largestIndex = index;
        auto lc = leftChild(index);
        auto rc = rightChild(index);

        // If left child lies in range of the heap and the value of left child is
        // Greater than the current largest value (the value at passed index)
        // Set the largest index to be the index of left child
        if (lc < size && store[lc] > store[largestIndex]) {
            largestIndex = lc;
        }

        // If right child lies in range and the value of right child is
        // Greater than the current largest value (the value at the index passed to function)
        // Set the largest index to be the index of the right child
        if (rc < size && store[rc] > store[largestIndex]) {
            largestIndex = rc;
        }

        // If the values of the largest index has changed, do the swapping
        // And then recursively call heapify on that the largest index
        // It is done so that violations if any, should be fixed.
        if (index != largestIndex) {
            swap(store[index], store[largestIndex]);
            heapify(largestIndex);
        }
    }

    void print() {
        if (size < 1) {
            cout << "Empty heap!" << endl;
            return;
        }

        for (int i = 0; i < size; ++i) {
            cout << store[i] << " ";
        }
        cout << endl;
    }

    /*
     * So you know how deletion in a heap works, right? We swap the root with the last and then
     * we decrease the current size of the heap. But those values are never really deleted, right?
     * So this function overrides the `size` and uses `capacity` instead. Doing so prints the hidden
     * data in our heap. Also, if you didn't use `replaceValAtIndex` or `deleteValAtIndex` then calling
     * this function will print your heap in a sorted manner. So this is why it exists.
     */
    void printAlt() {
        for (int i = 0; i < capacity; ++i) {
            cout << store[i] << " ";
        }
        cout << endl;
    }

    void insert(int val) {
        // Insertion always happens at the leaf node
        // Check overflow
        if (size == capacity) {
            cout << "Heap overflow\n";
            exit(1);
        }

        // Otherwise, insert at the current index + 1 (in the last)
        // Current index would be curr size - 1 as arrays are 0 indexed.
        size++;
        auto currIdx = size - 1;
        store[currIdx] = val;

        // Now fix any violations that might have happened till we don't reach root node
        // If parent is less than the child, swap parent and child
        // And set the currIdx value to it's parent and check again...
        while (currIdx != 0 && store[parent(currIdx) < store[currIdx]]) {
            swap(store[parent(currIdx)], store[currIdx]);
            currIdx = parent(currIdx);
        }
    }

    // This function deletes the root and returns its value
    int extractMax() {
        if (size < 1) {
            // There are no elements to delete
            // PANIK
            cout << "There are no elements in the heap." << endl;
            exit(1);
        }

        // Othewise, if size is just 1, return the elem at 0th index
        if (size == 1) {
            return store[size--];
        }

        // Else, we delete the elem, replace it with leaf node, and fix violations
        auto preVal = store[0];
        swap(store[0], store[size - 1]);
        size--;

        // Call heapify on index 0 as by convention, deletion always happens at root
        // And in heap, 0 is the root.
        heapify(0);

        return preVal;
    }

    void increaseValAtIndex(int index, int newValue) {
        if (index > size - 1) {
            cout << "Invalid index" << endl;
            exit(1);
        }

        if (newValue < store[index]) {
            cout << "New value is smaller than index." << endl;
            return;
        }

        // Otherwise, we set it's value to newValue and then fix the violations
        // Fixing the violation will push it to its proper position
        store[index] = newValue;
        while (index != 0 && store[parent(index)] < store[index]) {
            // We will keep swapping and updating the parent
            swap(store[index], store[parent(index)]);
            index = parent(index);
        }
    }

    // This is actually a hack, it is not possible to delete any X value in a heap
    // Only the root can be deleted, but here we change the value of prev value to
    // The highest int value possible and then call increaseValAtIndex,
    // which in turn fixes the violations for us by repalcing old value to new value
    // Then, we call extract max, which then deletes the largest val (root) in a max heap
    // And if you remember correctly, we set the largest value, we make our own rules.
    void deleteValueAtIndex(int index) {
        increaseValAtIndex(index, INT_MAX);
        extractMax();
    }

    [[nodiscard]]
    int getSize() const { return size; }

    [[nodiscard]]
    int isEmpty() const { return size == 0; }
};

int main() {
    MaxHeap h(10);
    h.insert(1);
    h.insert(2);
    h.insert(3);
    h.insert(4);
    h.insert(5);
    h.insert(6);
    h.insert(7);
    h.insert(8);
    h.insert(9);
    h.insert(10);

    h.print();

    while (!h.isEmpty()) {
        h.extractMax();
        h.print();
    }

    h.printAlt();

    return 0;
}

