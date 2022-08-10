#include "preprocessor.h"
#include "tables.h"

/* read .as file and create .am file with macro expansion */
FILE *readAndCreateFile(char *fname, macroPT *head)
{
	FILE *fpSource; /*pointer to a source file */
	FILE *fpAm; /* pointer to ".am" file */
	macroPT foundMacro = NULL;
	char *firstWord, *name, *textptr, *value;
	char fnameAm[MAX], fnameAs[MAX], buffer[100];
	int i = 1;
	value = name = textptr = firstWord = NULL;
	newMacro = FALSE;
	strcpy(fnameAm, fname);
	strcpy(fnameAs, fname);
	strncat(fnameAm, ".am", 3); /* filename.am */
	strncat(fnameAs, ".as", 3); /* filename.as */
	
	fpSource = fopen(fnameAs, "r");
	if(!fpSource)
		printf("Error: cannot open a file '%s' \n", fnameAs);
	fpAm = fopen(fnameAm, "w");
	if(!fpAm)
		printf("Error: cannot create a file '%s' \n", fnameAm);
	/* memory allocation for pointers */
	textptr = (char*)malloc(sizeof(char)*MAX);
	firstWord = (char*)malloc(sizeof(char)*MAX);
	name = (char*)malloc(sizeof(char)*MAX);
	
	while(fgets(buffer, 100, fpSource))
	{	
		lineLength(buffer); /* check if line length is valid */
		sscanf(buffer, "%s", firstWord); /* scan a first word in a line */
		foundMacro = findMacro(*head, firstWord);
		if(foundMacro)
		{
			fputs(foundMacro->line, fpAm);
			memset(buffer, '\0', MAX);
		}
		if(newMacro)  
		{
			if(strcmp(firstWord, "endmacro")) /* macro definition is still in progress */
			{
			strcat(value, buffer);
			value = (char*)realloc(value, sizeof(char)*MAX*i++);
			if(!value)
				printf("Memory allocation error: cannot allocate memory for %p\n",(void*)value);
			}
			else
			{
			newMacro = FALSE;
			addMacro(head, name, value);
			free(value); /* free the memory for next macro value */
			memset(buffer, '\0', MAX);
			}
		}
		if(!strcmp(firstWord, "macro")) /* found new macro definition */
		{
			newMacro = TRUE;
			value = (char*)malloc(sizeof(char)*MAX);
			textptr = buffer;
			textptr = textptr + strlen("macro"); /* move a pointer to the next word */
			sscanf(textptr, "%s", name); /* scan next word */
			if((isCommandName(name) > -1) || (isDirName(name) > -1) || (isRegisterName(name) > -1))
			{
				printf("\nError: macro name cannot be '%s'\n", name);
				error = TRUE;
				newMacro = FALSE;
			}
		}
		if(!newMacro)
			fputs(buffer, fpAm); /* copy a line of code which is not macro definition to .am file */
	}
	fclose(fpSource);
	rewind(fpAm);
	
	if(error) 
	{
		remove(fnameAm);
		printf("removed file\n");
	}
	return fpAm;
}
/* add new macro to list */
void addMacro(macroPT *head, char *name, char *string)
{
	macroPT new = (macroPT)malloc(sizeof(macroLS));
	macroPT temp = (*head); 
	
	if(!new)
		printf("\nError: Cannot build macro list\n");
	
	new->name = strdup(name);
	new->line = strdup(string);
	new->next = NULL;
	
	if(head == NULL) 
		(*head) = new;
	
	else
	{
		(*head) = new;
		(*head)->next = temp;
	}
}
/* find macro in a list */
macroPT findMacro(macroPT head, char *name)
{
	while(head)
	{
		if(!strcmp(name, head->name))
			return head;
		head = head->next;
	}
	return head;
}
/* print macro table */
void printList(macroPT head)
{	
	int i = 0;
	printf("\n****************** MACRO TABLE ******************\n");
	while(head)
	{
		printf("\n___macro #%d___ \n", ++i); 
		printf("name: %s\n", head->name);
		printf("value: %s\n", head->line);
		head = head->next;
	}
	printf("\n**************** END MACRO TABLE ****************\n");
}
void freeList(macroPT *head)
{
	macroPT temp;
	while(*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}
/* check line length */
void lineLength(char *line)
{	
	if(strlen(line) >= MAX) 
	{
		printf("\nError: a line must be 80 characters maximum\n");
		error = TRUE;
	}
}
