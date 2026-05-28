#include <stdio.h>
#include <limits.h>
#define MAX 10

void sjf_non_preemptive(int n, int at[], int bt[]) {
    int ct[MAX], tat[MAX], wt[MAX];
    int completed[MAX] = {0};
    int time = 0, done = 0;

    while (done < n) {
        int idx = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= time) {
                if (bt[i] < min_bt) {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++; // CPU idle
        } else {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed[idx] = 1;
            done++;
        }
    }

    printf("\n--- SJF Non-Preemptive ---\n");
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}

void sjf_preemptive(int n, int at[], int bt[]) {
    int rt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int completed = 0, time = 0;

    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    while (completed < n) {
        int idx = -1;
        int min_rt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {

                if (rt[i] < min_rt) {
                    min_rt = rt[i];
                    idx = i;
                }

                // FCFS tie breaker: earlier arrival time wins
                else if (rt[i] == min_rt) {
                    if (idx == -1 ||
                        at[i] < at[idx] ||
                        (at[i] == at[idx] && i < idx)) {
                        idx = i;
                    }
                }
            }
        }

        // CPU idle case
        if (idx == -1) {
            time++;
            continue;
        }

        rt[idx]--;
        time++;

        if (rt[idx] == 0) {
            ct[idx] = time;
            completed++;
        }
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printf("\n--- SJF Preemptive (SRTF) with FCFS Tie Break ---\n");
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}
int main() {
    int n = 4;
    int at[MAX] = {0,8,3,5};
    int bt[MAX] = {7,3,4,6};

    sjf_non_preemptive(n, at, bt);
    sjf_preemptive(n, at, bt);

    return 0;
}