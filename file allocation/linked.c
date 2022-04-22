#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct block
{
    int data;
    int ptr;
} memory[100];

int directoryTable[100][2], fileNo = 0, remainingSpace = 100;
const int mem_size = 100;

void addFile()
{
    int file_size, isSpace;
    printf("Size of file: ");
    scanf("%d", &file_size);

    if (file_size > remainingSpace)
        printf("File Size is more than the remaining space in the memory");

    srand(time(0));

    int prevBlock = -1, count = 0;

    while (count != file_size)
    {
        int location = rand() % mem_size;

        if (memory[location].data == -1)
        {
            memory[location].data = fileNo;
            remainingSpace--;

            if (count == 0)
                directoryTable[fileNo][0] = location;
            else if (count == file_size - 1)
                directoryTable[fileNo][1] = location;

            if (prevBlock != -1)
            {
                memory[prevBlock].ptr = location;
                prevBlock = location;
            }
            else
                prevBlock = location;

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
    printf("\nFile no \tStart Block\tEnd Block");

    for (int i = 0; i < fileNo; i++)
    {
        printf("\n   %d\t\t     %d\t\t    %d", i, directoryTable[i][0], directoryTable[i][1]);
    }
}
void showLinkedList()
{
    printf("\nLinked List:\n");

    for (int i = 0; i < fileNo; i++)
    {
        int pointer = directoryTable[i][0];
        while (pointer != -1)
        {
            printf("%d", pointer);
            pointer = memory[pointer].ptr;

            if (pointer != -1)
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
        memory[i].ptr = -1;
    }

    printf("\n----------------LINKED FILE ALLOCATION----------------\n");
    printf("\n1.Add File");
    printf("\n2.Display Memory");
    printf("\n3.Display Directory Table");
    printf("\n4.Display Linked List");
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