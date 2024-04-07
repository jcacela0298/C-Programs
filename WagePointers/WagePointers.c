//********************************************************
//
// Assignment 8 - Structures and Strings and Pointers
//
// Name: <Jack Cacela>
//
// Class: C Programming, <Spring 2024>
//
// Date: <3/25/2024>
//
// Description: Program which determines overtime and 
// gross pay for a set of employees using pointers with outputs sent 
// to standard output (the screen).
//
// This assignment also adds the employee name, their tax state,
// and calculates the state tax, federal tax, and net pay. It
// also calculates totals, averages, minimum, and maximum values.
//
// Array and Structure references are to be replaced with
// pointer references to speed up the processing of this code.
//
// Call by Reference design (using pointers)
//
//********************************************************

// necessary header files
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// define constants
#define SIZE 5
#define STD_HOURS 40.0
#define OT_RATE 1.5
#define MA_TAX_RATE 0.05
#define NH_TAX_RATE 0.0
#define VT_TAX_RATE 0.06
#define CA_TAX_RATE 0.07
#define DEFAULT_TAX_RATE 0.08
#define NAME_SIZE 20
#define TAX_STATE_SIZE 3
#define FED_TAX_RATE 0.25
#define FIRST_NAME_SIZE 10
#define LAST_NAME_SIZE 10

// Define a structure type to store an employee name
// ... note how one could easily extend this to other parts
// parts of a name:  Middle, Nickname, Prefix, Suffix, etc.
struct name
{
    char firstName[FIRST_NAME_SIZE];
    char lastName [LAST_NAME_SIZE];
};

// Define a structure type to pass employee data between functions
// Note that the structure type is global, but you don't want a variable
// of that type to be global. Best to declare a variable of that type
// in a function like main or another function and pass as needed.
struct employee
{
    struct name empName;
    char taxState [TAX_STATE_SIZE];
    long int clockNumber;
    float wageRate;
    float hours;
    float overtimeHrs;
    float grossPay;
    float stateTax;
    float fedTax;
    float netPay;
};

// this structure type defines the totals of all floating point items
// so they can be totaled and used also to calculate averages
struct totals
{
    float total_wageRate;
    float total_hours;
    float total_overtimeHrs;
    float total_grossPay;
    float total_stateTax;
    float total_fedTax;
    float total_netPay;
};

// this structure type defines the min and max values of all floating
// point items so they can be display in our final report
struct min_max
{
    float min_wageRate;
    float min_hours;
    float min_overtimeHrs;
    float min_grossPay;
    float min_stateTax;
    float min_fedTax;
    float min_netPay;
    float max_wageRate;
    float max_hours;
    float max_overtimeHrs;
    float max_grossPay;
    float max_stateTax;
    float max_fedTax;
    float max_netPay;
};

// define prototypes here for each function except main

// These prototypes have already been transitioned to pointers
void getHours (struct employee * emp_ptr, int theSize);
void printEmp (struct employee * emp_ptr, int theSize);

void calcEmployeeTotals (struct employee * emp_ptr,
                         struct totals * emp_totals_ptr,
                         int theSize);
                         
void calcEmployeeMinMax (struct employee * emp_ptr,
                         struct min_max * emp_MinMax_ptr,
                         int theSize);
                         
// This prototype does not need to use pointers
void printHeader (void);

void calcOvertimeHrs (struct employee * emp_ptr, int theSize);
void calcGrossPay (struct employee * emp_ptr, int theSize);
void calcStateTax (struct employee * emp_ptr, int theSize);
void calcFedTax (struct employee * emp_ptr, int theSize);
void calcNetPay (struct employee * emp_ptr, int theSize);
                                  
void printEmpStatistics (struct totals * emp_totals_ptr, 
                         struct min_max * emp_MinMax_ptr,
                         int theSize);


// pointer to the output file
FILE *outputfileptr; 


int main ()
{
    
    // Set up a local variable to store the employee information
    // Initialize the name, tax state, clock number, and wage rate
    struct employee employeeData[SIZE] = {
        { {"Connie", "Cobol"}, "MA", 98401, 10.60},
        { {"Mary", "Apl"}, "NH", 526488, 9.75 },
        { {"Frank", "Fortran"}, "VT", 765349, 10.50 },
        { {"Jeff", "Ada"}, "NY", 34645, 12.25 },
        { {"Anton", "Pascal"},"CA",127615, 8.35 }
    };
    
    // declare a pointer to the array of employee structures
    struct employee * emp_ptr;
    
    // set the pointer to point to the array of employees
    emp_ptr = employeeData;
    
    // set up structure to store totals and initialize all to zero
    struct totals employeeTotals  = {0,0,0,0,0,0,0};
    
    // pointer to the employeeTotals structure
    struct totals * emp_totals_ptr = &employeeTotals;
    
    // set up structure to store min and max values and initialize all to zero
    struct min_max employeeMinMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    // pointer to the employeeMinMax structure
    struct min_max * emp_minMax_ptr = &employeeMinMax;

    // Call functions as needed to read and calculate information

    // Prompt for the number of hours worked by the employee 
    getHours (employeeData, SIZE); 

    // Calculate the overtime hours
    calcOvertimeHrs (employeeData, SIZE);
       
    // Calculate the weekly gross pay
    calcGrossPay (employeeData, SIZE); 

    // Calculate the state tax                                       
    calcStateTax (employeeData, SIZE);

    // Calculate the federal tax                                                   
    calcFedTax (employeeData, SIZE);
 
    // Calculate the net pay after taxes   
    calcNetPay (employeeData, SIZE); 
        
    // Keep a running sum of the employee totals
    // Note the & to specify the address of the employeeTotals
    // structure.  Needed since pointers work with addresses.
    calcEmployeeTotals (employeeData, 
                        &employeeTotals, 
                        SIZE);
                                             
    // Keep a running update of the employee minimum and maximum values
    calcEmployeeMinMax (employeeData, 
                        &employeeMinMax,
                        SIZE); 
    // Print the column headers
    printHeader();

    // print out final information on each employee
    printEmp (employeeData, SIZE); 
    
    // print the totals and averages for all float items
    printEmpStatistics (&employeeTotals, 
                        &employeeMinMax, 
                        SIZE);

    return (0); // success

} // main

//**************************************************************
// Function: getHours 
// 
// Purpose: Obtains input from user, the number of hours worked 
//          per employee and updates it in the array of structures
//          for each employee.
// 
// Parameters:
//
//   emp_ptr - pointer to array of employees (i.e., struct employee)
//   theSize - the array size (i.e., number of employees)
// 
// Returns: void (the employee hours gets updated by reference)
//  
//**************************************************************

void getHours (struct employee * emp_ptr, int theSize) 
{ 

    int i;  // loop index

    // read in hours for each employee
    for (i = 0; i < theSize; ++i)
    {
        // Read in hours for employee 
        printf("\nEnter hours worked by emp # %06li: ", emp_ptr->clockNumber); 
        scanf ("%f", &emp_ptr->hours); 
        
        // set pointer to next employee
        ++emp_ptr;
    }
    
} // getHours

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
    // First, open a file called home8.txt, where the file pointer called outputfileptr will point to.
    if ((outputfileptr = fopen("home8.txt", "w")) == (FILE *) NULL)
    {
        fprintf(stderr, "Error, Unable to open file\n"); // error message
        // Instead of using printf, you use fprintf, which adds the
        // file pointer (outputfileptr) as one of its arguments so it goes to a file instead of terminal.
        exit(1);
    }
    fprintf (outputfileptr, "\n\n*** Pay Calculator ***\n");

    // print the table header
    fprintf (outputfileptr, "\n--------------------------------------------------------------");
    fprintf (outputfileptr, "-------------------");
    fprintf (outputfileptr, "\nName                Tax  Clock# Wage   Hours  OT   Gross ");
    fprintf (outputfileptr, "  State  Fed      Net");
    fprintf (outputfileptr, "\n                   State                           Pay   ");
    fprintf (outputfileptr, "  Tax    Tax      Pay");
    
    fprintf (outputfileptr, "\n--------------------------------------------------------------");
    fprintf (outputfileptr, "-------------------");

} // printHeader

//************************************************************* 
// Function: printEmp 
// 
// Purpose: Prints out all the information for each employee
//          in a nice and orderly table format.
// 
// Parameters: 
//
//   emp_ptr - pointer to array of struct employee
//   theSize - the array size (i.e., number of employees)
// 
// Returns: void
//  
//**************************************************************

void printEmp (struct employee * emp_ptr, int theSize)
{
    
    int i;  // array and loop index
    
    // Used to format the employee name
    char name [FIRST_NAME_SIZE + LAST_NAME_SIZE + 1];

    // read in hours for each employee
    for (i = 0; i < theSize; ++i)
    {
        // While you could just print the first and last name in the printf
        // statement that follows, you could also use various C string library
        // functions to format the name exactly the way you want it.  Breaking
        // the name into first and last members additionally gives you some 
        // flexibility in printing.  This also becomes more useful if we decide
        // later to store other parts of a person's name. I really did this just 
        // to show you how to work with some of the common string functions.
        strcpy (name, emp_ptr->empName.firstName);
        strcat (name, " "); // add a space between first and last names
        strcat (name, emp_ptr->empName.lastName);
    
        // Print out a single employee
        fprintf (outputfileptr, "\n%-20.20s %-2.2s  %06li %5.2f  %4.1f  %4.1f %7.2f %6.2f %7.2f %8.2f",
               name, emp_ptr->taxState, emp_ptr->clockNumber, 
               emp_ptr->wageRate, emp_ptr->hours,
               emp_ptr->overtimeHrs, emp_ptr->grossPay, 
               emp_ptr->stateTax, emp_ptr->fedTax, 
               emp_ptr->netPay);
               
        // set pointer to next employee
        ++emp_ptr;
               
    } // for
          
} // printEmp

//************************************************************* 
// Function: printEmpStatistics 
// 
// Purpose: Prints out the summary totals and averages of all 
//          floating point value items for all employees
//          that have been processed.  It also prints
//          out the min and max values.
// 
// Parameters: 
//
//   employeeTotals - a structure containing a running total 
//                    of all employee floating point items 
//   employeeMinMax - a structure containing all the minimum 
//                    and maximum values of all employee 
//                    floating point items
//   theSize - the total number of employees processed, used 
//             to check for zero or negative divide condition.
// 
// Returns: void
//  
//**************************************************************


void printEmpStatistics (struct totals * emp_totals_ptr, 
                         struct min_max * emp_MinMax_ptr,
                         int theSize)
{
    
    // print a separator line
    fprintf (outputfileptr, "\n--------------------------------------------------------------");
    fprintf (outputfileptr, "-------------------");
    
    // print the totals for all the floating point fields
    fprintf (outputfileptr, "\nTotals:                         %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
           emp_totals_ptr->total_wageRate,
           emp_totals_ptr->total_hours,
           emp_totals_ptr->total_overtimeHrs,
           emp_totals_ptr->total_grossPay,
           emp_totals_ptr->total_stateTax,
           emp_totals_ptr->total_fedTax,
           emp_totals_ptr->total_netPay);
    
    // make sure you don't divide by zero or a negative number
    if (theSize > 0)       
    {
        // print the averages for all the floating point fields
        fprintf (outputfileptr, "\nAverages:                       %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
               emp_totals_ptr->total_wageRate/theSize,
               emp_totals_ptr->total_hours/theSize,
               emp_totals_ptr->total_overtimeHrs/theSize,
               emp_totals_ptr->total_grossPay/theSize,
               emp_totals_ptr->total_stateTax/theSize,
               emp_totals_ptr->total_fedTax/theSize,
               emp_totals_ptr->total_netPay/theSize);
    } // if
    
    // print the min and max values
    
    fprintf (outputfileptr, "\nMinimum:                        %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
           emp_MinMax_ptr->min_wageRate,
           emp_MinMax_ptr->min_hours,
           emp_MinMax_ptr->min_overtimeHrs,
           emp_MinMax_ptr->min_grossPay,
           emp_MinMax_ptr->min_stateTax,
           emp_MinMax_ptr->min_fedTax,
           emp_MinMax_ptr->min_netPay);
    
    fprintf (outputfileptr, "\nMaximum:                        %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
           emp_MinMax_ptr->max_wageRate,
           emp_MinMax_ptr->max_hours,
           emp_MinMax_ptr->max_overtimeHrs,
           emp_MinMax_ptr->max_grossPay,
           emp_MinMax_ptr->max_stateTax,
           emp_MinMax_ptr->max_fedTax,
           emp_MinMax_ptr->max_netPay);

}  // printEmpStatistics

//*************************************************************
// Function: calcOvertimeHrs
//
// Purpose: Calculates the overtime hours worked by an employee
//          in a given week for each employee.
//
// Parameters:
//
//   employeeData - array of employees (i.e., struct employee)
//   theSize - the array size (i.e., number of employees)
//
// Returns: void (the overtime hours gets updated by reference)
//
//**************************************************************

void calcOvertimeHrs (struct employee * emp_ptr, int theSize)
{
    
    int i;  // array and loop index

    // calculate overtime hours for each employee
    for (i = 0; i < theSize; ++i)
    {  
        // Any overtime ?
        if (emp_ptr->hours >= STD_HOURS)
        {
            emp_ptr->overtimeHrs = emp_ptr->hours - STD_HOURS;
        }
        else // no overtime
        {
              emp_ptr->overtimeHrs = 0;
        }

        // set pointer to next employee
        ++emp_ptr;
        
    } // for

}  // calcOvertimeHrs

//*************************************************************
// Function: calcGrossPay
//
// Purpose: Calculates the gross pay based on the the normal pay
//          and any overtime pay for a given week for each
//          employee.
//
// Parameters:
//
//   employeeData - array of employees (i.e., struct employee)
//   theSize - the array size (i.e., number of employees)
//
// Returns: void (the gross pay gets updated by reference)
//
//**************************************************************

void calcGrossPay (struct employee * emp_ptr, int theSize)
{
    int i;                // loop and array index
    float theNormalPay;   // normal pay without any overtime hours
    float theOvertimePay; // overtime pay

    // calculate grossPay for each employee
    for (i=0; i < theSize; ++i)
    {
        // calculate normal pay and any overtime pay
        theNormalPay = emp_ptr->wageRate * 
                       (emp_ptr->hours - emp_ptr->overtimeHrs);
        theOvertimePay = emp_ptr->overtimeHrs * 
                         (OT_RATE * emp_ptr->wageRate);
  
        // calculate gross pay for employee as normalPay + any overtime pay
        emp_ptr->grossPay = theNormalPay + theOvertimePay;

        // set pointer to next employee
        ++emp_ptr;
    }

} // calcGrossPay

//*************************************************************
// Function: calcStateTax
//
// Purpose: Calculates the State Tax owed based on gross pay
//          for each employee.  State tax rate is based on the 
//          the designated tax state based on where the
//          employee is actually performing the work.  Each
//          state decides their tax rate.
//
// Parameters:
//
//   employeeData - array of employees (i.e., struct employee)
//   theSize - the array size (i.e., number of employees)
//
// Returns: void (the state tax gets updated by reference)
//
//**************************************************************

void calcStateTax (struct employee * emp_ptr, int theSize)
{
    
    int i; // loop and array index
    
    // calculate state tax based on where employee works
    for (i=0; i < theSize; ++i)
    {
        // Make sure tax state is all uppercase
        if (islower(emp_ptr->taxState[0]))
            emp_ptr->taxState[0] = toupper(emp_ptr->taxState[0]);
        if (islower(emp_ptr->taxState[1]))
            emp_ptr->taxState[1] = toupper(emp_ptr->taxState[1]);
        
        // calculate state tax based on where employee resides
        if (strcmp(emp_ptr->taxState, "MA") == 0)
            emp_ptr->stateTax = emp_ptr->grossPay * MA_TAX_RATE;
        else if (strcmp(emp_ptr->taxState, "VT") == 0)
            emp_ptr->stateTax = emp_ptr->grossPay * VT_TAX_RATE;
        else if (strcmp(emp_ptr->taxState, "NH") == 0)
            emp_ptr->stateTax = emp_ptr->grossPay * NH_TAX_RATE;
        else if (strcmp(emp_ptr->taxState, "CA") == 0)
            emp_ptr->stateTax = emp_ptr->grossPay * CA_TAX_RATE;
        else
            // any other state is the default rate
            emp_ptr->stateTax = emp_ptr->grossPay * DEFAULT_TAX_RATE;

        // set pointer to next employee
        ++emp_ptr;

    } // for
       
} // calcStateTax

//*************************************************************
// Function: calcFedTax
//
// Purpose: Calculates the Federal Tax owed based on the gross 
//          pay for each employee
//
// Parameters:
//
//   employeeData - array of employees (i.e., struct employee)
//   theSize - the array size (i.e., number of employees)
//
// Returns: void (the federal tax gets updated by reference)
//
//**************************************************************

void calcFedTax (struct employee * emp_ptr, int theSize)
{
    
    int i;  // loop and array index
    
    // calculate the federal tax for each employee
    for (i=0; i < theSize; ++i)
    {
        // Fed Tax is the same for all regardless of state
        emp_ptr->fedTax = emp_ptr->grossPay * FED_TAX_RATE;
        
        // set pointer to next employee
        ++emp_ptr;

    } // for
    
} // calcFedTax

//*************************************************************
// Function: calcNetPay
//
// Purpose: Calculates the net pay as the gross pay minus any
//          state and federal taxes owed for each employee.
//          Essentially, their "take home" pay.
//
// Parameters:
//
//   employeeData - array of employees (i.e., struct employee)
//   theSize - the array size (i.e., number of employees)
//
// Returns: void (the net pay gets updated by reference)
//
//**************************************************************

void calcNetPay (struct employee * emp_ptr, int theSize)
{
    int i;               // loop and array index
    float theTotalTaxes; // the total state and federal tax
    
    // calculate the take home pay for each employee
    for (i=0; i < theSize; ++i)
    {
        // calculate the total state and federal taxes
        theTotalTaxes = emp_ptr->stateTax + emp_ptr->fedTax;
    
        // calculate the net pay
        emp_ptr->netPay = emp_ptr->grossPay - theTotalTaxes;

        // set pointer to next employee
        ++emp_ptr;

    } // for
    
} // calcNetPay

//*************************************************************
// Function: calcEmployeeTotals
//
// Purpose: Performs a running total (sum) of each employee
//          floating point member in the array of structures 
//
// Parameters:
//
//   emp_ptr - pointer to array of employees (structure)
//   emp_totals_ptr - pointer to a structure containing the 
//                    running totals of all floating point
//                    members in the array of employee structure
//                    that is accessed and referenced by emp_ptr
//   theSize - the array size (i.e., number of employees)
//
// Returns: 
//
//   void (the employeeTotals structure gets updated by reference)
//
//**************************************************************

void calcEmployeeTotals (struct employee * emp_ptr,
                         struct totals * emp_totals_ptr,
                         int theSize)
{
    
    int i; // loop index
    
    // total up each floating point item for all employees
    for (i = 0; i < theSize; ++i)
    {
        // add current employee data to our running totals
        emp_totals_ptr->total_wageRate += emp_ptr->wageRate;
        emp_totals_ptr->total_hours += emp_ptr->hours;
        emp_totals_ptr->total_overtimeHrs += emp_ptr->overtimeHrs;
        emp_totals_ptr->total_grossPay += emp_ptr->grossPay;
        emp_totals_ptr->total_stateTax += emp_ptr->stateTax;
        emp_totals_ptr->total_fedTax += emp_ptr->fedTax;
        emp_totals_ptr->total_netPay += emp_ptr->netPay;
        
        // go to next employee in our array of structures
        // Note:  We don't need to increment the emp_totals_ptr
        //        because it is not an array
        ++emp_ptr;
        
    } // for
    
    // no need to return anything since we used pointers and have
    // been referring the array of employee structure and the 
    // the total structure from its calling function ... this
    // is the power of Call by Reference.
    
} // calcEmployeeTotals

//*************************************************************
// Function: calcEmployeeMinMax
//
// Purpose: Accepts various floating point values from an
//          employee and adds to a running update of min
//          and max values
//
// Parameters:
//
//   employeeData   - array of employees (i.e., struct employee)
//   employeeTotals - structure containing a running totals 
//                    of all fields above
//   theSize - the array size (i.e., number of employees)
//
// Returns: 
//
//   employeeMinMax - updated employeeMinMax structure
//
//**************************************************************

void calcEmployeeMinMax (struct employee * emp_ptr,
                         struct min_max * emp_minMax_ptr,
                         int theSize)
{

    int i; // loop index
    
    // At this point, emp_ptr is pointing to the first
    // employee which is located in the first element
    // of our employee array of structures (employeeData).
    
    // As this is the first employee, set each min 
    // min and max value using our emp_minMax_ptr
    // to the associated member fields below.  They
    // will become the initial baseline that we  
    // can check and update if needed against the 
    // remaining employees.
    
    // set the min to the first employee members
    emp_minMax_ptr->min_wageRate = emp_ptr->wageRate; 
    emp_minMax_ptr->min_hours = emp_ptr->hours;
    emp_minMax_ptr->min_overtimeHrs = emp_ptr->overtimeHrs; 
    emp_minMax_ptr->min_grossPay = emp_ptr->grossPay;
    emp_minMax_ptr->min_stateTax = emp_ptr->stateTax;
    emp_minMax_ptr->min_fedTax = emp_ptr->fedTax;
    emp_minMax_ptr->min_netPay = emp_ptr->netPay;
        
    // set the max to the first employee members
    emp_minMax_ptr->max_wageRate = emp_ptr->wageRate; 
    emp_minMax_ptr->max_hours = emp_ptr->hours;
    emp_minMax_ptr->max_overtimeHrs = emp_ptr->overtimeHrs; 
    emp_minMax_ptr->max_grossPay = emp_ptr->grossPay;
    emp_minMax_ptr->max_stateTax = emp_ptr->stateTax;
    emp_minMax_ptr->max_fedTax = emp_ptr->fedTax;
    emp_minMax_ptr->max_netPay = emp_ptr->netPay;
    
    // compare the rest of the employees to each other for min and max
    for (i = 1; i < theSize; ++i)
    {
        
        // go to next employee in our array of structures
        // Note:  We don't need to increment the emp_totals_ptr
        //        because it is not an array
        ++emp_ptr;
        
        // check if current Wage Rate is the new min and/or max
        if (emp_ptr->wageRate < emp_minMax_ptr->min_wageRate)
        {
            emp_minMax_ptr->min_wageRate = emp_ptr->wageRate;
        }
        
        if (emp_ptr->wageRate > emp_minMax_ptr->max_wageRate)
        {
            emp_minMax_ptr->max_wageRate = emp_ptr->wageRate;
        }
        
        // check is current Hours is the new min and/or max
        if (emp_ptr->hours < emp_minMax_ptr->min_hours)
        {
            emp_minMax_ptr->min_hours = emp_ptr->hours;
        }
        
        if (emp_ptr->hours > emp_minMax_ptr->max_hours)
        {
            emp_minMax_ptr->max_hours = emp_ptr->hours;
        }
        
        // check is current Overtime Hours is the new min and/or max
        if (emp_ptr->overtimeHrs < emp_minMax_ptr->min_overtimeHrs)
        {
            emp_minMax_ptr->min_overtimeHrs = emp_ptr->overtimeHrs;
        }
        
        if (emp_ptr->overtimeHrs > emp_minMax_ptr->max_overtimeHrs)
        {
            emp_minMax_ptr->max_overtimeHrs = emp_ptr->overtimeHrs;
        }
        
        // check is current Gross Pay is the new min and/or max
        if (emp_ptr->grossPay < emp_minMax_ptr->min_grossPay)
        {
            emp_minMax_ptr->min_grossPay = emp_ptr->grossPay;
        }
        
        if (emp_ptr->grossPay > emp_minMax_ptr->max_grossPay)
        {
            emp_minMax_ptr->max_grossPay = emp_ptr->grossPay;
        }
        
        // check is current State Tax is the new min and/or max
        if (emp_ptr->stateTax < emp_minMax_ptr->min_stateTax)
        {
            emp_minMax_ptr->min_stateTax = emp_ptr->stateTax;
        }
        
        if (emp_ptr->stateTax > emp_minMax_ptr->max_stateTax)
        {
            emp_minMax_ptr->max_stateTax = emp_ptr->stateTax;
        }
        
        // check is current Federal Tax is the new min and/or max
        if (emp_ptr->fedTax < emp_minMax_ptr->min_fedTax)
        {
            emp_minMax_ptr->min_fedTax = emp_ptr->fedTax;
        }
        
        if (emp_ptr->fedTax > emp_minMax_ptr->max_fedTax)
        {
            emp_minMax_ptr->max_fedTax = emp_ptr->fedTax;
        }
        
        // check is current Net Pay is the new min and/or max
        if (emp_ptr->netPay < emp_minMax_ptr->min_netPay)
        {
            emp_minMax_ptr->min_netPay = emp_ptr->netPay;
        }
        
        if (emp_ptr->netPay > emp_minMax_ptr->max_netPay)
        {
            emp_minMax_ptr->max_netPay = emp_ptr->netPay;
        }
        
    } // else if
    
    // no need to return anything since we used pointers and have
    // been referencing the employeeData structure and the 
    // the employeeMinMax structure from its calling function ...
    // this is the power of Call by Reference.
    
} // calcEmployeeMinMax