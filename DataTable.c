#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 81

enum flag {OFF =0,ON =1};

typedef struct nodeData *dataPT;
typedef struct nodeData
{
    int data;                       /*in decimal */
    int DC;                         /*data count in decimal */
    dataPT next;
}nodeData;
/******************************************* functions *******************************************/
char * readNextCommand(FILE *);
int skip2command(char *,FILE *);
/*************************************************************************************************/
char * readNextCommand(FILE *fpAm)
{
    static char buffer[MAX];
    if(fgets(buffer, MAX, fpAm))
    {
        if(skip2command(buffer,fpAm))
            return buffer;
    }
    return NULL;
}

int skip2command(char *buffer,FILE *fpAm)
{
    enum flag commentFlag =ON;
    int i;
    while (commentFlag == ON) {
        for (i = 0; i < MAX; i++) {         /*check if line is blank (whitespaces only)*/
            if (buffer[i] == '\n')
                break;
            if (!isspace(buffer[i])) {
                commentFlag = OFF;
                break;
            }
        }
        if (strstr(buffer, ";"))            /*check if a comment*/
            commentFlag = ON;
        if (commentFlag == OFF)
            return 1;
        if (!fgets(buffer, MAX, fpAm))
            return 0;
    }
}