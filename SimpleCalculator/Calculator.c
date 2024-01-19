#include <stdio.h>
#include <stdlib.h>

int main(){

   char operator;
   double number1;
   double number2;
   double result;

   printf("\nEnter an operator (+ - * /): ");
   scanf("%c", &operator);

   printf("Enter number 1: ");
   scanf("%lf", &number1);

   printf("Enter number 2: ");
   scanf("%lf", &number2);

   switch(operator){
      case '+':
         result = number1 + number2;
         printf("\nresult: %lf", result);
         break;
      case '-':
         result = number1 - number2;
         printf("\nresult: %lf", result);
         break;
      case '*':
         result = number1 * number2;
         printf("\nresult: %lf", result);
         break;
      case '/':
         result = number1 / number2;
         printf("\nresult: %lf", result);
         break;
      default:
         printf("%c is not valid", operator);
   }

   printf("\n"); // Add a single \n here
   
   system("pause");
   return 0;
}