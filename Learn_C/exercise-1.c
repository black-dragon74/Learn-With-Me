//
// Created by Nick on 2019-06-12.
//

/**
 *  A speed coding exercise, for some friend of mine.

    Take an input K. Allow user to insert K numbers. If he insert anything other than a number, reject that input and instruct the user to input only the number.
    Once it is done,
    1. Print K numbers in sequence given by the user
    2. Print only the even numbers out of those K numbers
    3. Print odd numbers in sorted sequenc
    4. Print that sequence again, as given by the user(same as 1)
    5. Print the maximum and minimum number out of it.

 *  Thank you!
 **/
#include <stdio.h>

/** CUSTOM FUNCTIONS USED IN THIS PROGRAM, WRITTEN BY NICK **/
void swap(int *a, int *b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

void selectionSort(int *array, int size){
    for (int i = 0; i < size - 1; ++i) {
        int smIndex = i;
        for (int j = i+1; j < size; ++j) {
            if (array[j] < array[smIndex]){
                smIndex = j;
            }
        }
        swap(&array[smIndex], &array[i]);
    }
}

int smallestInArray(int array[], int arraySize){
    int smallest = array[0]; // Let
    for (int i = 0; i < arraySize; i++) {
        if (smallest > array[i]){
            smallest = array[i];
        }
    }
    return smallest;
}

int largestInArray(int array[], int arrSize){
    int largest = array[0]; // Let
    for (int i = 0; i < arrSize; i++) {
        if (largest < array[i]){
            largest = array[i];
        }
    }
    return largest;
}
/** END OF CUSTOM FUNCTIONS USED IN THIS PROGRAM, WRITTEN BY NICK **/

int main() {
    // Step: 1, ask the user to enter a number K
    int numberOfInput = -1;
    printf("Please enter a number K (size of input): ");
    scanf("%d", &numberOfInput);

    // Check that the user really enter a number. The logic is:
    // Scanf command will not read anything other than the integer data type
    if (numberOfInput == -1) {
        printf("You did not enter a valid number");
        return -1; // To exit
    }

    // Now we create an array that will hold the numbers that the user enters
    int userInput[numberOfInput];

    // Run a for loop for the number of times the user has asked for the input to be
    for (int i = 0; i < numberOfInput ; ++i) {
        // Now is the key part. We have to ask the user to enter an integer.
        // If the integer is not valid, we will keep on asking the user to enter a valid integer
        // The logic of input validation is, the scan function returns 1 when integer input is found
        // Sp, unless 1 is found, we keep on asking the user to enter the number
        int currentInput = -1;
        printf("Please enter the value for position %d: ", i + 1);
        while (scanf("%d", &currentInput) != 1) {
            printf("Please enter the value for position %d: ", i + 1);
            while (getchar() != '\n');  // This prevents the program from going into a scanf infinite loop
        }

        // If we move ahead from the above lines of code, it means we have successfully got an integer
        // We might as well add it to the array
        userInput[i] = currentInput;    // No rocket science here

    }

    // Okay. So now upon completion of the above for loop. We have all the numbers in the array
    // Now comes the easy part
    // 1. Print K number in sequence as entered by the user ( now you know why I chose an array? )
    printf("Numbers in sequence\n");
    for (int j = 0; j < numberOfInput; ++j) {
        printf("%d\n", userInput[j]);
    }

    // 2. Print only the even numbers
    printf("Only even numbers\n");
    for (int k = 0; k < numberOfInput; ++k) {
        if (userInput[k] % 2 == 0) {
            printf("%d\n", userInput[k]);
        }
    }

    // 3. Sort the array and print the odd numbers in sequence
    printf("Sorted odd numbers in sequence\n");
    selectionSort(userInput, numberOfInput);
    for (int l = 0; l < numberOfInput; ++l) {
        if (userInput[l] % 2 != 0) {
            printf("%d\n", userInput[l]);
        }
    }

    // 4. Print the same array again but this time it will be sorted
    printf("Printing the same array again (sorted)\n");
    for (int m = 0; m < numberOfInput; ++m) {
        printf("%d\n", userInput[m]);
    }

    // 5. Print the smallest and largest elements
    printf("Largest element in array is: %d\n", largestInArray(userInput, numberOfInput));
    printf("Smallest element in array is: %d\n", smallestInArray(userInput, numberOfInput));

    return 0;
}
