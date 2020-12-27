//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);
#define printAndExit(...) do { print(__VA_ARGS__); exit(0); } while (0);

// O(n * sqrt(n))
void sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);

    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = 2 * i; j <= n; j += i) {   // Traverse all the multiples of i upto n
                isPrime[j] = false;     // Coz it will be divided by i and then it won't be a prime
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (isPrime[i])
            cout << i << " ";
    }
    cout << endl;
}

// O(n log(log(n)))
void sieveOfEratosthenesEfficient(int n) {
    vector<bool> isPrime(n + 1, true);

    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            cout << i << " ";
            for (int j = i * i; j <= n; j += i) {   // Traverse only the multiples that haven't been traversed b4.
                isPrime[j] = false;
            }
        }
    }
}

int main() {
    sieveOfEratosthenes(100);
    sieveOfEratosthenesEfficient(100);

    return 0;
}

