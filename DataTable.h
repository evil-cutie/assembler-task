#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tables.h"

#define MAX 81
enum flag {OFF,ON};

/******************************************* functions *******************************************/
char * readNextLine(FILE *);
int skip2command(char *,FILE *);
char * readNextWord(char *);
char * getCurrentWord(char *);

/*Command functions*/
commandPT createCommand(int,char *);
int isCommand(char *);
int operandCount(char *);
int * getOpLocation(char *buffer, int opNo);

/*Addressing mode determination functions*/
AddressingMode getAddressMode(char *);
int isImmediate(char *);
int isStruct(char *);
/*************************************************************************************************/
