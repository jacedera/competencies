// C Competency 1: Randomizer
/* Randomizer has the following functions:
              1: Dice roll/RNG. User inputs number of sides, number of dice, 
              and number of rolls. Output should be user friendly.
              2: Compute surface area of a circle with user input radius. Allow
              the user the option to save the result to a file for later reference.
              3: Compute volume of a cube with user input x, y, z. Allow the user
              the option to save the result ot a file for later reference.
              4: Exit the program. 

   Randomizer has the following requirements:
              1: A function must exist in a separate C file. 
              2: User input must be sanitized, that is, inputting strange values
              such as -1 or a char instead of a number will not crash the program
              or create opportunity for overflow attacks. 
              */

#include <stdio.h>
#include <string.h>

int main(){
	// note: use strings and atoi. Ignore anything that isn't 0, 1, 2, or 3.
	char input[255];
	int choice=9;
			
	while(choice != 0){
		// begin menu options
		printf("Welcome to Randomizer. Please select an option:\n");
		printf("0: Exit Randomizer\n");
		printf("1: Dice Roller\n");
		printf("2: Surface Area of a Circle\n");
		printf("3: Volume of a Cube\n");
		printf("Selection: ");

        scanf("%s", &input);
        
        if(strcmp(input, "0")==0 || strcmp(input, "1")==0 ||
           strcmp(input, "2")==0 || strcmp(input, "3")==0){
			
			choice = atoi(input);
        
			if(choice == 1) {
				printf("Dice roll.\n");
				system("pause");
			}
			else if(choice == 2){
				printf("Area of Circle.\n");
				system("pause");
			} 
			else if(choice == 3){
				printf("Volume of Cube.\n");
				system("pause");
            }
			else if(choice == 0){
				printf("Exiting...");
				return 0;
			}
		}
		else printf("Invalid option, please try again.");
	}
    return 0;
}
