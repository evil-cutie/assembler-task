#include "tables.h"

/* checks if a command is valid */
/* return command dec value if valid */
/* return -1 if not valid */
int isCommandName(char * word)
{
    int i = 0;
    while(i < COMMANDS)
    {
        if(strcmp(validCommands[i], word) == 0)
            return 1;
        i++;
    }
    return 0;
}

/* checks if a directive is valid */
/* return dir dec value if valid */
/* return -1 if not valid */
int isDirName(char * word)
{
    int i = 0;
    while(i < DIRECTIVES)
    {
        if(strcmp(validDirectives[i], word) == 0)
            return 1;
        i++;
    }
    return 0;
}

/* checks if a register name is valid */
/* return register dec value if valid */
/* return -1 if not valid */
int isRegisterName(char * word)
{
    int i = 0;
    while(i < REGISTERS)
    {
        if(strcmp(validRegisters[i], word) == 0)
            return 1;
        i++;
    }
    return 0;
}
