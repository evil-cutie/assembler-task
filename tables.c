#include <stdio.h>
#include <string.h>
#define MAX 81
#define COMMANDS 16
#define DIRECTIVES 4
#define REGISTERS 8

/* valid command names */
char validCommands[COMMANDS][MAX] = {
	{"mov"}, {"cmp"}, {"add"}, {"sub"}, 
	{"not"}, {"clr"}, {"lea"}, {"inc"}, 
	{"dec"}, {"jmp"}, {"bne"}, {"get"},
	{"prn"}, {"jsr"}, {"rts"}, {"hlt"}
};

/* valid register names */
char validRegisters[REGISTERS][MAX] = {
	{"r0"}, {"r1"}, {"r2"}, {"r3"},
	{"r4"}, {"r5"}, {"r6"}, {"r7"}
};

/* other reserved words */
char other[MAX][MAX] = { 
	{"macro"}, {"endmacro"} 
};

/* valid directive names */
char validDirectives[DIRECTIVES][MAX] = {
	 {".struct"}, {".data"}, {".string"}, {".entry"}
};

/* checks if a command is valid */
/* return 1 if valid */
/* return 0 if not valid */
int isCommandName(char * word)
{
	int i = 0;
	while(i++ <= COMMANDS)
	{
		if(strcmp(validCommands[i], word) == 0)
			return 1;
	}
	return 0;
}
