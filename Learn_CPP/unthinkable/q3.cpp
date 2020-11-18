//
//  Code is poetry
//  Created by Nick aka black-dragon74 on 17-11-2020
//

/*
 * Given a sentence, find the number of duplicate words which have vowels in ascending order
*/
#include <bits/stdc++.h>

using namespace std;

bool isVowel(char &s) {
    auto cCopy = toupper(s);

    return (cCopy == 'A' || cCopy == 'E' || cCopy == 'I' || cCopy == 'O' || cCopy == 'U');
}

bool vowelsInAscending(const string &word) {
    // This will contain the previously found vowel
    // But, we use an ASCII value one less than alphabet `A` as a starting point
    char prevVowel = static_cast<int>('A') - 1;

    for (auto w: word) {
        if (isVowel(w)) {
            if (w < prevVowel)
                return false;
            else
                prevVowel = w;
        }
    }
    return true;
}

void numOfDuplicateWords(const string &sentence, map<string, int> &dict) {
    istringstream stringStream(sentence);

    do {
        string currWord;
        stringStream >> currWord;
        transform(currWord.begin(), currWord.end(), currWord.begin(), ::tolower);

        if (dict.find(currWord) == dict.end()) {
            dict.insert({currWord, 1});
        } else {
            dict[currWord]++;
        }

    } while (stringStream);
}

int main(int argc, char **argv) {
    string sample = "They don't know that we know they know we know.";
    map<string, int> dict;

    numOfDuplicateWords(sample, dict);

    for (const auto &elem: dict) {
        if (vowelsInAscending(elem.first) && elem.second > 1) {
            cout << elem.first << " " << elem.second << " " << endl;
        }
    }
}
