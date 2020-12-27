//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);
#define printAndExit(...) do { print(__VA_ARGS__); exit(0); } while (0);

int numOfTrailingZerosInFactorialOf(int n) {
    int res{0};

    for (int i = 5; i <= n; i *= 5) {
        res += n / i;
    }

    return res;
}

int main() {
    print("Num of trailing zeros in factorial of 100 is: %d", numOfTrailingZerosInFactorialOf(100));

    return 0;
}

