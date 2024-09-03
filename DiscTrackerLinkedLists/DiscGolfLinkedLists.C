//********************************************************
//
// Disc Golf Disc Tracker
//
// Name: <John Cacela>
//
// Date: <4/3/2024>
//
// Description: Program that keeps track of discs and determines the 
// total weight for a set of discs using Linked Lists with outputs sent 
// to the home1.txt text file.
//
//********************************************************


//Write Header Files
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //for malloc
#include <ctype.h> //for char functions

//Define constants
#define NAME_SIZE 30

//Now define global structures, variables, etc.

struct discs // This will hold the information about each disc
{
    char name[NAME_SIZE];
    char brand[NAME_SIZE];
    char category[NAME_SIZE];
    float speed;
    float glide;
    float turn;
    float fade;
    float weight;

    struct discs * next; // This is to convert the struct to a linked list so
    // it points to the next discs struct in memory, specifically in the heap.
};

struct totals // This will hold the information about the total weight of all the discs.
{
    float totalWeight;
};




//Define prototypes
struct discs * getDiscData (void); # "struct discs *" indicates that this function returns a pointer to a structure of type discs.
int isDiscSize (struct discs * head_ptr);
void calcDiscWeights (struct discs * head_ptr, struct totals *comb_weight_ptr);
void printHeader (void);
void printDiscs (struct discs * head_ptr);
void printDiscTotals (struct totals * comb_weight_ptr, int theSize );
void freeMemory(struct discs *head_ptr);

//File pointer
FILE *outputfileptr;





//Main
int main() {

    struct discs * head_ptr; // define pointer to first node
    head_ptr = getDiscData(); // initialize pointer to getDiscsData function which returns the head_ptr. 

    struct  totals combinedWeight = {0}; //initialize the weight structure
    struct  totals * comb_weight_ptr = &combinedWeight; //initialize the pointer to the weight structure


    int theSize; // number of discs processed

    theSize = isDiscSize (head_ptr); //determine how many discs are in our linked lists

    if (theSize <= 0)  //if there are no discs friendly message to skip the rest of the processing.
    {
        printf("\n\n*** There was no disc input to process ***\n");
    }

    else

    {
        calcDiscWeights (head_ptr, &combinedWeight);
    
        // Print the column headers
        printHeader();

        // print out final information on each discs
        printDiscs (head_ptr); 
    
        printDiscTotals (&combinedWeight,  
                            theSize);

        freeMemory(head_ptr);

        printf ("\n\n *** End of Program *** \n");
        return (0); //success
    }
}





//**************************************************************
// Function: getDiscData
// 
// Purpose: Obtains input from user: disc name, brand, category, speed, 
//          glide, turn, fade, and weight, dynamically allocating space,
//          and also returns head_ptr.
//
//          Information in stored in a dynamically created linked
//          list for all discs.
//          
// Parameters: void
// 
// Returns:
//
//    head_ptr - a pointer to the beginning of the dynamically
//               created linked list that contains the initial
//               input for each disc.
//  
//**************************************************************



struct discs * getDiscData(void)
{
 
    char   answer[80];    // user prompt response
    int    more_data = 1; // a flag to indicate if another disc
                          // needs to be processed
    char   value;         // the first char of the user prompt response
 
    struct discs *current_ptr,   // define local pointer to current node
                    *head_ptr;      // always points to first node
 
    // Set up storage for first node   
    head_ptr = (struct discs *) malloc (sizeof(struct discs));
    current_ptr = head_ptr;
 
    // process while there is still input
    while (more_data)
    {
 
        // read in disc information
        printf ("\nEnter one disc name without any spaces (Examples: Destroyer, Raider): ");
        scanf ("%s", current_ptr->name);
        printf ("\nEnter one disc brand without any spaces (Examples: Innova, DynamicDiscs): ");
        scanf ("%s", current_ptr->brand);
         printf ("\nEnter one disc category without any spaces (Examples: Fairway, DistanceDriver): ");
        scanf ("%s", current_ptr->category);
        printf ("\nEnter the disc's speed (Numeric number between 1 and 15, Example: 12): ");
        scanf ("%f", &current_ptr->speed);
         printf ("\nEnter the disc's glide (Numeric number between 0 and 7, Example: 5): ");
        scanf ("%f", &current_ptr->glide);
        printf ("\nEnter the disc's turn factor (Numeric number between -5 and 1, Example: -1): ");
        scanf ("%f", &current_ptr->turn);
         printf ("\nEnter the disc's fade rating (Numeric number between 0 and 6, Example: 3): ");
        scanf ("%f", &current_ptr->fade);
        printf ("\nEnter the disc's weight in grams (Example: 175): ");
        scanf ("%f", &current_ptr->weight);

 
        // ask user if they would like to add another disc
        printf("\nWould you like to add another disc? (y/n): ");
        scanf("%s", answer);
 
        // check first character for a 'Y' for yes
        // Ask user if they want to add another disc
        if ((value = toupper(answer[0])) != 'Y')
        {
           // no more discs to process
           current_ptr->next = (struct discs *) NULL;
           //in this line above, need to typecast Null to type struct discs * so that 
           //the compiler will recognize it.

           more_data = 0; 
        }
        else // Yes, another disc
        {
           // set the next pointer of the current node to point to the new node
           current_ptr->next = (struct discs *) malloc (sizeof(struct discs));
           // move the current node pointer to the new node
           current_ptr = current_ptr->next;
        }
         
    } // while
 
    return(head_ptr);

} // getEmpData






//*************************************************************
// Function: isDiscSize
//
// Purpose: Traverses the linked list, and keeps a running count
//          on how many discs are currently in our list. 
//
// Parameters:
//
//   head_ptr - pointer to the initial node in our linked list
//
// Returns:
//
//   theSize - the number of discs in our linked list
//
//**************************************************************

int isDiscSize (struct discs * head_ptr)
{
    
    struct discs * current_ptr; // define pointer to current node
    int theSize;                // number of link list nodes


    theSize = 0; // initialize

    // assume there is no data if the first node does
    // not have a disc name
    if (head_ptr->name[0] != '\0')
    {
        
        // traverse through the linked list, keep a running count of nodes
        for (current_ptr = head_ptr; current_ptr; current_ptr = current_ptr->next)
        {  
   
            ++theSize;  // disc node found, increment
        
        } // for
    }

    return (theSize);  // number of nodes (i.e., discs)


} // isDiscSize





//*************************************************************
// Function: calcDiscWeights
//
// Purpose: Performs a running total (sum) of all of the discs'
//          floating point weight stored in our linked list 
//
// Parameters:
//
//   head_ptr - pointer to the beginning of our linked list
//   * comb_weight_ptr - pointer to a structure containing the 
//                    running totals of each floating point
//                    weight for all discs in our linked
//                    list
//
// Returns: 
//
//   void 
//
//**************************************************************

void calcDiscWeights (struct discs * head_ptr,
                         struct totals * comb_weight_ptr)
{
       
    struct discs * current_ptr; // pointer to current node

    // traverse through the linked list to calculate a running 
    // sum of each disc weight item
    for (current_ptr = head_ptr; current_ptr; current_ptr = current_ptr->next)
    {
        // add current disc data to our running totals
        comb_weight_ptr->totalWeight += current_ptr->weight;
        
    } // for
    
    // no need to return anything since we used pointers and have
    // been referencing the linked list stored in the Heap area. 
    // Since we used a pointer as well to the totals structure,
    // all values in it have been updated.
    
} // calcDiscWeights




//************************************************************** 
// Function: printHeader
// 
// Purpose: Prints the initial table header information and sets 
//          up the file pointer.
// 
// Parameters: none
// 
// Returns: void
//  
//**************************************************************

void printHeader(void) 
{ 
    // First, open a file called home1.txt, where the file pointer called outputfileptr will point to.
    if ((outputfileptr = fopen("home1.txt", "w")) == (FILE *) NULL)
    {
        fprintf(stderr, "Error, Unable to open file\n"); // error message
        // Instead of using printf, you use fprintf, which adds the
        // file pointer (outputfileptr) as one of its arguments so it goes to a file instead of terminal.
        exit(1);
    }
    fprintf(outputfileptr, "*** Disc Golf Disc Tracker ***\n");

    // Print the table header
    fprintf(outputfileptr, "\n%-20s%-20s%-20s%6s%6s%6s%6s%10s\n",
            "Name", "Brand", "Category", "Speed", "Glide", "Turn", "Fade", "Weight(g)");

    // Print the separator line
    fprintf(outputfileptr, "-----------------------------------------------------------------------------------------------\n");

} //printHeader










//************************************************************* 
// Function: printDiscs 
// 
// Purpose: Prints out all the information for each disc
//          in a nice and orderly table format.
// 
// Parameters: 
//
//   head_ptr - pointer to the beginning of our linked list
// 
// Returns: void
//  
//**************************************************************

void printDiscs(struct discs *head_ptr)
{
    struct discs *current_ptr; // pointer to current node

    // traverse through the linked list to process each disc
    for (current_ptr = head_ptr; current_ptr; current_ptr = current_ptr->next)
    {
        // Print out current disc in the current linked list node
        fprintf(outputfileptr, "%-20s%-20s%-20s%6.2f%6.2f%6.2f%6.2f%8.2f\n",
                current_ptr->name, current_ptr->brand, current_ptr->category,
                current_ptr->speed, current_ptr->glide,
                current_ptr->turn, current_ptr->fade,
                current_ptr->weight);
    } //for

} //printDiscs



void printDiscTotals (struct totals * comb_weight_ptr, int theSize)
{
    // print a separator line
    fprintf (outputfileptr, "-----------------------------------------------------------------------------------------------\n");
    
    // print the totals for all the floating point items
    fprintf(outputfileptr, "\nTotal Weight Of All Discs: %5.2f grams\n",
            comb_weight_ptr->totalWeight);
    
           
    // print out the total discs processed
    fprintf (outputfileptr, "\n\nTotal Number Of Discs Processed: %d\n", theSize);

} //printDiscTotals  





//************************************************************* 
// Function: freeMemory 
// 
// Purpose: frees the memory allocated for the linked list nodes.
// 
// Parameters: 
//
//   head_ptr - pointer to the beginning of our linked list
// 
// Returns: void
//  
//**************************************************************


void freeMemory(struct discs *head_ptr) {
    struct discs *current_ptr;

    while (head_ptr != NULL) {
        current_ptr = head_ptr;
        head_ptr = head_ptr->next;
        free(current_ptr);
    }
}
