#include "preprocessor.h"

int main(int argc, char *argv[])
{	
	int i;
	for (i = 1; i < argc; i++)
	{	
		macroPT head = NULL;
		readAndCreateFile(argv[i], &head);
		printList(head); 
		freeList(&head);
	}
}