#include <bits/stdc++.h>

using namespace std;

class MinHeap {
private:
    int *store;
    int size;
    int capacity;

    static int parent(int i) { return (i - 1) / 2; }

    static int leftChild(int i) { return (2 * i) + 1; }

    static int rightChild(int i) { return (2 * i) + 2; }

    [[nodiscard]]
    int leafIdx() const { return (size / 2) + 2; }

    [[nodiscard]]
    int heapIdx() const { return (size / 2) - 1; }

public:
    explicit MinHeap(int cap) {
        store = new int[cap];
        capacity = cap;
        size = 0;
    }

    void print() {
        if (size < 1)
            throw underflow_error("Heap is empty!");

        for (int i = 0; i < size; ++i) {
            cout << store[i] << " ";
        }
        cout << endl;
    }

    void printAlt() {
        for (int i = 0; i < capacity; ++i) {
            cout << store[i] << " ";
        }
        cout << endl;
    }

    auto get(int index) {
        if (index >= size)
            throw invalid_argument("Invalid index");

        return store[index];
    }

    void heapify(int idx) {
        if (idx >= size)
            throw invalid_argument("Index out of range");

        auto smallest = idx;
        auto lc = leftChild(idx);
        auto rc = rightChild(idx);

        if (lc < size && store[lc] < store[smallest])
            smallest = lc;

        if (rc < size && store[rc] < store[smallest])
            smallest = rc;

        if (smallest != idx) {
            swap(store[smallest], store[idx]);
            heapify(smallest);
        }
    }

    void insert(int val) {
        if (size == capacity)
            throw overflow_error("Heap overflow!");

        size++;
        auto currIdx = size - 1;
        store[currIdx] = val;

        // Fix violations
        while (currIdx != 0 && store[parent(currIdx)] > store[currIdx]) {
            swap(store[parent(currIdx)], store[currIdx]);
            currIdx = parent(currIdx);
        }
    }

    int extractMin() {
        if (size < 1)
            throw underflow_error("Empty heap!");

        if (size == 1)
            return store[--size];

        auto preVal = store[0];
        swap(store[0], store[--size]);

        heapify(0);

        return preVal;
    }

    void decreaseValAt(int index, int newVal) {
        if (size < 1)
            throw underflow_error("Empty heap!");

        if (index >= size)
            throw invalid_argument("Invalid index");

        if (newVal > store[index])
            throw invalid_argument("New value is greater than current value");

        store[index] = newVal;

        // Fix violations
        while (index != 0 && store[parent(index)] > store[index]) {
            swap(store[parent(index)], store[index]);
            index = parent(index);
        }
    }

    void deleteValueAt(int index) {
        decreaseValAt(index, INT_MIN);
        extractMin();
    }

    auto getLeafIndex() {
        return leafIdx();
    }

    auto getHeapifyIndex() {
        return heapIdx();
    }

    [[nodiscard]]
    auto empty() const { return size == 0; }

    [[nodiscard]]
    auto getSize() const { return size; }

};

int main(int argc, char **argv) {
    int n = 10;
    MinHeap m(10);

    for (int i = n; i >= 1; --i) {
        m.insert(i * 3);
    }

    m.print();

    while (!m.empty()) {
        m.extractMin();
    }

    m.printAlt();

    return 0;
}


