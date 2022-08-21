#include "firstcheck.h"
#include "tables.h"

void firstCheck(char *fname, labelPT *head)
{
    FILE *filePointer;
    char nextline[MAX], fileName[MAX];
    char **nextword;
    int *IC = (int*)malloc(sizeof(int));
    int *DC = (int*)malloc(sizeof(int));
    int lineCount = 1;
    *IC = *DC = 0;
    compilationError = FALSE;
    memset(fileName, '\0', MAX);
    memset(data, '\0', sizeof(char) * (BITS+1) * MAX);
    memset(instructions, '\0', sizeof(char) * (BITS+1) * MAX);
    strcpy(fileName, fname);
    strncat(fileName, ".am", 3);
    filePointer = fopen(fileName, "r");

    while(fgets(nextline, MAX, filePointer))
    {
        if(nextline[0] != ';')               /* skip comment */
        {
            nextword = getNextWord(nextline);                
            checkLine(nextword, DC, IC, head, lineCount); 
        }
        lineCount++;
    }
    if(compilationError == FALSE)
        updateDataAddress(*IC, head);
    printBinary();
    printLabelList(*head);
}

char **getNextWord(char *line)
{
    char delim[] = {' ', '\t', ',', '\n', '\r', '\v', '\f'};
    char **nextword = NULL;
    int i = 0;
    nextword = (char **)malloc(MAX * sizeof(*nextword));
    
    nextword[0] = strtok(line, delim);
    while(nextword[i])
    {
        i++;
        nextword[i] = strtok(NULL, delim);
    }
    return nextword;
}

void checkLine(char **line, int *DC, int *IC, labelPT *head, int lineCount)
{
    int tempIC = *IC;
    int tempDC = *DC;
    int pos = 0;
    if(isLabelDef(line[pos], lineCount))
    {
        char *newLabel = (char*)malloc(sizeof(line[0]));
        strncpy(newLabel, line[pos], strlen(line[pos]) - 1);
        pos++;
        if(isDirName(line[pos]))
        {
            addToTable(newLabel, head, tempDC, DATA, lineCount);
            tempDC = defineNewData(line, head, tempDC, lineCount, pos);
        }
        else 
        {
            if(searchEntryOrExtern(line, head, pos, lineCount))
                ;
            else if(isCommandName(line[pos]))
            {
                addToTable(newLabel, head, tempIC, CODE, lineCount); 
                tempIC = decodeCommand(line, pos, tempIC); 
            }
            else
            {
                printf("\nError: '%s' is illigal command ==> line %d", line[pos], lineCount);
                compilationError = TRUE;
            }
        }
    }    
    else 
    {
        if(searchEntryOrExtern(line, head, pos, lineCount))
            ;
        else if(isCommandName(line[pos]))
            tempIC = decodeCommand(line, 0, tempIC); 
        else
        {
            printf("\nError: '%s' is illigal command ==> line %d", line[pos], lineCount);
            compilationError = TRUE;
        }
    }
    *DC = tempDC;
    *IC = tempIC;
} 

void addToTable(char *newLabel, labelPT *head, int value, int type, int lineCount)
{
    if (!findLabel(*head, newLabel))
        addLabel(head, newLabel, value, type); 
    else
    {
        printf("\nError: label '%s' already exists ==> line %d", newLabel, lineCount);
        compilationError = TRUE;
    }
}

int defineNewData(char **line, labelPT *head, int DC, int lineCount, int pos)
{
    if(!strcmp(line[pos], validDirectives[2]))            /* string definition */
        DC = decodeString(line[pos + 1], DC);
            
    if(!strcmp(line[pos], validDirectives[1]))            /* array definition */
        DC = decodeData(line, DC);
            
    if(!strcmp(line[pos], validDirectives[0]))            /* struct definition */
        DC = decodeStruct(line, DC, lineCount);
    return DC;
}

int searchEntryOrExtern(char **line, labelPT *head, int pos, int lineCount)
{
    char *newLabel = (char*)malloc(sizeof(char) * MAX);
    if(!strcmp(line[pos], ".entry"))
        return 1;
    if(!strcmp(line[pos], ".extern"))
    {
        pos++;
        while(line[pos])
        {
            strcpy(newLabel, line[pos]);
            if(isLegalLabel(newLabel))
                addLabel(head, newLabel, '\0', EXTERN); 
            else
                printf("\nError: label name '%s' is illigal ==> line %d", newLabel, lineCount);
            pos++;
        }
        return 1;
    }
    return 0;
}

int isLabelDef(char *word, int lineCount)
{
    char *last = &word[strlen(word) - 1];
    if(!strcmp(last, ":"))
    {
        char *newLabel = (char*)malloc(sizeof(word));
        strncpy(newLabel, word, strlen(word) - 1);
        if(isLegalLabel(newLabel))
            return 1;
        else
        {
            printf("\nError: '%s' is illigal label name ==> line %d", newLabel, lineCount);
            compilationError = TRUE;
            return 0;
        }
    }
    return 0;
}

int isLegalLabel(char *label)
{
    int i = 0;
    if(strlen(label) > 30 || (!isalpha(label[i])) || isReservedWord(label))
        return 0;
    for(i = 1; i < strlen(label); i++)
    {
        if(!isalnum(label[i]))
            return 0;
    }
    return 1;
}
/* returns binary code of the opcode */
char *opcode(char *nextword)
{
	int i;
	for(i = 0; i < COMMANDS; i++)
	{
		if(!strcmp(nextword, validCommands[i]))
			return binaryOpcode[i];
	}
	return NULL;
}
/* returns binary code of a given operand */
char *operand(char *nextword)
{
	int i;
	for(i = 0; i < COMMANDS; i++)
	{
		if(isRegisterName(nextword))    /* register addressing */
			return "11";
		if(isLegalLabel(nextword))      /* direct addressing */
			return "01";
		if(strstr(nextword, "#"))       /* instant addressing */
			return "00";
        if(strstr(nextword, ".1") || strstr(nextword, ".2"))    /* struct access */
            return "10";
	}
	return NULL;
}
/* returns binary code of a given register */
char *registerBin(char *regist)
{
    int i;
    for(i = 0; i < REGISTERS; i++)
    {
        if(!strcmp(regist, validRegisters[i]))
            return binaryRegister[i];
    }
    return NULL;
}

int decodeString(char *string, int DC)
{
	int value;
	char *binary = (char*)malloc(sizeof(int)*BITS);
	char *ptr = string + 1;
	while(*ptr && *ptr != '"')
	{
        value = *ptr - '0'; /* ascii value of character */
		binary = decimalToBinary(value);
        strcpy(data[DC], binary);
        DC++;
        ptr++;
	}
    strcpy(data[DC], "0000000000"); /* end of string */
    DC++;
    return DC;
}

int decodeData(char **line, int DC)
{
    int decimal;
    int i = 2;
    char *binary = (char*)malloc(sizeof(int)*BITS);
    while(line[i])
    {
        decimal = atoi(line[i]);
        binary = decimalToBinary(decimal); 
        strcpy(data[DC], binary);
        i++;
        DC++;
    }
    return DC;
}

int decodeStruct(char **line, int DC, int lineCount)
{
    int decimal;
    char *binary = (char*)malloc(sizeof(int)*BITS);
    int i = 2;
    char num = *line[i];
    if(isdigit(num))
    {
        decimal = atoi(line[i]);
        binary = decimalToBinary(decimal);
        strcpy(data[DC], binary);
        DC++;
        i++;
    }
    else
        printf("\nError: invalid struct definition, first field must be integer ==> line %d", lineCount);
    
    DC = decodeString(line[i], DC);
    return DC;
}
/* decode first line */
int decodeCommand(char **line, int pos, int IC)
{
    char *destOp, *sourceOp, *tmp, *command;
    char *binary = (char*)malloc(sizeof(char)*BITS);
    int L = 0;
    tmp =  NULL;
    command = line[pos];
    sourceOp = line[pos+1];
    destOp = line[pos+2];
    
    if(!destOp)
    {
        destOp = sourceOp;
        sourceOp = NULL;
    }
    /* bits 9-6 */
    strcpy(binary, opcode(command));
    /* bits 5-4 */
    if(sourceOp && (tmp = operand(sourceOp)))
        strcat(binary, tmp);
    else
        strcat(binary, "00");
    /* bits 3-2 */
    if(destOp && (tmp = operand(destOp)))
        strcat(binary, tmp);
    else
        strcat(binary, "00");   /* A, R, E */
    /* bits 1-0 */
    strcat(binary, "00");
    strcpy(instructions[IC], binary);
    IC++;
    if(isLegalOperand(command, sourceOp, destOp))
    {
        L = checkOperands(sourceOp, destOp, IC); 
    }
    return (IC + L);
}

int checkOperands(char *sourceOp, char *destOp, int IC)
{
    int L = 0;
    int diff = 0;
    char *tempOp1, *tempOp2;
    char *binary1 = (char*)malloc(sizeof(char)*BITS);
    char *binary2 = (char*)malloc(sizeof(char)*BITS);
    tempOp1 = tempOp2 = NULL;

    if(sourceOp)
    {
        if ((tempOp1 = registerBin(sourceOp)))      /* source operand is a register */
        {    
            strcpy(binary1, tempOp1);
            if (destOp && (tempOp2 = registerBin(destOp)))     /* both operands are registers */
            {
                strcat(binary1, tempOp2);
                strcat(binary1, "00");   /* A, R, E */
                strcpy(instructions[IC], binary1);
                return (L+1);
            }
            strcat(binary1, "000000"); 
            strcpy(instructions[IC], binary1);
            L++;
        }
        if (isLegalLabel(sourceOp))                 /* source operand is a label */
        {
            strcpy(instructions[IC], "label");
            L++;
        }
        if ((diff = decodeNum(sourceOp, IC)))       /* source operand is a digit */
            L = L + diff;
        if ((diff = decodeStructAccess(sourceOp, IC)))
            L = L + diff;
    }
    if (destOp)
    {
        if ((tempOp2 = registerBin(destOp)))        /* destination operand is a register */
        {
            strcpy(binary2, "0000");
            strcat(binary2, tempOp2);
            strcat(binary2, "00");   /* A, R, E */
            strcpy(instructions[IC+L], binary2);
            return (L+1);
        }
        if (isLegalLabel(destOp))                   /* destination operand is a label */
        {
            strcpy(instructions[IC+L], "label");
            return (L+1);
        }
        if ((diff = decodeNum(destOp, IC+L)))      /* destination operand is a digit */
            L = L + diff;
        if ((diff = decodeStructAccess(destOp, IC+L)))
            L = L + diff;
    }
    return L;
}

int decodeStructAccess(char *op, int IC)
{
    int L = 0;
    char *one = NULL;
    char *two = NULL;
    if((one = strstr(op, ".1")) || (two =  strstr(op, ".2"))) 
    {
        strcpy(instructions[IC], "struct");
        L++;
        if(one)     /* access to first field */
        {
            strcpy(instructions[IC+L], "0000000100");
            return (L+1);
        }
        strcpy(instructions[IC+L], "0000001000");       /* access to second field */
        return (L+1);
    }
    return L;
}

int decodeNum(char *op, int IC)
{
    int L = 0;
    char *binary = (char*)malloc(sizeof(char)*BITS);
     if (!strcmp(operand(op), "00"))       
        {
            int num = 0;
            char *temp = (char*)malloc(sizeof(op));
            char *binaryNum = (char*)malloc(sizeof(char)*BITS);
            strcpy(temp, &op[1]);
            num = atoi(temp);
            binaryNum = decimalToBinary(num);
            strcpy(binary, &binaryNum[2]);
            strcat(binary, "00");
            strcpy(instructions[IC], binary);
            return (L+1);
        }
    return L;
} 

void updateDataAddress(int IC, labelPT *head)
{
    labelPT current = *head;
    while(current)
    {
        if(current->type == DATA)
            current->address = (current->address) + IC;
        current = current->next;
    } 
}

int isLegalOperand(char *command, char *sourceOp, char *destOp)
{
    return 1;
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

