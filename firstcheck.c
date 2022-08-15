#include "firstcheck.h"
#include "tables.h"

void firstCheck(char *fileName, labelPT *head)
{
    FILE *filePointer;
    char nextline[MAX];
    int *IC = (int*)malloc(sizeof(int));
    int *DC = (int*)malloc(sizeof(int));
    *IC = *DC = 0;
    strncat(fileName, ".am", 3);
    filePointer = fopen(fileName, "r");
    memset(data, '\0', sizeof(data[0][0]) * SIZE * 10);
    memset(instructions, '\0', sizeof(instructions[0][0]) * SIZE * 10);
    
    while(fgets(nextline, MAX, filePointer))
    {
        
        char **nextword = getNextWord(nextline);
        checkLine(nextword, DC, IC, head); 
       
        
    }
    printBinary();
    printLabelList(*head);
    freeLabelList(head);
   
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

void checkLine(char **line, int *DC, int *IC, labelPT *head)
{
    int tempIC = *IC;
    int tempDC = *DC;
    int i = 0;
    if (isLabelDef(line[i]))
    {
        char *newLabel = (char*)malloc(sizeof(line[0]));
        printf("\nfound command: %s, command length: %lu", line[1], strlen(line[1]));
        strncpy(newLabel, line[i], strlen(line[i]) - 1);
        printf("\nstring %s length: %lu", newLabel,strlen(line[i]) - 1);
        
        label = TRUE;
        i++;
        if (isDirName(line[i]))
        {
            if(!findLabel(*head, newLabel) && isLegalLabel(newLabel))
                addLabel(head, newLabel, tempDC, 0); /* data type = 0 */
            else
                printf("\nError: label %s already exists", newLabel);
            
            if(!strcmp(line[i], validDirectives[2]))    /* string definition */
            {        
                printf("\n************** FOUND STRING! Name: %s **************\n", newLabel);                                        
                tempDC = decodeString(line[i + 1], tempDC);
                printf("\ncurrent DC is: %d", tempDC);
            }
            if(!strcmp(line[i], validDirectives[1]))    /* array definition */
            {
                printf("\n************** FOUND ARRAY! Name: %s **************\n", newLabel); 
                tempDC = decodeData(line, tempDC);
                printf("\ncurrent DC is: %d", tempDC);
            }
            if(!strcmp(line[i], validDirectives[0]))    /* struct definition */
            {
                printf("\n************** FOUND STRUCT! Name: %s **************\n", newLabel);
                tempDC = decodeStruct(line, tempDC);
                printf("\ncurrent DC is: %d", tempDC);
            }
        }
        if(isCommandName(line[i]))
        {
            if(!findLabel(*head, newLabel) && isLegalLabel(newLabel))
                addLabel(head, newLabel, tempIC, 1); 
            else
                printf("\nError: label %s already exists", newLabel);
                tempIC = decodeCommand(line, i, tempIC); 
        }
    }
    
    *DC = tempDC;
    *IC = tempIC;
} 

int isLabelDef(char *word)
{
    char *last = &word[strlen(word) - 1];
    if(!strcmp(last, ":"))
        return 1;
    return 0;
}

int isLegalLabel(char *label)
{
    int i = 0;
    if(strlen(label) > 30)
    {
        printf("\nError: label '%s' name must be no longer than 30 characters", label);
        return -1;
    }
    if(!isalpha(label[i]))
    {
        printf("\nError: label '%s' name must start with a letter", label);
        return -1;
    }
    for(i = 1; i < strlen(label); i++)
    {
        if(!isalnum(label[i]))
        {
            printf("\nError: label '%s' name must contain only alphanumeric characters", label);
            return -1;
        }
    }
    if(isCommandName(label) || isDirName(label) || isRegisterName(label))
    {
        printf("\nError: label name cannot be '%s'", label);
        return -1;
    }
    return 1;
}


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

char *operand(char *nextword)
{
	int i;
	for(i = 0; i < COMMANDS; i++)
	{
		if(!strcmp(nextword, validRegisters[i])) /* register addressing */
			return "11";
		if(isLegalLabel(nextword)) /* direct addressing */
			return "01";
		if(!strcmp(nextword, "#")) /* instant addressing */
			return "00";
        if(strstr(nextword, ".1") || strstr(nextword, ".2"))    /* struct access */
            return "10";
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
		/*printf("\nchar: %c", *ptr);*/
        strcpy(data[DC], binary);
        /*printf("\nbinary char: %s", data[DC]);*/
        DC++;
        ptr++;
	}
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
        /*printf("\ndecimal value: %s", line[i]);*/
        strcpy(data[DC], binary);
        /*printf("\nbinary value: %s", data[DC]); */
        i++;
        DC++;
    }
    return DC;
}

int decodeStruct(char **line, int DC)
{
    int decimal;
    char *binary = (char*)malloc(sizeof(int)*BITS);
    int i = 2;
    char num = *line[i];
    if(isdigit(num))
    {
        decimal = atoi(line[i]);
        binary = decimalToBinary(decimal);
        printf("\ndecimal value: %d", decimal);
        strcpy(data[DC], binary);
        printf("\nbinary value: %s", data[DC]); 
        DC++;
        i++;
    }
    else
        printf("\nError: invalid struct definition, first field must be integer");
    
    DC = decodeString(line[i], DC);
    return DC;
}

int decodeCommand(char **line, int pos, int IC)
{
    char *destOp = NULL;
    char *sourceOp = NULL;
    char *temp = NULL;
    char *tmp;
    char *command = line[pos];
    char *binary = (char*)malloc(sizeof(char)*BITS);
    
    strcpy(binary, opcode(command));
    
    if((sourceOp = line[pos+1]) && (tmp = operand(sourceOp)))
        strcat(binary, tmp);
    else
        strcat(binary, "00");
    
    if((destOp = line[pos+2]) && (tmp = operand(destOp)))
        strcat(binary, tmp);
    else
        strcat(binary, "00");
    
    strcat(binary, "00");
    temp = strdup(binary);
    strcpy(instructions[IC], temp);
    printf("\n%s  binary code: %s\n", *line, instructions[IC]);
    IC++;
    return IC;
}

void printBinary()
{
    int i;
    printf("\n***************** INSTRUCTIONS LIST *****************\n");
    for(i = 0; i < 5; i++)
    {
        printf("\naddress: %d\t\tcommand: %s", i, instructions[i]);
    }
    printf("\n***************** DATA LIST *****************\n");
    for(i = 0; i < 5; i++)
    {
        printf("\naddress: %d\t\tcommand: %s", i, data[i]);
    }
}

