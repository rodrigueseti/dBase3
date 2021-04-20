struct posicoes
{
	Status *sttAtual;
};
typedef struct posicoes Posicoes;

Posicoes posis;

short int setdel_onoff = 0;


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
		gotoxy(posX, posY++); printf("%s", aux->nomeDBF);
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
		
		posY = 5;
		if(aux != NULL) //Exibicao das Fields
		{
			
			//system("cls");
			while(aux != NULL)
			{
				gotoxy(2, posY++); printf("%s", aux->fieldName);
				aux = aux->prox;
			}
			aux = arq->cmps;
			createNewStatus(arq);
		}
		
		//int i = 1;
		posY = 5;
		while(aux != NULL)
		{
			gotoxy(17, posY++); fflush(stdin); gets(info);
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
	{
		if(aux->status)
			i++;
		aux = aux->prox;
	}
	return i;
}
void showFieldType(Campos *auxCmps)
{
	switch(auxCmps->type)
	{
		case 'N' : {
			printf("%.2f\t", auxCmps->pAtual->valor.valorN);
			break;
		}
		
		case 'L' : {
			printf("%c\t", auxCmps->pAtual->valor.valorL);
			break;
		}
		
		case 'D' : {
			printf("%s\t", auxCmps->pAtual->valor.valorD);
			break;
		}
		case 'C' : {
			printf("%s\t", auxCmps->pAtual->valor.valorC);
			break;
		}
		case 'M' : {
			printf("%s\t", auxCmps->pAtual->valor.valorM);
			break;
		}
	}
}

void list (Arq *arq) { //Ok
	
	if(arq->stts != NULL)
	{
		system("cls");
		//DesenhaBorda();
		
		int i = 0, x = 15, y = 3, u = 3;
		Status *posStts = arq->stts;
		Campos *auxCmps = arq->cmps;
		pDados *auxP;
		
		gotoxy(u, 2); printf("Record#			");
		u = u + 15;
		while (auxCmps != NULL)
		{
			gotoxy(u, 2);printf("%s			", auxCmps->fieldName); 
			auxCmps = auxCmps->prox;
			u = u + 15;
		}
		
		auxCmps = arq->cmps;
		while(auxCmps != NULL){
			auxP = auxCmps->p_dados;
			posStts = arq->stts;
			while(auxP != NULL)	{
				if(setdel_onoff || posStts->status){
					switch(auxCmps->type)
					{
						case 'N' : {
							gotoxy(x, y++); printf("%.2f			", auxP->valor.valorN);
							break;
						}
						
						case 'L' : {
							gotoxy(x, y++); printf("%c			", auxP->valor.valorL);
							break;
						}
						
						case 'D' : {
							gotoxy(x, y++); printf("%s			", auxP->valor.valorD);
							break;
						}
						case 'C' : {
							gotoxy(x, y++); printf("%s			", auxP->valor.valorC);
							break;
						}
						case 'M' : {
							gotoxy(x, y++); printf("%s		", auxP->valor.valorM);
							break;
						}
					}
				}
				auxP = auxP->prox;
				posStts = posStts->prox;
			}
			y = 3;
			x = x + 15;
			auxCmps = auxCmps->prox;
		}
	
		auxP =  arq->cmps->p_dados;
		posStts = arq->stts;
		y = 3;
		while(posStts != NULL){
			if(setdel_onoff || posStts->status)
			{
				gotoxy(5, y++); printf(" %d ", i+1);
			}
			i++;
			posStts = posStts->prox;
		}
		gotoxy(25, 21); printf("press any key to continue");
		getch();
	}
}

void copy_value(char str[], Campos *field)
{
	switch(field->type)
	{
		case 'N' : {
			sprintf(str, "%f", field->pAtual->valor.valorN);
			break;
		}
		case 'L' : {
			str[0] = field->pAtual->valor.valorL;
			str[1] = '\0';
			break;
		}
		
		case 'D' : {
			strcpy(str, field->pAtual->valor.valorD);
			break;
		}
		case 'C' : {
			strcpy(str, field->pAtual->valor.valorC);
			break;
		}
		case 'M' : {
			strcpy(str, field->pAtual->valor.valorM);
			break;
		}
	}
}

/*
pDados *busca_dado(Campos *campo, char valor[])
{
	
}
*/

int compara_dado(Campos *campo, pDados *reg, char valor[])
{
	if((toupper(campo->type) == 'N' || toupper(campo->type) == 'L') && (reg->valor.valorN == valor[0] || reg->valor.valorL == valor[0]))
	    return 1;
	
	if(toupper(campo->type) == 'C' && !stricmp(reg->valor.valorC, valor))
	    return 1;
	
	if(toupper(campo->type) == 'D' && !stricmp(reg->valor.valorD, valor))
	    return 1;
	    
	if(toupper(campo->type) == 'M' && !stricmp(reg->valor.valorM, valor))
	    return 1;
	
	return 0;
}

Campos *busca_campo(Arq *arq, char valor[])
{
	Campos *auxCmps = arq->cmps;
	while(auxCmps != NULL && stricmp(auxCmps->fieldName, valor))
		auxCmps = auxCmps->prox;
		
	return auxCmps;
}

void exibeFields(Arq *arq)
{
	Campos *auxCmps = arq->cmps;
	
	if(auxCmps != NULL)
	{
		printf("Record#		");
		while (auxCmps != NULL)
		{
			printf("%s\t", auxCmps->fieldName);
			auxCmps = auxCmps->prox;
		}
		printf("\n");
	}
}

void listFor (Arq *arq, char field[], char valor[]) //Testar junto com display goto e edit
{
	if(arq != NULL && arq->stts != NULL && (setdel_onoff || getRegSize(arq->stts)))
	{
		//POSICIONA PONTEIROS
		int i = 1;
		int flag = 0;
		char str[50];
		Status *posStts = arq->stts;
		Campos *auxCmps = arq->cmps;
		Campos *fieldEncontrada;
		//POSICIONA PONTEIROS
		
		
		//Já verificando se Field exisite
		fieldEncontrada = busca_campo(arq, field);
		//Já verificando se Field existe
		
		//printf("%s", valor);
		if(fieldEncontrada != NULL)
		{
			//posicionando pAtual no primeiro registro
			while(auxCmps != NULL)
			{
				auxCmps->pAtual = auxCmps->p_dados;
				auxCmps = auxCmps->prox;
			}
			auxCmps = arq->cmps;
			//posicionando pAtual no primeiro registro
			
			//Exibe linha de Fields
			exibeFields(arq);
			//Exibe linha de Fields
			
			while(posStts != NULL)
			{
				flag = 1;
				copy_value(str, fieldEncontrada);
				
				while(auxCmps != NULL)
				{
					if((setdel_onoff || posStts->status) && indexOf(str, valor) != -1)
					{
						if(flag)
						{
							printf("%d\t", i++);
							flag = 0;
						}
						
						showFieldType(auxCmps);
					}
					auxCmps->pAtual = auxCmps->pAtual->prox;
					auxCmps = auxCmps->prox;
				}
				if(!flag)
					printf("\n"); //Tratar
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
				auxCmps = auxCmps->prox;
			}
			auxCmps = arq->cmps;
		}
	}
}

void DeleteAll(Status *s) //Atribuir nulo ao pAtual pois pAtual nao pode continuar apontando para um registro marcado para exclusao
{
	if(s != NULL) 
	{
		DeleteAll(s->prox);
		s->status = 0;
	}
}

void RecallAll(Status *s)  
{
	if(s != NULL) 
	{
		RecallAll(s->prox);
		s->status = 1;
	}
}


void set_delete(char valor[])
{
	if(!stricmp("on", valor))
	{
		setdel_onoff = 0;
		printf("set deleted 0\n");
	}
	else if(!stricmp("off", valor))
	{
		setdel_onoff = 1;
		printf("set deleted 1\n");
	}
	else printf("Comando Invalido\n");
}

int locate_for(Arq *arq, char field[], char valor[])
{
	Campos *campo_encontrado = busca_campo(arq, field);
	
	if(campo_encontrado != NULL)
	{
		pDados *aux;
	    Status *auxStts;
		short int flag = 1;
		int pos = 0;
		aux = campo_encontrado->p_dados;
		auxStts = arq->stts;
		
		while(aux != NULL && flag)
		{
			if((auxStts->status || setdel_onoff) && compara_dado(campo_encontrado, aux, valor))
				flag = 0;
			else
			{
				aux = aux->prox;
				auxStts = auxStts->prox;
			}
			pos++;
		}
		if(aux != NULL)
		    return pos;
	}
	return -1;
}


void Goto (Arq *arq, int numReg)
{
	if(arq != NULL && numReg > 0 && arq->stts != NULL)
	{
		Status *auxStts = arq->stts;
		int limit = 1;
		while(auxStts != NULL && (limit < numReg || setdel_onoff || !auxStts->status))
		{
			auxStts = auxStts->prox;
			limit++;
		}
		
		if(auxStts != NULL)
		{
			int i;
			Campos *auxCmp = arq->cmps;
			while(auxCmp != NULL)
			{
				i = 1;
				auxCmp->pAtual = auxCmp->p_dados;
				while(i < limit)
				{
					auxCmp->pAtual = auxCmp->pAtual->prox;
					i++;
				}
				auxCmp = auxCmp->prox;
			}
		}
	}
}

void display(Arq *arq)
{
	if(arq != NULL && arq->stts != NULL)
	{
		int i = 1;
		pDados *auxReg = arq->cmps->p_dados;
		Status *auxStts = arq->stts;
		while(auxReg != NULL && auxReg != arq->cmps->pAtual || (auxStts->status == 0 && setdel_onoff == 0))
		{
			if(setdel_onoff || auxStts->status == 1)
				i++;
			auxStts = auxStts->prox;
			auxReg = auxReg->prox;
		}
		
		if(auxStts != NULL)
		{
			exibeFields(arq);
			Campos *auxCmp = arq->cmps;
			printf("%d\t", i);
			while(auxCmp != NULL)
			{
			    showFieldType(auxCmp);
			    auxCmp = auxCmp->prox;
			}
		}
	}
}


void edit (Arq *arq)
{
	if(arq != NULL && arq->cmps != NULL)
	{
		char info[50];
		Campos *aux = arq->cmps;
		
		system("cls");
		while(aux != NULL)
		{
			printf("%s\n", aux->fieldName);
			aux = aux->prox;
		}
		aux = arq->cmps;
		
		int i = 1;
		while(aux != NULL)
		{
			gotoxy(17, i++); fflush(stdin); gets(info);
			
			switch (aux->type)
			{
				case 'N' :
				case 'n' : {
					aux->pAtual->valor.valorN = strtof(info, NULL);
					break;
				}
				case 'D' :
				case 'd' : {
					strcpy(aux->pAtual->valor.valorD, info);
					break;
				}
				case 'L' :
				case 'l' : {
					aux->pAtual->valor.valorL = atoi(info);/*info[0];*/
					break;
				}
				case 'C' :
				case 'c' : {
					strcpy(aux->pAtual->valor.valorC, info);
					break;
				}
				case 'M' :
				case 'm' : {
					strcpy(aux->pAtual->valor.valorM, info);
					break;
				}
			}
			aux = aux->prox;
		}
	}
}

void Delete(Arq *arquivo_aberto)
{
	if(arquivo_aberto != NULL && arquivo_aberto->stts != NULL)
	{
		Status *s = arquivo_aberto->stts;
		pDados *auxReg = arquivo_aberto->cmps->p_dados;
		
		while(s != NULL && auxReg != arquivo_aberto->cmps->pAtual)
		{
			auxReg = auxReg->prox;
			s = s->prox;
		}
		if (s != NULL){
			s->status = 0;
			//gotoxy(25, 21); printf("%d record deleted", i+1);
		} else {
			//gotoxy(25, 21); printf("does not exist");
		}	
	}
}

void recall(Arq *arquivo_aberto)
{
	if(arquivo_aberto != NULL && arquivo_aberto->stts != NULL)
	{
		Status *s = arquivo_aberto->stts;
		pDados *auxReg = arquivo_aberto->cmps->p_dados;
		
		while(s != NULL && auxReg != arquivo_aberto->cmps->pAtual)
		{
			auxReg = auxReg->prox;
			s = s->prox;
		}
		if (s != NULL)
		{
			s->status = 1;
			//gotoxy(25, 21); printf("%d record deleted", i+1);
		} else {
			//gotoxy(25, 21); printf("does not exist");
		}	
	}
}

void pack(Arq *arquivo_aberto)
{
	Campos *cmp = arquivo_aberto->cmps;
	
	//pDados
	pDados *antP;
	pDados *p; 
	pDados *del;
	
	//Status
	Status *s = arquivo_aberto->stts;
	Status *sttsDel;
	Status *sttsAnt;
	
	int vet[100]; //Converter para pilha ou lista linkada
	int pos = 0;
	int TL = 0;
	int i = 0;
	int j;
	
	while(s != NULL)
	{
		if(s->status == 0)
		{
			vet[TL] = i;
			TL++;
		}	
		i++;
		s = s->prox;
	}
	
	
	//Remover da coluna status
	s = arquivo_aberto->stts;
	for(i = 0, j = 0; s != NULL && j < TL; i++)
	{
		if(i == vet[j])
		{
			if(s == arquivo_aberto->stts)
			{
				sttsDel = s;
				arquivo_aberto->stts = arquivo_aberto->stts->prox;
				sttsAnt = arquivo_aberto->stts;
				s = sttsAnt;
			} 
			else
			{
				sttsAnt->prox = s->prox;
				sttsDel = s;
				s = s->prox;
			}
			free(sttsDel);
			j++;
		}
		else
		{
			sttsAnt = s;
			s = s->prox;
		}
	}
	//Remover dados.
	while(cmp != NULL)
	{
		p = cmp->p_dados;
		for(i = 0, j = 0; s != NULL && j < TL; i++)
		{
			if(i == vet[j])
			{
				
				if(p == arquivo_aberto->cmps->p_dados)
				{
					del = p;
					cmp->p_dados = cmp->p_dados->prox;
					cmp->pAtual = cmp->p_dados;
					antP = cmp->p_dados;
					p = antP;
				}
				else
				{
					antP->prox = p->prox;
					del = p;
					p = p->prox;
				}
				free(del);
				j++;
			}
			else
			{
				antP = p;
				p = p->prox;
			}
		}
		cmp = cmp->prox;
	}
}

void delReg(pDados *auxReg)
{
    if(auxReg->prox != NULL)
        delReg(auxReg->prox);
    free(auxReg);
}


void delField(Campos *cmp)
{
    if(cmp->prox != NULL)
        delField(cmp->prox);
    
    delReg(cmp->pAtual);
    free(cmp);
}

void delStatus(Status *stts)
{
	if(stts->prox != NULL)
		delStatus(stts->prox);
	
	free(stts);
}

void zap(Arq *arquivo_aberto)
{
    Campos *auxCmps = arquivo_aberto->cmps;
    Status *auxStts = arquivo_aberto->stts;
    delField(auxCmps);
    delStatus(auxStts);
    
    arquivo_aberto->cmps = NULL;
    arquivo_aberto->stts = NULL;
}

