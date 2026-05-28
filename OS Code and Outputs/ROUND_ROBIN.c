#include <stdio.h>

int main() {
    int n = 5;
    int quantum = 2;

    int burst_time[5]   = {5, 3, 1, 2, 3};
    int arrival_time[5] = {0, 1, 2, 3, 4};

    int remaining[5];
    int completion[5];
    int waiting[5];
    int turnaround[5];

    int queue[100];
    int front = 0, rear = 0;

    int visited[5] = {0};

    for (int i = 0; i < n; i++)
        remaining[i] = burst_time[i];

    int time = 0;
    int completed = 0;

    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {

        if (front == rear) {
            time++; // CPU idle
            for (int i = 0; i < n; i++) {
                if (!visited[i] && arrival_time[i] <= time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++];

        if (remaining[i] > quantum) {
            time += quantum;
            remaining[i] -= quantum;
        } else {
            time += remaining[i];
            remaining[i] = 0;
            completion[i] = time;
            completed++;
        }

        for (int j = 0; j < n; j++) {
            if (!visited[j] && arrival_time[j] <= time) {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        if (remaining[i] > 0) {
            queue[rear++] = i;
        }
    }

    for (int i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival_time[i];
        waiting[i] = turnaround[i] - burst_time[i];
    }

    printf("P\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               arrival_time[i],
               burst_time[i],
               completion[i],
               turnaround[i],
               waiting[i]);
    }

    return 0;
}