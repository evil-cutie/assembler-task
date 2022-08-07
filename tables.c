#include "tables.h"
#include "DataTable.h"

/******************************************* functions *******************************************/
int isCommandName(char *);
int isDirName(char * word);
int isRegisterName(char *);

/*Command functions*/
commandPT createCommand(int,char *);
int isCommand(char *);
int operandCount(char *);
/*************************************************************************************************/

/* checks if a command is valid */
/* return 1 if valid */
/* return 0 if not valid */
int isCommandName(char * word)
{
    int i = 0;
    while(i++ <= COMMANDS)
    {
        if(strcmp(validCommands[i], word) == 0)
            return i;
    }
    return -1;
}

/* checks if a directive is valid */
/* return 1 if valid */
/* return 0 if not valid */
int isDirName(char * word)
{
    int i = 0;
    while(i++ <= DIRECTIVES)
    {
        if(strcmp(validDirectives[i], word) == 0)
            return i;
    }
    return -1;
}

/* checks if a register name is valid */
/* return 1 if valid */
/* return 0 if not valid */
int isRegisterName(char * word)
{
    int i = 0;
    while(i++ <= REGISTERS)
    {
        if(strcmp(validRegisters[i], word) == 0)
            return i;
    }
    return -1;
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
