//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);
#define printAndExit(...) do { print(__VA_ARGS__); exit(0); } while (0);

bool isPrimeNaive(int n) {
    if (n == 1)
        return false;

    // we omitted 1 and the number, if it is divisible by anything else, it's not a prime
    for (int i = 2; i < n; ++i) {
        if (n % i == 0)
            return false;
    }

    return true;
}

bool isPrimeOpt1(int n) {
    if (n == 1)
        return false;

    for (int i = 2; i * i <= n; ++i) {  // Coz divisors are always in pairs
        if (n % i == 0)
            return false;
    }

    return true;
}

// Best worst case time complexity
bool isPrimeOpt2(int n) {
    if (n == 1)
        return false;

    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}

int main() {

    cout << isPrimeOpt2(101) << endl;

    return 0;
}

