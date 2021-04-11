#include <prova.h>
/*
	VICTOR TAVEIRA RODRIGUES RA: 261911759
*/
Campos *busca_campo(Arq *arq, char valor[])
{
	Campos *auxCmps = arq->cmps;
	while(auxCmps != NULL && stricmp(auxCmps->fieldName, valor))
		auxCmps = auxCmps->prox;
		
	return auxCmps;
}

int obterQtdeReg (Arq *arq)
{
	int qtde = 0;
	Status *auxStts = arq->stts;
	
	while(auxStts != NULL)
	{
		auxStts = auxStts->prox;
		qtde++;
	}
	return 0;
}

int eMaior(Campos *campo, pDados *regDado1, pDados *regDado2)
{
	int flag = 0;
	switch(toupper(campo->type))
	{
		case 'N' : {
			if(regDado2->valor.valorD < regDado1->valor.valorD)
				flag = 1;
			break;
		}
		case 'L' : {
			if(regDado2->valor.valorC < regDado1->valor.valorC)
				flag = 1;
			break;
		}
		
		case 'D' : {
			if(stricmp(regDado2->valor.valorD, regDado1->valor.valorD) == -1)
				flag = 1;
			break;
		}
			
		case 'C' : {
			if(stricmp(regDado2->valor.valorC, regDado1->valor.valorC) == -1)
				flag = 1;
			break;
		}
			
		case 'M' : {
			if(stricmp(regDado2->valor.valorM, regDado1->valor.valorM) == -1)
				flag = 1;
			break;
		}
	}
	return flag;
}

void sort(Arq *arq, char field[])
{
	Campos *field_encontrada = busca_campo(arq);
	Status *aux;
	//se(achou field E existe mais de um registro)
	if(field_encontrada != NULL && obterQtdeReg(arq) > 1)
	{
		//Posicionando ponteiros no primeiro registro
		pDados *reg_dado = field_encontrada->p_dados;
		Status *reg_stts = arq->stts;
		
		int i = 0;
		while(reg_dado->prox != NULL)
		{
			auxRegDado = reg_dado;
			if(eMaior(field_encontrada, auxRegDado, auxRegDado->prox)) 
			{
				aux = reg_stts;
				reg_stts->valor = reg_stts->prox->valor;
				
				
			}
		}
	}
}

int main()
{
	
	return 0;
}
