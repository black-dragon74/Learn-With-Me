//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);
#define printAndExit(...) do { print(__VA_ARGS__); exit(0); } while (0);

int fact(int n) {
    if (n == 0)
        return 1;

    return n * fact(n - 1);
}

int main() {
    print("Factorial of 5 is: %d", fact(5));

    return 0;
}

