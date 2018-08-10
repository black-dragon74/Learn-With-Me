//
// Created by Nick on 8/10/18.
// This simple program just raises a integer to the given power and prints the result.
// Compile using any compiler of your choice, I use GCC
//
#include <stdio.h> // Note: Header "conio.h" is removed in recent versions of the C language.

/**
 * @var result, stores the result of the program and prints it in the end.
 * @var unum, stores the number that is to be raised to the power.
 * @var upow, stores the number of times a number is to be raised.
 */
int result = 0, unum, upow;

// Function to raise a given number to the power
// Function to raise a number to the power, bole toh, logic
int raiseToPower(int num, int pow){
    /* @var tans, stores the temporary answer for this loop */
    int tans=1;
    // For loop to iterate the number of times a number is to be raised.
    for (int i = 1; i <= pow; ++i) {
        tans *= num;
    }
    return tans;
}

// Off we go!
void main(){
    // Ask the number
    printf("Enter the number: ");
    scanf("%d", &unum);

    // Ask the power
    printf("Enter the power: ");
    scanf("%d", &upow);

    // Call the function with the params and store the result in a variable
    result = raiseToPower(unum, upow);

    // Answer and exit
    printf("Num raised to power is: %d\n", result);
}
