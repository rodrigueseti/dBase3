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
