#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../C/MyLib/mylib_file.h"
#include "../../C/MyLib/mylib_string.h"

int main(int argc, char const *argv[]) {
    char** input = readFileByLine("input");
    int lines = numOfLine(input) - 1;

    char* originalStack[9];
    originalStack[0] = "BZT";
    originalStack[1] = "VHTDN";
    originalStack[2] = "BFMD";
    originalStack[3] = "TJGWVQL";
    originalStack[4] = "WDGPVFQM";
    originalStack[5] = "VZQGHFS";
    originalStack[6] = "ZSNRLTCW";
    originalStack[7] = "ZHWDJNRM";
    originalStack[8] = "MQLFDS";


    int stackPtr[9];
    for (int i = 0; i < 9; i++) {
        stackPtr[i] = strlen(originalStack[i])-1;
    }

    char** stack = malloc(9 * sizeof(char*));

    // Part one
    for (int i = 0; i < 9; i++) {
        stack[i] = malloc((stackPtr[i]+2) * sizeof(char));
        memcpy(stack[i], originalStack[i], stackPtr[i]+1);
        stack[i][stackPtr[i]+1] = '\0';
    }

    // Procedures begin at 10
    for (int i = 10; i < lines; i++) {
        char** tmp = strSplit(input[i], "from");

        // Remove "move " from the string
        char* moveStr = malloc((strlen(tmp[0])-5) * sizeof(char));
        for (int j = 0; j < strlen(tmp[0])-5; j++) {
            moveStr[j] = tmp[0][j+5];
        }
        moveStr[strlen(tmp[0])-6] = '\0';   // Terminate string
        int move = strtol(moveStr, NULL, 10);

        tmp = strSplit(tmp[1], "to");
        // Arrays starts from 0 -> -1
        int from = strtol(tmp[0], NULL, 10) - 1;
        int to = strtol(tmp[1], NULL, 10) - 1;


        for (int j = 0; j < move; j++) {
            stackPtr[to]++;
            stack[to] = realloc(stack[to], (stackPtr[to]+1) * sizeof(char));
            stack[to][stackPtr[to]] = stack[from][stackPtr[from]];

            stackPtr[from]--;
            stack[from] = realloc(stack[from], (stackPtr[from]+1) * sizeof(char));
        }
    }

    char stackTop[9];
    for (int i = 0; i < 9; i++) {
        stackTop[i] = stack[i][stackPtr[i]];
    }
    printf("Part one: %s\n", stackTop);


    // Part two
    input = readFileByLine("input");
    for (int i = 0; i < 9; i++) {
        stackPtr[i] = strlen(originalStack[i])-1;
    }
    stack = malloc(9 * sizeof(char*));
    for (int i = 0; i < 9; i++) {
        stack[i] = malloc((stackPtr[i]+2) * sizeof(char));
        memcpy(stack[i], originalStack[i], stackPtr[i]+1);
        stack[i][stackPtr[i]+1] = '\0';
    }

    for (int i = 10; i < lines; i++) {
        char** tmp = strSplit(input[i], "from");

        // Remove "move " from the string
        char* moveStr = malloc((strlen(tmp[0])-5) * sizeof(char));
        for (int j = 0; j < strlen(tmp[0])-5; j++) {
            moveStr[j] = tmp[0][j+5];
        }
        moveStr[strlen(tmp[0])-6] = '\0';   // Terminate string
        int move = strtol(moveStr, NULL, 10);

        tmp = strSplit(tmp[1], "to");
        // Arrays starts from 0 -> -1
        int from = strtol(tmp[0], NULL, 10) - 1;
        int to = strtol(tmp[1], NULL, 10) - 1;


        stackPtr[to] += move;
        stack[to] = realloc(stack[to], (stackPtr[to]+1) * sizeof(char));
        for (int j = 0; j < move; j++) {
            stack[to][stackPtr[to]-move+1+j] = stack[from][stackPtr[from]-move+j+1];
        }
        stackPtr[from] -= move;
        stack[from] = realloc(stack[from], (stackPtr[from]+1) * sizeof(char));
    }

    for (int i = 0; i < 9; i++) {
        stackTop[i] = stack[i][stackPtr[i]];
    }
    printf("Part two: %s\n", stackTop);


    return 0;
}
