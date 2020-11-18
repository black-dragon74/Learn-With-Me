/*
 There is a collection of input strings and a collection of query strings. 
 For each query string, determine how many times it occurs in the list of input strings. 
 Return an array of the results.
*/
#include <bits/stdc++.h>

using namespace std;

vector<int> matchingStrings(const vector<string> &strings, const vector<string> &queries) {
    vector<int> results;

    for (const auto &query : queries) {
        int count{0};

        for (const auto &string : strings) {
            if (string == query)
                count++;
        }

        results.emplace_back(count);
    }

    return results;
}

int main() {
    int strings_count;
    cin >> strings_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> strings(strings_count);

    for (int i = 0; i < strings_count; i++) {
        string strings_item;
        getline(cin, strings_item);

        strings[i] = strings_item;
    }

    int queries_count;
    cin >> queries_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        string queries_item;
        getline(cin, queries_item);

        queries[i] = queries_item;
    }

    vector<int> res = matchingStrings(strings, queries);

    for (int i = 0; i < res.size(); i++) {
        cout << res[i];

        if (i != res.size() - 1) {
            cout << "\n";
        }
    }

    return 0;
}
