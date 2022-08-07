#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "DataTable.h"

#define MAX 81

/******************************************* functions *******************************************/
char * readNextLine(FILE *);
int skip2command(char *,FILE *);
char * readNextWord(char *);
char * getCurrentWord(char *);

/*************************************************************************************************/
/*read next line in file. return pointer to line beginning*/
char * readNextLine(FILE *fpAm)
{
    static char buffer[MAX];

    int i=0, length =0;
    if(skip2command(buffer,fpAm)) {
        i = strspn(buffer, " \t");
        char *p = strchr(buffer + i, '\n');
        if(p)
            *p = '\0';
        return (buffer + i);
    } else
        return NULL;
}

char * readNextWord(char *buffer)
{
    char *currentWord, *txtPT;
    int j,i = 0;
    currentWord = (char *)malloc(sizeof(char) * MAX);

    j= strspn(buffer," \t");            /*if there is no next word*/
    if(j == strlen(buffer))
        return NULL;

    sscanf(buffer, "%s", currentWord);
    i = i+ strlen(currentWord);
    while(buffer[i] == ' '|| buffer[i] == '\t')
        i++;
    txtPT = buffer;
    txtPT = txtPT + i;
    return txtPT;
}
char * getCurrentWord(char *buffer)
{
    char *currentWord;
    currentWord = (char *)malloc(sizeof(char) * MAX);

    sscanf(buffer, "%s", currentWord);
    return currentWord;
}

/*skips comment lines and blank lines*/
int skip2command(char *buffer,FILE *fpAm)
{
    enum flag commentFlag =ON;
    int i;
    if(fgets(buffer, MAX, fpAm)) {
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
    } else
        return 0;
}