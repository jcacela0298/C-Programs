//********************************************************
//
// Minimum Value Returner Program
//
// Name: <John Cacela>
//
// Date: <4/29/2024>
//
// Description: Returns the lowest value in a highly
// efficient manner from four integers that the user 
// enters in.
//
//********************************************************


// function prototype
int minValue(int value1, int value2, int value3, int value4);

// necessary preprocessor header files
#include <stdio.h>
#include <string.h>


int main () {
    
    // declare the variables for each value
    int value1, value2, value3, value4;

    // then collect input and store in each respective variable
    printf("Enter in the first integer: ");
    scanf("%d", &value1);

    printf("Enter in the second integer: ");
    scanf("%d", &value2);

    printf("Enter in the third integer: ");
    scanf("%d", &value3);

    printf("Enter in the fourth integer: ");
    scanf("%d", &value4);

    // after the input is obtained, pass it to the minValue function
    // and store the result in the minimum variable
    int minimum = minValue(value1, value2, value3, value4);

    // print the minimum value
    printf("The minimum value is: %d\n", minimum);
    
    // pause the terminal so it doesn't close immediately 
    system("pause");

    // return 0 for a success
    return 0;
}


// **************************************************
// Function: minValue
//
// Parameters: value 1- First value
//	           value 2- Second value
//	           value 3- Third value
//	           value 4- Fourth value
//
// Returns:    theMin - the minimum value among the input parameters.
//
// ***************************************************


int minValue(int value1, int value2, int value3, int value4) 
{
    // Calculates the minimum with minimal checks
    // Once one item is eliminated, just check the remaining three 
    int theMin = (value1 <= value2 && value1 <= value3 && value1 <= value4) ? value1 : (value2 <= value3 && value2 <= value4) ? value2 : (value3 <= value4) ? value3 : value4;

    return theMin; // return the min value
} // end of minValue