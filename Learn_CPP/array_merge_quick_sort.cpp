#include <bits/stdc++.h>

using namespace std;

//MARK:- Quick sort begin
int partition(int *array, int lb, int ub) {
    int pivot, start, end;
    pivot = array[lb];
    start = lb;
    end = ub;

    while (start < end) {
        while (array[start] <= pivot)
            start++;

        while (array[end] > pivot)
            end--;

        if (start < end)
            swap(array[start], array[end]);
    }

    swap(array[lb], array[end]);

    return end;
}

void quickSort(int *array, int lb, int ub) {
    if (lb < ub) {
        auto pIndx = partition(array, lb, ub);
        quickSort(array, lb, pIndx - 1);
        quickSort(array, pIndx + 1, ub);
    }
}
//MARK:- Quick sort end

//MARK:- Merge sort begin
void merge(int *array, int lb, int mid, int ub) {
    auto *answer = new int[ub + 1]();
    int i, j, k;
    i = k = lb;
    j = mid + 1;

    while (i <= mid && j <= ub) {
        if (array[i] <= array[j]) {
            answer[k] = array[i];
            i++;
        } else {
            answer[k] = array[j];
            j++;
        }
        k++;
    }

    if (i > mid) {
        while (j <= ub) {
            answer[k] = array[j];
            j++;
            k++;
        }
    } else {
        while (i <= mid) {
            answer[k] = array[i];
            i++;
            k++;
        }
    }

    for (int l = lb; l <= ub; ++l) {
        array[l] = answer[l];
    }
}

void mergeSort(int *array, int lb, int ub) {
    if (lb < ub) {
        auto mid = (lb + ub) / 2;
        mergeSort(array, lb, mid);
        mergeSort(array, mid + 1, ub);
        merge(array, lb, mid, ub);
    }
}
//MARK:- Merge sort end

void print(int *array, int size) {
    for (int i = 0; i <= size; ++i) {
        cout << array[i] << " ";
    }

    cout << endl;
}

int main(int argc, char **argv) {
    int arr[] = {12, 2, 4, 43, 1, 2, 43, 5, 65656, 75, 56};

    auto size = (sizeof(arr) / sizeof(int)) - 1;

    print(arr, size);

    mergeSort(arr, 0, size);

    print(arr, size);

    return 0;
}

