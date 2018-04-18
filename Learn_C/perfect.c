// Create a program to find if a given number (in input) is a perfect number.

// A perfect number is a number whose factor's sums equals to the number itself/.

// Like, Factors if 6 are 1, 2 and 3 and 1+2+3=6

// Created by black.dragon74

// Code is poetry.

#include "stdio.h"

int main(){

    // Declare variables to store the program's runtime val
    int num; // Will store the user input number
    int sum = 0; // Will store the sum of the numbers (factors)
    int i = 1; // Will be used in the while loop for testing various expressions.
    // All the above vars may also be declared in a single line like, int num, sum=0, i=1;

    // Tell user to input something.
    printf("Please enter the number to check: ");

    // Scan the user input and store it in the variable "num"
    scanf("%d", &num);

    // Start the loop
    while (i < num){
        if (num%i == 0){
            // The number is a factor of the input
            sum+=i; // Same as "sum = sum + i;"
        }

        i++; // Increment the i for the loop.
    }

    // Now, logically, if the sum is equal to the number then the number is a perfect number
    // A simple if statement to check the above cond
    if (sum == num){
        printf("The number %d is a perfect number", num);
    }
    else{
        printf("The number %d is not a perfect number", num);
    }

    return 0;
}