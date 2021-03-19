Campos *Busca_Campos(Campos *Inicio, char valor[]){
	
	while(Inicio != NULL && stricmp(Inicio->fieldName, valor)!=0)
		Inicio = Inicio->prox;
		
	return Inicio;
}
void Busca_ValorC(pDados *Inicio, char valor[], Status *s){
	
	int i=0;
	
	while(Inicio != NULL){
		if(stricmp(Inicio->valor.valorC, valor)==0 && s->status == 1){
			printf("\nRecord = %d", i+1);
		}
		Inicio =  Inicio->prox;
		s = s->prox;
		i++;
	}
	if(i == 0)
		printf("\nElemento nao encontrado!");
}
void Busca_ValorN(pDados *Inicio, char v[], Status *s){
	int i=0, valor = atof(v);
	
	while(Inicio != NULL){
		if(Inicio->valor.valorN == valor && s->status == 1){
			printf("\nRecord = %d", i+1);
		}
		Inicio =  Inicio->prox;
		s = s->prox;
		i++;
	}
	if(i == 0)
		printf("\nElemento nao encontrado!");
}
void Busca_ValorD(pDados *Inicio, char valor[], Status *s){
	int i=0;
	
	while(Inicio != NULL){
		if(stricmp(Inicio->valor.valorD, valor)==0 && s->status){
			printf("\nRecord = %d", i+1);
		}
		Inicio =  Inicio->prox;
		s = s->prox;
		i++;
	}
	if(i == 0)
		printf("\nElemento nao encontrado!");
}
void Busca_ValorL(pDados *Inicio, char valor[], Status *s){
	int i=0;
	
	while(Inicio != NULL){
		if(Inicio->valor.valorL == valor[0] && s->status){
			printf("\nRecord = %d", i+1);
		}
		Inicio =  Inicio->prox;
		s = s->prox;
		i++;
	}
	if(i == 0)
		printf("\nElemento nao encontrado!");
}
void Busca_ValorM(pDados *Inicio, char valor[], Status *s){
	int i=0;
	
	while(Inicio != NULL){
		if(stricmp(Inicio->valor.valorM, valor)==0 && s->status){
			printf("\nRecord = %d", i+1);
		}
		Inicio =  Inicio->prox;
		s = s->prox;
		i++;
	}
	if(i == 0)
		printf("\nElemento nao encontrado!");
}
void locate(Arq *arquivo_aberto, char comando_field[], char valor[]){
	
	Campos *c = arquivo_aberto->cmps;
	Campos *aux = Busca_Campos(c, comando_field);
	int pos;
	if(aux != NULL){
		
		switch(c->type){
			case 'N':
				Busca_ValorN(aux->p_dados, valor, arquivo_aberto->stts);
				break;
			case 'D':
				Busca_ValorD(aux->p_dados, valor, arquivo_aberto->stts);
				break;
			case 'L':
				Busca_ValorL(aux->p_dados, valor, arquivo_aberto->stts);
				break;
			case 'C':
				Busca_ValorC(aux->p_dados, valor, arquivo_aberto->stts);
				break;
			case 'M':
				Busca_ValorM(aux->p_dados, valor, arquivo_aberto->stts);
				break;
		}
	}	
}
Status *DeleteALL(Status *s){
	if(s != NULL){
		DeleteALL(s->prox);
		s->status = 0;
	}
	return s;
}
Status *ReacallAll(Status *s){
	if(s != NULL){
		ReacallAll(s->prox);
		if(s->status == 0)
			s->status = 1;
	}
	return s;
}




	//LOCATE FOR
	case 24 : {
		locate(arquivo_aberto, comando_field, valor);
		break;
	}
			
			
	//RECALL ALL
	case 14: 
		//arquivo_aberto->stts =  ReacallAll(arquivo_aberto->stts);
		break;
	//LIST STRUCTURE
	case 16 : {
		listarFields(arquivo_aberto, unid);
		break;
	}
