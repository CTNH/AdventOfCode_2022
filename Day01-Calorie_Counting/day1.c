#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Compare function for qsort
int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int* find3largest(int arr[], int n) {
    qsort(arr, n, sizeof(int), cmpfunc);

    int* out = malloc(3*sizeof(int));

    int check = 0, count = 1;
    for (int i = 1; i <= n; i++) {
        if (count < 4) {
            if (check != arr[n - i]) {
                // to handle duplicate values
                // printf("%d ", arr[n - i]);
                check = arr[n - i];
                out[count-1] = arr[n-i];
                count++;
            }
        }
        else
            break;
    }
    return out;
}


int main(int argc, char const *argv[]) {
    FILE* fp;

    fp = fopen("input", "r");

    int elfNumber = 0;
    int* elf = malloc(0); // sizeof(int*)

    int foodNum = 0;
    int* currentElf = malloc(0);

    int current, prev;

    char* line = malloc(0);
    int lineSize = 0;

    // Read input and store in array
    while (1) {
        // Get character from file
        int current = fgetc(fp);
        // Break on end of file
        if (feof(fp)) {
            break;
        }

        // Increment line size and reallocate line
        lineSize++;
        line = realloc(line, lineSize * sizeof(char));
        // Append character to line
        line[lineSize-1] = current;

        if (current == '\n' && prev == '\n') {
            // Add space for one more elf
            elfNumber++;
            elf = realloc(elf, elfNumber*sizeof(int));
            // Add total calories of food current elf has
            for (int i = 0; i < foodNum; i++) {
                elf[elfNumber-1] += currentElf[i];
            }
            // Reset current elf
            foodNum = 0;
            currentElf = malloc(0);
        }

        if (current == '\n') {
            // Terminate current line
            line[lineSize-1] = '\0';
            // Append food calories to current elf
            foodNum++;
            currentElf = realloc(currentElf, foodNum*sizeof(int));

            // Convert line to integers
            long calories;
            char *str;
            calories = strtol(line, &str, 10);

            currentElf[foodNum-1] = calories;

            lineSize = 0;
            line = malloc(0);
        }

        prev = current;
    }

    int maxCalories = elf[0];
    int maxCalElf = 0;
    for (int i = 1; i < elfNumber; i++) {
        if (elf[i] > maxCalories) {
            maxCalElf = i;
            maxCalories = elf[i];
        }
    }
    printf("Elf %i has the most food of %i calories\n", maxCalElf, maxCalories);
    int *topElf = find3largest(elf, elfNumber);
    printf("%i\n", topElf[0]+topElf[1]+topElf[2]);
    printf("\n");

    return 0;
}
