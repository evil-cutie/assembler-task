#include "firstcheck.h"

void firstCheck(char *fileName, labelPT *head)
{
    FILE *filePointer;
    char nextline[MAX];
    int *IC = (int*)malloc(sizeof(int));
    int *DC = (int*)malloc(sizeof(int));
    *IC = *DC = 0;
 
    strncat(fileName, ".am", 3);
    filePointer = fopen(fileName, "r");
    
    while(fgets(nextline, MAX, filePointer))
    {
        char **nextword = getNextWord(nextline);
        checkLine(nextword, DC, IC, head);
        printf("\n%d %d", *DC, *IC);
    }
}



char **getNextWord(char *line)
{
    char delim[] = {' ', '\t', ','};
    char **nextword;
    int i = 0;
    nextword = (char **)malloc(MAX * sizeof(*nextword));
    
    nextword[0] = strtok(line, delim);
    while(nextword[i])
    {
        i++;
        nextword[i] = strtok(NULL, delim);
    }
    return nextword;
}

void checkLine(char **line, int *DC, int *IC, labelPT *head)
{
    int tempIC = *IC;
    int tempDC = *DC;
    int i = 0;
    if (isLabel(line[0]))
    {
        label = TRUE;
        if (isDirName(line[1]))
        {
            if(!findLabel(*head, line[0]))
                addLabel(head, line[0], tempDC, 0); /* data type = 0 */
            else
                printf("Error: label %s already exists", line[1]);
            
        }
    }
    while(line[i])
    {
        
        i++;
    }
    *DC = tempDC;
    *IC = tempIC;
} 

int isLabel(char *word)
{
    if(strstr(word, ":"))
        return 1;
    return 0;
}



