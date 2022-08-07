#include "DataTable.h"
/******************************************* functions *******************************************/
char * readNextLine(FILE *);
int skip2command(char *,FILE *);
char * readNextWord(char *);
char * getCurrentWord(char *);

/*Command functions*/
commandPT createCommand(int,char *);
int isCommand(char *);
int operandCount(char *);
/*************************************************************************************************/
/*read next line in file. return pointer to line beginning*/
char * readNextLine(FILE *fpAm)
{
    static char buffer[MAX];

    int i=0, length =0;
    if(skip2command(buffer,fpAm)) {
        i = strspn(buffer, " \t");
        char *p = strchr(buffer + i, '\n');
        if(p)
            *p = '\0';
        return (buffer + i);
    } else
        return NULL;
}

char * readNextWord(char *buffer)
{
    char *currentWord, *txtPT;
    int j,i = 0;
    currentWord = (char *)malloc(sizeof(char) * MAX);

    j= strspn(buffer," \t");            /*if there is no next word*/
    if(j == strlen(buffer))
        return NULL;

    sscanf(buffer, "%s", currentWord);
    i = i+ strlen(currentWord);
    while(buffer[i] == ' '|| buffer[i] == '\t')
        i++;
    txtPT = buffer;
    txtPT = txtPT + i;
    return txtPT;
}
char * getCurrentWord(char *buffer)
{
    char *currentWord;
    currentWord = (char *)malloc(sizeof(char) * MAX);

    sscanf(buffer, "%s", currentWord);
    return currentWord;
}

/*skips comment lines and blank lines*/
int skip2command(char *buffer,FILE *fpAm)
{
    enum flag commentFlag =ON;
    int i;
    if(fgets(buffer, MAX, fpAm)) {
        while (commentFlag == ON) {
            for (i = 0; i < MAX; i++) {         /*check if line is blank (whitespaces only)*/
                if (buffer[i] == '\n')
                    break;
                if (!isspace(buffer[i])) {
                    commentFlag = OFF;
                    break;
                }
            }
            if (strstr(buffer, ";"))            /*check if a comment*/
                commentFlag = ON;
            if (commentFlag == OFF)
                return 1;
            if (!fgets(buffer, MAX, fpAm))
                return 0;
        }
    } else
        return 0;
}

commandPT createCommand(int op,char *command)
{
    int i=0;
    AssemblerCommandLine assemblerLine;
    commandPT new = (commandPT)malloc(sizeof(commandPT));
    new = &assemblerLine;
    assemblerLine.line = command;
    assemblerLine.opcode = op;

    return new;
}

int operandCount(char *buffer)
{
    char * txtPT;
    int operandIdx, i = 0;
    if((txtPT = readNextWord(buffer)) == NULL)        /*skips command/directive name*/
        return i;
    else
        i++;
    operandIdx = strcspn(txtPT,",");
    while(operandIdx!= strlen(txtPT)){
        i++;
        txtPT = txtPT+operandIdx+1;
        operandIdx = strcspn(txtPT,",");
    }
    return i;
}

int isCommand(char *line)
{
    int opcode;
    char *currWord;

    currWord = getCurrentWord(line);
    for (opcode =0;opcode<COMMANDS;opcode++){
        if (strcmp(allCommands[opcode].name,currWord)==0)
            return opcode;
    }
    return -1;
}