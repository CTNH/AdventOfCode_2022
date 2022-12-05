#include <stdio.h>

#include "../C_BasicLib/basiclib_file.h"

// Part 1
// A for Rock, B for Paper, and C for Scissors
// X for Rock, Y for Paper, and Z for Scissors

// Ascii
// A = 65
// B = 66
// C = 67
// X = 88
// Y = 89
// Z = 90


int main(int argc, char const *argv[]) {

    char** input = readFileByLine("input");
    int lines = numOfLine(input) - 1;

    int totalscore = 0;

    // Part one
    for (int i = 0; i < lines; i++) {
        switch (input[i][0]) {
            case 65:    // A (Rock)
                switch (input[i][2]) {
                    case 88:    // X
                        totalscore += 3;
                        break;
                    case 89:    // Y
                    totalscore += 6;
                        break;
                    case 90:    // Z
                        break;
                }
                break;
            case 66:    // B (Paper)
                switch (input[i][2]) {
                    case 88:    // X
                        break;
                    case 89:    // Y
                        totalscore += 3;
                        break;
                    case 90:    // Z
                        totalscore += 6;
                        break;
                }
                break;
            case 67:    // C (Scissors)
                switch (input[i][2]) {
                    case 88:    // X
                        totalscore += 6;
                        break;
                    case 89:    // Y
                        break;
                    case 90:    // Z
                        totalscore += 3;
                        break;
                }
                break;
        }

        switch (input[i][2]) {
            case 88:
                totalscore += 1;
                break;
            case 89:
                totalscore += 2;
                break;
            case 90:
                totalscore += 3;
                break;
        }
    }
    printf("Part one: %i\n", totalscore);


    // Part two
    totalscore = 0;
    for (int i = 0; i < lines; i++) {
        switch (input[i][2]) {
            case 88:    // X - Lose
                switch (input[i][0]) {
                    case 65:
                        totalscore += 3;
                        break;
                    case 66:
                        totalscore += 1;
                        break;
                    case 67:
                        totalscore += 2;
                        break;
                }
                break;
            case 89:    // Y - Draw
                totalscore += 3;
                switch (input[i][0]) {
                    case 65:
                        totalscore += 1;
                        break;
                    case 66:
                        totalscore += 2;
                        break;
                    case 67:
                        totalscore += 3;
                        break;
                }
                break;
            case 90:    // Z - Win
                totalscore += 6;
                switch (input[i][0]) {
                    case 65:
                        totalscore += 2;
                        break;
                    case 66:
                        totalscore += 3;
                        break;
                    case 67:
                        totalscore += 1;
                        break;
                }
                break;
        }
    }
    printf("Part two: %i\n", totalscore);

    return 0;
}
