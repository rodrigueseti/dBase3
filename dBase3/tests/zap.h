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
