/*
 * Created by Nick
 */
#include <string.h>
#include <stdio.h>
 // Required header definition, ignore it.
#ifndef BCA_BCA_H
#define BCA_BCA_H
#endif

/*
 * This header file contains functions for:
 * Even number checks
 * Read an array
 * Print an array
 * Smallest element in an array
 * Largest element in an array
 * Linear Search
 * Binary Search
 * Bubble Sort
 * Insertion Sort
 * Selection Sort
 * Check Leap Year
 * Print Prime numbers
 * Print Factorials of a number
 * Reverse a number
 * Check if a number is palindrome
 */

 // Set to 1 to enable debug logs (mess will be made)
 int DEBUG = 0;

 // Function to print debug message
 void printDebug(char debugMessage[]){
     if (DEBUG){
         printf("%s\n", debugMessage);
     }
 }

 // Swaps two number with each other
 void swap(int *a, int *b){
     int temp = *a;
     *a = *b;
     *b = temp;
     printDebug("Swap called");
 }

 // Function to read an array of n length
 void readArray(int array[], int arraySize){
     printf("Please enter %d elements: ", arraySize);
     for (int i = 0; i < arraySize; i++) {
        scanf("%d", &array[i]);
     }
 }

 // Prints an array of n length
 void printArray(int array[], int arraySize){
     for (int i = 0; i < arraySize; i++) {
         printf("Element %d: %d\n", i, array[i]);
     }
 }

 // Checks for even or odd, returns 1 on even 0 on odd
 int checkEvenOdd(int num){
     return num % 2 == 0;
 }

 // Returns the smallest element in an array on n size
 int smallestInArray(int array[], int arraySize){
     int smallest = array[0]; // Let
     for (int i = 0; i < arraySize; i++) {
         if (smallest > array[i]){
             smallest = array[i];
         }
     }
     return smallest;
 }

 // Returns the largest element in array
 int largestInArray(int array[], int arrSize){
     int largest = array[0]; // Let
     for (int i = 0; i < arrSize; i++) {
         if (largest < array[i]){
             largest = array[i];
         }
     }
     return largest;
 }

 /*
  * Searching the array
  */
 // Linear search
 void linearSearch(int numToFind, int array[], int arrSize){
     int found = 0;
     printf("Linear search for %d started.\n", numToFind);
     for (int i = 0; i < arrSize; ++i) {
         if (array[i] == numToFind){
             printf("Element %d found at index %d\n", numToFind, i);
             found = 1;
             break;
         }
     }
     if (!found){
         printf("Element not found in the array.\n");
     }
 }

 // Binary Searching
 void binarySearch(int numToFind, int array[], int arrSize){
     printf("Binary search for %d started.\n", numToFind);
     int lowerBound, upperBound, mid; // Declaration
     lowerBound = 0, upperBound = arrSize-1, mid = (lowerBound + upperBound) / 2; // Definition
     // Looping start
     while (lowerBound <= upperBound){
         if (numToFind < array[mid]){
             // Shift upper bound to mid -1
             upperBound = mid-1;
         }
         else if (numToFind > array[mid]){
             // Shift lower bound to mid + 1
             lowerBound = mid + 1;
         }
         else {
             // Element is found!
             printf("Element found at index: %d\n", mid);
             break;
         }

         mid = (lowerBound + upperBound) / 2;
     }

     // Now if the lowerBound > upperBound, it implies that the element is not found
     if (lowerBound > upperBound){
         printf("Element is not in the given arrayn\n");
     }
 }

 /*
  * Sorting the array
  */
// Bubble sort an array
 void bubbleSort(int array[], int arrSize){
     printf("Bubble sort on array has started for %d elem.\n", arrSize);
     for (int i = 0; i < arrSize - 1; i++) {
        for (int j = 0; j < arrSize - i - 1; j++) {
            if (array[j] > array[j+1]){
                swap(&array[j+1], &array[j]); // Shift largest number to right
            }
        }
     }
     printf("Bubble sort has completed.\n");
 }

 // Insertion sort
 void insertionSort(int array[], int arrSize){
     printf("Insertion sort on array has started for %d elem.\n", arrSize);
     int valueToInsert, insertAtIndex;
     for (int i = 1; i < arrSize; ++i) {
         valueToInsert = array[i];
         insertAtIndex = i - 1 ;
         while (insertAtIndex >= 0 && array[insertAtIndex] > valueToInsert){
             array[insertAtIndex + 1] = array[insertAtIndex];
             insertAtIndex--;
         }
         array[insertAtIndex + 1] = valueToInsert;
     }
     printf("Insertion sort completed.\n");
 }
 
 // Selection sort
 void selectionSort(int array[], int arrSize){
     printf("Selection sort on array has started for %d elem.\n", arrSize);
     int smallestIndex;
     for (int i = 0; i < arrSize - 1; ++i) {
         smallestIndex = i; // Let
         for (int j = i + 1; j < arrSize; ++j) {
             if (array[j] < array[smallestIndex]){
                 smallestIndex = j;
             }
         }
         swap(&array[smallestIndex], &array[i]);
     }
     printf("Selective sort complete.\n");
 }

 /*
  * General algorithms
  */
 // Check for leap year
 int isLeap(int year){
     if (year % 4 == 0){
         if (year % 100 == 0){
             return year % 400 == 0;
         }
         else {
             return 1;
         }
     }
     else {
         return 0;
     }
 }

 // Print prime numbers in a range
 void printPrime(int start, int upto){
     if (start < 2)
         start = 2;
     for (int i = start; i <= upto; i++){
         int composite = 0;
         for (int j = 1; j <= i ; ++j) {
             if (i % j == 0 && j != 1 && j != i){
                 composite++;
             }
         }
         if (!composite){
             printf("Number: %d\n", i);
         }
     }
 }

 // Print factorials of a number
 void printFactorial(int number){
     printf("Factorials for number %d are:\n", number);
     for (int i = 1; i <= number; ++i) {
         if (number % i == 0){
             // Number is a factorial
             printf("%d\n", i);
         }
     }
 }

 // Reverse a number
 int reverseNumber(int numToReverse){
     int reversed=0, remainder = 0;
     while (numToReverse != 0){
         remainder = numToReverse % 10;
         reversed = reversed * 10 + remainder;
         numToReverse /= 10;
     }
     return reversed;
 }

 // Check a integer for palindrome
 int isPalindrome(int num){
     return num == reverseNumber(num);
 }