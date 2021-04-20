#include <stdio.h>
#include <stdlib.h>


struct dynString
{
	char letter;
	struct dynString *next;
};
typedef struct dynString dynStr;

void recDisplay (dynStr *str) //Ok
{
	if (str != NULL) {
		
		printf("%c", str->letter);
		recDisplay(str->next);
	}
}

void insert (dynStr **str, char c) // Item 6) Insere um caracter ao final
{
	dynStr *aux = *str;
	dynStr *n = (dynStr*) malloc (sizeof(dynStr));
	n->letter = c;
	n->next  = NULL;
	
	if (*str == NULL)
		*str = n;
	else {
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = n;
	}
}

void main()
{
	char c;
	dynStr *txt  = NULL;
	
	c = getchar();
	while (c != '*')
	{
		insert(&txt, c);
		c = getche();
	}
	
	printf("\n\n");
	recDisplay(txt);
}
