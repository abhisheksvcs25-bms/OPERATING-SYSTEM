#include <stdio.h>

#define N 3
#define LCM 24

struct Process {
    int id;
    int burst;
    int rel_deadline;
    int period;
};

struct Job {
    int active;
    int remaining;
    int deadline;
    int id;
};

int main() {

    struct Process p[N] = {
        {1, 1, 4, 4},
        {2, 2, 6, 6},
        {3, 3, 8, 8}
    };

    struct Job job[100];  

    for(int i = 0; i < 100; i++)
        job[i].active = 0;

    int jobCount = 0;

    printf("Gantt Chart:\n");

    for(int t = 0; t < LCM; t++) {

        for(int i = 0; i < N; i++) {
            if(t % p[i].period == 0) {

                job[jobCount].id = p[i].id;
                job[jobCount].remaining = p[i].burst;
                job[jobCount].deadline = t + p[i].rel_deadline;
                job[jobCount].active = 1;

                jobCount++;
            }
        }

        int idx = -1;
        int min_deadline = 99999;

        for(int i = 0; i < jobCount; i++) {
            if(job[i].active && job[i].remaining > 0) {
                if(job[i].deadline < min_deadline) {
                    min_deadline = job[i].deadline;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            printf(" P%d ", job[idx].id);
            job[idx].remaining--;

            if(job[idx].remaining == 0)
                job[idx].active = 0;
        }
        else {
            printf(" - ");
        }
    }

    printf("\n");
    return 0;
}