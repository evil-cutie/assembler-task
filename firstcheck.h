
#include <stdio.h>

/******************************************* functions *******************************************/
void firstCheck(char *filename);
char **getNextWord(char *line);
void checkLine(char **line, int DC);
int isLabel(char *word);
void addToLableTable(char *label, int address, char *type);
void scan1(FILE *fpAm);
/*************************************************************************************************/
