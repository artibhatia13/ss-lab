#include <stdio.h>

int n, at[10], bt[10], tt[10], wt[10], rt[10], ct[10], pno[10], completed[10], temp_bt[10];
int total_tt = 0, total_wt = 0;
float avg_tt, avg_wt;

const int timeQuantum = 2;

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

void roundRobin()
{
    int currTime = at[0];
    int count = 0, i = 0;

    for (int i = 0; i < n; i++)
        temp_bt[i] = bt[i];

    while (count != n)
    {
        if (at[i] > currTime)
            currTime = at[i];

        if (temp_bt[i] == bt[i])
            rt[i] = currTime - at[i];

        if (temp_bt[i] <= timeQuantum && temp_bt[i] > 0)
        {
            currTime += temp_bt[i];
            temp_bt[i] = 0;

            ct[i] = currTime;
            tt[i] = ct[i] - at[i];
            wt[i] = tt[i] - bt[i];
            total_tt += tt[i];
            total_wt += wt[i];
            count++;
        }
        else if (temp_bt[i] > 0)
        {
            temp_bt[i] -= timeQuantum;
            currTime += timeQuantum;
        }

        if (i == n - 1)
            i = 0;
        else
            i++;
    }
}

void show()
{
    printf("\nPno\t\tAT\t\tBT\t\tCT\t\tTT\t\tWT\t\tResponse Time");
    for (int i = 0; i < n; i++)
    {
        printf("\nP%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", pno[i], at[i], bt[i], ct[i], tt[i], wt[i], rt[i]);
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
        completed[i] = 0;
    }

    sort();
    roundRobin();
    show();
}