//
// Created by Nick on 11/21/20.
//
// This is a solution of all the questions asked in the untinkable interview (round-1). Please read the comments.
// There were 2 practical questions and 4 verbal questions.
// I implemented both practical question in O(n) and O(nLogn) time complexity respectively.
// Upon review, he asked me to optimize my code to do the same but in less time or space complexity.
// The solutions will have two variant A and B where B is the optimized approach.
// The verbal questions will be listed for ref, without answers ofc. (Google!)
//
// Please note, this file won't compile and run due to missing stubs and is for reference only.
//

#include <bits/stdc++.h>

using namespace std;

// This is there for an idea of the Node's structure
struct Node {
    int data;
    Node *next;
};

//MARK:- Question 1 begin.
// Complete the function below to detect the loop in a singly linked list.
// A linked list is said to contain a loop if any node is visited more than once while traversing the list.
// Implementation A to solve the problem in O(n) time and O(n) space complexity.
bool hasLoopA(Node *head) {
    // Get a local reference of the head.
    auto *ptr = head;

    // We will use a set to store the addresses of each node.
    // TLDR; Sets can't have duplicate values
    unordered_set<Node *> mySet;

    // Now iterate over each node, means while ptr != NULL
    while (ptr) {
        // If element is already present in set, means that address has been found earlier, right?
        // Return true
        if (mySet.find(ptr) != mySet.end())
            return true;

        // Otherwise, insert the address in our set and increment the ptr
        mySet.insert(ptr);
        ptr = ptr->next;
    }

    // If we reach here, means all the addresses were unique, in that case, there is no cycle.
    // Return false.
    return false;
}

// Implementation B to solve the same problem in O(n) time and O(1) space complexity.
// The space complexity is optimized in this approach and hence it is more efficient.
bool hasLoopB(Node *head) {
    auto *ptr = head;
    auto *slowPtr = head;

    // Increment slowPtr by one and ptr by two, as long as both of them are not null.
    // By doing that, fast will be one ahead of slow, right?
    // And if at any point of time, fast and slow are pointing to same address, oh boy, are we in a loop?
    // Enough talking, let's get to it then.
    while (ptr && slowPtr) {
        ptr = ptr->next;    // Increment 1 of 2
        if (ptr) {
            ptr = ptr->next;    // Increment 2 of 2
            slowPtr = slowPtr->next;    // Increment 1 of 1
        }

        // Both are point to the same node, which should not happen, right?
        // This is an indication of a cycle or loop.
        if (ptr == slowPtr)
            return true;
    }

    // Otherwise, we reached end of the list, and didn't face no fucking cycle
    // Victory
    return false;
}
//MARK:- End question 1

//MARK:- Question 2 begin
// Complete the function below to find if the two given strings are anagrams
// An anagram of a string is another string that contains the same characters,
// Only the order of characters can be different. Like, iceman and cinema.
// Note how the characters are the same, but arrangment is not.

// Implementation A to solve the problem in O(nLogn) time complexity.
bool isAnagramA(const string &s1, const string &s2) {
    // Okay, think now. What could be the condition for two words to be anagrams.
    // A: They should must be of the same length, right?
    // B: All the letters contained in word 1 must be also there in word 2. Correct?
    // Right then, let's handle part A first.

    // Compare the lengths
    if (s1.length() != s2.length())
        return false;   // Never possible

    // Now, compare each letter but how can we do that.
    // We can't iterate over each element as their order might not be the same, right?
    // So, what we can do, is we sort both the arrays and then compare each element.
    // That way, if all elements are the same, an anagram can be formed else not.
    for (int i = 0; i < s1.length(); ++i) {
        if (s1[i] != s2[i])
            return false;
    }

    // If we reached here, it means all the elements were same
    // Say hello to an anagram, return true.
    return true;
}

// Implementation B to solve the same problem in O(n) time and O(1) space complexity.
// Both the time and space complexities are minimized in this approach and hence it is more efficient.
bool isAnagramB(const string &str1, const string &str2) {
    // First condition is still the same as above approach.
    // If length is not equal, forming an anagram is never possible.
    if (str1.length() != str2.length())
        return false;

    // Otherwise, we iterate over each letter in both the words
    // Add ASCII value of the letter to a count variable.
    // In the second step, we will be subtracting the ASCII value of the letter from the count variable.
    // Now if count = 0, it means, we subtracted whatever we added, right?
    // And if it is not zero it means, there is a mismatch of letters, hence an anagram cannot be formed. Correct?
    // Let's get to it.

    int count {0};

    // Add to count
    for (char i : str1) {
        count += i;
    }

    // Subtract from count
    for (char i : str2) {
        count -= i;
    }

    // If count is 0, return true else false. Why you may ask?
    // I just explained above.
    return count == 0;
}
//MARK:- End question 2

//
//  Now the comments below contain the verbal questions asked. Google for answers.
//

/*
 * 1: What is a semaphore.
 * 2: What is ROG-HID (LOL, it is something created by me)
 * 3: What are extraction and insertion operators in C++ and why are the called that.
 * 4: What is a system software and an application software
 */

//
//  Thank you! Have a good day, night, whatever!
//

