#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void getIsbnNumber(char* isbnNumber);
bool checkNumbersAndHyphens(char* isbnNumber);
int isbnCalculation(char* isbnNumber);
bool isValidIsbn(char* isbnNumber);

bool isNumber(char* currentIsbnChar);
bool isHyphen(char* currentIsbnChar);
bool isLetterX(char* currentIsbnChar);
bool isAdjacentHyphen(char* currentIsbnChar, char* previousIsbnChar);



int main(){

    bool isValid = false;
	char* isbnNumber[14];

	do{// Asks for the ISBN every time its false
        getIsbnNumber(isbnNumber);
        isValid = isValidIsbn(isbnNumber);
	}while(!isValid);
}



void getIsbnNumber(char* isbnNumber){
    printf("ENTER YOUR ISBN: ");
	gets(isbnNumber);
}


bool checkNumbersAndHyphens(char* isbnNumber){
    int numberCounter = 0;
    int hyphonCounter = 0;

    for(int i = 0; i <= 13; i++){  // Iterating over the ISBN to check how many numbers and hyphens there are

        char currentIsbnChar = isbnNumber[i];

        if(i > 0 && isAdjacentHyphen(&currentIsbnChar, &isbnNumber[i-1])){
            printf("TWO OR MORE HYPHENS ADJACENT");
            return false;
        }
        else if(isNumber(&currentIsbnChar) || isLetterX(&currentIsbnChar))
            numberCounter++;
        else if(isHyphen(&currentIsbnChar))
            hyphonCounter++;
    }
    return hyphonCounter == 3 && numberCounter == 10;
}


int isbnCalculation(char* isbnNumber){
    int result = 0;
    int isbnMultiplier = 10;

    for(int i = 0; i <= 13; i++){

        char currentIsbnChar = isbnNumber[i];
        if(isNumber(&currentIsbnChar)){
            result += (currentIsbnChar-48) * isbnMultiplier; // The Character gets interpreted as its ASCII value, so we need to Subtract 48
            isbnMultiplier--;
        }
        else if(isLetterX(&currentIsbnChar)){
            result += 10 * isbnMultiplier; // The Letter X is treated as if its the number 10
            isbnMultiplier--;
        }
    }
    return result % 11;
}


bool isValidIsbn(char* isbnNumber){
    if(checkNumbersAndHyphens(isbnNumber) && isbnCalculation(isbnNumber) == 0){
        printf("\nVALID ISBN\n");
        return true;
    }
    else{
        printf("\nINVALID ISBN\n\n");
        return false;
    }
}


// "Helper Functions"

bool isNumber(char* currentIsbnChar){
    return *currentIsbnChar >=48 && *currentIsbnChar <=57; // Checks if the current ISBN Character is a Number
}

bool isHyphen(char* currentIsbnChar){
    return *currentIsbnChar == 45; // Checks if the current ISBN Character is a Hyphen
}

bool isLetterX(char* currentIsbnChar){
    return *currentIsbnChar == 120 || *currentIsbnChar == 88; // Checks if the current ISBN Character is the letter X or x
}

bool isAdjacentHyphen(char* currentIsbnChar, char* previousIsbnChar){
    return *currentIsbnChar == 45 && *previousIsbnChar == 45; // Checks if the current and previous ISBN Characters are both a Hyphen
}
