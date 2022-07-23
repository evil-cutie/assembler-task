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
char *getSymbolLabel(char *);
int add2symbolList(symbolPT *,char *);
/*************************************************************************************************/
/* create a new symbol and add it to the end of symbol list. return 1 if append is successful, 0 otherwise */
int addToEnd(symbolPT* head,char *label,int address,short type)
{
    symbolPT new = (symbolPT)malloc(sizeof(nodeSymbol));
    symbolPT pt;

    if(!new) {
        printf("\nError: Cannot build symbol list\n");
        return 0;
    }

    new->label = label;                     /*create node in symbol list*/
    new->address = address;
    new->type = type;
    new->next = NULL;

    if(*head){                              /*append node to end of list if not empty*/
        pt = *head;
        while (pt->next != NULL)
            pt = pt->next;
        pt->next = new;
    }
    else                                    /*if list empty defy node as head of list*/
        *head = new;
    return 1;
}

/* check if symbol exists in symbol list. return: 1 if symbol exists in symbol list, returns 0 otherwise*/
int checkInList(symbolPT head,char *label)
{
    while (head)
    {
        if(strcmp(head->label,label) == 0)
            return 1;
        head = head->next;}
    return 0;
}

/*free dynamic memory allocation of symbol list*/
void freeSymbolList(symbolPT *head)
{
    symbolPT temp;
    while(*head)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

/*check if command is a symbol definition. return 1 if a symbol and 0 otherwise*/
int isSymbol(char *buffer)
{
    char *firstWord;
    firstWord = (char*)malloc(sizeof(char)*MAX);
    sscanf(buffer, "%s", firstWord);            /*get first word in line*/
    if(strstr(firstWord, ":"))                  /*check label definition*/
        return 1;
    return 0;
}

/*gets a pointer to line in text contains symbol definition and return pointer to symbol label*/
char *getSymbolLabel(char *buffer)
{
    char *temp;
    temp = (char*)malloc(sizeof(char)*MAX);
    sscanf(buffer, "%s", temp);
    char label[strlen(temp)-1];
    memcpy( label, temp, strlen(temp)-1 );
    label[strlen(temp)-1] = '\0';
    printf("%s\n",label);
}

int add2symbolList(symbolPT *head,char *buffer)
{
    char *label = getSymbolLabel(buffer);
    if(checkInList(*head,label))            /*if already*/
        return 1;
    if(addToEnd(head,label,0,0))
        return 1;
    return 0;
}