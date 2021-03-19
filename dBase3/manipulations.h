/*struct posicoes
{
	unsigned int y;
};
typedef struct posicoes Posicoes;
*/
struct field
{
	char nome[50];
	char tipo; 
	int largura;
	int dec;
};
typedef struct field Entradas;

int trocaUnidade (Dir **unid, char letra)
{
	/*
	*return 1 - successfully
	*return 0 - unsuccessfully
	*/
	
	Dir *aux = *unid;
	while(aux->top != NULL && aux->letter != letra)
		aux = aux->top;
	
	if(aux->letter == letra)
	{
		*unid = aux;
		return 1;
	}
		
	aux = *unid;
	while(aux->bottom != NULL && aux->letter != letra)
		aux = aux->bottom;
		
	if(aux->letter == letra)
	{
		*unid = aux;
		return 1;
	}
	return 0;
}

Arq *novoArquivo (Dir *unid, char nomeArq[])
{
	return createNewDBF(unid, nomeArq);
}

void listaArquivo (Dir *unid)
{
	Arq *aux = unid->arqs;
	while(aux != NULL)
	{
		printf("%s\n", aux->nomeDBF);
		aux = aux->prox;
	}
}

Arq *abrirArquivo (Dir *unid, const char *nomeArq)
{
	Arq *aux = unid->arqs;
	while(aux != NULL && stricmp(aux->nomeDBF, nomeArq))
		aux = aux->prox;
		
	return aux;
}

void insertFields(Arq *arq)
{
	Entradas in;
	int i = 1;
	show();
	printf("  %d  ", i);
	fflush(stdin);
	gets(in.nome);
	
	while(stricmp(in.nome, "\0"))
	{
		gotoxy(17, i + 2); in.tipo = getche();
		fflush(stdin);
		gotoxy(25, i + 2); scanf("%d", &in.largura);
		fflush(stdin);
		gotoxy(33, i + 2); scanf("%d", &in.dec);
		i++;
		
		createNewField(arq, in.nome, toupper(in.tipo), in.largura, in.dec);
		
		printf("  %d  ", i);
		fflush(stdin);
		gets(in.nome);
	}
	system("cls");
}

void listarFields(Arq *arq, Dir *uni)
{
	if(arq != NULL)
	{
		Campos *f = arq->cmps;
		int i = 1;
		system("cls");
		printf("Structure for database: %c:%s\n", uni->letter, arq->nomeDBF);
		printf("Field	Field Name		Type	Width	Dec\n");
		while(f != NULL)
		{
			gotoxy(3, i + 2); printf("  %d  ", i);
			gotoxy(9, i + 2); printf("%s", f->fieldName);
			gotoxy(33, i + 2); printf("%c", f->type);
			gotoxy(41, i + 2); printf("%d", f->width);
			gotoxy(49, i + 2); printf("%d", f->dec);
			f = f->prox;
			i++;
		}
		printf("\n");
	}
}

void append (Arq *arq)
{
	if(arq != NULL)
	{
		Campos *aux = arq->cmps;
		char info[50];
		
		if(aux != NULL) //Exibicao das Fields
		{
			system("cls");
			while(aux != NULL)
			{
				printf("%s\n", aux->fieldName);
				aux = aux->prox;
			}
			aux = arq->cmps;
			createNewStatus(arq);
		}
		
		int i = 1;
		while(aux != NULL)
		{
			gotoxy(17, i++);
			fflush(stdin);
			gets(info);
			createNewCell(aux, info);
			aux = aux->prox;
		}
	}
}

int getRegSize(Status *stts)
{
	int i = 0;
	Status *aux = stts;
	while(aux != NULL)
		if(aux->status)
			i++;
	return i;
}

void list (Arq *arq) { //Ok
	
	if(arq != NULL && arq->stts != NULL && getRegSize(arq->stts)) //Ok
	{
		int i = 1;
		Status *posStts = arq->stts;
		Campos *auxCmps = arq->cmps;
		unsigned char flag;
		
		
		printf("Record#		");
		while (auxCmps != NULL)
		{
			printf("%s		", auxCmps->fieldName);
			auxCmps = auxCmps->prox;
		}
		printf("\n");
		auxCmps = arq->cmps;
		
		while(posStts != NULL) //ou posStts != NULL
		{
			flag = 1;
			while(auxCmps != NULL)
			{
				if(/*SET DELETED off/on*/ 0 || posStts->status)
				{
					if(flag)
					{
						printf("%d		", i++);
						flag = 0;
					}
					
					switch(auxCmps->type)
					{
						case 'N' : {
							printf("%.2f		", auxCmps->pAtual->valor.valorN);
							break;
						}
						
						case 'L' : {
							printf("%c		", auxCmps->pAtual->valor.valorL);
							break;
						}
						
						case 'D' : {
							printf("%s		", auxCmps->pAtual->valor.valorD);
							break;
						}
						case 'C' : {
							printf("%s		", auxCmps->pAtual->valor.valorC);
							break;
						}
						case 'M' : {
							printf("%s		", auxCmps->pAtual->valor.valorM);
							break;
						}
					}
				}
				auxCmps->pAtual = auxCmps->pAtual->prox;
				auxCmps = auxCmps->prox;
			}
			printf("\n");
			posStts = posStts->prox;
			auxCmps = arq->cmps;
		}
		//Retornar pAtual posStts para primeira posicao valida (nao marcada para exclusao).
		
		/*struct pointers {
			//unidade aberta
			//arquivo aberto
			//registro atual
		};*/
		
		posStts = arq->stts;
		while(auxCmps != NULL)
		{
			auxCmps->pAtual = auxCmps->p_dados;
			while(posStts != NULL  && posStts->status == 0)
			{
				auxCmps->pAtual = auxCmps->pAtual->prox;
				posStts = posStts->prox;
			}
			auxCmps = auxCmps->prox;
			if(auxCmps != NULL)
				posStts = arq->stts;
		}
		auxCmps = arq->cmps;
		//printf("\n");
	}
}



void listFor (Arq *arq, char field[], char valor[])
{
	if(arq != NULL && arq->stts != NULL && getRegSize(arq->stts))
	{
		//POSICIONA PONTEIROS
		int i = 1;
		unsigned char flag = 0;
		Status *posStts = arq->stts;
		Campos *auxCmps = arq->cmps;
		Campos *fieldEncontrada;
		//POSICIONA PONTEIROS
		
		
		
		//Já verificando se Field exisite
		while (auxCmps != NULL && !flag)
		{
			if(!stricmp(auxCmps->fieldName, field))
				flag = 1;
			auxCmps = auxCmps->prox;
		}
		fieldEncontrada = auxCmps;
		auxCmps = arq->cmps;
		//Já verificando se Field exisite
				
				
		//EXIBE FIELDS
		printf("Record#		");
		while (auxCmps != NULL)
		{
			printf("%s		", auxCmps->fieldName);
			auxCmps = auxCmps->prox;
		}
		printf("\n");
		auxCmps = arq->cmps;
		//EXIBE FIELDS
		
		
		while(posStts != NULL)
		{
			printf("%d		", i++);
			while(auxCmps != NULL)
			{
				if((/*SET DELETED off/on*/ 0 || posStts->status) && indexOf(field, valor))
				{
					switch(auxCmps->type)
					{
						case 'N' : {
							printf("%.2f		", auxCmps->pAtual->valor.valorN);
							break;
						}
						
						case 'L' : {
							printf("%c		", auxCmps->pAtual->valor.valorL);
							break;
						}
						
						case 'D' : {
							printf("%s		", auxCmps->pAtual->valor.valorD);
							break;
						}
						case 'C' : {
							printf("%s		", auxCmps->pAtual->valor.valorC);
							break;
						}
						case 'M' : {
							printf("%s		", auxCmps->pAtual->valor.valorM);
							break;
						}
					}
				}
				auxCmps->pAtual = auxCmps->pAtual->prox;
				auxCmps = auxCmps->prox;
			}
			printf("\n");
			posStts = posStts->prox;
			auxCmps = arq->cmps;
		}
		//Retornar pAtual posStts para primeira posicao valida (nao marcada para exclusao).
		
		/*struct pointers {
			//unidade aberta
			//arquivo aberto
			//registro atual
		};*/
		
		posStts = arq->stts;
		while(auxCmps != NULL)
		{
			auxCmps->pAtual = auxCmps->p_dados;
			while(posStts != NULL  && posStts->status == 0)
			{
				auxCmps->pAtual = auxCmps->pAtual->prox;
				posStts = posStts->prox;
			}
			auxCmps = auxCmps->prox;
			if(auxCmps != NULL)
				posStts = arq->stts;
		}
		auxCmps = arq->cmps;
		//printf("\n");
	}
}
