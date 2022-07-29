#include "convert.h"

/* convert decimal to binary */
char *decimalToBinary(int num)
{
	int i;
	char temp;
	char *binaryNum = (char*)malloc(sizeof(char)*10);
	int absnum = abs(num);
	memset(binaryNum, '0', BITS);	
	for(i = 0; absnum > 0; i++)    
	{    
		binaryNum[i]= absnum % 2 + '0';    
		absnum = absnum/2;    
	} 
	/* need to reverse binary number to get its true value */
	for(i = 0; i < BITS/2; i++)
	{
		temp = binaryNum[BITS - i - 1];
		binaryNum[BITS - i - 1] = binaryNum[i];
		binaryNum[i] = temp;
	}
	if(num < 0)
	{
		binaryNum = twosComplement(binaryNum);
	}
	return binaryNum;
}
/* convert binary to decimal */
int binaryToDecimal(char *binaryNum)
{
	int i, num, next, negative;
	num = 0;
	negative = 0; /* 0 when positive num, 1 when negative num */
	/* negative number case */
	if((binaryNum[0] - '0') == 1)
	{
		negative = 1;
		binaryNum = twosComplement(binaryNum);
	}
	/* convert to decimal */
	for(i = BITS - 1; i >= 0; i--)
	{
		next = binaryNum[i] - '0';
		num += next * pow(2, BITS - (i+1));
	}
	if(negative)
		return 0 - num;
	return num;
}
/* find two's complement of a given binary number */
char *twosComplement(char *num) 
{
   int i, carry = 1;
   char one[BITS + 1];
   char *complement = (char*)malloc(sizeof(int)*BITS);
   /* find one's complement */
   for(i = 0; i < BITS; i++)
   {
      if(num[i] == '0')
      {
         one[i] = '1';
      }
      
      else if (num[i] == '1') 
      {
         one[i] = '0';
      }
   }
   one[BITS] = '\0';
   /* find two's complement */
   for(i = BITS - 1; i >= 0; i--)
   {
      if(one[i] == '1' && carry == 1)
         complement[i] = '0';
      
      else if(one[i] == '0' && carry == 1)
      {
         complement[i] = '1';
         carry = 0;
      }
      else
      {
         complement[i] = one[i];
      }
   }
   complement[BITS] = '\0';
   return complement;
}

