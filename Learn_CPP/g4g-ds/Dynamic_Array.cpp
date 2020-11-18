/*
Create a list, seqList, of n empty sequences, where each sequence is indexed from 0 to n-1.
The elements within each of the  sequences also use n-1 indexing.
Create an integer,lastAnswer and initialize it to 0.
There are 2 types of queries that can be performed on the list of sequences:
Query: 1 x y
Find the sequence, seq, at index ((x ^ lastAnswer) % n) in seqList.
Append integer y to sequence seq.
Query: 2 x y
Find the sequence, seq, at index ((x ^ lastAnswer) % n) in seqList.
Find the value of element y%size in seq (where `size` is the size of seq) and assign it to lastAnswer.
Print the new value of lastAnswer on a new line.
 */
#include <bits/stdc++.h>

using namespace std;

void dynamicArray(int n, vector<vector<int>> &queries) {
    vector<vector<int>> seqList(n);

    int lastAnswer{0};

    for (auto &q : queries) {
        auto type = q[0];
        auto x = q[1];
        auto y = q[2];
        int idx = (x ^ lastAnswer) % n;

        if (type == 1) {
            // Type 1
            auto &seq = seqList[idx];
            seq.push_back(y);
        } else {
            // Type 2
            auto &seq = seqList[idx];
            lastAnswer = seq[y % seq.size()];

            cout << lastAnswer << endl;
        }
    }

}

int main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> my2DArr(q);

    for (int i = 0; i < q; ++i) {
        my2DArr[i].resize(3);

        for (int j = 0; j < 3; ++j) {
            int t;
            cin >> t;

            my2DArr[i][j] = t;
        }
    }

    dynamicArray(n, my2DArr);


    return 0;
}