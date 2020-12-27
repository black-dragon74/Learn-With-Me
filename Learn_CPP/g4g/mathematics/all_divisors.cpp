//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);
#define printAndExit(...) do { print(__VA_ARGS__); exit(0); } while (0);

// Best time complexity
void printAllDivisorsInAscendingOrder(int n) {
    int i;
    for (i = 1; i * i <= n; i++) {  // Coz divisors appear in pairs
        if (n % i == 0) {
            cout << i << " ";
        }
    }

    for (; i >= 1; --i) {
        if (n % i == 0) {
            cout << n / i << " ";   // Coz we already printed the other pair above
        }
    }

    cout << endl;
}

int main() {

    printAllDivisorsInAscendingOrder(15);

    return 0;
}

