#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main()
{
    char label[10], operand[10], opcode[10], name[10];
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;
    fp1 = fopen("input_macro.txt", "r");
    fp2 = fopen("argtab.txt", "w+");
    fp3 = fopen("defttab.txt", "w+");
    fp4 = fopen("namtab.txt", "w+");
    fp5 = fopen("output.txt", "w");

    fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    if (strcmp(opcode, "MACRO") == 0)
    {
        fprintf(fp3, "%s\t%s\t%s\n", label, opcode, operand);
        fprintf(fp4, "%s\n", label);
        fseek(fp4, SEEK_SET, 0);
        char count = '1';
        while (strcmp(opcode, "MEND") != 0)
        {
            fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
            if (operand[0] == '&')
            {
                operand[1] = count;
                count = count + 1;
            }
            fprintf(fp3, "%s\t%s\t%s\n", label, opcode, operand);
        }
    }
    fseek(fp3, SEEK_SET, 0);
    fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    while (strcmp(opcode, "END") != 0)
    {
        fscanf(fp4, "%s", name);
        if (strcmp(opcode, name) == 0)
        {
            fprintf(fp5, ".\t%s\t%s\n", opcode, operand);
            for (int i = 0; i < strlen(operand); i++)
            {
                if (operand[i] != ',')
                    fprintf(fp2, "%c", operand[i]);
                else
                    fprintf(fp2, "\n");
            }
            fseek(fp2, SEEK_SET, 0);
            fscanf(fp3, "%s\t%s\t%s", label, opcode, operand);
            while (strcmp(opcode, "MEND") != 0)
            {
                fscanf(fp3, "%s\t%s\t%s", label, opcode, operand);
                if (strcmp(opcode, "MEND") != 0)
                    fprintf(fp5, "%s\t%s\t", label, opcode);
                if (operand[0] == '&')
                {
                    char arg[10];
                    fscanf(fp2, "%s", arg);
                    fprintf(fp5, "%s\n", arg);
                }
            }
        }
        else
            fprintf(fp5, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }
    fprintf(fp5, "%s\t%s\t%s\n", label, opcode, operand);
}