#include "firstcheck.h"
#include "SymbolTable.h"
#include "DataTable.h"


enum flag symbolFlag = OFF;
enum flag errorFlag = OFF;

void firstCheck(char *fileName)
{
   /* int IC, DC;
    IC = DC = 0; 
    char nextline[MAX]; */
    FILE *filePointer;
    strncat(fileName, ".am", 3);
    filePointer = fopen(fileName, "r+");
    scan1(filePointer);
    /*while(fgets(nextline, MAX, filePointer))
    {
        char **nextword = getNextWord(nextline);
        checkLine(nextword);
     }*/
}

void scan1(FILE *fpAm) {
    symbolPT head = NULL;
    symbolPT *symbolListHead = &head;

    int IC, DC, i, lineCount;
    IC = DC = i = lineCount = 0;
    char *line;
    char *txtPT;

    line = (char *) malloc(sizeof(char) * MAX);
    txtPT = (char *) malloc(sizeof(char) * MAX);

    while (line = readNextLine(fpAm)) {
        lineCount++;
        printf("%s\n", line);
        if (isSymbol(line)) {
            symbolFlag = ON;
            if (!isValidSymbol(head,line))
                printf(" (line %d)\n", lineCount);
            else
                addToEnd(symbolListHead,getSymbolLabel(line),0,0);
            txtPT = readNextWord(line);
        } else
            txtPT = line;
        if( (i = isCommand(txtPT)) != -1) {
            commandPT newCommand = createCommand(i,txtPT);
            if(newCommand == NULL)
                printf(" (line %d)\n", lineCount);
            printf("number of operands in line: %d\n",operandCount(txtPT));
        }
    }
}

char **getNextWord(char *line)
{
    int i = 0;
    char delim[] = {' ', '\t', ','};
    char **nextword;
    nextword = (char **)malloc(MAX * sizeof(*nextword));
    
    nextword[0] = strtok(line, delim);
    while(nextword[i])
    {
        i++;
        nextword[i] = strtok(NULL, delim);
    }
    return nextword;
}

void checkLine(char **line, int DC)
{
    int labelFlag = 0;
    int i = 0;
    if (isLabel(line[0]))
    {
        labelFlag = 1;
        if (isDirName(line[1]))
            addToLableTable(line[0], DC, "data");
    }
    while(line[i])
    {
        
        i++;
    }
}

int isLabel(char *word)
{
    if(strstr(word, ":"))
        return 1;
    return 0;
}

void addToLableTable(char *label, int address, char *type)
{
   /* printf("\n%s", label); */
}


