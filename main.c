#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isValidIsbn( char* isbnNumber);
bool checkNumbersAndHyphons( char* isbnNumber);
void getIsbnNumber(char* isbnNumber);
bool isHyphon( char* currentIsbnChar);
bool isLetterX( char* currentIsbnChar);
bool isNumber( char* currentIsbnChar);
bool isAdjacentHyphen(char * currentIsbnChar, char * previousIsbnChar);

int main(){
    bool isValid = false;
	char* isbnNumber[14];

	do{
        getIsbnNumber(*isbnNumber);
        isValid = isValidIsbn(*isbnNumber);
	} while(!isValid);
}

void getIsbnNumber(char* isbnNumber){
    printf("ENTER YOUR ISBN: ");
	gets(isbnNumber);
}

bool checkNumbersAndHyphons( char* isbnNumber){
    int hyphonCounter = 0;
    int numberCounter = 0;

    for(int i = 0; i < 13; i++){
        char currentIsbnChar = isbnNumber[i];

        if(isHyphon(&currentIsbnChar))
            hyphonCounter++;
        else if(isNumber(&currentIsbnChar))
            numberCounter++;
    }
    return hyphonCounter == 3 && numberCounter == 10;
}

int isbnCalculation(char* isbnNumber){
    int result = 0;
    int isbnMultiplier = 10;

    for(int i = 0; i <= 13; i++){
        char currentIsbnChar = isbnNumber[i];

        if(i > 0 && isAdjacentHyphen(&currentIsbnChar, &isbnNumber[i-1])){
            printf("TWO OR MORE HYPHENS ADJACENT");
            return false;
        }
        else if(isNumber(&currentIsbnChar)){
            result += (currentIsbnChar-48) * isbnMultiplier;
            isbnMultiplier--;
        }
        else if(isLetterX(&currentIsbnChar)){
            result += 10 * isbnMultiplier;
            isbnMultiplier--;
        }
    }
    return result % 11;
}

bool isValidIsbn(char* isbnNumber){
    if(checkNumbersAndHyphons(isbnNumber) && isbnCalculation(isbnNumber) == 0){
        printf("VALID ISBN");
        return true;
    }
    else{
        printf("INVALID ISBN");
        return false;
    }
}


bool isAdjacentHyphen(char* currentIsbnChar, char* previousIsbnChar){
    return *currentIsbnChar == 45 && *previousIsbnChar == 45;
}

bool isLetterX(char* currentIsbnChar){
    return *currentIsbnChar == 120 || *currentIsbnChar == 88;
}
bool isNumber(char *currentIsbnChar){
    return *currentIsbnChar >=48 && *currentIsbnChar <=57;
}
bool isHyphon(char *currentIsbnChar){
    return *currentIsbnChar == 45;
}
