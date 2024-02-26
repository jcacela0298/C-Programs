//********************************************************
//
// Assignment 6 - Structures
//
// Name: <Jack Cacela>
//
// Class: C Programming, <Spring 2024>
//
// Date: <2/26/2024>
//
// Description: Program which determines overtime and 
// gross pay for a set of employees using structures with outputs sent 
// to standard output (the screen).
//
// Call by reference design
//
//********************************************************

// Includes
#include <stdio.h>
#include <stdlib.h>

// Define Constants
#define SIZE 5                      // number of employees to process
#define STD_HOURS 40.0f             // normal work week hours before overtime
#define OT_RATE 1.5f                // time and a half overtime setting
#define _CRT_SECURE_NO_WARNINGS     // Disables warnings related to scanf, printf functions.

// Create a structure called employee
struct employee
{
    long clockNumber;
    float wageRate;
    float hours;
    float overtimeHrs;
    float grossPay;
};

// define prototypes here for each function except main
void getHours (struct employee employeeData[], int theSize );
void calculateOvertimeHours (struct employee employeeData[], int theSize);
void calculateGrossPay (struct employee employeeData[], int theSize );
void printHeader (void);
void printEmp (struct employee emp [ ], int theSize);

// pointer to the output file
FILE *outputfileptr; 



int main ()
{
    // Set up a local variable and initialize the clock and wages of my employees
    struct employee employeeData [SIZE] = {
        { 98401, 10.60 },
        { 526488, 9.75 },
        { 765349, 10.50 },
        { 34645, 12.25 },
        { 127615, 8.35 }
    };

    // Function call to read in the hours worked for each employee:
    getHours (employeeData, SIZE); 

    // Function call to calculate overtime hours:
    calculateOvertimeHours (employeeData, SIZE); 

    // Function call to calculate gross pay:
    calculateGrossPay (employeeData, SIZE); 

    // Function call to print the initial table header:
    printHeader ();

    // Function call to output results to the screen:
    printEmp (employeeData, SIZE); 

    system("pause");
    return (0); //success
 
}  // end of main



//**************************************************************
// Function: getHours 
// 
// Purpose: Obtains input from user, the number of hours worked 
// per employee and stores the result in an array of structures
// that is passed back to the calling function by reference. 
// 
// Parameters:
// 
//     employeeData - an array of structures containing Employees
//     theSize - number of employees to process
//
// Returns: Nothing (void)
//  
//**************************************************************

void getHours (struct employee employeeData[], int theSize) 
{

    int i; // loop and array index

    // read hours in for each employee
    for (i = 0; i < theSize ; ++i)
    {
        printf("\nEnter hours worked by emp # %06li: ",
                employeeData[i].clockNumber);
        scanf ("%f", &employeeData[i].hours);
    } // end of for loop

} // end of getHours



//***************************************************************
//  Function: calculateOvertimeHours  
// 
//  Purpose: Calculates the amount of overtime hours per employee and
//  stores the results in an array of structures that is 
//  passed back to the calling function by reference. 
// 
//  Parameters: 
//
//     employeeData - an array of structures containing Employees
//     theSize - Number of employees to process
// 
//  Returns: Nothing (call by reference)
//  
//**************************************************************

void calculateOvertimeHours (struct employee employeeData[], int theSize)
{

    int i; // loop and array index


    for (i = 0; i < theSize; ++i)
        {
        
            if (employeeData[i].hours <= STD_HOURS) {
            employeeData[i].overtimeHrs = 0.00;

            } else {

            employeeData[i].overtimeHrs = employeeData[i].hours - STD_HOURS;
            }

        } // end of for loop

} // end of calculateOvertimeHours



//***************************************************************
//  Function: calculateGrossPay  
// 
//  Purpose: Calculates the gross pay per employee and
//  stores the results in an array of structures that is 
//  passed back to the calling function by reference. 
// 
//  Parameters: 
//
//     employeeData - an array of structures containing Employees
//     theSize - Number of employees to process
// 
//  Returns: Nothing (call by reference)
//  
//**************************************************************

void calculateGrossPay (struct employee employeeData[], int theSize)
{

    int i; // loop and array index

    for (i = 0; i < theSize; ++i)
        {
        
            if (employeeData[i].overtimeHrs > 0.00) {
            employeeData[i].grossPay = (employeeData[i].wageRate * STD_HOURS) + ((employeeData[i].wageRate * OT_RATE) * employeeData[i].overtimeHrs);

            } else {
                
            employeeData[i].grossPay = employeeData[i].wageRate * employeeData[i].hours;
            }
            
        } // end of for loop

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
    // Open a file called home6.txt, where the file pointer called outputfileptr will point to.
    if ((outputfileptr = fopen("home6.txt", "w")) == (FILE *) NULL)
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



// ********************************************************************
// Function: printEmp
//
// Purpose: Outputs to screen in a table format the following
// information about an employee: Clock, Wage,
// Hours, Overtime Hours, and Gross Pay.
//
// Parameters:
//
//     employeeData - an array of structures containing Employees
//     theSize - number of employees to process
//
// Returns: Nothing (void)
//
// *********************************************************************

void printEmp ( struct employee employeeData[], int theSize )
{
    int i; // loop and array index

    // print information about each employee
    for (i = 0; i < theSize ; ++i)
    {
        fprintf(outputfileptr, "\t%06i %5.2f %5.1f %5.1f %7.2f\n",
        employeeData[i].clockNumber, employeeData[i].wageRate, employeeData[i].hours,
        employeeData[i].overtimeHrs, employeeData[i].grossPay);
    } // end of for loop

} // end of printEmp