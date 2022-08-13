#include "preprocessor.h"
#include "firstcheck.h"

int main(int argc, char *argv[])
{	 
	int i;
	for (i = 1; i < argc; i++)
	{	
		macroPT head = NULL;
		labelPT lhead = NULL;
		readAndCreateFile(argv[i], &head); 
		freeList(&head);
		firstCheck(argv[i], &lhead);
	}
}
