/// brief: getCharTest.c
///
/// My personal notes 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INC 10 // string size will be in multiples of ten.

char* ReadString(FILE* ofInput, size_t iSize);

int main(void){
// dynamically allocated string practice
    char *sOut;     // dynamically allocated string
    size_t iSize;   // initial size of string. 
  
    iSize = INC; // arbitrary size
    printf("Size is %d.\n", iSize); // for reference
    
    printf("Please enter in a string. Make is as long as you'd like.\n");
    
    sOut = ReadString(stdin, iSize);
    
    printf("Your string:\n%s\n", sOut);
    free(sOut);
    return 0;
} // main

/**
 * \brief ReadString reads in a string of potentially unlimited length. 
 *
 * Adapted from http://stackoverflow.com/questions/16870485/how-can-i-read-an-input-string-of-unknown-length
 */
char* ReadString(FILE* ofInput, size_t iSize){
    char *szStr;    // output string
    int iCh;        // input character to concat to the string
    size_t ii = 0;  // string position counter
    
    // The next line obtains a new block of memory for the string of size "iSize".
    // Using NULL instead of a pointer will obtain a new block of memory.
    // Typically the first argument is a pointer previously allocated with "malloc". 
    // "realloc" will change the allocated size of the memory block pointed to
    // in the first argument. 
    szStr = realloc(NULL, sizeof(char)*iSize);//size is start size
    
    // Here, in case we have a null string and have run out of memory
    // we'll return with the empty string.
    if(!szStr)return szStr;
    
    // Essentially the next line will keep getting input from the
    // keyboard until you hit a new line. Or Enter. 
    while(EOF!=(iCh=fgetc(ofInput)) && iCh != '\n'){
        
        // set the string value at location ii to the
        // input character, then increment ii after the operation.
        szStr[ii++]=iCh;
        
        // if the string position is at the size of the string
        // (this will happen before the while loop repeats and 
        // a new character is read from the buffer)...
        if(ii==iSize){
            // ...increase the string size because we're about to hit a buffer
            // overflow.
            // Like we said, the first argument is a pointer to the location
            // in memory. We're returning a pointer to the same location
            // but with a greater size. It will return a NULL if it fails, 
            // like if there's no more memory available.
            // Here we're incresing the size by iIncSize. 
            // sizeof(char) is the size in bytes of the char data type.
            // sizeof(char)*(iSize+=iIncSize) is the new size of the memory block.
            szStr = realloc(szStr, sizeof(char)*(iSize+=INC));
            if(!szStr)return szStr;
        }
    }
    // Here we'll null-terminate the string. However I don't know why we increase the 
    // counter value again. 
    szStr[ii++]='\0';

    // At this point in time we have a null-terminated string but with extra 
    // empty blocks of memory that we don't want reserved. So we'll now free up that memory
    // so it can be used again. We'll combine this step with returning the
    // pointer to the string. It looks cooler than two-steps. 
    return realloc(szStr, sizeof(char)*ii);
}// ReadString

