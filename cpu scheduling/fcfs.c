#include <stdio.h>

int n, at[10], bt[10], tt[10], wt[10], ct[10], pno[10];
int total_tt = 0, total_wt = 0;
float avg_tt, avg_wt;

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sort()
{
    for (int i = 0; i < n; i++)
    {
        int shortest = i;
        for (int j = i + 1; j < n; j++)
        {
            if (at[j] < at[shortest])
            {
                shortest = j;
            }
        }
        swap(&at[i], &at[shortest]);
        swap(&bt[i], &bt[shortest]);
        swap(&pno[i], &pno[shortest]);
    }
}

void fcfs()
{
    int exitTime = at[0];
    for (int i = 0; i < n; i++)
    {
        ct[i] = exitTime + bt[i];
        tt[i] = ct[i] - at[i];
        wt[i] = tt[i] - bt[i];
        exitTime = ct[i];
        total_tt += tt[i];
        total_wt += wt[i];
    }
}

void show()
{
    printf("\n\nPno\t\tAT\t\tBT\t\tCT\t\tTT\t\tWT");
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
        pno[i] = i + 1;

    sort();
    fcfs();
    show();
}