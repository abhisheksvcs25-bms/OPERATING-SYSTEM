#include <stdio.h>

#define MAX 10

typedef struct {
    int pid;
    int at;   // arrival time
    int bt;   // burst time
    int pr;   // priority
    int rt;   // remaining time (for preemptive)
    int ct;   // completion time
    int wt;
    int tat;
    int completed;
} Process;

void sortByArrival(Process p[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j].at > p[j+1].at) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void priorityNonPreemptive(Process p[], int n) {
    int time = 0, completed = 0;

    while(completed < n) {
        int idx = -1;
        int bestPr = 1e9;

        for(int i = 0; i < n; i++) {
            if(!p[i].completed && p[i].at <= time) {
                if(p[i].pr < bestPr ||
                  (p[i].pr == bestPr && p[i].at < p[idx].at)) {
                    bestPr = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].completed = 1;

        completed++;
    }

    printf("\n--- Non Preemptive Priority Scheduling ---\n");
    printf("PID\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].ct, p[i].tat, p[i].wt);
}

void priorityPreemptive(Process p[], int n) {
    int time = 0, completed = 0;

    for(int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while(completed < n) {
        int idx = -1;
        int bestPr = 1e9;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0) {
                if(p[i].pr < bestPr ||
                  (p[i].pr == bestPr && p[i].at < p[idx].at)) {
                    bestPr = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            time++;
            continue;
        }

        p[idx].rt--;
        time++;

        if(p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
    }

    printf("\n--- Preemptive Priority Scheduling ---\n");
    printf("PID\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].ct, p[i].tat, p[i].wt);
}

int main() {
    Process p1[MAX] = {
        {1, 0, 3, 5, 0, 0, 0, 0, 0},
        {2, 2, 2, 3, 0, 0, 0, 0, 0},
        {3, 3, 5, 2, 0, 0, 0, 0, 0},
        {4, 4, 4, 4, 0, 0, 0, 0, 0},
        {5, 6, 1, 1, 0, 0, 0, 0, 0}
    };

    Process p2[MAX];

    int n = 5;

    for(int i = 0; i < n; i++)
        p2[i] = p1[i];

    sortByArrival(p1, n);
    sortByArrival(p2, n);

    priorityNonPreemptive(p1, n);
    priorityPreemptive(p2, n);

    return 0;
}