#include "ltable.h"

void addLabel(labelPT *head, char *label, int address, short type)
{
	labelPT new = (labelPT)malloc(sizeof(labelLS));
	labelPT temp = (*head); 
	
	if(!new)
		printf("\nError: Cannot build label list\n");
	
	new->label = strdup(label);
	new->address = address;
    new->type = type;
	new->next = NULL;
	
	if(head == NULL) 
		(*head) = new;
	
	else
	{
		(*head) = new;
		(*head)->next = temp;
	}
}

labelPT findLabel(labelPT head, char *name)
{
	while(head)
	{
		if(!strcmp(name, head->label))
			return head;
		head = head->next;
	}
	return head;
}

void printLabelList(labelPT head)
{	
	int i = 0;
	printf("\n****************** LABEL TABLE ******************\n");
	while(head)
	{
		printf("\n___label #%d___ \n", ++i); 
		printf("label: %s\n", head->label);
		printf("address: %d\n", head->address);
		head = head->next;
	}
	printf("\n**************** END LABEL TABLE ****************\n");
}