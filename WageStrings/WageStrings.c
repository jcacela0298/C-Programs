//********************************************************
//
// Assignment 7 - Structures and Strings
//
// Name: <Jack Cacela>
//
// Class: C Programming, <Spring 2024>
//
// Date: <3/18/2024>
//
// Description: Program which determines overtime and 
// gross pay for a set of employees with outputs sent 
// to standard output (the screen).
//
// This assignment also adds the employee name, their tax state,
// and calculates the state tax, federal tax, and net pay.   It
// also calculates totals, averages, minimum, and maximum values.
//
// Call by Reference design
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
// This scales if we want to ever add Middle, Nickname, Prefix, Suffix, etc.
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
void getHours (struct employee employeeData[], int theSize);
void calcOvertimeHrs (struct employee employeeData[], int theSize);
void calcGrossPay (struct employee employeeData[], int theSize);
void printHeader (void);
void printEmp (struct employee employeeData[], int theSize);
void calcStateTax (struct employee employeeData[], int theSize);
void calcFedTax (struct employee employeeData[], int theSize);
void calcNetPay (struct employee employeeData[], int theSize);
struct totals calcEmployeeTotals (struct employee employeeData[],
                                  struct totals employeeTotals,
                                  int theSize);
                                 
struct min_max calcEmployeeMinMax (struct employee employeeData[],
                                   struct min_max employeeMinMax,
                                   int theSize);
                                  
void printEmpStatistics (struct totals employeeTotals, 
                         struct min_max employeeMinMax,
                         int theSize);
                         
// pointer to the output file
FILE *outputfileptr; 




int main ()
{   
    // Set up a local variable to store the employee information
    // Initialize the name, tax state, clock number, and wage rate
    // Don't initialize  hours, overtimeHrs, grossPay, stateTax, fedTax, or netPay yet.
    struct employee employeeData[SIZE] = {
        { {"Connie", "Cobol"}, "MA", 98401, 10.60},
        { {"Mary", "Apl"}, "NH", 526488, 9.75 },
        { {"Frank", "Fortran"}, "VT", 765349, 10.50 },
        { {"Jeff", "Ada"}, "NY", 34645, 12.25 },
        { {"Anton", "Pascal"},"CA",127615, 8.35 }
    };
    
    // set up structure to store totals and initialize all to zero
    struct totals employeeTotals  = {0,0,0,0,0,0,0};
    
    // set up structure to store min and max values and initialize all to zero
    struct min_max employeeMinMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

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
    // Note:  This remains a Call by Value design
    employeeTotals = calcEmployeeTotals (employeeData, employeeTotals, SIZE); //DONE
                                             
    // Keep a running update of the employee minimum and maximum values
    // Note:  This remains a Call by Value design
    employeeMinMax = calcEmployeeMinMax (employeeData, 
                                         employeeMinMax,
                                         SIZE); 
    // Print the column headers
    printHeader(); 

    // print out final information on each employee
    printEmp (employeeData, SIZE); 
    
    // print the totals and averages for all float items
    printEmpStatistics (employeeTotals, employeeMinMax, SIZE); 

    system("pause");
    return (0); //success

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
//   employeeData - array of employees (i.e., struct employee)
//   theSize - the array size (i.e., number of employees)
// 
// Returns: void
//  
//**************************************************************

void getHours (struct employee employeeData[], int theSize) 
{ 

    int i;  // array and loop index

    // read in hours for each employee
    for (i = 0; i < theSize; ++i)
    {
        // Read in hours for employee 
        printf("\nEnter hours worked by emp # %06li: ", employeeData[i].clockNumber); 
        scanf ("%f", &employeeData[i].hours); 
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
    // First, open a file called home7.txt, where the file pointer called outputfileptr will point to.
    if ((outputfileptr = fopen("home7.txt", "w")) == (FILE *) NULL)
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
//   employeeData - array of struct employee
//   theSize - the array size (i.e., number of employees)
// 
// Returns: void
//  
//**************************************************************

void printEmp (struct employee employeeData[], int theSize)
{
    
    int i;  // array and loop index
    
    // used to format the employee name
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
        strcpy (name, employeeData[i].empName.firstName);
        strcat (name, " "); // add a space between first and last names
        strcat (name, employeeData[i].empName.lastName);
    
        // Print out a single employee
        fprintf(outputfileptr, "\n%-20.20s %-2.2s  %06li %5.2f  %4.1f  %4.1f %7.2f %6.2f %7.2f %8.2f",
                 name, employeeData[i].taxState, employeeData[i].clockNumber, 
                 employeeData[i].wageRate, employeeData[i].hours,
                 employeeData[i].overtimeHrs, employeeData[i].grossPay, 
                 employeeData[i].stateTax, employeeData[i].fedTax, 
                 employeeData[i].netPay);
               

             
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

void printEmpStatistics (struct totals employeeTotals, 
                         struct min_max employeeMinMax,
                         int theSize)
{
    
    // print a separator line
    fprintf(outputfileptr, "\n--------------------------------------------------------------");
    fprintf(outputfileptr, "-------------------");
    
    // print the totals for all the floating point fields

    fprintf(outputfileptr, "\nTotals:                         %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
             employeeTotals.total_wageRate,
             employeeTotals.total_hours,
             employeeTotals.total_overtimeHrs,
             employeeTotals.total_grossPay,
             employeeTotals.total_stateTax,
             employeeTotals.total_fedTax,
             employeeTotals.total_netPay);

    // make sure you don't divide by zero or a negative number
    if (theSize > 0)       
    {
        // print the averages for all the floating point fields

        fprintf(outputfileptr, "\nAverages:                       %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
                 employeeTotals.total_wageRate/theSize,
                 employeeTotals.total_hours/theSize,
                 employeeTotals.total_overtimeHrs/theSize,
                 employeeTotals.total_grossPay/theSize,
                 employeeTotals.total_stateTax/theSize,
                 employeeTotals.total_fedTax/theSize,
                 employeeTotals.total_netPay/theSize);
    } // if
    
    // print the min and max values
   
    fprintf(outputfileptr, "\nMinimum:                        %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
              employeeMinMax.min_wageRate,
              employeeMinMax.min_hours,
              employeeMinMax.min_overtimeHrs,
              employeeMinMax.min_grossPay,
              employeeMinMax.min_stateTax,
              employeeMinMax.min_fedTax,
              employeeMinMax.min_netPay);
    
   
    fprintf(outputfileptr, "\nMaximum:                        %5.2f %5.1f %5.1f %7.2f %6.2f %7.2f %8.2f",
              employeeMinMax.max_wageRate,
              employeeMinMax.max_hours,
              employeeMinMax.max_overtimeHrs,
              employeeMinMax.max_grossPay,
              employeeMinMax.max_stateTax,
              employeeMinMax.max_fedTax,
              employeeMinMax.max_netPay);

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
// Returns: void
//
//**************************************************************

void calcOvertimeHrs (struct employee employeeData[], int theSize)
{
    
    int i;  // array and loop index

    // calculate overtime hours for each employee
    for (i = 0; i < theSize; ++i)
    {  
        // Any overtime ?
        if (employeeData[i].hours >= STD_HOURS)
        {
            employeeData[i].overtimeHrs = employeeData[i].hours - STD_HOURS;
        }
        else // no overtime
        {
              employeeData[i].overtimeHrs = 0;
        }
        
    } // for


} // calcOvertimeHrs






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
// Returns: void
//
//**************************************************************

void calcGrossPay (struct employee employeeData[], int theSize)
{
    int i;                // loop and array index
    float theNormalPay;   // normal pay without any overtime hours
    float theOvertimePay; // overtime pay

    // calculate grossPay for each employee
    for (i=0; i < theSize; ++i)
    {
        // calculate normal pay and any overtime pay
        theNormalPay = employeeData[i].wageRate * 
                                   (employeeData[i].hours - employeeData[i].overtimeHrs);
        theOvertimePay = employeeData[i].overtimeHrs * 
                                      (OT_RATE * employeeData[i].wageRate);
  
        // calculate gross pay for employee as normalPay + any overtime pay
        employeeData[i].grossPay = theNormalPay + theOvertimePay;
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
// Returns: void
//
//**************************************************************

void calcStateTax (struct employee employeeData[], int theSize)
{
    
    int i; // loop and array index
    
    // calculate state tax based on where employee works
    for (i=0; i < theSize; ++i)
    {
        // Make sure tax state is all uppercase
        if (islower(employeeData[i].taxState[0]))
            employeeData[i].taxState[0] = toupper(employeeData[i].taxState[0]);
        if (islower(employeeData[i].taxState[1]))
            employeeData[i].taxState[1] = toupper(employeeData[i].taxState[1]);
        
        // calculate state tax based on where employee resides
        if (strcmp(employeeData[i].taxState, "MA") == 0)
            employeeData[i].stateTax = employeeData[i].grossPay * MA_TAX_RATE;
        else if (strcmp(employeeData[i].taxState, "NH") == 0)
            employeeData[i].stateTax = employeeData[i].grossPay * NH_TAX_RATE;
        else if (strcmp(employeeData[i].taxState, "VT") == 0)
            employeeData[i].stateTax = employeeData[i].grossPay * VT_TAX_RATE;
        else if (strcmp(employeeData[i].taxState, "CA") == 0)
           employeeData[i].stateTax = employeeData[i].grossPay * CA_TAX_RATE;
        else
            // any other state is the default rate
            employeeData[i].stateTax = employeeData[i].grossPay * DEFAULT_TAX_RATE;
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
// Returns: void
//
//**************************************************************

void calcFedTax (struct employee employeeData[], int theSize)
{
    
    int i;  // loop and array index
    
    // calculate the federal tax for each employee
    for (i=0; i < theSize; ++i)
    {

        employeeData[i].fedTax = employeeData[i].grossPay * FED_TAX_RATE;
        
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
// Returns: void
//
//**************************************************************

void calcNetPay (struct employee employeeData[], int theSize)
{
    int i;               // loop and array index
    float theTotalTaxes; // the total state and federal tax
    
    // calculate the take home pay for each employee
    for (i=0; i < theSize; ++i)
    {
        // calculate the total state and federal taxes
        theTotalTaxes = employeeData[i].stateTax + employeeData[i].fedTax;
        employeeData[i].netPay = employeeData[i].grossPay - theTotalTaxes;

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
//   employeeData - array of employees (i.e., struct employee)
//   employeeTotals - structure containing a running totals 
//                    of all fields above
//   theSize - the array size (i.e., number of employees)
//
// Returns: employeeTotals - updated totals in the updated 
//                           employeeTotals structure
//
//**************************************************************

struct totals calcEmployeeTotals (struct employee employeeData[],
                                  struct totals employeeTotals,
                                  int theSize)
{
    
    int i;  // loop and array index
    
    // total up each floating point item for all employees
    for (i = 0; i < theSize; ++i)
    {
        // add current employee data to our running totals
        employeeTotals.total_wageRate += employeeData[i].wageRate;
        employeeTotals.total_hours += employeeData[i].hours;
        employeeTotals.total_overtimeHrs += employeeData[i].overtimeHrs;
        employeeTotals.total_grossPay += employeeData[i].grossPay;
        employeeTotals.total_stateTax += employeeData[i].stateTax;
        employeeTotals.total_fedTax += employeeData[i].fedTax;
        employeeTotals.total_netPay += employeeData[i].netPay;
        
    } // for
    
    return (employeeTotals);
    
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
//                               of all fields above
//   theSize - the array size (i.e., number of employees)
//
// Returns: employeeMinMax - updated employeeMinMax structure
//
//**************************************************************

struct min_max calcEmployeeMinMax (struct employee employeeData[],
                                   struct min_max employeeMinMax,
                                   int theSize)
{

    int i;  // array and loop index
    
    // if this is the first set of data items, set 
    // them to the min and max
    employeeMinMax.min_wageRate = employeeData[0].wageRate; 
    employeeMinMax.min_hours = employeeData[0].hours;
    employeeMinMax.min_overtimeHrs = employeeData[0].overtimeHrs; 
    employeeMinMax.min_grossPay = employeeData[0].grossPay;
    employeeMinMax.min_stateTax = employeeData[0].stateTax;
    employeeMinMax.min_fedTax = employeeData[0].fedTax;
    employeeMinMax.min_netPay = employeeData[0].netPay;
        
    // set the max to the first element members
    employeeMinMax.max_wageRate = employeeData[0].wageRate; 
    employeeMinMax.max_hours = employeeData[0].hours;
    employeeMinMax.max_overtimeHrs = employeeData[0].overtimeHrs; 
    employeeMinMax.max_grossPay = employeeData[0].grossPay;
    employeeMinMax.max_stateTax = employeeData[0].stateTax;
    employeeMinMax.max_fedTax = employeeData[0].fedTax;
    employeeMinMax.max_netPay = employeeData[0].netPay;
    
    // compare the rest of the items to each other for min and max
    for (i = 1; i < theSize; ++i)
    {
        
        // check if current Wage Rate is the new min and/or max
        if (employeeData[i].wageRate < employeeMinMax.min_wageRate)
        {
            employeeMinMax.min_wageRate = employeeData[i].wageRate;
        }
        
        if (employeeData[i].wageRate > employeeMinMax.max_wageRate)
        {
            employeeMinMax.max_wageRate = employeeData[i].wageRate;
        }
        
        if (employeeData[i].hours < employeeMinMax.min_hours)
        {
            employeeMinMax.min_hours = employeeData[i].hours;
        }

        if (employeeData[i].hours > employeeMinMax.max_hours)
        {
            employeeMinMax.max_hours = employeeData[i].hours;
        }


        if (employeeData[i].overtimeHrs < employeeMinMax.min_overtimeHrs)
        {
            employeeMinMax.min_overtimeHrs = employeeData[i].overtimeHrs;
        }

        if (employeeData[i].overtimeHrs > employeeMinMax.max_overtimeHrs)
        {
            employeeMinMax.max_overtimeHrs = employeeData[i].overtimeHrs;
        }
        
        if (employeeData[i].grossPay < employeeMinMax.min_grossPay)
        {
            employeeMinMax.min_grossPay = employeeData[i].grossPay;
        }

        if (employeeData[i].grossPay > employeeMinMax.max_grossPay)
        {
            employeeMinMax.max_grossPay = employeeData[i].grossPay;
        }

        if (employeeData[i].stateTax < employeeMinMax.min_stateTax)
        {
            employeeMinMax.min_stateTax = employeeData[i].stateTax;
        }

        if (employeeData[i].stateTax > employeeMinMax.max_stateTax)
        {
            employeeMinMax.max_stateTax = employeeData[i].stateTax;
        }

        if (employeeData[i].fedTax < employeeMinMax.min_fedTax)
        {
            employeeMinMax.min_fedTax = employeeData[i].fedTax;
        }

        if (employeeData[i].fedTax > employeeMinMax.max_fedTax)
        {
            employeeMinMax.max_fedTax = employeeData[i].fedTax;
        }
        
        if (employeeData[i].netPay < employeeMinMax.min_netPay)
        {
            employeeMinMax.min_netPay = employeeData[i].netPay;
        }

        if (employeeData[i].netPay > employeeMinMax.max_netPay)
        {
            employeeMinMax.max_netPay = employeeData[i].netPay;
        }
    } //for
    
    // return all the updated min and max values to the calling function
    return (employeeMinMax);
    
} // calcEmployeeMinMax