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
char * readNextWord(char *);

char ** split2words(char *);
/*************************************************************************************************/
/*read next line in file. return pointer to line beginning*/
char * readNextCommand(FILE *fpAm)
{
    static char buffer[MAX];

    int i=0, length =0;
    if(fgets(buffer, MAX, fpAm)) {
        if(skip2command(buffer,fpAm)){
            while(buffer[i] == ' '|| buffer[i] == '\t')
                i++;
            length = strlen(buffer);
            buffer[length-1] = '\0';
            return &buffer[i];
        }
    }
    return NULL;
}

char * readNextWord(char *buffer)
{
    char *currentWord, *txtPT;
    int i = 0;
    currentWord = (char *)malloc(sizeof(char) * MAX);

    sscanf(buffer, "%s", currentWord);
    i = i+ strlen(currentWord);
    while(buffer[i] == ' '|| buffer[i] == '\t')
        i++;
    txtPT = buffer;
    txtPT = txtPT + i;
    return txtPT;
}

char ** split2words(char *buffer)
{
    static char **separated;
    char word[MAX];
    int i,wordIdx =0,wordCount =0,charCount=0;
    separated = (char **) malloc(sizeof(char *)*MAX);

    for (i = 0; i < MAX; i++) {
        if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n') {
            if (charCount) {
                separated[wordCount] = (char *) malloc(sizeof(char) * charCount);
                separated[wordCount] = &buffer[wordIdx];
                printf("%s",separated[wordCount]);
                if (buffer[i] == '\n')
                    break;
                wordIdx = -1;
                wordCount++;
                charCount = 0;
            }
        } else
            charCount++;
        if (charCount == 0 && wordIdx == -1 && buffer[i] != ' ')
            wordIdx = i + 1;
    }
}

/*skips comment lines and blank lines*/
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