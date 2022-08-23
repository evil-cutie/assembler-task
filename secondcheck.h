#include "firstcheck.h"

/******************************************* functions *******************************************/
void secondcheck(char *fname, labelPT *head, labelPT *externalHead, int DC);
int secondCheckLine(char **line, int IC, labelPT *head, labelPT *externalHead, int lineCount);
char *decodeLabel(char *label, labelPT *head, labelPT *externalHead, int lineCount, int IC);
void createExternFile(labelPT externalHead, char *fname);
void createEntryFile(labelPT head, char *fname);
void createObjectFile(char *fname, int IC, int DC);
void printBinary();
/*************************************************************************************************/
