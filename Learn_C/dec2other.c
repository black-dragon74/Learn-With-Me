/*
 * Code is poetry.
 * The code below is an intellectual property of Nick aka black.dragon74.
 * This programs converts a decimal input to binary, octal and hex forms.
 */

 // Ignore this part
#ifdef COMPILE_AS_HEADER
define AUTHOR = 'Nick';
define VERSION = 1.0;
define LICENSE = 'GNU GPL v3.0';
#endif

// Start the code
#include <stdio.h>

// Function to convert a decimal to binary
// Can also be done using for loop but that will be a bit complicated. Ask me if you need that method.
long long decToBin(int num){
    int quotient = num, remainder = 0, i = 1;
    long long binaryNumber;
    while (quotient != 0){
        remainder = quotient % 2; // Base of binary is 2
        binaryNumber += remainder * i;
        i *= 10;
        quotient /= 2;
    }
    return binaryNumber;
}

// Function to convert decimal to Octal, can also be done using for loop
long long decToOct(int num){
    int quotient, remainder, i = 1;
    long long octalNumber;
    quotient = num;
    while (quotient != 0){
        remainder = quotient % 8; // Base of octal number is 8
        octalNumber += remainder * i;
        i *= 10;
        quotient /= 8;
    }

    return octalNumber;
}

// Here we go!!!
int main(){
    printf("Programmed by Nick\n");
    int num;

    // Ask the user for the decimal number
    printf("Enter the number in decimal format: ");
    scanf("%d", &num);

    // Print decimal to binary
    printf("Number in binary form is: %lld\n", decToBin(num));

    // Print decimal to octal
    printf("Number in octal form is: %lld\n", decToOct(num));

    // Print decimal to hex (using easiest way)
    // If you really wanna know how to convert decimal to hex, you need to know ASCII first
    // Which, ain't that easy. Still, I am adding that method below for reference.
    printf("Number in hexadecimal form is: %X\n", num);
}

// TO BE USED AS A REFERENCE, DON'T THINK TOO MUCH ON THIS, IT IS A BIT TOO ADVANCED.
void convertDecToHex(int number){
    long quotient = number, remainder;
    int i, j = 0;
    char hexNumber[100]; // An array of 100 characters, Generally, hex doesn't exceed 100 chars.
    while (quotient != 0){
        remainder = quotient % 16; // Base of hex is 16
        if (remainder < 10) {
            hexNumber[j++] = 48 + remainder;
        }
        else {
            hexNumber[j++] = 55 + remainder;
        }

        quotient /= 16;
    }

    // Now let's print the array backwards
    for (i = j; i >= 0 ; i--) {
        printf("%c", hexNumber[i]);
    }

    /*
     * Explanation of 48 + remainder and 55 + remainder for those who need it:
     *
     * In ASCII encoding numbers 0 to 9 are from 48 to 57
     * And, Char A to F are from 65 to 70. See the exmaple below.
     *
     * 48 + 0 = 48 => '0' in ASCII
     * 48 + 1 = 49 => '1' in ASCII and so on.......
     * 48 + 9 = 57 => '9' in ASCII
     *
     * Likewise,
     * 55 + 10 = 65 => 'A' in ASCII
     * 55 + 11 = 66 => 'B' in ASCII and so on.......
     * 55 + 15 = 70 => 'F" in ASCII.
     *
     * And in case you are thinking what if the number is greater than 15, well,
     * It can't be as we are dividing by 16. Also, character encoding in C sucks.
     *
     * An easter egg (rotten one): Using Strings is a nightmare in C.
     *
     * So you read it all? Damn! You are gonna be one good programmer someday.
     */
}

