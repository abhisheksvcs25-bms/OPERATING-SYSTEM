#include <stdio.h>

#define MAX 20

struct process {
    int pid;
    int burst_time;
    int category; // 0 = System, 1 = User
};

void fcfs(struct process p[], int n) {
    int wt[MAX], tat[MAX];
    int i;

    wt[0] = 0;

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + p[i - 1].burst_time;
    }

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + p[i].burst_time;
    }

    printf("\nPID\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].burst_time,
               wt[i],
               tat[i]);
    }
}

int main() {
    struct process system[] = {
        {1, 5, 0},
        {3, 2, 0},
        {5, 3, 0}
    };

    struct process user[] = {
        {2, 4, 1},
        {4, 6, 1}
    };

    int sys_count = 3;
    int user_count = 2;

    printf("=== Multi-Level Queue Scheduling (FCFS) ===\n");

    printf("\n--- System Processes (High Priority) ---");
    fcfs(system, sys_count);

    printf("\n--- User Processes (Low Priority) ---");
    fcfs(user, user_count);

    return 0;
}