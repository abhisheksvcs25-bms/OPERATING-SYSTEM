#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: "); 
    scanf("%d", &n);
    printf("Enter number of resources: "); 
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];

    printf("Enter Allocation Matrix:\n"); 
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Demand Matrix:\n"); 
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n"); 
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int work[m]; 
    for (i = 0; i < m; i++) work[i] = avail[i];

    bool finish[n]; 
    for (i = 0; i < n; i++) finish[i] = false;

    int safeSeq[n], ind = 0;

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (finish[i] == false) { 
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) { 
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) { 
                    for (int y = 0; y < m; y++)
                        work[y] += alloc[i][y]; 
                    finish[i] = true; 
                    safeSeq[ind++] = i; 
                }
            }
        }
    }

    bool isSafe = true;
    for (i = 0; i < n; i++) {
        if (finish[i] == false) {
            isSafe = false;
            break;
        }
    }

    if (isSafe) {
        printf("\nSystem is in a safe state.\n"); 
        printf("Safe sequence is: "); 
        
        for (i = 0; i < n - 1; i++) printf("P%d -> ", safeSeq[i]);
        printf("P%d\n", safeSeq[n - 1]);
    } else {
        printf("\nSystem is in an UNSAFE STATE (Potential Deadlock).\n"); 
    }

    return 0;
}