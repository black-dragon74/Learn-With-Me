#include <bits/stdc++.h>

using namespace std;

// Very simple, read the code and you'll get it why
// 2 + 2 + 2 is 6 and 2 * 3 is also 6. Got it??
void qAndR(int dividend, int divisor) {
    assert(dividend > 0 && divisor > 0);

    int quotient{0};
    while (dividend >= divisor) {
        dividend -= divisor;
        quotient++;
    }

    cout << "Quotient is: " << quotient << endl;
    cout << "Remainder is: " << dividend << endl;
}

int main(int argc, char **argv) {

    qAndR(8, 2);

    return 0;
}

