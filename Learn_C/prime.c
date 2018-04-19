//
// Created by black.dragon74 on 4/19/18.
// Code is poetry.
//


#include <stdio.h>

// Prime numbers are the numbers that are divisible by 1 and the number itself.

int input, count=0;

int main(){

    printf("Enter the max number of the range: ");
    scanf("%d", &input);

    // Create a for loop that will print all the numbers in an input's range
    for (int i=1; i <= input; i++){

        // Now on each iteration of the loop the number will increment by one and we will get values from 1 to &input.

        count = 0;

        for (int j=2; j <= i/2; j++){

            if (i%j == 0){
                // Not a prime
                count++;
                break;
            }

        }

        if (count == 0 && i != 1){
            // A prime number
            printf("%d\n", i);
        }

    }
}