//*******************************************************
//
// Assignment 4 - Arrays
//
// Name: <Jack Cacela>
//
// Class: C Programming, <Spring 2024>
//
// Date: <2/12/2024>
//
// Description: Program which utilizes arrays to determine overtime and 
// gross pay for a set of employees with outputs sent 
// to standard output (the screen).
//
//********************************************************

#include <stdio.h>
#include <stdlib.h>

// constants to use
#define SIZE 5           // number of employees to process
#define STD_HOURS 40.0   // normal work week hours before overtime
#define OT_RATE 1.5      // time and half overtime setting
#define _CRT_SECURE_NO_WARNINGS  // Disables warnings related to scanf, printf functions.

int main()
{
    
// unique employee identifier
long int clockNumber [SIZE] = {98401, 526488, 765349, 34645, 127615};   // clock number for each of the 5 employees
float wageRate [SIZE] = {10.6, 9.75, 10.5, 12.25, 8.35};                // hourly pay for each employee
float grossPay [SIZE] = {0.00, 0.00, 0.00, 0.00, 0.00};                 // weekly gross pay, which is normal pay + overtime pay         
float hours [SIZE];                                                     // total hours worked in a given week
float overtimeHrs[SIZE] = {0.00, 0.00, 0.00, 0.00, 0.00};               // overtime hours worked for a given week
float overtimePay [SIZE];                                               // overtime pay earned for a given week
FILE *outputfileptr;                                                    // pointer to the output file
int i;                                                                  // loop and array index


    // Then, open a file called home4.txt, where the file pointer called outputfileptr will point to.
    if ((outputfileptr = fopen("home4.txt", "w")) == (FILE *) NULL)
    {
        fprintf(stderr, "Error, Unable to open file\n"); // error message
        // Instead of using printf, you use fprintf, which adds the
        // file pointer (outputfileptr) as one of its arguments so it goes to a file instead of terminal.
        exit(1);
    }

    
    // Title Screen
    printf ("\n*** Pay Calculator ***\n\n");

        // Process each employee one at a time
        for (i = 0; i < SIZE; i++)
        {

            float tempHours; // Temporary variable to store hours for each employee    
            printf ("\nHow many hours did the employee with clock number %.2d work? ", clockNumber[i]);
            scanf ("%f", &tempHours);
        
            if (tempHours <= STD_HOURS) {
            grossPay[i] = wageRate[i] * tempHours;
            }
            else {
            overtimeHrs[i] = tempHours - STD_HOURS;
            grossPay[i] = (wageRate[i] * STD_HOURS) + ((wageRate[i] * OT_RATE) * overtimeHrs[i]);
            }
            hours[i] = tempHours; // Assign the value to the array after processing
            } // end of for loop

    // Now, print a nice table header
        fprintf (outputfileptr, "\n\n\t----------------------------------------------------------\n");
        fprintf (outputfileptr, "\tClock # Wage Hours   OT   Gross\n");
        fprintf (outputfileptr, "\t----------------------------------------------------------\n");


    // Now that we have all the information in our arrays, we can access each employee and print to screen or file
        for (i = 0; i < SIZE; i++)
        {
            // TODO: Print employee information from your arrays
            fprintf (outputfileptr, "\t%06i %5.2f %5.1f %5.1f %7.2f\n",
                clockNumber[i], wageRate[i], hours[i], overtimeHrs[i], grossPay[i]);
        } // end of for loop

   system("pause");
   return (0); // success
   
} // end of main