#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct dynString
{
	char letter;
	struct dynString *next;
};
typedef struct dynString dynStr;


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

void restartRec(dynStr **str) //Ok
{
	if (*str != NULL)
	{
		restartRec(&(*str)->next);
		free(*str);
		*str = NULL;
	}
}

void recDisplay (dynStr *str) //Ok
{
	if (str != NULL) {
		
		printf("%c", str->letter);
		recDisplay(str->next);
	}
}

void displayRecInv (dynStr *str) //Ok
{
	if(str != NULL)
	{
		displayRecInv(str->next);
		printf("%c", str->letter);
	}
}

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

void append (dynStr **dest, dynStr *source) //Insere string ao final ao final 
{
	while (source != NULL) {
		
		insert(&*dest, source->letter);
		source = source->next;
	}
}

void replaceAll (dynStr **dest, dynStr *source) //Item 7) zera a string destino e copia conteudo da string origem
{
	restartRec(&*dest);
	while (source != NULL) {
		
		insert(&*dest, source->letter);
		source = source->next;
	}
}

void concat (dynStr **dest, dynStr *firstSource, dynStr *secSource) //Item 8) Concatena retornando a uma terceira string
{
	restart(&*dest);
	append(&*dest, firstSource);
	append(&*dest, secSource);
}

void delSubs (dynStr **str, int start, int n) //Item 9)
{
	dynStr *aux;
	dynStr *auxDel;
	
	if (start < size(*str) && start >= 0) {
		
		if (start == 0) {
			
			while (*str != NULL && n--)
			{ 
				auxDel = *str;
				*str = (*str)->next;
				free(auxDel);
			}
			
		} else {
			
			start--;
			aux = *str;
			while (start--)
				aux = aux->next;
			
			while (aux->next != NULL && n--)
			{
				auxDel = aux->next;
				aux->next = aux->next->next;
				free(auxDel);
			}
		}
	}
}

void subsInsert (dynStr **dest, dynStr *source, int start) //Item 10) //Tem que alocar mais memoria, ou seja, usar Insert ERROOO CONCERTAR
{
	int i;
	dynStr *auxSource = NULL;
	append(&auxSource, source);
	dynStr *aux = auxSource;
	dynStr *auxDest = *dest;
	
	if (start >= 0 && start <= size(*dest) && auxSource != NULL)
	{
		while (aux->next != NULL)
			aux = aux->next;
			
		if (start == 0) 
		{
			aux->next = *dest;
			*dest = auxSource;
		} 
		else
		{
			for (i = 0; i < start - 1; i++)
				auxDest = auxDest->next;
			
			aux->next = auxDest->next;
			auxDest->next = auxSource;
		}
	}
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

void stringToArray (char vet[], dynStr *source)
{
	int i = 0;
	while (source != NULL) {
		vet[i] = source->letter;
		source = source->next;
		i++;
	}
	vet[i] = '\0';
}

void arrayToString (dynStr **dest, char source[])
{
	int i = 0;
	while (source[i] != '\0')
		insert(&*dest, source[i++]);
}

int main()
{
	
	dynStr *txt  = NULL;
	dynStr *txt1 = NULL;
	dynStr *txt2 = NULL;
	dynStr *txt3 = NULL;
	
	printf("----------------insert----------------\n");
	insert(&txt, 'V');
	insert(&txt, 'i');
	insert(&txt, 'c');
	insert(&txt, 't');
	insert(&txt, 'o');
	insert(&txt, 'r');
	recDisplay(txt);
	printf("\n");
	
	insert(&txt1, 'R');
	insert(&txt1, 'o');
	insert(&txt1, 'd');
	insert(&txt1, 'r');
	insert(&txt1, 'i');
	insert(&txt1, 'g');
	insert(&txt1, 'u');
	insert(&txt1, 'e');
	insert(&txt1, 's');
	recDisplay(txt1);
	printf("\n\n");
	
	printf("----------------concat----------------\n");
	concat(&txt2, txt, txt1);
	
	recDisplay(txt2);
	printf("\n\n");
	
	printf("--------------subsInsert--------------\n");
	insert(&txt3, 'T');
	insert(&txt3, 'a');
	insert(&txt3, 'v');
	insert(&txt3, 'e');
	insert(&txt3, 'i');
	insert(&txt3, 'r');
	insert(&txt3, 'a');
	recDisplay(txt3);
	printf("\n");
	
	
	subsInsert(&txt2, txt3, 6);
	recDisplay(txt2);
	printf("\n\n");
	
	
	printf("----------------indexOf---------------\n");
	
	
	dynStr *teste = NULL;
	insert(&teste, 'R');
	insert(&teste, 'o');
	insert(&teste, 'd');
	char vetTeste[size(teste)];
	stringToArray(vetTeste, teste);
	
	char vet2[size(txt2)];
	stringToArray(vet2, txt2);
	
	char vet3[size(txt3)];
	stringToArray(vet3, txt3);
	
	
	if(indexOf(txt2, txt3) >= 0)
		printf("[%s] esta contido em [%s] e comeca na posicao: %d\n", vet3, vet2, indexOf(txt2, txt3));
		
	if(indexOf(txt2, teste) >= 0)
		printf("[%s] esta contido em [%s] e comeca na posicao: %d\n\n", vetTeste, vet2, indexOf(txt2, teste));
	
	
	
	printf("----------------delSubs---------------\n");
	recDisplay(txt2);
	int start = 0;
	int nro = 6;
	printf("\nStart: %d", start);
	printf("\nNro: %d\n", nro);
	delSubs(&txt2, start, nro); //Trocar para variaveis
	recDisplay(txt2);
	
	printf("\n\n-------------displayRecInv------------\n");
	recDisplay(txt2);
	printf("\n");
	displayRecInv(txt2);
	printf("\n\n");
	
	printf("----------------append---------------\n");
	char umaverdade[] = " O MaIs LiNdO dA FiPp";
	dynStr *trueDaTrue = NULL;
	arrayToString(&trueDaTrue, umaverdade);
	
	recDisplay(txt2);
	printf("\n");
	recDisplay(trueDaTrue);
	printf("\n");
	
	append(&txt2, trueDaTrue);
	recDisplay(txt2);
	printf("\n");
	return 0;
}

