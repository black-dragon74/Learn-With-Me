//
// Created by black.dragon74 on 4/23/18.
// Code is poetry.
//

#include <stdio.h>

// A void method that simply prints an empty line using the escape character "\n"
void printEmptyLine(){

    printf("\n");

}

int main() {

    int* ptest; // A pointer that will point to the address of a variable of type int
    int test; // Normal var test with int data type.

    /*
     * We have assigned the pointer ptest to the address of the test variable.
     * We can't use pointers to alter values unless we bind it to some variable like in the line below.
     */

     ptest = &test; // The pointer ptest is now binded the the address of the variable test.

    /*
     * While dealing with pointers a pointer variable of a datatype can only be assigned to it's address
     * The address of a variable is given by a reference operator (&)
     * In the above declaration. ptest = test; would have given errors at the time of compilation.
     *
     * We can use a pointer to alter the variable's value at runtime.
     * The value of a pointer is given by a dereference operator (*)
     */


    // Now we will be printing a few statements to understand the pointers

    /*
     * We will now assign some value to the variable test like test = 10
     * We will be printing the values of the variables test and ptest.
     * We will also pe printing the address of the variables test and ptest.
     *
     * Now, you have to notice, the address of test and ptest must be same as ptest is a pointer to the address of test.
     * The value of the variable test and val of the pointer ptest will also be same as pointer is reading from the same address.
     */

    test = 10; // We have assigned some value to the variable test.

    printf("The value of the variable test is: %d\n", test);
    printf("The address of the variable test is: %u\n", &test);

    printEmptyLine();

    printf("The value of pointer ptest is: %d\n", *ptest);
    printf("The address of pointer ptest is: %u\n", ptest);

    printEmptyLine();

    /*
     * Now we will alter the value of pointer ptest using dereference operator (*)
     * You will notice that the value of the variable test will also change as we modified it's value in the memory address.
     */

    *ptest = 20; // It is same as test = 20; Note: *ptest will return value not the address

    printf("The value of the variable test is: %d\n", test);
    printf("The address of the variable test is: %u\n", &test);

    printEmptyLine();

    printf("The value of pointer ptest is: %d\n", *ptest);
    printf("The address of pointer ptest is: %u\n", ptest);

    printEmptyLine();

    /*
     * To recap:
     * "&" also known as the reference operator is used to get the mem address of a variable.
     * "*" also known as the dereference operator is used to get a value from the pointer's mem address.
     *
     * A pointer points to the address of a variable and can only be defined to it like:
     * int* someint; someint = &someothervar.
     * In the above line, a pointer someint is created with datatype int. It is then assigned to the address(&) of some other var.
     *
     * When dereference operator is used on a pointer it will return the value of the variable to which pointer is assigned.
     * Like, printf("Value of someint is: %d", *someint); will print the value of "someothervar" as someint = value of "someothervar"
     */

    // Return 0 if the execution is successful
    return 0;

}
