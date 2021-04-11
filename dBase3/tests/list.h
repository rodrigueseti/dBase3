void list (Arq *arq) { //Ok
	
	if(arq != NULL && arq->stts != NULL &&  (setdel_onoff || getRegSize(arq->stts)))  //Ok
	{
		int i = 1;
		Status *posStts = arq->stts;
		Campos *auxCmps = arq->cmps;
		unsigned char flag; //Inutil
		
		
		printf("Record#			");
		while (auxCmps != NULL)
		{
			printf("%s			", auxCmps->fieldName); 
			auxCmps = auxCmps->prox;
		}
		printf("\n");
		auxCmps = arq->cmps;
		
		while(posStts != NULL) //ou posStts != NULL
		{
			flag = 1; //Inutil
			while(auxCmps != NULL)
			{
				if(setdel_onoff || posStts->status)
				{
					if(flag) //Inutil
					{
						printf("%d			", i++);
						flag = 0;
					}
					
					switch(auxCmps->type)
					{
						case 'N' : {
							printf("%.2f			", auxCmps->pAtual->valor.valorN);
							break;
						}
						
						case 'L' : {
							printf("%c			", auxCmps->pAtual->valor.valorL);
							break;
						}
						
						case 'D' : {
							printf("%s			", auxCmps->pAtual->valor.valorD);
							break;
						}
						case 'C' : {
							printf("%s			", auxCmps->pAtual->valor.valorC);
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

		posStts = arq->stts;
		while(auxCmps != NULL)
		{
			auxCmps->pAtual = auxCmps->p_dados;
			auxCmps = auxCmps->prox;
		}
		auxCmps = arq->cmps;
	}
}
