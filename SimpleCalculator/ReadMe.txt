I worked on a simple calculator program that contains various functionality for client interaction.

If you would like to view my IT YouTube channel, follow this link: https://www.youtube.com/@ITtutorjack

To use and interact with this program, feel free to download the files and make sure they are in the same folder. Then, either click on the "Calculator.exe" file, or go to the command prompt in terminal, and after navigating to the appropriate directory, run the exe file by entering the following command: 

Calculator.exe

Then, follow the simple prompt directions.
.
.
.
.
.
During this project, I learned more about the gcc compiler, how C tends to prefer file structures without spaces, how VS Code needs to be restarted once in a while to resolve bugs, how the following code section: 

___________________________________________
printf("\n"); // Add a single new line here
   system("pause");
   return 0;
___________________________________________

is a great way to finish my C programs so the program doesn't exit too quickly, how C is not object oriented, pre-processor commands for basic functionality as well as #include <stdlib.h> for system("pause") functionality, how to rename the executable by the following command: gcc Calculator.c -o Calculator, format specifiers with an example: 

_________________________________________________________________________________________________
If you want 15 digits of pi stored in a float named pie, and then print 15 digits of it, do this:

float pie = 3.14159265358979323;

printf("%0.15f\n", pie);
_________________________________________________________________________________________________


decimal precision, minimum field with, left align and right align, (%.1 vs. %1 vs. %-), how when we want to make something constant, we add const and make the variable name all capital letters: 

_________________________
const float PI = 3.14159;
_________________________

scanner functionality, if statements, switch statements, and overall basic C syntax.
