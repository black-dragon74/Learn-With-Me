//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);
#define printAndExit(...) do { print(__VA_ARGS__); exit(0); } while (0);

int _gcd(int a, int b) {
    if (b == 0)
        return a;

    return _gcd(b, a % b);
}

int lcmNaive(int a, int b) {
    int res = max(a, b);

    while (true) {
        if (res % a == 0 && res % b == 0)
            break;

        res++;
    }

    return res;
}

int lcm(int a, int b) {
    // Coz, a * b = gcd * lcm
    // Hence, LCM = a * b / gcd
    return (a * b) / _gcd(a, b);
}

int main() {
    cout << lcm(4, 6) << endl;
    cout << lcmNaive(4, 6) << endl;

    return 0;
}

