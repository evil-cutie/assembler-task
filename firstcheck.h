#include "preprocessor.h"
#include "ltable.h"
#include "convert.h"
#define ROWS 100
#define DATA 0
#define CODE 1
#define EXTERN 2

static char instructions[ROWS][BITS + 1];
static char data[ROWS][BITS + 1];

enum boolean label;
enum boolean compilationError;

/******************************************* functions *******************************************/
void firstCheck(char *filename, labelPT *head);
char **getNextWord(char *line);
void checkLine(char **nextword, int *DC, int *IC, labelPT *head);
int isLabelDef(char *word);
char *operand(char *nextword);
char *opcode(char *nextword);
int decodeString(char *string, int DC);
int decodeData(char **line, int DC);
int decodeStruct(char **line, int DC);
int isLegalLabel(char *label);
int decodeCommand(char **line, int pos, int IC);
void printBinary();
int checkOperands(char *sourceOp, char *destOp, int IC);
char *registerBin(char *regist);
int isLegalOperand(char *command, char *sourceOp, char *destOp);
int decodeNum(char *op, int IC);
int decodeStructAccess(char *op, int IC);
void updateDataAddress(int IC, labelPT *head);
/*************************************************************************************************/
