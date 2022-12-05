#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../C_BasicLib/basiclib_file.h"
#include "../C_BasicLib/basiclib_string.h"

// Find common characters between two strings
char* commonASCIIChar(char* str1, char* str2) {

    char* out = malloc(1);
    int outSize = 1;

    for (int i = 0; i < strlen(str1); i++) {
        if (charInStr(str1[i], str2)) {
            outSize++;
            out = realloc(out, outSize * sizeof(char));
            out[outSize-2] = str1[i];
        }
    }
    out[outSize-1] = '\0';
    return uniqueASCIICharInStr(out);
}


int main(int argc, char const *argv[]) {

    char** input = readFileByLine("input");
    int lines = numOfLine(input) - 1;

    // Part one
    int* dupItemType = malloc(0);
    int dupItemNum = 0;

    for (int i = 0; i < lines; i++) {
        int lineLength = strlen(input[i]);

        // Two compartments in each rucksack
        char** compartments = malloc(2 * sizeof(char*));
        for (int i = 0; i < 2; i++) {
            compartments[i] = malloc((lineLength/2 + 1) * sizeof(char));
        }

        // Copy line into compartments character by character
        for (int j = 0; j < lineLength/2; j++) {
            compartments[0][j] = input[i][j];
        }
        compartments[0][lineLength/2] = '\0';
        for (int j = lineLength/2; j < lineLength-1; j++) {
            compartments[1][j-(lineLength/2)] = input[i][j];
        }
        compartments[1][lineLength/2] = '\0';

        char* uCom1 = uniqueASCIICharInStr(compartments[0]);
        char* uCom2 = uniqueASCIICharInStr(compartments[1]);
        for (int j = 0; j < strlen(uCom1); j++) {
            if (charInStr(uCom1[j], uCom2) == 1) {
                dupItemNum++;
                dupItemType = realloc(dupItemType, dupItemNum * sizeof(int));
                dupItemType[dupItemNum-1] = uCom1[j];
                break;
            }
        }

    }

    int prioritySum = 0;
    for (int i = 0; i < dupItemNum; i++) {
        // a-z
        if (dupItemType[i] > 96) {
            prioritySum += dupItemType[i] - 96;
        }
        // A-Z
        else {
            prioritySum += dupItemType[i] - 38;
        }
    }
    printf("Part one: %d\n", prioritySum);


    // Part 2
    prioritySum = 0;
    for (int i = 0; i < lines/3; i++) {

        // Extract unique characters from each elf
        char** elfGroup = malloc(3 * sizeof(char*));
        for (int j = 0; j < 3; j++) {
            elfGroup[j] = uniqueASCIICharInStr(input[i*3 + j]);
        }

        char* str = commonASCIIChar(elfGroup[2], commonASCIIChar(elfGroup[0], elfGroup[1]));

        if (str[1] > 96) {
            prioritySum += str[1] - 96;
        }
        else {
            prioritySum += str[1] - 38;
        }
    }
    printf("Part two: %d\n", prioritySum);


    return 0;
}
