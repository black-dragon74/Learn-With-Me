//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);
#define printAndExit(...) do { print(__VA_ARGS__); exit(0); } while (0);

int countNoOfDigits(int n) {
    int count{0};
    while (n) {
        count++;
        n /= 10;
    }

    return count;
}

int main() {
    int a = 1232456789;

    print("Number of digits in %d is %d", a, countNoOfDigits(a));

    return 0;
}

