#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define BITS 10

/* base 32 characters */
static char base32chars[32] = {
	'!', '@', '#', '$', '%', '^', '&', '*', '<', '>', 'a', 'b', 'c',
	'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
	'q', 'r', 's', 't', 'u', 'v'
};

/******************************************* functions *******************************************/
char *decimalToBinary(int num);
int binaryToDecimal(char *binaryNum);
char *twosComplement(char *num);
/*************************************************************************************************/
