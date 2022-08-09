#include "DataTable.h"
enum flag SynthaxError = OFF;

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

/*points to next word in given line. get: current line in file. return: pointer to next word beginning*/
char * readNextWord(char *buffer)
{
    char *currentWord, *txtPT;
    int j,i = 0;
    currentWord = (char *)malloc(sizeof(char) * MAX);

    sscanf(buffer, "%s", currentWord);
    i = i+ strlen(currentWord);
    if(buffer[i] == '\0')
        return NULL;
    while(buffer[i] == ' '|| buffer[i] == '\t')
        i++;
    txtPT = buffer;
    txtPT = txtPT + i;
    free(currentWord);
    return txtPT;
}
/*reads next word in given line. get: current line in file. return: pointer to next word only*/
char * getCurrentWord(char *buffer)
{
    int i;
    char *currentWord;
    currentWord = (char *)malloc(sizeof(char) * MAX);

    sscanf(buffer, "%s", currentWord);
    if(i=strcspn(currentWord, ","))
        currentWord[i] = '\0';
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

/************************************ command functions ************************************/
/*checks if first word in line is a valid command. get: pointer to line
 * return: opcode if command is valid, -1 otherwise*/
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

/*creat a command object out of line. get: int -op code,char *-current line, return:pointer to new command */
commandPT createCommand(int op,char *command)
{
    SynthaxError = OFF;
    int addMode,i=0;
    int *opLocs;
    commandPT newCommand = (commandPT)malloc(sizeof(AssemblerCommandLine));

    newCommand->line = command;
    newCommand->opcode = op;
    newCommand->numOperands = operandCount(command);

    /*get no. of operands and pointers to their location*/
    if(newCommand->numOperands >2) {
        printf("Command error: too many operands ");
        SynthaxError = ON;
    } else
    {
        opLocs = getOpLocation(command, newCommand->numOperands);
        for(i=0;i<newCommand->numOperands;i++)
            newCommand->operand[i] = getCurrentWord(command + opLocs[i]);
    }

    /*determine addressing modes of operands*/
    if(newCommand->numOperands > 0 && newCommand->numOperands < 3 ){
        addMode = isImmediate(newCommand->operand[0]);
    }
    if(SynthaxError == ON)
        return NULL;
    return newCommand;
}

/*count no. of operands in line. get: pointer to current line, return: no of operands*/
int operandCount(char *buffer)
{
    char * txtPT;
    int operandIdx, i = 0;
    if((txtPT = readNextWord(buffer)) == NULL)        /*skips command or directive name*/
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
/*return int array of operand locations as index offset from beginning of line*/
int *getOpLocation(char *buffer, int opNo)
{
    static int locs[2];
    if(opNo == 0)
        return NULL;
    int operandIdx;

    operandIdx = strcspn(buffer, " \t");                            /*skips command or directive name*/
    operandIdx = operandIdx + strspn(buffer+operandIdx, " \t");
    locs[0] = operandIdx;
    if(opNo ==2){
        operandIdx = operandIdx + strcspn(buffer+operandIdx,",");       /*skips first operand*/
        operandIdx = operandIdx + strspn(buffer+operandIdx, ", \t");     /*skips whitespaces and ','*/
        locs[1] = operandIdx;
    } else
        locs[1] = NULL;
    return locs;
}

/*************************** addressing mode determination functions *******************************/
/*check if addressing mode is immediate. return 0 if it is, -1 otherwise*/
int isImmediate(char *opLocation)
{
    int i,j;
    i = strcspn(opLocation, "#");       /*check if an immediate declaration*/
    if (i ==strlen(opLocation))
        return -1;
    if(strlen(opLocation) ==1) {
        printf("Immediate addressing mode error: whitespaces in declaration ");
        return -1;
    }
    j = strspn(opLocation+i+1, "-1234567890");
    if( j != strlen(opLocation+i+1))  /*check if an integer is declared*/
    {
        printf("Immediate addressing mode error: not an int ");
        return -1;
    }
    return modeImmediate;
}