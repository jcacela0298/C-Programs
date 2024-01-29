//******************************************************* 
// 
// Homework: 2
// 
// Name: Jack Cacela
// 
// Class: C Programming, <Spring 2024>
// 
// Date: <1/29/2024>
// 
// Description: Program which determines gross pay
// and outputs are sent to standard output (the screen).
// 
// 
//******************************************************** 

#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int main ( )
{
    int clockNumber;        // employee clock number
    float grossPay;         // gross pay for week (wage * hours)
    float hours;            // number of hours worked per week
    FILE *outputfileptr;    // pointer to the output file
    float wageRate;         // hourly wage

    // Add two variables, one for a loop index, another for a loop test:
    int idx;
    int empNum; 
    
    // open a file called home2.txt:
    // In the example below, a file pointer called outputfileptr 
    // is created that will point to a new file called home1.txt.
    if ((outputfileptr = fopen("home2.txt", "w")) == (FILE *) NULL)
    {
        // stderr will print to the screen
        fprintf(stderr, "Error, Unable to open file\n"); 
        // The key point here is that output can be sent to a file as well as the
        // terminal screen. Instead of using printf, you use fprintf, which adds the
        // file pointer (outputfileptr) as one of its arguments so it goes to a file.
        exit(1);
    }

    printf ("*** Pay Calculator ***\n");

   
    // Add a prompt to capture how many employees to process
    printf ("\nEnter the number of employees to process: ");
    scanf ("%i", &empNum);
    // Add a loop here to process each employee

    for(idx = 1; idx <= empNum; ++idx){

    
    // Prompt for input values from the screen
    printf ("\nEnter clock number for employee: ");
    scanf ("%d", &clockNumber);
    printf ("\nEnter hourly wage for employee: ");
    scanf ("%f", &wageRate);
    printf ("\nEnter the number of hours the employee worked: ");
    scanf ("%f", &hours);
    
    // calculate gross pay
    grossPay = wageRate * hours;
    
    // print out employee information to a file
    fprintf (outputfileptr,
             "\n\n\t----------------------------------------------------------\n");
    fprintf (outputfileptr, "\tClock # Wage Hours Gross\n");
    fprintf (outputfileptr,
             "\t----------------------------------------------------------\n");
    
    // print out data for current employee to the file:
    fprintf (outputfileptr, "\t%06i %5.2f %5.1f %7.2f\n",
             clockNumber, wageRate, hours, grossPay);

    // End of loop code 
    }  
    system("pause");
    return (0); // success
    
} // main