//
// Created by Nick on 11/21/19.
//
//  References(&) have been used instead of pointers as using pointers would lead to more un-necessary code.
//  Underlying working is same, references are de-referenced pointers with pointer arithmetics disabled.

#include <iostream>

using namespace std;

class Test
{
private:
    int a;
public:
    explicit Test(int x)
    {
        a = x;
    }

    void printElems()
    {
        cout << "A: " << a << endl;
    }
    
    // Only so it could access the private members
    friend void swap(Test&, Test&);
};

void swap(Test &t1, Test &t2)
{
    int temp = t1.a;
    t1.a = t2.a;
    t2.a = temp;
}

int main(int argc, char **argv)
{
    Test t1 = Test(90);
    Test t2 = Test(34);

    swap(t1, t2);

    t1.printElems();
    t2.printElems();

    return 0;
}