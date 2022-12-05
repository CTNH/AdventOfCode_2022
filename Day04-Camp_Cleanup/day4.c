#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../C/MyLib/mylib_file.h"
#include "../../C/MyLib/mylib_string.h"

int main(int argc, char const *argv[]) {

    char** input = readFileByLine("input");
    int lines = numOfLine(input) - 1;

    int fullyContainPairs = 0;      // Part one
    int overlap = 0;                // Part two

    for (int i = 0; i < lines; i++) {
        char** elf = strSplit(input[i], ",");

        long start[2], end[2];
        for (int j = 0; j < 2; j++) {
            char** tmp = strSplit(elf[j], "-");

            char* str;
            start[j] = strtol(tmp[0], &str, 10);
            end[j] = strtol(tmp[1], &str, 10);
        }

        // Part one - Check if pairs are fully contained
        for (int j = 0; j < 2; j++) {
            if (start[j] >= start[1-j]) {
                if (end[j] <= end[1-j]) {
                    fullyContainPairs++;
                    break;
                }
            }
        }

        // Part Two
        for (int j = 0; j < 2; j++) {
            if ((start[j] <= end[1-j] && start[j] >= start[1-j]) || (end[j] <= end[1-j] && end[j] >= start[1-j])) {
                overlap++;
                break;
            }
        }
    }

    printf("Part one: %d\n", fullyContainPairs);
    printf("Part two: %d\n", overlap);

    return 0;
}
