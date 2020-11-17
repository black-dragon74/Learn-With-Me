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

void numOfDuplicateWords(const string &sentence, vector<string> &vec, vector<int> &countVec) {
    char wordStore[UINT16_MAX][UINT16_MAX];        // Barbaric, IK, but that is what competitve programmig is.
    memset(wordStore, 0, sizeof(wordStore));    // Zeroing the array before use is needed on some systems

    int rowIterator = 0, colIterator = 0, i, length, count;
    for (i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] != ' ' && sentence[i] != '\0' && sentence[i] != '.') {
            wordStore[rowIterator][colIterator++] = static_cast<char>(tolower(sentence[i]));
        } else {
            wordStore[rowIterator++][colIterator] = '\0';
            colIterator = 0;
        }
    }
    // Add 1 to the length as arrays start from 0
    length = i + 1;

    for (i = 0; i < length; i++) {
        count = 1;
        for (int j = i + 1; j < length; j++) {
            if (!strcmp(wordStore[i], wordStore[j]) && strcmp(wordStore[j], "0") != 0) {
                count++;
                strcpy(wordStore[j], "0");
            }
        }

        if (count > 1) {
            auto repeatedWord = wordStore[i];

            if (strcmp(repeatedWord, "") != 0) {
                vec.emplace_back(repeatedWord);
                countVec.emplace_back(count);
            }
        }
    }
}

int main(int argc, char **argv) {
    string sample = "They don't know that we know they know we know.";
    vector<string> strVec;
    vector<int> countVec;

    numOfDuplicateWords(sample, strVec, countVec);

    for (int i = 0; i < strVec.size(); ++i) {
        cout << strVec[i] << " " << countVec[i] << " ";
    }
}
