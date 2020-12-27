//
//  Created by Nick aka black-dragon74
//

#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);
#define printAndExit(...) do { print(__VA_ARGS__); exit(0); } while (0);

int rev(int n) {
    int reverse = 0;
    while (n) {
        reverse = reverse * 10 + n % 10;
        n /= 10;
    }

    return reverse;
}

bool isPalindrome(int n) { return n == rev(n); }

int main() {
    int n = 121121;

    cout << isPalindrome(n) << endl;

    return 0;
}

