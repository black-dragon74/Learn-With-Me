//
// Created by Nick on 11/21/19.
//
//  The addition and subtraction is implemented using operator overload.
//  The printing is acheived in fewer lines of code by `ostream` overload.
//  All overloaded operators are declared as friends coz they access the private members of the class.
//  The class is named `MyDate` as `Date` and `Dates` are predefined in `std` namespace.

#include <iostream>

using namespace std;

class MyDate
{
private:
    int day;
    int month;
public:
    MyDate(int d, int m)
    {
        day = d;
        month = m;
    }

    // Arithmetic perator overloads
    friend MyDate operator+ (const MyDate&, const MyDate&);
    friend MyDate operator- (const MyDate&, const MyDate&);

    // Stream operator overloads
    friend ostream & operator<< (ostream &out, const MyDate&);
};

MyDate operator+ (const MyDate &d1, const MyDate &d2)
{
    int dSum = d1.day + d2.day;
    int mSum = d1.month + d2.month;

    return { dSum, mSum };
}

MyDate operator- (const MyDate &d1, const MyDate &d2)
{
    int dSub = d1.day - d2.day;
    int mSub = d1.month - d2.month;

    return { dSub, mSub };
}

ostream& operator<< (ostream &out, const MyDate &d)
{
    out << d.month << " months, " << d.day << " days.";
    return out;
}

int main(int argc, char **argv)
{
    MyDate d1 = MyDate(15, 20);
    MyDate d2 = MyDate(4, 5);

    MyDate sumOfDates = d1 + d2;
    MyDate subOfDates = d1 - d2;

    cout << sumOfDates << endl;
    cout << subOfDates << endl;

    return 0;
}