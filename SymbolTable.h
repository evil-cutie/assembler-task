#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 81

typedef struct nodeSymbol *symbolPT;
typedef struct nodeSymbol
{
    char *label;
    int address;                   /* in decimal*/
    short type;                    /*directive: 0,command: 1,external: 2, code: 3 */
    symbolPT next;
}nodeSymbol;
/******************************************* functions *******************************************/
int addToEnd(symbolPT *,char *,int,short);
int checkInList(symbolPT,char *);
void freeSymbolList(symbolPT *);

int isSymbol(char *);
int isValidSymbol(symbolPT, char *);
char *getSymbolLabel(char *);
/*************************************************************************************************/