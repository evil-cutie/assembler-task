#include "tables.h"
#include "DataTable.h"

/******************************************* functions *******************************************/
int isCommandName(char *);
int isDirName(char * word);
int isRegisterName(char *);
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
