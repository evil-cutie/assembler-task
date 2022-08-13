#include "preprocessor.h"
#include "ltable.h"
#include "tables.h"
#define SIZE 1000

static char instructions[SIZE][10];
static char data[SIZE][10];
enum boolean label;
enum boolean compilationError;

/******************************************* functions *******************************************/
void firstCheck(char *filename, labelPT *head);
char **getNextWord(char *line);
void checkLine(char **nextword, int *DC, int *IC, labelPT *head);
int isLabel(char *word);
/*************************************************************************************************/
