#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 81

enum boolean {FALSE, TRUE};
enum boolean newMacro;
enum boolean error;
typedef struct macroLS * macroPT;
typedef struct macroLS {
	char *name;
	char *line;
	macroPT next;
} macroLS;
/******************************************* functions *******************************************/
FILE *readAndCreateFile(char *fname, macroPT *head);
void addMacro(macroPT *head, char *name, char *string);
macroPT findMacro(macroPT head, char *name);
void printList(macroPT head);
void freeList(macroPT *head);
void lineLength(char *line);
/*************************************************************************************************/
