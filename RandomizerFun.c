// Randomizer functions


// ReadString. Helper function to take as an input a string of potentially
// unlimited length. Uses dynamic allocation.
// Adapted from http://stackoverflow.com/questions/16870485/how-can-i-read-an-input-string-of-unknown-length
char* ReadString(FILE* ofInput, size_t iSize){
//The size is extended by the input with the value of the provisional
    char *szStr;
    int iCh;
    size_t len = 0;
    szStr = realloc(NULL, sizeof(char)*iSize);//size is start size
    if(!szStr)return szStr;
    while(EOF!=(iCh=fgetc(ofInput)) && iCh != '\n'){
        szStr[len++]=iCh;
        if(len==iSize){
            szStr = realloc(szStr, sizeof(char)*(iSize+=16));
            if(!szStr)return szStr;
        }
    }
    szStr[len++]='\0';

    return realloc(szStr, sizeof(char)*len);
}// ReadString

// DiceRoll. User inputs number of dice, number of sides, and number of rolls.
// Input sanitation must be utilized. Return -1 if any invalid input is detected. 
// Print out the results of each roll per die. 
int DiceRoll(){
	int iNumDie, iSides, iRolls;
	int ii, jj, kk; // loop counters
	//int t; // "RNG" initializer
	//char szNumDie[256], szSides[256], szRolls[256]; /// todo: dynamic allocation
	char *szNumDie, *szSides, *szRolls;
	
	srand((unsigned) time());
	
// OBTAIN USER INPUT
	
	// number of dice
	printf("Enter number of dice: ");
	//scanf("%s", &szNumDie);
	szNumDie = ReadString(stdin, 10);	
	iNumDie = atoi(szNumDie);
	if(iNumDie<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		//system("pause");
		return -1;
	}
	//printf("\n");
	
	// number of sides per die
	printf("Enter number of sides per die: ");
	//scanf("%s", &szSides);
	szSides = ReadString(stdin, 10);
	iSides = atoi(szSides);
	if(iSides<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		//system("pause");
		return -1;
	}
	//printf("\n");
	
	// number of rolls
	printf("Enter number of rolls per die: ");
	//scanf("%s", &szRolls);
	szRolls = ReadString(stdin, 10);
	iRolls = atoi(szRolls);
	if(iRolls<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		//system("pause");
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
	//system("pause");
	
	free(szNumDie);
	free(szRolls);
	free(szSides);
	return 0;
} // DiceRoll

// CalculateCircleArea. User inputs radius. 
// Input sanitation must be utilized. 
// Print out the surface area of the circle.
// User has option to save result to a text file. 
int CalculateCircleArea(){
	double dbRadius, dbResult;
	char* szRadius, szAnswer;
	
	const double dbPi = 3.14159;
	//const char *szOutputFile; // for file writing purposes 
	
	printf("Input circle radius: ");
	//scanf("%s", &szRadius);
	szRadius = ReadString(stdin, 10);
	
	dbRadius = atof(szRadius);
	
	if(dbRadius<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		//system("pause");
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
        //system("pause");
        return 0;
    }
// NO DON'T SAVE THE FILE
    else if((strcmp(szAnswer, "N") == 0) || (strcmp(szAnswer, "n") == 0)){
        printf("Exiting without saving...\n");
        //system("pause");
        return 0;
    }
// INVALID INPUT, DON'T SAVE THE FILE
    else{
        printf("Invalid input (neither Y, y, N, nor n). \nExiting without saving...\n");
        //system("pause");
        return -1;
    }
} // CalculateCircleArea


// CalculateCubeVolume. User inputs height, width, and depth. 
// Input sanitation must be utilized. 
// Print out the volume of the cube. 
// User has option to save result to a text file.
int CalculateCubeVolume(){
	double dbLength, dbWidth, dbDepth, dbResult;
    char* szLength, szWidth, szDepth, szAnswer;
    
    // length
    printf("Input cube length: ");
    //scanf("%s", &szLength);
    szLength = ReadString(stdin, 10);
    dbLength = atof(szLength);
    if(dbLength<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		//system("pause");
		return -1;
	}
    
    // width
    printf("Input cube width: ");
    scanf("%s", &szWidth);
    dbWidth = atof(szWidth);    
    if(dbWidth<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		//system("pause");
		return -1;
	}
    
    // depth
    printf("Input cube depth: ");
    scanf("%s", &szDepth);
    dbDepth = atof(szDepth);    
    if(dbDepth<=0){
		printf("Invalid (input is zero, begins with non-integers, or is negative)\nExiting...\n");
		//system("pause");
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
        //system("pause");
        return 0;
    }
// NO DON'T SAVE THE FILE
    else if((strcmp(szAnswer, "N") == 0) || (strcmp(szAnswer, "n") == 0)){
        printf("Exiting without saving...\n");
        //system("pause");
        return 0;
    }
// INVALID INPUT, DON'T SAVE THE FILE
    else{
        printf("Invalid input (neither Y, y, N, nor n). \nExiting without saving...\n");
        //system("pause");
        return -1;
    }
} // CalculateCubeVolume
