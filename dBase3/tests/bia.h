

Campos *busca_campo(Arq *arq_aberto, char valor[])
{
	Campos *auxCmp = arq_aberto->cmps;
	while(auxCmp != NULL && stricmp(auxCmp->nome_campo, valor))
		auxCmps = auxCmps->prox;
		
	return auxCmps;
}

void sort (Arq *arq_aberto, char valor[])
{
	Campos *aux;
	Campos *campo_encontrado = busca_campo(arq_aberto, valor);
	p_dado *aux;
	int tl;
	
	
	if(campo_encontrado != NULL && campo_encontrado->p_dados != NULL)
	{
		p_dado = campo_encontrado->pDados;
		aux = arq_aberto->cmps;
		tl = getQtdeRegistro(campo_encontrado);
		
		while(aux)
		{
			
		}
	}
}
