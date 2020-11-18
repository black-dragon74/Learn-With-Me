/*
A left rotation operation on an array of size n shifts each of the array's elements 1 unit to the left.
Given an integer, d, rotate the array that many steps left and return the result.
 */
#include <bits/stdc++.h>

using namespace std;

void rotateLeftByOne(vector<int> &arr) {
    int i, temp = arr[0];

    for (i = 0; i < arr.size() - 1; i++)
        arr[i] = arr[i + 1];

    arr[i] = temp;
}


int main() {
    int n, nPasses;
    cin >> n >> nPasses;

    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;

        arr[i] = t;
    }

    for (int i = 0; i < nPasses; ++i) {
        rotateLeftByOne(arr);
    }

    for (auto &a: arr) {
        cout << a << " ";
    }

    return 0;
}