#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 81
enum flag {OFF,ON};

/******************************************* functions *******************************************/
char * readNextLine(FILE *);
int skip2command(char *,FILE *);
char * readNextWord(char *);
char * getCurrentWord(char *);
/*************************************************************************************************/