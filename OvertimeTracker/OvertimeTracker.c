//******************************************************* 
// 
// Homework: 3 - Conditionals
// 
// Name: Jack Cacela
// 
// Class: C Programming, <Spring 2024>
// 
// Date: <2/05/2024>
// 
// Description: Program which determines overtime hours and gross pay,
// and outputs are sent to standard output (the screen).
// 
// 
//******************************************************** 

#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define STD_HOURS 40.0  // constant for pre-overtime hours
#define empNum 5        // constant for number of employees

int main ( )
{
    int clockNumber;        // employee clock number
    int idx;                // index for the "for loop" definition
    float overtimeHours;    // captures overtime hours
    float grossPay;         // gross pay for week (wage * hours)
    float hours;            // number of hours worked per week
    float wageRate;         // hourly wage
    FILE *outputfileptr;    // pointer to the output file
    
    
    // open a file called home3.txt:
    // In the example below, a file pointer called outputfileptr 
    // is created that will point to a new file called home3.txt.
    if ((outputfileptr = fopen("home3.txt", "w")) == (FILE *) NULL)
    {
        // stderr will print to the screen
        fprintf(stderr, "Error, Unable to open file\n"); 
        // The key point here is that output can be sent to a file as well as the
        // terminal screen. Instead of using printf, you use fprintf, which adds the
        // file pointer (outputfileptr) as one of its arguments so it goes to a file.
        exit(1);
    }

    printf ("*** Pay Calculator ***\n");

    // Add a loop here to process each employee

    for(idx = 1; idx <= empNum; ++idx){

    
    // Prompt for input values from the screen
    printf ("\nEnter clock number for employee: ");
    scanf ("%d", &clockNumber);
    printf ("\nEnter hourly wage for employee: ");
    scanf ("%f", &wageRate);
    printf ("\nEnter the number of hours the employee worked: ");
    scanf ("%f", &hours);

    // calculate normal and overtime hours

    if (hours <= STD_HOURS) {
        grossPay = wageRate * hours;
    }
    else {
        overtimeHours = hours - STD_HOURS;
        grossPay = (wageRate * STD_HOURS) + ((wageRate * 1.5) * overtimeHours);
    }
    
    
    // print out employee information to a file
    fprintf (outputfileptr,
             "\n\n\t----------------------------------------------------------\n");
    fprintf (outputfileptr, "\tClock # Wage Hours   OT   Gross\n");
    fprintf (outputfileptr,
             "\t----------------------------------------------------------\n");
    
    // print out data for current employee to the file:
    fprintf (outputfileptr, "\t%06i %5.2f %5.1f %5.1f %7.2f\n",
             clockNumber, wageRate, hours, overtimeHours, grossPay);

    // End of loop code 
    }  
    system("pause");
    return (0); // success
    
} // main