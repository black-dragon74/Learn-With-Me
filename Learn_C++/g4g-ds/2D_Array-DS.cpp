/*
Given a 6x6 2D Array, arr:
1 1 1 0 0 0
0 1 0 0 0 0
1 1 1 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
An hourglass in A is a subset of values with indices falling in this pattern in arr's graphical representation:

a b c
  d
e f g
 
There are 16 hourglasses in arr. An hourglass sum is the sum of an hourglass' values.
Calculate the hourglass sum for every hourglass in arr, then print the maximum hourglass sum.
The array will always be 6x6.
*/

#include <bits/stdc++.h>

using namespace std;

// Complete the hourglassSum function below.
int hourglassSum(vector<vector<int>> &a) {
    int len = a[0].size();
    auto maxSum = LONG_MIN;
    int currSum{0};

    for (int row = 0; row < len; ++row) {
        if (row > len - 1 - 2) {
            break;
        }

        for (int col = 0; col < len; ++col) {
            if (col > len - 1 - 2) {
                continue;
            }

            currSum = a[row][col] + a[row][col + 1] + a[row][col + 2] +
                      a[row + 1][col + 1] +
                      a[row + 2][col] + a[row + 2][col + 1] + a[row + 2][col + 2];

            if (currSum > maxSum)
                maxSum = currSum;
        }
    }

    return maxSum;
}

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> arr(6);
    for (int i = 0; i < 6; i++) {
        arr[i].resize(6);

        for (int j = 0; j < 6; j++) {
            cin >> arr[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = hourglassSum(arr);

    fout << result << "\n";

    fout.close();

    return 0;
}
