
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


void zap(Arq *arquivo_aberto)
{
    Campos *auxCmps = arquivo_aberto->cmps;
    delField(auxCmps);
}
