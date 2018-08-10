/*
 * This header file contains the functions and logic that we will be using in the number conversion.
 * This code is an intellectual property of Nick a.k.a black.dragon74.
 * The reason I am using this header is, anyone can include and use it as a library in their program.
 * This program will cover conversions from decimal to all formats and vice-versa.
 * Read the comments thoroughly to understand how the code works.
 * I will be using both the for and while loops to do the conversions. Use the one that you like.
 * NOTE: You can only define functions and constants in a header file. You can't use a print statement here.
 */

// Requisites for a C header file (requires it to be defined for the compiler)
#ifndef NUMCONLOGIC //ifndef means, if not defined
#define NUMCONLOGIC //define is obvious
#endif //ending the if block (define specific if block)

// Includes go here
/*
 * Some general info about includes:
 * Includes are used to bring a library's functions into the file that you are writing the code in.
 * To make it simpler, including a file is like, copying entire content of that file and pasting it.
 * The only thing is, #include does so with just one line, pretty efficient, right?
 *
 * There is a difference between using the angular brackets and double quotes while using includes
 * Like, for including STDIO library we use: #include <stdio.h> but,
 * To include this header, we will use: #include "numconlogic.h" (we used double quotes instead of ang. brackets)
 * That is because, ang. brackets are used to include in-built headers while,
 * double quotes are used to include custom written headers, like this one.
 */
#include <math.h>

/*
 * Now, We will be creating a function that takes a decimal as an input and outputs the binary value.
 * We will first do that using a for loop and then again using a while loop
 *
 * Before we proceed, let's learn how we convert a decimal number to a binary number.
 * I will be using these steps in a small example below
 * Step one: We take a decimal number and divide it by 2
 * Step Two: We take a note of the remainder for the binary digit content.
 * Step Three: We take a note of the quotient from the step 2 and divide it again by 2.
 * Step Four: We keep repeating it until we get quotient = 0
 * Step Five: We read the reaminder in the reverse order to form the binary digit.
 *
 * Simple example. Let's take a number say, 13, note the steps (we will keep repeating until quotient = 0):
 * - Divide 13 by 2 => 13/2 (Step One), remainder 1 (Step Two), gives us quotient 6 (Step Three); Binary: 1
 * - Divide 6 by 2 => 6/2 (Step One), remainder 0 (Step Two), gives us quotient 3 (Step Three); Binary: 0
 * - Divide 3 by 2 => 3/2 (Step One), remainder 1 (Step Two), gives us quotient 1 (Step Three); Binary: 1
 * - Divide 1 by 2 => 1/2 (Step One), remainder 1 (Step Two), gives us quotient 0 (Step Three); Binary: 1
 * - Binary Digit is: 1101 (Step Five)
 *
 * Now let's use this logic and try to create a program that can do that automatically for us.
 */

 // Function type will be int as a binary contains numbers (1 and 0) that are basically decimals.
 // First, we will see how to do it using for loop.
 // int n in the parentheses (brackets) means this function requires user to input an integer
 // And, we are storing that input in the variable called numberToConvert
 // This is how functions work in general in the programming languages.
 int convertDecimalToBinaryUsingForLoop(int numberToConvert){
     // Now we need 3 variables: remainder, quotient and the binaryNumber(result)
     // Let's define them.
     int remainder, quotient, binaryNumber;

     // Now, we assign values to the variables
     quotient = numberToConvert; // Coz, initially, we start by diving the number.

     /*
      * Understanding the for loops.
      * For loops are used to loop between statements until a condition is met
      * like for (int i=1; i<=5; i++) { print i } will print 1, 2, 3, 4, 5 as,
      * the loop ran for 5 times, after that, value of i was equal to 5 and hence,
      * the loop was terminated. So, we will use the same logic to keep dividing the quotient until,
      * it becomes Zero (0)
      */

     for (int i=0; quotient > 0; i++){
         // The above line means,
         // Run loop for i, while the quotient is greater than zero, and keep icreasing the value,
         // of I on every iteration of the loop. We will be using I to keep a count of how many times,
         // The loop has ran.
         remainder = quotient % 2; // Mod operator returns remainder, Divided by 2 coz base of binary is 2
         binaryNumber += remainder * pow(10, i); // Pow function raises 10 to the power of i.
         quotient /= 2; // We divide the quotient again by 2. Loop will stop once quotient = 0.
     }

     return binaryNumber;
 }

 // Let's see the same using while loop, it is much more simple.
 int convertDecimalToBinaryUsingWhileLoop(int numberToConvert){
     int remainder, quotient, binaryNumber, i=1;
     quotient = numberToConvert;
     while (quotient != 0){
         remainder = quotient%2;
         binaryNumber += remainder * i;
         i *= 10;
         quotient /= 2;
     }

     return binaryNumber;
 }
