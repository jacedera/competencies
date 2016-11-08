// Randomizer functions

// DiceRoll. User inputs number of dice, number of sides, and number of rolls.
// Input sanitation must be utilized. Return -1 if any invalid input is detected. 
// Print out the results of each roll per die. 
int DiceRoll(){
	int iNumDie, iSides, iRolls;
	int ii, jj, kk; // loop counters
	//int t; // "RNG" initializer
	char szNumDie[256], szSides[256], szRolls[256]; /// todo: dynamic allocation
	
	
	srand((unsigned) time(NULL));
	
// OBTAIN USER INPUT
	
	// number of dice
	printf("Enter number of dice: ");
	scanf("%s", &szNumDie);
	iNumDie = atoi(szNumDie);
	if(iNumDie<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		system("pause");
		return -1;
	}
	//printf("\n");
	
	// number of sides per die
	printf("Enter number of sides per die: ");
	scanf("%s", &szSides);
	iSides = atoi(szSides);
	if(iSides<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		system("pause");
		return -1;
	}
	//printf("\n");
	
	// number of rolls
	printf("Enter number of rolls per die: ");
	scanf("%s", &szRolls);
	iRolls = atoi(szRolls);
	if(iRolls<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		system("pause");
		return -1;
	}
	//printf("\n");
	
// OUTPUT RESULTS
	
	// header
	printf("Roll\t");
	for(ii=0; ii<iNumDie; ii++)
		printf("Die #%i\t", ii+1);
	printf("\n");
	
	// results
	for(ii=0; ii<iRolls; ii++){
		printf("%i\t", ii+1);
		for(jj=0; jj<iNumDie; jj++)
			printf("%i\t", ((rand()%(iSides))+1));
		printf("\n");
	}
	system("pause");
	return 0;
}

// CalculateCircleArea. User inputs radius. 
// Input sanitation must be utilized. 
// Print out the surface area of the circle.
// User has option to save result to a text file. 
int CalculateCircleArea(){
	double dbRadius, dbResult;
	char szRadius[256], szAnswer;
	
	const double dbPi = 3.14159;
	//const char *szOutputFile; // for file writing purposes 
	
	printf("Input circle radius: ");
	scanf("%s", &szRadius);
	
	dbRadius = atof(szRadius);
	
	if(dbRadius<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		system("pause");
		return -1;
	}
	
	dbResult = 0.5 * dbPi * (dbRadius * dbRadius);
	printf("Result is: %.3f.\n", dbResult);
	printf("Would you like to save your result to a file? (Y/N)");
	
	system("pause");
	return 0;
}

// CalculateCubeVolume. User inputs height, width, and depth. 
// Input sanitation must be utilized. 
// Print out the volume of the cube. 
// User has option to save result to a text file.
int CalculateCubeVolume(){
	
}
