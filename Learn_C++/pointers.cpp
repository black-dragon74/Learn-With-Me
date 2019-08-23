//
//  Created by Nick on 23-08-2019
//

//
//  The code below assumes you have a proper understanding of how functions work in C and C++
//  The below concept applies both for C and C++
//  Please read this file with a calm and peaceful mind. If you opened this up casually. Please close and come back later.
//  The concepts are a bit advanced and might seem confusing to the reader.
//  Take time, read carefully and most important, practice on your own.
//  Pointers are a very important aspect of C and C++. These are the sole reason why C and C++ are such lightning fast performing languages.
//
//  Shall you choose to stay, May the force be with you!
//

#include <iostream>

using namespace std;

/** Please ignore the declarations for now, come back when asked. read from line: 64 **/
void Function1()
{
    cout << "I am function 1." << endl;
}

void Function2(int a)
{
    cout << "I am function 2. Argument passed to me is: " << a << endl;
}

void callback(  void (*functionToCall)()    ) // To understand the arg, see line 99
{
    functionToCall();   // We are calling the function passed as a parameter.
}

void callbackWithParams(    void (*functionToCall)(int), int a  )   // To understand the arg, see line 116
{
    // The function accepts two args, one is a function pointer to a function with void return type. Other is an int named 'a'
    // We have added a second arg to the function as the latter is required by our passed function.
    functionToCall(a);
}

int CustomSortingFunction(const void *arg1, const void *arg2)   // Args are in the same order and type as needed by the qsort function.
{
    // As void pointer cannot point to any data. We are type casting it explicitly to an integer pointer and then de-referencing to get the value.
    int num1 = *(int*)arg1;
    int num2 = *(int*)arg2;

    if (num1 < num2)
    {
        return -1;
    }
    else if (num1 ==  num2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
/** End function declarations **/

//
//  We will be taking a look at different kind of pointers like, const pointers, pointers to const, function pointers and callbacks
//  Please make it a habit to add asterisk(*) with the variable name rather than the data type keyword, like:
//  "int *p" is correct way not "int* p", the latter creates confusion and is discouraged.
//

int main(int argc, char **argv)
{
    // Let's first look at the normal pointers, i.e. pointers to primitive data types
    int a = 5;  // Self explanatory
    int *pointerToA = &a;   // Pointer to int data type. Can be assigned to address of any variable with data type int.

    // Now we will look at the de-referencing, i.e. Extracting the data contained at the address of the pointer.
    // We use an asterisk symbol before the pointer variable name to get the actual data at that address.
    // Please remember that using asterisk after a data type but before the pointer variable name is declaring the pointer.
    // If you write some value after the assignment operator, that will be considered as the address, not the value.
    // Like, int *pointer = 123; Here 123 is not raw value but the raw address in the memory. We generally pass address by using '&' before a var name.
    // De-referencing only happens when you use the asterisk symbol without any data type before it. Like, '*pointer' will return raw value.
    // Note: Using just the variable name will return the address that is assigned to that pointer.
    cout << "Value stored in pointerToA is: " << *pointerToA << endl;

    // You can alter the data by de-referencing a pointer followed by an assignment operator, like:
    *pointerToA = 124;  // Here, the value will be changed from 5 to 124
    cout << "Value store in pointerToA after de-referencing and updating is: " << *pointerToA << endl;

    //
    // Now we will take a look at somewhat confusing concept of "Pointer to constant vs Constant pointer"
    // Please read carefully and try it yourself to understand it thoroughly.
    //

    //
    // Let's look at Pointers to Constant first. Let's declare a constant
    //
    const int b = 10;   // B is a constant of int data type, meaning, it's value can never be altered and will always remain the same.

    // Take a close look at the declaration below, let's forget the const written before int *pointerToB for a moment.
    // We can tell that pointerToB is a pointer to int data type with name B, right? Now let's bring back the 'const' keyword.
    // Best way to understand it is to read inside out. pointer to B is a pointer to 'const int' data type.
    // Meaning, it can only point to a variable which is a constant of integer data type. This however does not mean that the pointer itself is constant.
    // We can alter the value of the pointer but not of the variable that it is pointing to
    const int *pointerToB = &b;

    // To prove that the pointer itself is not constant:
    pointerToB++;   // Correct, reassigning pointer's address is allowed.
    //*pointerToB = 55;   // Incorrect, reassigning value is disallowed as pointerToB point to const int data type.

    // Summary: We can change value of the pointer's address but not of the variable that it is pointing to with 'const int *pointer' declaration type.

    //
    //  Now let's take a look at constant pointers.
    //

    // The logic is very simple here, they are pointers which are constant. Meaning, you cannot change address of the pointer once assigned.
    // They however will allow changing the value to whatever data they are pointing to.
    // Now let's declare a constant pointer
    int c = 23;
    int *const constantPointerToC = &c; // Take a note of how the keywords have exchanged places and also asterisk before the const keyword.
    // Above statement means, constantPointerToC is a constant pointer to integer data type. Not getting it? Read everything from Line No 33 again.

    // Remember we cannot reassign address but change the value of the variable they are pointing to. Let's prove that:
    *constantPointerToC = 25; // Correct, changing value is allowed.
    //constantPointerToC++;   // Incorrect, reassigning the pointer is disallowed.

    //
    //  Alright. Now that we have them out of the way. Kudos to you. Take a break. Come back later. We will then look at pointer to functions.
    //

    //
    //  Pointers to functions can be confusing to look at and read at first but follow along.
    //  They are used mainly for creating callback functions. Meaning, we can pass function as a parameter to some other function and,
    //  That function will then call the passed function. Fucked up, right? Well, this is used by many functions in the C and C++ language.
    //

    // Scroll below and you will see there is a function of return type void named Function1. We will create a pointer to that and call the function using that.
    void (*pointerToFunc1)() = Function1;   // Notice how the asterisk symbol is inside parentheses. Removing them will create a pointer to Void data type.
    // To understand this, let's first see how we create a normal function. void func() { ... }. Right?
    // All we did was, write pointer name in parentheses, add an asterisk before the name and replace curly braces with "= functionAddress"
    // Note: I did not add an ampersand before the function name as a function name when used standalone returns the address. Like the case with arrays.

    // Now let's call the function using the newly created pointer.
    pointerToFunc1();

    //
    //  What if the function that we are pointing to has arguments or parameters required? Well, function 2 exists for that. Scroll to top and take a look.
    //  Now let's create a pointer to point to our nice little function2
    //
    void (*pointerToFunction2)(int) = Function2;    // Compare this and line no 94
    // Only difference is instead of just the parens, I have also added the data type in it.
    // Note: I have only written the type of data that the function is accepting. Not the variable name. Like: "int" not "int a"
    // Because, the arg is not needed by the pointer but the function. Now let's call that function.
    pointerToFunction2(25);

    //
    //  Good job you! Time for a break.
    //  Come back later and then we will understand the concept of callback and also see why they are important.
    //

    // Scroll to top and take a look at line number 19. I have created a callback function that accepts any function with void return type and no args.
    // If you remember, our function1 was of the same type. It returned void and took not args as params.
    callback(Function1);    // We are passing Function1 as a param to callback function. That is then calling the Function1. Hence, callback.

    // Now we will take a look at callback with params. Scroll to top and take a look at line no: 24
    // There is a callback function which accepts two args, a function with void return type and a int as param. And, a integer data.
    // If you remember, Function2 was one such function.
    callbackWithParams(Function2, 19);

    //
    //  That's all. You now have a solid understanding of pointers and even the callbacks. Want to see why callbacks are important? Go below.
    //  Be warned, the lines of code below are a bit advanced and might mess you up. You are free to leave. But can proceed if you choose so.
    //  Scroll to top and take a look at the function defined at line: 31
    //

    int unsortedArray[10] = { 29, 28, 1, 99, 34, 12, 90, 50, 20, 74 };

    // Now we will call qsort with our custom sorting function as a parameter.
    qsort(unsortedArray, (sizeof(unsortedArray) / sizeof(unsortedArray[0])), sizeof(int), CustomSortingFunction);

    for (int n : unsortedArray) // This is a new range based loop in c++11. read as "for n in unsortedArray; print n"
    {
        cout << n << endl;  // N will have successive values from unsortedArray on each iteration.
    }

    // You saw how the above array is sorted. Using our custom function.


    // That's all. See ya next time ;)

    return 1;
}
// EOF

