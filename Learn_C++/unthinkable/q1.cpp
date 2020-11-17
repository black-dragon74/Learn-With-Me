//
//  Code is poetry
//  Created by Nick aka black-dragon74 on 17-11-2020  
//

/*
 * Given an expression with only ‘}’ and ‘{‘. The expression may not be balanced.
 * Find minimum number of bracket reversals to make the expression balanced.
*/
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Get the minimum reversals needed to make the expression balanced
 * @param expr Const reference to the expression, using reference instead of a regular string to prevent copying
 * @return int Min reversals needed
 */
int getRevCount(const string &expr) {
    auto sLen = expr.length();

    // if number of brackets are not equal, bail
    if (sLen % 2)
        return -1;

    // Reduce the expr to only contain unbalanced braces
    stack<char> exprStack;
    for (auto s: expr) {
        if (s == '}' && !exprStack.empty()) {
            if (exprStack.top() == '{')
                exprStack.pop();
            else
                exprStack.push(s);
        } else {
            exprStack.push(s);
        }
    }

    int unbalancedCount = exprStack.size();

    // Count opening braces in the stack
    int openBraces {0};
    while (!exprStack.empty() && exprStack.top() == '{') {
        openBraces++;
        exprStack.pop();
    }

    return (unbalancedCount / 2 + openBraces % 2);
}

int main(int argc, char **argv) {
    string expr;
    cin >> expr;

    auto count = getRevCount(expr);

    if (count == -1) {
        cout << "Can't be done";
    } else {
        cout << count;
    }
}
