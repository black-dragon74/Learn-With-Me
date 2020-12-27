//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);
#define printAndExit(...) do { print(__VA_ARGS__); exit(0); } while (0);

int gcdNaive(int a, int b) {
    int ans = min(a, b);

    for (int i = ans; i >= 1; --i) {
        if (a % i == 0 && b % i == 0)
            return i;
    }

    return ans;
}

// GCD(a,b) = GCD(a-b, b) when b is smaller than a
int gcdEucledian(int a, int b) {
    while (a != b) {
        if (a > b)
            a -= b;
        else
            b -= a;
    }

    return a;   // or b, whichever you want
}

int gcdEucledianOptimized(int a, int b) {
    if (b == 0)
        return a;

    return gcdEucledianOptimized(b, a % b);
}

int main() {
    cout << gcdEucledianOptimized(10, 15);

    return 0;
}

