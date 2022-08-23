#include "secondcheck.h"
#include "tables.h"

char instructions[ROWS][BITS + 1];
char data[ROWS][BITS + 1];

void secondcheck(char *fname, labelPT *head, labelPT *externalHead, int DC)
{
    FILE *filePointer;
    char nextline[MAX], fileName[MAX];
    char **nextword;
    int IC = 0;
    int lineCount = 1;

    compilationError = FALSE;
    memset(fileName, '\0', MAX);
    strcpy(fileName, fname);
    strncat(fileName, ".am", 3);
    filePointer = fopen(fileName, "r");

    while(fgets(nextline, MAX, filePointer))
    {   
        if(nextline[0] != ';')                       /* skip comment */
        {
            nextword = getNextWord(nextline);   
            if(nextword[0])                          /* skip empty line */
                IC = secondCheckLine(nextword, IC, head, externalHead,lineCount); 
        }
        lineCount++;
    }

    if(compilationError == FALSE)
    {
        createExternFile(*externalHead, fname);
        createEntryFile(*head, fname);
        createObjectFile(fname, IC, DC);
    }
    printBinary();
    printLabelList(*externalHead);
    freeLabelList(head);
    freeLabelList(externalHead);
}

int secondCheckLine(char **line, int IC, labelPT *head, labelPT *externalHead, int lineCount)
{
    char *sourceOp, *destOp, *binary, *name;
    labelPT *current = NULL;
    int pos = 0;
    binary = (char*)malloc(sizeof(char)*BITS);
    name = (char*)malloc(sizeof(char)*MAX);
    /* skip labels and data */
    if(isLabelDef(line[pos], lineCount))
        pos++;
    if((isDirName(line[pos])) || (!strcmp(line[pos], ".extern")))
        return IC;
    /* new entry found */
    if(!strcmp(line[pos], ".entry"))
    {
        if((current = findLabel(head, line[pos+1])))
        {
            if((*current)->type != EXTERN)
                (*current)->type = ENTRY;
            else
                printf("\nError: '%s' cannot be .entry and .extern in th same file ==> line %d", line[pos+1], lineCount);
        }
        else
            printf("\nError: entry '%s' not found ==> line %d", line[pos+1], lineCount);
        return IC;
    }
    /* check if there's missing binary code in a command */
    sourceOp = line[pos+1];
    destOp = line[pos+2];
    IC++;
    if(!destOp)
    {
        destOp = sourceOp;
        sourceOp = NULL;
    }
    if(sourceOp)
    {
        if((registerBin(sourceOp)))      
        {   
            IC++;
            if(destOp && (registerBin(destOp)))    
                return IC;
        }
        if(isLegalLabel(sourceOp))               
        {
            binary = decodeLabel(sourceOp, head, externalHead, lineCount, IC);
            strcpy(instructions[IC], binary);
            IC++;
        }
        if(!strcmp(operand(sourceOp), "00"))
            IC++;
        if((strstr(sourceOp, ".1")) || (strstr(sourceOp, ".2"))) 
        {
            strncpy(name, sourceOp, strlen(sourceOp) - 2);
            binary = decodeLabel(name, head, externalHead, lineCount, IC);
            strcpy(instructions[IC], binary);
            IC = IC + 2;
        }
    }
    if(destOp)
    {
        if((registerBin(destOp)))
            return (IC+1);
        if(isLegalLabel(destOp))               
        {
            binary = decodeLabel(destOp, head, externalHead, lineCount, IC);
            strcpy(instructions[IC], binary);
            IC++;
        }
        if(!strcmp(operand(destOp), "00"))
            IC++;
        if((strstr(destOp, ".1")) || (strstr(destOp, ".2"))) 
        {
            strncpy(name, destOp, strlen(destOp) - 2);
            binary = decodeLabel(name, head, externalHead,lineCount, IC);
            strcpy(instructions[IC], binary);
            IC = IC + 2;
        }
    }
return IC;
}

char *decodeLabel(char *label, labelPT *head, labelPT *externalHead, int lineCount, int IC)
{
    char *binary = (char*)malloc(sizeof(char)*BITS);
    char *binaryAddress = (char*)malloc(sizeof(char)*BITS);
    char *external = "0000000001";
    labelPT *temp = NULL;
    int decimalAddress = 0;
    if((temp = findLabel(head, label)))
    {
        if(((*temp)->type) == EXTERN)
        {
            addLabel(externalHead, label, IC, EXTERN);
            return external;
        }
        else
        {
            decimalAddress = ((*temp)->address) + 100;
            binary = decimalToBinary(decimalAddress);
            strcpy(binaryAddress, &binary[2]);
            strcat(binaryAddress, "10");
            return binaryAddress;
        }
    }
    else
    {
        printf("\nError: label '%s' not found ==> line: %d", label, lineCount);
        compilationError = TRUE;
    }
    return NULL;
}

void createExternFile(labelPT externalHead, char *fname)
{
    FILE *filePointer;
    char filename[MAX];
    char *address32 = (char*)malloc(sizeof(char)*BITS);
    int decimalAddress = 0;
    memset(filename, '\n', MAX);
    strcpy(filename, fname);
    strcat(filename, ".ext");
    filePointer = fopen(filename, "w");

    while(externalHead)
    {
        decimalAddress = externalHead->address + 100;
        address32 = decimalTo32(decimalAddress);
        
        fputs(externalHead->label, filePointer);
        fputs("\t\t", filePointer);
        fputs(address32, filePointer);
        fputs("\n", filePointer);

        externalHead = externalHead->next;
    }
    fclose(filePointer);
}

void createEntryFile(labelPT head, char *fname)
{
    FILE *filePointer;
    char filename[MAX];
    char *address32 = (char*)malloc(sizeof(char)*BITS);
    int decimalAddress = 0;
    memset(filename, '\n', MAX);
    strcpy(filename, fname);
    strcat(filename, ".ent");
    filePointer = fopen(filename, "w");

    while(head)
    {
        if(head->type == ENTRY)
        {
            decimalAddress = head->address + 100;
            address32 = decimalTo32(decimalAddress);
            fputs(head->label, filePointer);
            fputs("\t\t", filePointer);
            fputs(address32, filePointer);
            fputs("\n", filePointer);
        }
        head = head->next;
    }
    fclose(filePointer);
}

void createObjectFile(char *fname, int IC, int DC)
{
    int i, j;
    FILE *filePointer;
    char filename[MAX];
    char *address32 = (char*)malloc(sizeof(char)*BITS);
    char *value32 = (char*)malloc(sizeof(char)*BITS);
    int decimalAddress = 0;
    memset(filename, '\n', MAX);
    strcpy(filename, fname);
    strcat(filename, ".ob");
    filePointer = fopen(filename, "w");
    
    fputs(decimalTo32(IC), filePointer);
    fputs(" ", filePointer);
    fputs(decimalTo32(DC), filePointer);
    
    for(i = 0; strcmp(instructions[i], "\0"); i++)
    {
        decimalAddress = i + 100;
        value32 = binaryTo32(instructions[i]);
        address32 = decimalTo32(decimalAddress);
        fputs(" \n", filePointer);
        fputs(address32, filePointer);
        fputs("\t\t", filePointer);
        fputs(value32, filePointer);
    }

    for(j = 0; strcmp(data[j], "\0"); j++)
    {
        decimalAddress = i + j + 100;
        value32 = binaryTo32(data[j]);
        address32 = decimalTo32(decimalAddress);
        fputs(" \n", filePointer);
        fputs(address32, filePointer);
        fputs("\t\t", filePointer);
        fputs(value32, filePointer);
    }
    fclose(filePointer);
}

void printBinary()
{
    int i, j;
    printf("\n***************** INSTRUCTIONS LIST *****************\n");
    for(i = 0; strcmp(instructions[i], "\0"); i++)
    {
        printf("\naddress: %d\t\tcommand: %s", i+100, instructions[i]);
    }
    printf("\n***************** DATA LIST *****************\n");
    for(j = 0; strcmp(data[j], "\0"); j++)
    {
        printf("\naddress: %d\t\tcommand: %s", j+i+100, data[j]);
    }
}


