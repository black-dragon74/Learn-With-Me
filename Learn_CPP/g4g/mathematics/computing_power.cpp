//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);
#define printAndExit(...) do { print(__VA_ARGS__); exit(0); } while (0);

int powNaive(int x, int n) {
    if (n == 0)
        return 1;

    int res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= x;
    }

    return res;
}

int powOptimized(int x, int n) {
    if (n == 0)
        return 1;

    int temp = powOptimized(x, n / 2);
    temp *= temp;   // Coz X^n can be written as [x ^ (n/2) + x ^ (n/2)] when n is even

    if (n % 2 == 0)
        return temp;
    else
        return temp * x;    // Coz X^n can be written as [x ^ (n-1) * x] when n is odd
}

int powBinaryExponentiation(int x, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1)    // Bit has value of 1
            res *= x;
        x *= x;      // Power keeps increasing by one as we go from LSB to MSB
        n >>= 1;  // Divide by 2
    }
    return res;
}

int main() {
    cout << powNaive(3, 5) << endl;
    cout << powOptimized(3, 5) << endl;
    cout << powBinaryExponentiation(3, 5) << endl;

    return 0;
}

