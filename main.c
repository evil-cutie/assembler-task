#include "firstcheck.h"

int main(int argc, char *argv[])
{	 
	int i;
	for (i = 1; i < argc; i++)
	{	
		macroPT head = NULL;
		labelPT labelHead = NULL;
		readAndCreateFile(argv[i], &head); 
		freeList(&head);
		if(error == FALSE)
			firstCheck(argv[i], &labelHead);
	}
}
