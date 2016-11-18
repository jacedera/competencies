// Randomizer functions

// DiceRoll. User inputs number of dice, number of sides, and number of rolls.
// Input sanitation must be utilized. Return -1 if any invalid input is detected. 
// Print out the results of each roll per die. 
int DiceRoll(){
	int iNumDie, iSides, iRolls;
	int ii, jj, kk; // loop counters
	//int t; // "RNG" initializer
	char szNumDie[256], szSides[256], szRolls[256]; /// todo: dynamic allocation
	
	
	srand((unsigned) time());
	
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
} // DiceRoll

// CalculateCircleArea. User inputs radius. 
// Input sanitation must be utilized. 
// Print out the surface area of the circle.
// User has option to save result to a text file. 
int CalculateCircleArea(){
	double dbRadius, dbResult;
	char szRadius[256], szAnswer[256];
	
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

// the promised file stuff
	printf("Would you like to save your result to a file? (Y/N)");
    scanf("%s", &szAnswer);

// YES SAVE THE FILE
    if((strcmp(szAnswer, "Y") == 0) || (strcmp(szAnswer, "y") == 0)){
        printf("Saving the result... ");
        FILE *ofResult = fopen("./CalculateCircleAreaResult.txt", "w");
        fprintf(ofResult, "The area of a circle with radius %.f is %.3f.", dbRadius, dbResult);
        fclose(ofResult);
        printf("Done. \nResult saved to \"CalculateCircleAreaResult.txt\". Exiting...\n");
        system("pause");
        return 0;
    }
// NO DON'T SAVE THE FILE
    else if((strcmp(szAnswer, "N") == 0) || (strcmp(szAnswer, "n") == 0)){
        printf("Exiting without saving...\n");
        system("pause");
        return 0;
    }
// INVALID INPUT, DON'T SAVE THE FILE
    else{
        printf("Invalid input (neither Y, y, N, nor n). \nExiting without saving...\n");
        system("pause");
        return -1;
    }
} // CalculateCircleArea


// CalculateCubeVolume. User inputs height, width, and depth. 
// Input sanitation must be utilized. 
// Print out the volume of the cube. 
// User has option to save result to a text file.
int CalculateCubeVolume(){
	double dbLength, dbWidth, dbDepth, dbResult;
    char szLength[256], szWidth[256], szDepth[256], szAnswer[256];
    
    // length
    printf("Input cube length: ");
    scanf("%s", &szLength);
    dbLength = atof(szLength);
    if(dbLength<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		system("pause");
		return -1;
	}
    
    // width
    printf("Input cube width: ");
    scanf("%s", &szWidth);
    dbWidth = atof(szWidth);    
    if(dbWidth<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		system("pause");
		return -1;
	}
    
    // depth
    printf("Input cube depth: ");
    scanf("%s", &szDepth);
    dbDepth = atof(szDepth);    
    if(dbDepth<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		system("pause");
		return -1;
	}
    
    dbResult = dbLength * dbWidth * dbDepth;
    
    printf("Result is: %.3f.\n", dbResult);
    printf("Would you like to save your result to a file? (Y/N)");
    scanf("%s", &szAnswer);
 
 // YES SAVE THE FILE
    if((strcmp(szAnswer, "Y") == 0) || (strcmp(szAnswer, "y") == 0)){
        printf("Saving the result... ");
        FILE *ofResult = fopen("./CalculateCubeVolumeResult.txt", "w");
        fprintf(ofResult, "The volume of a cube with length %.f, width %.f, and depth %.f is %.3f.", dbLength, dbWidth, dbDepth, dbResult);
        fclose(ofResult);
        printf("Done. \nResult saved to \"CalculateCubeVolumeResult.txt\". Exiting...\n");
        system("pause");
        return 0;
    }
// NO DON'T SAVE THE FILE
    else if((strcmp(szAnswer, "N") == 0) || (strcmp(szAnswer, "n") == 0)){
        printf("Exiting without saving...\n");
        system("pause");
        return 0;
    }
// INVALID INPUT, DON'T SAVE THE FILE
    else{
        printf("Invalid input (neither Y, y, N, nor n). \nExiting without saving...\n");
        system("pause");
        return -1;
    }
} // CalculateCubeVolume
