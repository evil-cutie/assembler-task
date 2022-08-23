#include "ltable.h"

void addLabel(labelPT *head, char *label, int address, short type)
{
	labelPT new = (labelPT)malloc(sizeof(labelLS));
	
	if(!new)
		printf("\nError: Cannot build label list\n");
	
	new->label = strdup(label);
	new->address = address;
    new->type = type;
	new->next = NULL;
	
	if(!(*head)) 
		(*head) = new;
	
	else
	{
		labelPT *current = head;
		while((*current)->next)
			current = &(*current)->next;
		
		(*current)->next = new;
	}
}

labelPT *findLabel(labelPT *head, char *name)
{
	labelPT *current = (labelPT*)malloc(sizeof(labelPT));
	current = head;
	while(*current)
	{
		if(!strcmp(name, (*current)->label))
			return current;
		current = &(*current)->next;
	}
	return NULL;
}

void printLabelList(labelPT head)
{	
	int i = 0;
	printf("\n****************** LABEL TABLE ******************\n");
	while(head)
	{
		printf("\n___label #%d___ \n", ++i); 
		printf("label: %s\n", head->label);
		printf("address: %d\n", 100 + (head->address));
        if((head->type) == 0)
            printf("type: data\n");
        if ((head->type) == 1)
            printf("type: code\n");
		if((head->type) == 2)
			printf("type: extern\n"); 
		if((head->type) == 3)
			printf("type: entry\n"); 
		head = head->next;
	}
	printf("\n**************** END LABEL TABLE ****************\n");
}

void freeLabelList(labelPT *head)
{
	labelPT temp;
	while(*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}
