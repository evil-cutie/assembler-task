#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct labelLS *labelPT;
typedef struct labelLS
{
    char *label;
    int address;                   /* in decimal */
    short type;                    /* data = 0, code = 1 */
    labelPT next;
}labelLS;

/******************************************* functions *******************************************/
labelPT findLabel(labelPT head, char *name);
void addLabel(labelPT *head, char *label, int address, short type);
void printLabelList(labelPT head);
void freeLabelList(labelPT *head);
/*************************************************************************************************/
