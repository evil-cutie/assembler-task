#include "SymbolTable.h"

/* create a new symbol and add it to the end of symbol list. return 1 if append is successful, 0 otherwise */
int addToEnd(symbolPT* head,char *label,int address,short type)
{
    symbolPT new = (symbolPT)malloc(sizeof(nodeSymbol));
    symbolPT pt;

    if(!new) {
        printf("\nError: Cannot add symbol to list\n");
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
    int i;
    i = strcspn(buffer, ":");                   /*get first word in line*/
    firstWord = (char *)malloc(sizeof(char)*i);
    memcpy( firstWord, buffer,i+1);
    firstWord[i+1] = '\0';
    if(strstr(firstWord, ":"))                  /*check label definition*/
        return 1;
    return 0;
}
int isValidSymbol(symbolPT head, char *buffer)
{
    char label[MAX];
    int i,j;
    i = strcspn(buffer, " :\t");
    if(buffer[i] != ':') {
        printf("Label name error: white spaces or tab in label name ");
        return 0;
    }
    memcpy( label, buffer,i);
    label[i] = '\0';
    if(checkInList(head,label)) {
        printf("Label name error: multiple definition ");
        return 0;
    }
    j= strspn(buffer+i+1," \t");
    if(j == 0){
        printf("Label name error: label in an empty line ");
        return 0;
    }
    return 1;
}

/*gets a pointer to label name, does not check if label is valid*/
char *getSymbolLabel(char *buffer)
{
    char *label, *temp;
    int i;
    i = strcspn(buffer, " :\t");
    label = memcpy( label, buffer,i);
    label[i] = '\0';
    return label;
}
