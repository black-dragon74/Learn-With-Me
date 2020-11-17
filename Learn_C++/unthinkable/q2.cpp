/*
 * Given a range from m to n(inclusive), find the sum of all the mega-primes
 * Mega primes are the numbers which have each individual digit as a prime too.
*/
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Check if the given number is prime
 * @param num Const reference to the number
 * @return bool True if number is prime else false
 */
bool isPrime(const int &num) {
    if (num < 2) { return false; }

    int timesDivided {0};
    for (int i = 1; i <= num; ++i) {
        if (num % i == 0)
            timesDivided++;
    }

    return timesDivided == 2;
}

/**
 * @brief Checks if a given number is megaprime
 * @param num Constant reference to the number
 * @return True if number is mega prime else false
 */
bool isMegaPrime(const int &num) {
    int mNum = num;
    int primeCount {0};
    int nIterations {0};

    while (mNum > 0) {
        int currNum = mNum % 10;
        if (isPrime(currNum))
            primeCount++;
        nIterations++;

        mNum /= 10;
    }

    return primeCount == nIterations;
}

int main(int argc, char **argv) {
    int from, to;
    cin >> from >> to;

    int sum {0};
    for (int i = from; i <= to; ++i) {
        if (isPrime(i) && isMegaPrime(i))
            sum += i;
    }

    cout << sum;
}
