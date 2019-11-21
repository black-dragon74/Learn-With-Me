//
// Created by Nick on 11/21/19.
//
//  Variadics have been used to calculate the average of the function
//  I do not expect any amongst you to even try to understand CPP Variadic Templates.
//  Just copy as is.

#include <iostream>

using namespace std;

class Employee
{
public:
    int emp_no;
    string emp_name;
    int age;
    string dob;

    Employee(int no, string name, int ag, string da)
    {
        emp_no = no;
        emp_name = move(name);  // As the string is passed by value, this is done to prevent unnecessary copies of it
        age = ag;
        dob = move(da);
    }
};

class Technical : public Employee
{
public:
    int experience;
    int salary;
    int bonus;

    Technical(int no, string name, int ag, string da, int exp, int sal, int b) : Employee(no, std::move(name), ag, std::move(da))
    {
        experience = exp;
        salary = sal;
        bonus = b;
    }

    Technical operator+ (const Technical &obj2)
    {
        int ss = (*this).salary + obj2.salary;
        int bs = (*this).bonus + obj2.bonus;
        return {1, "", 1, "", 1, ss, bs };
    }
};

class NonTechnical : public Employee
{
public:
    int experience;
    int salary;
    int bonus;

    NonTechnical(int no, string name, int ag, string da, int exp, int sal, int b) : Employee(no, std::move(name), ag, std::move(da))
    {
        experience = exp;
        salary = sal;
        bonus = b;
    }

    NonTechnical operator+ (const NonTechnical &obj2)
    {
        int ss = (*this).salary + obj2.salary;
        int bs = (*this).bonus + obj2.bonus;
        return {1, "", 1, "", 1, ss, bs };
    }
};

template <typename T>
T SalaryOfEmps(T single)
{
    return single;
}

template <typename T, typename... Args>
T SalaryOfEmps(T first, Args... args)
{
    return first + SalaryOfEmps(args...);
}

int main(int argc, char **argv)
{
    Technical t1 = Technical(1, "tech 1", 18, "07-JUL-2000", 1, 5000, 1000);
    Technical t2 = Technical(1, "tech 2", 18, "07-JUL-2000", 1, 5000, 1000);


    NonTechnical nt1 = NonTechnical(2, "non tech 1", 21, "07-SEP-1998", 1, 1000, 2000);
    NonTechnical nt2 = NonTechnical(2, "non tech 2", 21, "07-SEP-1998", 1, 1000, 2000);
    NonTechnical nt3 = NonTechnical(2, "non tech 3", 21, "07-SEP-1998", 1, 1000, 2000);

    auto techEmps = SalaryOfEmps(t1, t2);
    auto nonTechEmps = SalaryOfEmps(nt1, nt2, nt3);

    int techSal = (techEmps.salary + techEmps.bonus) / 2;
    int nonTechSal = (nonTechEmps.salary + nonTechEmps.bonus) / 3;

    cout << "Mean of tech employee salaries: " << techSal << endl;
    cout << "Mean of nontech employee salaries: " << nonTechSal << endl;

    return 0;
}