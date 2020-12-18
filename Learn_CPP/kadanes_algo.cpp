#include <bits/stdc++.h>

using namespace std;

#define print(...) do { fprintf(stdout, __VA_ARGS__); cout << endl; } while (0);

// Basic impl of kadane's algo, common in bitmap handling
int kadanesAlgoSimple(const vector<int> &array) {
    int max_so_far = INT_MIN, max_till_here = 0;

    for (const auto &num: array) {
        max_till_here += num;
        max_so_far = max(max_so_far, max_till_here);
        max_till_here = max(max_till_here, 0);
    }

    return max_so_far;
}

// Greedy, has faster runtime but won't work with -ve values
int kadanesAlgoGreedy(const vector<int> &array) {
    int max_so_far = INT_MIN, max_till_here = 0;

    for (const auto &num: array) {
        max_till_here += num;
        if (max_till_here < 0)
            max_till_here = 0;
        else if (max_till_here > max_so_far)
            max_so_far = max_till_here;
    }

    return max_so_far;
}

// DP approach to solve the above problem, requires no aux space and has fastest runtime.
int kadanesAlgoDP(const vector<int> &array) {
    int old_max = array[0], curr_max = old_max;

    for (int i = 1; i < array.size(); ++i) {
        old_max = max(old_max + array[i], array[i]);  // DP: You either choose or don't. Pick the best
        curr_max = max(curr_max, old_max);
    }

    return curr_max;
}

int main() {
    vector<int> array = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    print("%d", kadanesAlgoSimple(array));
    print("%d", kadanesAlgoGreedy(array));
    print("%d", kadanesAlgoDP(array));

    return 0;
}

