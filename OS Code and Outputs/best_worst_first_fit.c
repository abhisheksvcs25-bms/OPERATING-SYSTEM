#include <stdio.h>

#define BLOCKS 6
#define PROCESSES 5

void firstFit(int blockSize[], int processSize[]) {
    int allocation[PROCESSES];

    for (int i = 0; i < PROCESSES; i++)
        allocation[i] = -1;

    for (int i = 0; i < PROCESSES; i++) {
        for (int j = 0; j < BLOCKS; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] = 0;
                break;
            }
        }
    }

    printf("\nFIRST FIT\n");
    for (int i = 0; i < PROCESSES; i++) {
        printf("Process %d -> ", i + 1);

        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int processSize[]) {
    int allocation[PROCESSES];

    for (int i = 0; i < PROCESSES; i++)
        allocation[i] = -1;

    for (int i = 0; i < PROCESSES; i++) {

        int best = -1;

        for (int j = 0; j < BLOCKS; j++) {

            if (blockSize[j] >= processSize[i]) {

                if (best == -1 || blockSize[j] < blockSize[best]) {
                    best = j;
                }
            }
        }

        if (best != -1) {
            allocation[i] = best;
            blockSize[best] = 0;
        }
    }

    printf("\nBEST FIT\n");
    for (int i = 0; i < PROCESSES; i++) {
        printf("Process %d -> ", i + 1);

        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int processSize[]) {

    int allocation[PROCESSES];

    for (int i = 0; i < PROCESSES; i++)
        allocation[i] = -1;

    for (int i = 0; i < PROCESSES; i++) {

        int worst = -1;

        for (int j = 0; j < BLOCKS; j++) {

            if (blockSize[j] >= processSize[i]) {

                if (worst == -1 || blockSize[j] > blockSize[worst]) {
                    worst = j;
                }
            }
        }

        if (worst != -1) {
            allocation[i] = worst;
            blockSize[worst] = 0;
        }
    }

    printf("\nWORST FIT\n");
    for (int i = 0; i < PROCESSES; i++) {
        printf("Process %d -> ", i + 1);

        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {

    int blocks1[BLOCKS] = {300,600,350,200,750,125};
    int blocks2[BLOCKS] = {300,600,350,200,750,125};
    int blocks3[BLOCKS] = {300,600,350,200,750,125};

    int processes[PROCESSES] = {115,500,358,200,375};

    firstFit(blocks1, processes);
    bestFit(blocks2, processes);
    worstFit(blocks3, processes);

    return 0;
}