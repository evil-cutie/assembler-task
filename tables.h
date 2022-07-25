#include <stdio.h>
#include <string.h>
#define MAX 81
#define COMMANDS 16
#define DIRECTIVES 4
#define REGISTERS 8

/* valid command names */
static char validCommands[COMMANDS][MAX] = {
	{"mov"}, {"cmp"}, {"add"}, {"sub"}, 
	{"not"}, {"clr"}, {"lea"}, {"inc"}, 
	{"dec"}, {"jmp"}, {"bne"}, {"get"},
	{"prn"}, {"jsr"}, {"rts"}, {"hlt"}
};

/* valid register names */
static char validRegisters[REGISTERS][MAX] = {
	{"r0"}, {"r1"}, {"r2"}, {"r3"},
	{"r4"}, {"r5"}, {"r6"}, {"r7"}
};

/* other reserved words */
static char other[MAX][MAX] = { 
	{"macro"}, {"endmacro"} 
};

/* valid directive names */
static char validDirectives[DIRECTIVES][MAX] = {
	 {".struct"}, {".data"}, {".string"}, {".entry"}
};

/******************************************* functions *******************************************/
int isCommandName(char * word);
int isDirName(char * word);
int isRegisterName(char * word);
/*************************************************************************************************/

