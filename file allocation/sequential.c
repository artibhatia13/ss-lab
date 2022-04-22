#include <stdio.h>

int memory[100], directoryTable[100][2], fileNo = 0;
const int mem_size = 100;

void addFile()
{
    int file_size, isSpace;
    printf("Size of file: ");
    scanf("%d", &file_size);

    for (int i = 0; i < mem_size; i++)
    {
        isSpace = 1;
        for (int j = 0; j < file_size; j++)
        {
            if (memory[i + j] != -1 || i + j >= mem_size)
            {
                isSpace = 0;
                break;
            }
        }
        if (isSpace == 1)
        {
            for (int k = 0; k < file_size; k++)
                memory[i + k] = fileNo;

            directoryTable[fileNo][0] = i;
            directoryTable[fileNo][1] = file_size;
            fileNo++;
            isSpace = 2;
            break;
        }
    }
    if (isSpace == 2)
        printf("File is allocated to memory successfully");
    else
        printf("Contiguous memory of file size does not exist");
}

void showMemory()
{
    printf("\nMemory\n");
    for (int i = 0; i < mem_size; i++)
    {
        printf("%d\t", memory[i]);
        if (i % 10 == 9 && i != 0 && i != mem_size - 1)
            printf("\n");
    }
}
void showDirectoryTable()
{
    printf("\nFile no \tStart Block\tFile Size");
    for (int i = 0; i < fileNo; i++)
    {
        printf("\n   %d\t\t     %d\t\t    %d", i, directoryTable[i][0], directoryTable[i][1]);
    }
}

void main()
{
    //initialize memory
    for (int i = 0; i < mem_size; i++)
        memory[i] = -1;

    printf("\n----------------SEQUENTIAL FILE ALLOCATION----------------\n");
    printf("\n1.Add File");
    printf("\n2.Display Memory");
    printf("\n3.Display Directory Table");
    printf("\n4.Exit");

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
            break;
        default:
            printf("\nWrong Input");
        }
    } while (ch != 4);
}