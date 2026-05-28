#include <stdio.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int execution;
    int period;
    int remaining;
} Task;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int n = 3;

    Task tasks[MAX_TASKS] = {
        {1, 1, 4, 0},   // T1
        {2, 2, 5, 0},   // T2
        {3, 1, 20, 0}   // T3
    };

    int hyperperiod = tasks[0].period;

    for (int i = 1; i < n; i++) {
        hyperperiod = lcm(hyperperiod, tasks[i].period);
    }

    printf("RATE MONOTONIC SCHEDULING\n");
    printf("-------------------------\n");
    printf("Hyperperiod = %d\n\n", hyperperiod);

    printf("Gantt Chart:\n");

    for (int time = 0; time < hyperperiod; time++) {

        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining = tasks[i].execution;
            }
        }

        int selected = -1;

        for (int i = 0; i < n; i++) {

            if (tasks[i].remaining > 0) {

                if (selected == -1 ||
                    tasks[i].period < tasks[selected].period) {

                    selected = i;
                }
            }
        }

        if (selected != -1) {

            printf("| T%d ", tasks[selected].id);

            tasks[selected].remaining--;

        } else {

            printf("| IDLE ");
        }
    }

    printf("|\n\n");

    for (int i = 0; i <= hyperperiod; i++) {
        printf("%-5d", i);
    }

    return 0;
}