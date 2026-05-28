#include <stdio.h>

int main() {
    int n = 5;  

    int at[] = {0, 1, 2, 3, 4};
    int bt[] = {5, 3, 1, 2, 3};

    int ct[5], tat[5], wt[5];

    int current_time = 0;

    puts("FCFS Scheduling Algorithm");

    for (int i = 0; i < n; i++) {
        if (current_time < at[i]) {
            current_time = at[i];
        }

        ct[i] = current_time + bt[i];
        current_time = ct[i];

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    puts("\nP\tAT\tBT\tCT\tTAT\tWT");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    return 0;
}