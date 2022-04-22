#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct block
{
    int data;
    int ptr[99];
} memory[100];

int directoryTable[100], fileNo = 0, remainingSpace = 100;
const int mem_size = 100;

void addFile()
{
    int file_size, isSpace;
    printf("Size of file: ");
    scanf("%d", &file_size);

    if (file_size > remainingSpace)
        printf("File Size is more than the remaining space in the memory");

    srand(time(0));

    //chosing a block to act as index table
    int index_block = rand() % mem_size;
    memory[index_block].data = -2;
    remainingSpace--;

    int count = 0;

    while (count != file_size)
    {
        int location = rand() % mem_size;

        if (memory[location].data == -1)
        {
            memory[location].data = fileNo;
            memory[index_block].ptr[count] = location;

            if (count == 0)
                directoryTable[fileNo] = index_block;

            remainingSpace--;
            count++;
        }
    }
    fileNo++;
    printf("File allocated successfully");
}

void showMemory()
{
    printf("\nMemory\n");
    for (int i = 0; i < mem_size; i++)
    {
        printf("%d\t", memory[i].data);
        if (i % 10 == 9 && i != 0 && i != mem_size - 1)
            printf("\n");
    }
}
void showDirectoryTable()
{
    printf("\nFile no \tIndex Table Location");

    for (int i = 0; i < fileNo; i++)
    {
        printf("\n   %d\t\t\t%d", i, directoryTable[i]);
    }
}
void showLinkedList()
{
    printf("\nIndex:\n");

    for (int i = 0; i < fileNo; i++)
    {
        int IndexTableLoc = directoryTable[i], j = 0, currIndexValue = 0;
        while (currIndexValue != -1)
        {
            currIndexValue = memory[IndexTableLoc].ptr[j];
            printf("%d", currIndexValue);
            j++;

            if (currIndexValue != -1)
                printf(" -> ");
        }
        printf("\n");
    }
}

void main()
{
    //initialize memory
    for (int i = 0; i < mem_size; i++)
    {
        memory[i].data = -1;
        for (int j = 0; j < mem_size - 1; j++)
            memory[i].ptr[j] = -1;
    }

    printf("\n----------------INDEXED FILE ALLOCATION----------------\n");
    printf("\n1.Add File");
    printf("\n2.Display Memory");
    printf("\n3.Display Directory Table");
    printf("\n4.Display Index");
    printf("\n5.Exit");

    int ch;
    do
    {
        printf("\n\nYour choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            addFile();
            break;
        case 2:
            showMemory();
            break;
        case 3:
            showDirectoryTable();
            break;
        case 4:
            showLinkedList();
            break;
        case 5:
            break;
        default:
            printf("\nWrong Input");
        }
    } while (ch != 5);
}