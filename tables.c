#include "tables.h"

/* checks if a command is valid */
/* return return number of command if valid (in decimal) */
/* return -1 if not valid */
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
/* return number of directive if valid (in decimal) */
/* return -1 if not valid */
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
/* return number of register if valid (in decimal) */
/* return -1 if not valid */
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
