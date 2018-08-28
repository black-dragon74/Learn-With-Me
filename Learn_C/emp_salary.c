// Created by Nick

#include <stdio.h>

int main(){
    // Variables declaration;
    int elvl;
    printf("Enter the employee level: ");
    scanf("%d", &elvl);

    // Custom vars required in this program
    float bpa, house, conv,  ent, tax, gross, salary;

    printf("Enter the Base Pay: ");
    scanf("%f", &bpa);

    // There are 4 emp levels. Set val accordingly.
    switch (elvl){
        case 1:
            conv = 1000;
            ent = 500;
            house = bpa*0.25;
            break;
        case 2:
            conv = 750;
            ent = 200;
            house = bpa*0.25;
            break;
        case 3:
            conv = 500;
            ent = 100;
            house = bpa*0.25;
            break;
        case 4:
            conv = 250;
            ent = 0;
            house = bpa*0.25;
            break;
        default:
            conv = 0;
            ent = 0;
            house = 0;
            break;
    }

    // We have the definitions set now all we need to do is calculate the salary
    gross = bpa + conv + ent + house;

    // If gross is between a range, tax
    if (gross <= 5000 && gross >= 4000){
        tax = .05;
    }
    else if (gross <= 3999 && gross >= 2000){
        tax = .03;
    }
    else {
        tax = 0;
    }

    // The final salary is gross - tax;
    salary = gross - (tax*gross);

    // Print the salary
    printf("Your salary rounded off is: %.2f", salary);
    // EOF
    return 1;
}
