//
// Created by black.dragon74 on 4/23/18.
// Code is poetry.
//
#include <stdio.h>

/*
 * To print the factorials of large number like 100 you will have to use arrays
 * And then manipulate arrays with for loops.
 * That is beyond the scope of this tutorial and hence is not implemented.
 */

int main() {

    int num; // The number we want to find factorials of

    unsigned long long factorial = 1; // It will store the factorial. Initialization with val = 1 is necessary.

    printf("Enter the number you want factorials of: "); // Ask user for the input.
    scanf("%d", &num); // Pass the input to the address of num.

    // The factorials of the negative integers are non-existent.
    if (num == 0){
        printf("The factorial of %d does not exist!", num);
        return 0;
    }

    /*
     * I have used a for loop in the lines below to find factorial.
     * This is the simplest way to find a factorial. How it works?
     *
     * The for loop will keep incrementing the value of i until i = num
     * Suppose the number is 6 so the val of 1 per loop will be like: 1, 2, 3, 4, 5, 6
     * Now we will be multiplying the val of i to val of factorial. Like,
     * Per iteration of loop, the code will be in format of "factorial*i", like: { 1*1, 1*2, 2*3, 6*4, 24*5, 120*6 }
     */

    for (int i = 1; i <= num; i++) {

        factorial *= i; // Same as factorial = factorial * i;

        #ifdef DEBUG
                printf("Value of I is : %d\n", i);
        #endif

    }

    // Print the value to the user
    printf("\nFactorial of %d is %llu\n", num, factorial);

    // Program execution is successful!
    return 0;
}
