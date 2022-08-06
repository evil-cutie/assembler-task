#include "tables.h"
Command allCommands[] = {
        {"mov", 0,  2,  {0,1,2,3} , {1,2,3}},
        {"cmp", 1,  2,  {0,1,2,3} , {0,1,2,3}},
        {"add", 2,  2,  {0,1,2,3} , {1,2,3}},
        {"sub", 3,  2,  {0,1,2,3} , {0,1,2,3}},
        {"not", 4,  1,  {}        , {1,2,3}},
        {"clr", 5,  1,  {}        , {1,2,3}},
        {"lea", 6,  2,  {1,2}     , {1,2,3}},
        {"inc", 7,  1,  {}        , {1,2,3}},
        {"dec", 8,  1,  {}        , {1,2,3}},
        {"jmp", 9,  1,  {}        , {1,2,3}},
        {"bne", 10, 1,  {}        , {1,2,3}},
        {"get", 11, 1,  {}        , {1,2,3}},
        {"prn", 12, 1,  {}        , {0,1,2,3}},
        {"jsr", 13, 1,  {}        , {1,2,3}},
        {"rts", 14, 0,  {}        , {}},
        {"hlt", 15, 0,  {}        , {}}
};

/* checks if a command is valid */
/* return 1 if valid */
/* return 0 if not valid */
int isCommandName(char * word)
{
    int i = 0;
    while(i++ <= COMMANDS)
    {
        if(strcmp(validCommands[i], word) == 0)
            return i;
    }
    return -1;
}

/* checks if a directive is valid */
/* return 1 if valid */
/* return 0 if not valid */
int isDirName(char * word)
{
    int i = 0;
    while(i++ <= DIRECTIVES)
    {
        if(strcmp(validDirectives[i], word) == 0)
            return i;
    }
    return -1;
}

/* checks if a register name is valid */
/* return 1 if valid */
/* return 0 if not valid */
int isRegisterName(char * word)
{
    int i = 0;
    while(i++ <= REGISTERS)
    {
        if(strcmp(validRegisters[i], word) == 0)
            return i;
    }
    return -1;
}