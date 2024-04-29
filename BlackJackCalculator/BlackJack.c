//********************************************************
//
// BlackJack Card Value Calculator Program
//
// Name: <John Cacela>
//
// Date: <4/29/2024>
//
// Description: This program takes the values of a two-card 
// blackjack HAND as input (1 card at a time), and returns the point total of the hand.
// The value of the cards '2' through '9' is equal to their face value,
// the cards 'T', 'K', 'Q', 'J' are worth 10 points and the ace ('A') 
// is worth 11 points unless it comes with another ace, then that second
// ace is worth 1 point. The program should be able to catch incorrect input. 
//
// A value of 'T' for the 10 card so one can simply pass in two characters, 
// instead of strings, as parameters to this function.
//
//********************************************************


// function prototypes
int blackJackValue (char card1, char card2); 

// necessary header files
#include <stdio.h>
#include <string.h>
#include <ctype.h>  // necessary to use the toupper() function




int main() {

    char card1; // initialize the card1 variable to hold the first card
    char card2; // initialize the card2 variable to hold the second card
    int total;  // initialize the total variable to hold the total value of both cards added together


    // collect input for each card
    printf("Please enter in the value of the first card.  (for ex. 2, 9, J, K, Q, A) If the value is 10, enter in T: ");
    scanf(" %c", &card1); // Added & before card1 and corrected the format specifier

    printf("Please enter in the value of the second card.  (for ex. 2, 9, J, K, Q, A) If the value is 10, enter in T: ");
    scanf(" %c", &card2); // Added & before card2 and corrected the format specifier

    // pass the input to the blackJackValue function, which returns the total that becomes stored in the total variable.
    total = blackJackValue(card1, card2); 

    // print the total value after calculation
    printf("The total value is: %d \n", total);


    system("pause");
    return(0);
}



//**************************************************************
// Function: blackJackValue// 
// Purpose: Takes 2 cards and returns the total integer value of 
// both cards added together, while also performing error handling.
//          
// Parameters: char card1, char card2
// Two cards to be valued and have their values added togther
// 
// Returns:
//
//    total - the total value of the two cards added together
//  
//**************************************************************
 

int blackJackValue(char card1, char card2) {

    // Initialize the total variable to keep track of the total hand value
    int total = 0;

    // declare the currentCard variable to store the value of the card that is 
    // being processed
    char currentCard; 

    // Convert both cards to uppercase
    card1 = toupper(card1);
    card2 = toupper(card2);
    

    // Resolve the double ace card special circumstance first by making the total
    // equal to 12 if both cards are A
    if (card1 == 'A' && card2 == 'A') {
    total = 12;

    } else {

      // Iterate through each card and calculate the total value
      for (int i = 0; i < 2; i++) {

	    // Initialize the currentCard variable to equal card1 or card2
	    // depending on the value of the loop variable i. The first iteration
        // of the loop is 0, which is to process card1, and the second iteration 
        // of the loop is 1, which is to process card2
        if (i == 0) {
            currentCard = card1;
        } else {
            currentCard = card2;
        }

        //discover the value of currentCard, and add it to the total
        switch (currentCard) {
            case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                total += currentCard - '0'; // Convert character digit to integer
                break;
            case 'T': case 'J': case 'Q': case 'K':
                total += 10;
                break;
	        case 'A':
		        total += 11;
		        break;
            default:
                printf("Invalid card: %c\n", currentCard);
                return -1; // Return -1 for invalid input

           } //else

        } //switch

    } //for

    return total;

} //blackJackValue
