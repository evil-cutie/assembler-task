#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 81

enum status {OFF, ON} error;
enum boolean {FALSE, TRUE} newMacro;
typedef struct macroLS * macroPT;
typedef struct macroLS {
	char *name;
	char *line;
	macroPT next;
} macroLS;
/******************************************* functions *******************************************/
void readAndCreateFile(char *fname, macroPT *head);
void addMacro(macroPT *head, char *name, char *string);
macroPT findMacro(macroPT head, char *name);
void printList(macroPT head);
void freeList(macroPT *head);
void lineLength(char *line);
/*************************************************************************************************/
