//  Code is poetry.
//  Created by Nick aka black.dragon74
//
//  A program to sort a given array in ascending or descending order
//
//  User is presented with a choice to choose from the methods to use for the sorting
//

#include <stdio.h>

// Functions related to input/output
int selectSortingType(); // Sets the sorting method to use. Allowed: Bubble, Insertion and Selective sorting.
void readArray(int array[], int numElem); // Reads an array
void printArray(int array[], int arrSize); // Prints an array
void swap(int *a, int *b); // Swaps two numbers using pointers, requires variable's address as arguments.

// Logical functions, does the sorting.
void bubbleSort(int array[], int numElem);
void selectionSort(int array[], int numElem);
void insertionSort(int array[], int numElem);

// Main function, returns 0 on success.
int main(){
    
    // Declare the variables to be used in this program
    int array[100], i, j, num, method;
    
    // Ask user about number of elements in the array
    printf("Please enter the number of elements in the array: ");
    scanf("%d", &num);
    
    // Call the read array function
    readArray(array, num);
    
    // Set the sorting type
    method = selectSortingType();
    
    // Print array to sorting
    printf("\nArray to sort is:\n");
    printArray(array, num);
    printf("\n");
    
    // Now we have the array and the sorting type. Do the magic.
    switch (method) {
        case 0:
            bubbleSort(array, num);
            break;
            
        case 1:
            insertionSort(array, num);
            break;
            
        case 2:
            selectionSort(array, num);
            break;
            
        default:
            break;
    }
    
    // As the array is now sorted, print the sorted array
    printArray(array, num);
    
    // We're good guys, say thanks.
    printf("\nThanks for using this program - Nick\n");
    
    return 0;
}

// I/O functions begin here
int selectSortingType(){
    int method, count = 0;
    do {
        if (count >= 1){
            printf("INVALID INPUT. TRY AGAIN.\n");
        }
        printf("Please choose the sorting type.\n");
        printf("Enter 0 for Bubble, 1 for Insertion and 2 for Selective sorting: ");
        scanf("%d", &method);
        count++;
    }
    while (method < 0 || method > 2); // Limits input from 0 to 2
    return method;
}

void readArray(int array[], int numElem){
    for (int i = 0; i < numElem; i++){
        scanf("%d", &array[i]);
    }
}

void printArray(int array[], int arrSize){
    
    for (int i=0; i < arrSize; i++) {
        printf("Element %d of array: %d\n", i, array[i]);
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Logical functions begin here.
void bubbleSort(int array[], int numElem){
    
    int i, j;
    
    for (i = 0; i < numElem - 1; i++) {
        
        for (j = 0; j < numElem - i - 1; j++) {
            
            if (array[j] > array[j+1]) {
                swap(&array[j], &array[j+1]);
            }
        }
    }
    
    printf("Bubble sort complete.\n");
}

void insertionSort(int array[], int numElem){
    
    int i, j, temp;
    
    for (i = 1; i < numElem; i++) {
        
        temp = array[i];
        j = i - 1;
        
        while (j >= 0 && array[j] > temp){
            
            array[j+1] = array[j];
            j--;
            
        }
        array[j+1] = temp;
    }
    
    printf("Insertion sort complete.\n");
}

void selectionSort(int array[], int numElem){
    int i, j, smIndex;
    
    for (i = 0; i < numElem - 1 ; i++) {
        smIndex = i;
        
        for (j = i + 1; j < numElem; j++) {
            if (array[j] < array[smIndex]) {
                smIndex = j;
                swap(&array[smIndex], &array[i]);
            }
        }
    }
    
    printf("Selective sort complete.\n");
}
