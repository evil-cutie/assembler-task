#include "secondcheck.h"

int main(int argc, char *argv[])
{	 
	int i, DC;
	for (i = 1; i < argc; i++)
	{	
		macroPT macroHead = NULL;
		labelPT labelHead = NULL;
		labelPT externalHead = NULL;
		readAndCreateFile(argv[i], &macroHead); 
		freeList(&macroHead);
		if(error == FALSE)
			DC = firstCheck(argv[i], &labelHead);
		if(compilationError == FALSE)
			secondcheck(argv[i], &labelHead, &externalHead, DC);
		freeLabelList(&labelHead);
	}
}
