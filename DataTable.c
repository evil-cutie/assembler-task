#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 81

enum flag {OFF =0,ON =1};
enum flag commentFlag =OFF;

typedef struct nodeData *dataPT;
typedef struct nodeData
{
    int data;                       /*in decimal */
    int DC;                         /*data count in decimal */
    dataPT next;
}nodeData;
/******************************************* functions *******************************************/
char * readNextCommand(FILE *);
void skipComments(char *,FILE *);
/*************************************************************************************************/
char * readNextCommand(FILE *fpAm)
{
    static char buffer[MAX];
    if(fgets(buffer, MAX, fpAm))
    {
        skipComments(buffer,fpAm);
        return buffer;
    }
    return NULL;
}

void skipComments(char *buffer,FILE *fpAm)
{
    if (strstr(buffer, "/*") || strstr(buffer, "*/")) {
        commentFlag = ON;
        while (fgets(buffer, MAX, fpAm) && commentFlag == ON) {
            if (strstr(buffer, "*/"))
                commentFlag = OFF;
        }
    }
}