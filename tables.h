#include <stdio.h>
#include <string.h>
#define MAX 81
#define COMMANDS 16
#define DIRECTIVES 3
#define REGISTERS 8
#define ADDRESSING_MODES 4

typedef enum {
    modeImmediate, modeDirect, modeStruct, modeRegister
} AddressingMode;

typedef enum {
    DATA, STRUCT ,STRING
} DirectiveMode;

typedef enum {
    ENTRY , EXTERNAL
} EntExt;

typedef struct {
    char* name;
    int opcode;
    int numOperands;
    int modeSource[ADDRESSING_MODES];
    int modeDestination[ADDRESSING_MODES];
} Command;

typedef struct {
    char buffer[MAX];
    int cmdIdx;                          /*index of the tab of the command*/
    AddressingMode AddressingMode[2];
    char* operand[2];                   /*pointer to the operands*/
} AssemblerCommandLine;

typedef struct {
    char buffer[MAX];
    int dirIdx;                          /*index of the tab of the directive*/
    DirectiveMode type;
    char* operand[2];                   /*pointer to the operands*/
} AssemblerDirectLine;

/* valid command names */
static char validCommands[COMMANDS][MAX] = {
        {"mov"}, {"cmp"}, {"add"}, {"sub"},
        {"not"}, {"clr"}, {"lea"}, {"inc"},
        {"dec"}, {"jmp"}, {"bne"}, {"get"},
        {"prn"}, {"jsr"}, {"rts"}, {"hlt"}
};

/* valid register names */
static char validRegisters[REGISTERS][MAX] = {
        {"r0"}, {"r1"}, {"r2"}, {"r3"},
        {"r4"}, {"r5"}, {"r6"}, {"r7"}
};

/* other reserved words */
static char other[MAX][MAX] = {
        {"macro"}, {"endmacro"}
};

/* valid directive names */
static char validDirectives[DIRECTIVES][MAX] = {
        {".struct"}, {".data"}, {".string"}
};

/* binary command code */
static char binaryOpcode[COMMANDS][4] = {
        {"0000"}, {"0001"}, {"0010"}, {"0011"},
        {"0100"}, {"0101"}, {"0110"}, {"0111"},
        {"1000"}, {"1001"}, {"1010"}, {"1011"},
        {"1100"}, {"1101"}, {"1110"}, {"1111"}
};
/******************************************* functions *******************************************/
int isCommandName(char * word);
int isDirName(char * word);
int isRegisterName(char * word);
/*************************************************************************************************/
