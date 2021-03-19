#include<stdio.h>
#include<stdlib.h>

struct dynString
{
	char letter;
	struct dynString *next;
};
typedef struct dynString dynStr;

int size (dynStr *str) //Ok
{
	if(str != NULL)
		return size (str->next) + 1;
	return 0;
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


void restart(dynStr **str) //Ok
{
	dynStr *aux;
	
	while(*str != NULL)
	{
		aux = *str;
		*str = (*str)->next;
		free(aux);
	}
}

void arrayToString (dynStr **dest, char source[])
{
	restart(&*dest);
	int i = 0;
	while (source[i] != '\0')
		insert(&*dest, source[i++]);
}

int indexOf(dynStr *str1, dynStr *str2) // 13)
{
	int i = -1;
	int flag = 0;
	dynStr *auxStr1;
	dynStr *auxStr2;
	
	if (str1 == NULL || str2 == NULL || size(str2) > size(str1))
		return -1;
	
	while (str1 != NULL && !flag)
	{
		if(str1->letter == str2->letter)
		{
			flag = 1;
			auxStr1 = str1;
			auxStr2 = str2;
			
			while (auxStr1 != NULL && auxStr2 != NULL && flag)
			{
				if (auxStr1->letter != auxStr2->letter)
					flag = 0;
					
				auxStr1 = auxStr1->next;
				auxStr2 = auxStr2->next;
			}
		}
		str1 = str1->next;
		i++;
	}
	if (auxStr2 == NULL && flag == 1)
		return i;
	return -1;
}

void recDisplay (dynStr *str) //Ok
{
	if (str != NULL) {
		
		printf("%c", str->letter);
		recDisplay(str->next);
	}
}

int main()
{
	printf("\"");
	system("title INDEX OF");
	dynStr *txt  = NULL;
	dynStr *str_dest = NULL;
	int i;
	char vetDest[50];
	char vetTeste[50];
	
	
	printf("Input Dest: ");
	fflush(stdin);
	gets(vetDest);
	arrayToString(&txt, vetDest);
	
	system("cls");
	printf("----------------insert----------------\n");
	/*insert(&txt, 'V');
	insert(&txt, 'i');
	insert(&txt, 'c');
	insert(&txt, 't');
	insert(&txt, 'o');
	insert(&txt, 'r');*/
	recDisplay(txt);
	
	
	
	printf("\nInput: ");
	fflush(stdin);
	gets(vetTeste);
	
	
	
	while (vetTeste[0] != '\0')
	{
		arrayToString(&str_dest, vetTeste);
		
		printf("Index: %d", indexOf(txt, str_dest));
		//getch();
		
		system("cls");
		printf("----------------insert----------------\n");
		recDisplay(txt);
		printf("\nInput: ");
		fflush(stdin);
		gets(vetTeste);
	}
	return 0;
}
