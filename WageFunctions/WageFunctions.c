
//********************************************************
//
// Assignment 5 - Functions
//
// Name: <Jack Cacela>
//
// Class: C Programming, <Spring 2024>
//
// Date: <2/19/2024>
//
// Description: Program which uses functions to  
// determine overtime and gross pay for a set of employees  
// with outputs sent to standard output (the screen) using functions.
//
// All functions called by reference (sending entire array)
// instead of calling by value (sending specific array values)
//
//******************************************************** 

#include <stdio.h> 
#include <stdlib.h>

// constants
#define SIZE 5                      // number of employees to process
#define STD_HOURS 40.0f             // normal work week hours before overtime
#define OT_RATE 1.5f                // time and a half overtime setting
#define _CRT_SECURE_NO_WARNINGS     // Disables warnings related to scanf, printf functions.

// function prototypes
void getHours (long int clockNumber[], float hours[], int theSize);
void calculateOvertimeHours (float hours[], float overtimeHrs[], int theSize);
void calculateGrossPay (float hours[], float overtimeHrs[], float grossPay[], float wageRate[], int theSize);
void printHeader (void);
void printEmp (long int clockNumber[], float wageRate[], float hours[], float overtimeHrs[], float grossPay[], int theSize);

// pointer to the output file
FILE *outputfileptr; 

int main() 
{ 

// Variable Declarations

long int clockNumber [SIZE] = {98401, 526488, 765349, 34645, 127615};   // clock numbers for each of the 5 employees
float wageRate [SIZE] = {10.6, 9.75, 10.5, 12.25, 8.35};                // hourly pay rate (USD) for each employee
float grossPay [SIZE] = {0.00, 0.00, 0.00, 0.00, 0.00};                 // weekly gross pay         
float hours [SIZE];                                                     // weekly hours worked
float overtimeHrs[SIZE] = {0.00, 0.00, 0.00, 0.00, 0.00};               // overtime hours worked for a given week


    // Function call to read in the hours worked for each employee and store data into hours array:
    getHours (clockNumber, hours, SIZE); 

    // Function call to calculate overtime hours and store data into overtimeHrs array:
    calculateOvertimeHours (hours, overtimeHrs, SIZE);

    // Function call to calculate gross pay and stores data into grossPay array:
    calculateGrossPay (hours, overtimeHrs, grossPay, wageRate, SIZE);

    // Print the initial table header:
    printHeader ();

    // Function call to output results to the screen:
    printEmp (clockNumber, wageRate, hours, overtimeHrs, grossPay, SIZE);

    system("pause");
    return (0); //success
 
}  // end of main

//***************************************************************
//  Function: getHours  
// 
//  Purpose: Obtains input from user, the number of hours worked 
//  per employee and stores the results in an array that is 
//  passed back to the calling function by reference. 
// 
//  Parameters: 
//
//      clockNumber - Array of employee clock numbers for each employee
//      hours - Array of hours worked by each employee
//      theSize - Number of employees to process
// 
//  Returns: Nothing (call by reference)
//  
//**************************************************************

void getHours (long int clockNumber[], float hours[], int theSize)
{

    int i; // loop and array index

    // Read in hours for each employee
    for (i= 0; i < theSize; ++i)
    {
        printf("\nEnter hours worked by emp # %06li: ", clockNumber[i]);
        scanf ("%f", &hours[i]);
    }

} // end of getHours

//***************************************************************
//  Function: calculateOvertimeHours  
// 
//  Purpose: Calculates the amount of overtime hours per employee and
//  stores the results in the overtimeHrs array that is 
//  passed back to the calling function by reference. 
// 
//  Parameters: 
//
//      hours - Array of hours worked by each employee
//      overtimeHrs - Array of overtime hours worked by each employee
//      theSize - Number of employees to process
// 
//  Returns: Nothing (call by reference)
//  
//**************************************************************

void calculateOvertimeHours (float hours[], float overtimeHrs[], int theSize)
{

    int i; // loop and array index


    for (i = 0; i < theSize; ++i)
        {
        
            if (hours[i] <= STD_HOURS) {
            overtimeHrs[i] = 0.00;

            } else {

            overtimeHrs[i] = hours[i] - STD_HOURS;
            }

        } 

} // end of calculateOvertimeHours


//***************************************************************
//  Function: calculateGrossPay  
// 
//  Purpose: Calculates the gross pay per employee and
//  stores the results in the grossPay array that is 
//  passed back to the calling function by reference. 
// 
//  Parameters: 
//
//      hours - Array of hours worked by each employee
//      overtimeHrs - Array of overtime hours earned by each employee
//      grossPay - Array that contains the total pay earned by each employee including overtime hours
//      wageRate - Array that contains the wages of each employee
//      theSize - Number of employees to process
// 
//  Returns: Nothing (call by reference)
//  
//**************************************************************

void calculateGrossPay (float hours[], float overtimeHrs[], float grossPay[], float wageRate[], int theSize)
{

    int i; // loop and array index

    for (i = 0; i < theSize; ++i)
        {
        
            if (overtimeHrs[i] > 0.00) {
            grossPay[i] = (wageRate[i] * STD_HOURS) + ((wageRate[i] * OT_RATE) * overtimeHrs[i]);

            } else {
                
            grossPay[i] = wageRate[i] * hours[i];
            }
            
        } 

} // end of calculateGrossPay


//**************************************************************
// Function: printHeader
// 
// Purpose: Prints the initial table header information.
// 
// Parameters: none
// 
// Returns: void
//  
//**************************************************************

void printHeader (void) 
{ 

    // Open a file called home5.txt, where the file pointer called outputfileptr will point to.
    if ((outputfileptr = fopen("home5.txt", "w")) == (FILE *) NULL)
    {
        fprintf(stderr, "Error, Unable to open file\n"); // error message
        // Instead of using printf, you use fprintf, which adds the
        // file pointer (outputfileptr) as one of its arguments so it goes to a file instead of terminal.
        exit(1);
    }

    printf ("\n\n*** Pay Calculator ***\n");

    // print the table header
    fprintf (outputfileptr, "\n\n\t----------------------------------------------------------\n");
    fprintf (outputfileptr, "\tClock # Wage Hours   OT   Gross\n");
    fprintf (outputfileptr, "\t----------------------------------------------------------\n");

} // end of printHeader

//**************************************************************
// Function: printEmp 
// 
// Purpose: Prints out all the employee information in a
// nice and orderly table format.
// 
// Parameters: 
//
//     clockNumber - Array of employee clock numbers
//     wageRate - Array of employee wages per hour
//     hours - Array of number of hours worked by an employee
//     overtimeHrs - Array of overtime hours for each employee
//     grossPay - Array of gross pay calculations for each employee
//     theSize - Number of employees to process 
// 
// Returns: Nothing (call by reference)
//  
//**************************************************************

void printEmp (long int clockNumber[], float wageRate[], float hours[],
                float overtimeHrs[], float grossPay[], int theSize)
{
    int i; // loop and array index

    // access and print each employee
    for (i = 0; i < theSize; ++i)
    {
       fprintf (outputfileptr, "\t%06i %5.2f %5.1f %5.1f %7.2f\n",
       clockNumber[i], wageRate[i], hours[i], overtimeHrs[i], grossPay[i]);
    } 

} // end of printEmp 
