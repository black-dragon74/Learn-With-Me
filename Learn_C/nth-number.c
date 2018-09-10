// Code is poetry
// Created by black.dragon74

#include <stdio.h>

int main(){
    
    // Define an integer
    int a = 12345;
    
    /**
     * a % 10 will always print last number.
     * (a%100)/10 will print second last.
     * (a%1000)/100 will print third last.
     * (a%10000)/1000 will print fourth last.
     * (a%100000)/10000 will print 1st number.
     **/
    
    int toPrint = (a%100000)/10000; // will print the first number
    
    printf("The selected number is: %d\n", toPrint);
    
    return 1;
}
