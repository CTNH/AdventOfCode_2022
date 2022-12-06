#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../C_BasicLib/basiclib_file.h"
#include "../C_BasicLib/basiclib_string.h"


int main(int argc, char const *argv[]) {
    char** input = readFileByLine("input");

    int markerLength[] = {4, 14};

    for (int part = 0; part < 2; part++) {
        for (int i = 0; i < strlen(input[0])-1; i++) {
            char tmp[markerLength[part]];
            for (int j = 0; j < markerLength[part]; j++) {
                tmp[j] = input[0][i+j];
            }
            if (strlen(uniqueASCIICharInStr(tmp)) == markerLength[part]) {
                printf("Part %i: %d\n", part+1, i+markerLength[part]);
                break;
            }
        }
    }

    return 0;
}
