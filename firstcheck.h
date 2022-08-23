#include "preprocessor.h"
#include "ltable.h"
#include "convert.h"
#define ROWS 256
#define DATA 0
#define CODE 1
#define EXTERN 2
#define ENTRY 3

extern char instructions[ROWS][BITS + 1];
extern char data[ROWS][BITS + 1];
enum boolean compilationError;

/******************************************* functions *******************************************/
int firstCheck(char *filename, labelPT *head);
char **getNextWord(char *line);
void checkLine(char **nextword, int *DC, int *IC, labelPT *head, int lineCount);
int isLabelDef(char *word, int lineCount);
char *operand(char *nextword);
char *opcode(char *nextword);
int decodeString(char *string, int DC, int lineCount);
int decodeData(char **line, int DC, int lineCount);
int decodeStruct(char **line, int DC, int lineCount);
int isLegalLabel(char *label);
int decodeCommand(char **line, int pos, int IC, int lineCount);
int checkOperands(char *sourceOp, char *destOp, int IC, int lineCount);
char *registerBin(char *regist);
int isLegalOperand(char *command, char *sourceOp, char *destOp, int lineCount);
int decodeNum(char *op, int IC, int lineCount);
int decodeStructAccess(char *op, int IC);
void updateDataAddress(int IC, labelPT *head);
int searchEntryOrExtern(char **line, labelPT *head, int pos, int lineCount);
int defineNewData(char **line, labelPT *head, int DC, int lineCount, int pos);
void addToTable(char *newLabel, labelPT *head, int value, int type, int lineCount);
char *isValidString(char *string, int lineCount);
int isValidNumber(char *num, int lineCount);
/*************************************************************************************************/
