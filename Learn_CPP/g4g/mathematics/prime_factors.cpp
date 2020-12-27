//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);
#define printAndExit(...) do { print(__VA_ARGS__); exit(0); } while (0);

bool isPrime(int n) {
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

void printPrimeFactors(int n) {
    if (n == 1)
        return;

    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            cout << i << " ";
            n /= i;
        }
    }

    if (n > 1)
        cout << n;
    cout << endl;
}

void printPrimeFactorsOptimized(int n) {
    if (n == 1)
        return;

    while (n % 2 == 0) {
        cout << 2 << " ";
        n /= 2;
    }

    while (n % 3 == 0) {
        cout << 3 << " ";
        n /= 3;
    }

    for (int i = 5; i * i <= n; i += 6) {
        while (n % i == 0) {
            cout << i << " ";
            n /= i;
        }

        while (n % (i + 2) == 0) {
            cout << (i + 2) << " ";
            n /= (i + 2);
        }
    }

    if (n > 3)
        cout << n;

    cout << endl;
}

int main() {
    printPrimeFactors(450);
    printPrimeFactorsOptimized(450);

    return 0;
}

