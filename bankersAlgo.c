#include <stdio.h>

void main()
{
    int no_of_resources, no_of_process, allocation[10][10], maximum[10][10], available[10], total_no_of_resources[10], need[10][10];

    printf("No of resources: ");
    scanf("%d", &no_of_resources);

    printf("No of processes: ");
    scanf("%d", &no_of_process);

    printf("total number of resources of each type: ");
    for (int i = 0; i < no_of_resources; i++)
        scanf("%d", &total_no_of_resources[i]);

    printf("Allocation matrix: ");
    for (int i = 0; i < no_of_process; i++)
        for (int j = 0; j < no_of_resources; j++)
            scanf("%d", &allocation[i][j]);

    printf("Maximum matrix: ");
    for (int i = 0; i < no_of_process; i++)
        for (int j = 0; j < no_of_resources; j++)
            scanf("%d", &maximum[i][j]);

    // calculating available resources
    int sum;
    for (int i = 0; i < no_of_resources; i++)
    {
        sum = 0;
        for (int j = 0; j < no_of_process; j++)
        {
            sum += allocation[j][i];
            available[i] = total_no_of_resources[i] - sum;
        }
    }

    // calculating need matrix
    for (int i = 0; i < no_of_process; i++)
        for (int j = 0; j < no_of_resources; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];

    printf("\nTotal no of resources: ");
    for (int i = 0; i < no_of_resources; i++)
        printf("%d ", available[i]);

    printf("\n\nAllocation matrix:\n");
    for (int i = 0; i < no_of_process; i++)
    {
        for (int j = 0; j < no_of_resources; j++)
            printf("%d   ", allocation[i][j]);
        printf("\n");
    }

    printf("\nMaximum matrix:\n");
    for (int i = 0; i < no_of_process; i++)
    {
        for (int j = 0; j < no_of_resources; j++)
            printf("%d   ", maximum[i][j]);
        printf("\n");
    }

    printf("\nNeed matrix:\n");
    for (int i = 0; i < no_of_process; i++)
    {
        for (int j = 0; j < no_of_resources; j++)
            printf("%d   ", need[i][j]);
        printf("\n");
    }

    printf("\nAvailable resources: ");
    for (int i = 0; i < no_of_resources; i++)
        printf("%d ", available[i]);

    int needsatisfy, process_running[10];
    for (int i = 0; i < no_of_process; i++)
        process_running[i] = 1;

    int safe, counter = no_of_process;
    while (counter != 0)
    {
        safe = 0;
        for (int i = 0; i < no_of_process; i++)
        {
            if (process_running[i])
            {
                needsatisfy = 1;
                for (int j = 0; j < no_of_resources; j++)
                {
                    if (available[j] < need[i][j])
                    {
                        needsatisfy = 0;
                        break;
                    }
                }
                if (needsatisfy)
                {
                    safe = 1;
                    process_running[i] = 0;
                    counter--;

                    printf("\n\nExecuting process %d", i + 1);
                    for (int k = 0; k < no_of_resources; k++)
                        available[k] += allocation[i][k];

                    break;
                }
            }
        }
        if (!safe)
        {
            printf("\nThe processs are in unsafe state");
            break;
        }
        else
        {
            printf("\nAvailable matrix :");
            for (int k = 0; k < no_of_resources; k++)
                printf("%d ", available[k]);
        }
    }
    printf("\n");
}