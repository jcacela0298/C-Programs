//********************************************************
//
// String Attribute Calculator Program
//
// Name: <John Cacela>
//
// Date: <4/29/2024>
//
// Description: 
// This program will return in a structure the following 
// characteristics of a given string:
//
//    the length of the string
//    number of upper case characters
//    number of lower case characters
//    number of digits
//    number of blank spaces
//    number of non-alphanumeric characters
//
//********************************************************

// necessary header files
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// define structures
typedef struct stringStats
{
    int stringLength;
    int upperCaseCount;
    int lowerCaseCount;
    int digits;
    int blankSpaces;
    int nonAlphanumeric;
} STRINGSTATS; /* Typedef implementation  to replace "struct stringStats" with "STRINGSTATS" */

// function prototypes
STRINGSTATS getStringStats(char *theString); /* getStringStats function prototype */


int main() {

    char theString[99]; // Declare the string

    printf("Please enter a string up to 99 characters: \n");
    // Read up to 99 characters (including spaces) by 
    // using fgets instead of scanf:
    fgets(theString, sizeof(theString), stdin); 

    // Remove trailing newline character from fgets function above
    if (theString[strlen(theString) - 1] == '\n') {
        theString[strlen(theString) - 1] = '\0';
    }

    // Validate that the string is 99 or fewer characters
    if(strlen(theString) > 100) {
        printf("This string is over 99 characters.\n");
        return -1;
    } else {

    STRINGSTATS stats = getStringStats(theString); // Call the getStringStats function

    // Print the resumt of the getStringStats function
    printf("Length: %d, Number of uppercase: %d, Number of lowercase: %d, Number of digits: %d, Number of blank spaces: %d, Number of non-alphanumeric characters: %d\n", stats.stringLength, 
    stats.upperCaseCount, stats.lowerCaseCount, stats.digits, stats.blankSpaces, stats.nonAlphanumeric);


    // Pause the system so terminal doesn't close immediately
    system("pause");

    // Return success
    return 0;

    } // else

} //main


//**************************************************************
// Function: getStringStats
// 
// Purpose: calculates the total number of characteristics of a 
// given char array (string) and adds them to the premade structure
//          
// Parameters: theString - pointer to the char array
// 
// Returns:
//
//    stats - the structure that contains each calculated value
//  
//**************************************************************

STRINGSTATS getStringStats (char * theString) {

STRINGSTATS stats = {0}; // Initialize all counts to 0
STRINGSTATS *statsPtr = &stats; // Initialize *statsPtr of type stringStats structure to the address of the structure

while (*theString != '\0') {

    //Calculate uppercase letters
	if (isupper(*theString)) {
			statsPtr->upperCaseCount ++;
		}
        //Calculate lowercase letters
		else if (islower(*theString)) {
			statsPtr->lowerCaseCount ++;
		}
        //Calculate number of digits
		else if (isdigit(*theString)) {
			statsPtr->digits ++;
		}
        //Calculate blank spaces
        else if (*theString == ' ') {
            statsPtr->blankSpaces++;
        }
        //Calculate non alphanumeric characters
		else if (!isalnum(*theString)) {
			statsPtr->nonAlphanumeric ++;
		}

	    statsPtr->stringLength++; // increment the length of the string automatically with each iteration
	
        ++theString; // increment the pointer to move to the next char automatically with each iteration

   } //While

   return stats; // return the modified structure

} // getStringStats