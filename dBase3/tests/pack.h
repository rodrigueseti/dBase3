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
/*
i = 2
pos = 2
*/
void remove_status(Status **status,  int pos){
    int i=0;
    if(pos == 0)
	{
        *status = (*status)->prox;
        //free(aux);
    }else{
        Status *aux = *status, *ant;
        
        while(i < pos){
            ant = aux;
            aux = aux->prox;
            i++;
        }
        ant->prox =  aux->prox;
        free(aux);
    }
}

void remove_pDados(Campos **Campos, int pos){
    int i=0;
    if(pos == 0){
        (*Campos)->p_dados = (*Campos)->p_dados->prox;
    }else{
        pDados *aux = (*Campos)->p_dados, *ant;
        
        while(i < pos){
            ant = aux;
            aux = aux->prox;
            i++;
        }
        ant->prox = aux->prox;
        free(aux);
    }
}

void pack(Arq **arquivo_aberto){

    pDados *p = (*arquivo_aberto)->cmps->p_dados, *antP;
    Campos *c = (*arquivo_aberto)->cmps;
    Status *s = (*arquivo_aberto)->stts;
    
    int pos = 0, vet[100], TL = 0, i=0;
    
    /*
    
    */
    
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
    
    int x = 0;
    
    /*
    pos = 2
    vet[0][2][][][]
    TL = 2
    i = 1
	x = 0
	*/
    //Remover da coluna status
    s = (*arquivo_aberto)->stts;
    
    for(i = 0; i < TL; i++)
	{
        pos = vet[i];
        remove_status(&s, pos);
    }
    
    while(s != NULL){
        s = s->prox;
        x++;
    }
    printf("\n TL: %d | x = %d", TL, x);
    getch();
    
    //Remover pDados
    while(c != NULL){
        for(i = 0; i<TL;i++){
            pos = vet[i];
            printf("pos = %d      ", pos);
            remove_pDados(&c, pos);
        }
        c = c->prox;
    }
    gotoxy(25, 21); printf("\n* Elementos Excluidos * \n");
    getch();
}
