#include <stdio.h>
#include <limits.h>

int n, at[10], bt[10], tt[10], wt[10], ct[10], pno[10], visited[10];
int total_tt = 0, total_wt = 0;
float avg_tt, avg_wt;

void sjn()
{
    int count = 0, currTime = 0;
    while (count != n)
    {
        int pid = -1, min_bt = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= currTime && visited[i] == 0)
            {
                if (bt[i] < min_bt)
                {
                    min_bt = bt[i];
                    pid = i;
                }
                else if (bt[i] == min_bt)
                {
                    if (at[i] < at[pid])
                        pid = i;
                }
            }
        }

        if (pid != -1)
        {
            currTime += bt[pid];
            ct[pid] = currTime;
            tt[pid] = ct[pid] - at[pid];
            wt[pid] = tt[pid] - bt[pid];
            visited[pid] = 1;

            total_tt += tt[pid];
            total_wt += wt[pid];
            count++;
        }
        else
            currTime++;
    }
}

void show()
{
    printf("\nPno\t\tAT\t\tBT\t\tCT\t\tTT\t\tWT");
    for (int i = 0; i < n; i++)
    {
        printf("\nP%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", pno[i], at[i], bt[i], ct[i], tt[i], wt[i]);
    }

    avg_tt = (float)total_tt / n;
    avg_wt = (float)total_wt / n;
    printf("\n\nAverage TT : %.3f", avg_tt);
    printf("\nAverage WT : %.3f", avg_wt);
}

void main()
{
    printf("\nNumber of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("arrival time: ");
        scanf("%d", &at[i]);
        printf("burst time: ");
        scanf("%d", &bt[i]);
    }

    for (int i = 0; i < n; i++)
    {
        pno[i] = i + 1;
        visited[i] = 0;
    }

    sjn();
    show();
}