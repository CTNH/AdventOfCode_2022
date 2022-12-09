#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../C_BasicLib/basiclib_file.h"
#include "../C_BasicLib/basiclib_string.h"

int main(int argc, char const *argv[]) {
    char** input = readFileByLine("input");
    int lines = numOfLine(input);

    int invisTree = 0;
    int maxScenicScore = 0;
    for (int i = 1; i < lines-2; i++) {
        for (int j = 1; j < strlen(input[i])-2; j++) {
            // Assume tree is visible from all sides
            int currVisSides = 4;
            int treeView[] = {0, 0, 0, 0};

            // Check above of current
            for (int k = i-1; k > -1; k--) {
                treeView[0]++;
                if (input[k][j] >= input[i][j]) {
                    currVisSides--;
                    break;
                }
            }

            // Check below of current
            for (int k = i+1; k < lines-1; k++) {
                treeView[1]++;
                if (input[k][j] >= input[i][j]) {
                    currVisSides--;
                    break;
                }
            }

            // Check left of current
            for (int k = j-1; k > -1; k--) {
                treeView[2]++;
                if (input[i][k] >= input[i][j]) {
                    currVisSides--;
                    break;
                }
            }

            // Check right of current
            for (int k = j+1; k < strlen(input[i])-1; k++) {
                treeView[3]++;
                if (input[i][k] >= input[i][j]) {
                    currVisSides--;
                    break;
                }
            }

            // If tree is not visible from all sides
            if (currVisSides == 0) {
                invisTree++;
            }

            // Calculate scene score from current
            int scenicScore = 1;
            for (int k = 0; k < 4; k++) {
                scenicScore *= treeView[k];
            }
            // Set new max score if current is bigger than max
            if (scenicScore > maxScenicScore) {
                maxScenicScore = scenicScore;
            }
        }
    }
    printf("Part one: %d\n", (lines-1)*(strlen(input[0])-1) - invisTree);
    printf("Part two: %d\n", maxScenicScore);

    return 0;
}
