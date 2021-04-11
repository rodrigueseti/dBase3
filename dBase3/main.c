#include <stdio.h>
#include <stdlib.h> //strtof();
#include <string.h> //strcpy()
#include <time.h> //time(), localtime();
#include <conio2.h>

#include "display.h"
#include "tad_comandos.h"
#include "tad.h"
#include "operations.h"
#include "manipulations.h"

/*struct pointers {
	
	//unidade aberta
	//arquivo aberto
	//registro atual
};*/


int main()
{
	system("title dBase III - Estruturas de Dados II - Fipp - By: @rodrigueseti @rafael8paulo - github.com/rodrigueseti/dBase3");
	
	Dir *unid;
	Arq *arquivo_aberto = NULL;
	Entradas en;
	initDir(&unid); //Initializing
	
	buildUnit(&unid); //Build Unit C:
	buildUnit(&unid); //Build Unit D:
	buildUnit(&unid); //Build Unit E:
		
	int opc;
	//int posY = 5;
	char comando_field[50];
	char valor[50];
	valor[0] = '\0';
	
	
	molduraPrincipal();
	//sprintf(valor, "Diretorio atual: [%c:]xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxzzzzzzzzzzzzzz", unid->letter);
	sprintf(valor, "Diretorio atual: [%c:]", unid->letter);
	leftFooterMsg(valor); //printf("Diretorio atual: [%c:]\n", unid->letter);
	gotoxy(2, posY++); printf(". ");
	fflush(stdin);
	gets(comando_field);
	opc = Compara_String(comando_field, valor);
	
	while(opc != 3)
	{
		switch (opc)
		{
			//DIR
			case 2 : {
				listaArquivo(unid);
				break;
			}
			//EDIT
			case 4 : {
				edit(arquivo_aberto);
				break;
			}
			
			//PACK
			case 5 : {
				pack(arquivo_aberto);
				break;
			}
			
			//LIST
			case 7 : {
				list(arquivo_aberto);
				break;
			}
		
			//CLEAR
			case 8 : {
				system("cls");
				break;
			}
			//RECALL
			case 9 : {
				recall(arquivo_aberto);
				break;
			}
			//DELETE
			case 10 : {
				Delete(arquivo_aberto);
				break;
			}
			//APPEND
			case 11 : { //*******************T*******************estar
				append(arquivo_aberto);
				break;
			}
			
			//DISPLAY
			case 12 : {
				display(arquivo_aberto);
				break;
			}
			
			//DELETE ALL
			case 13 : {
				DeleteAll(arquivo_aberto->stts);
				printf("All deleted recordings\n");
				break;
			}
			
			//RECALL ALL
			case 14 : {
				RecallAll(arquivo_aberto->stts);
				printf("All records retrieved\n");
				break;
			}
			
			//LIST STRUCTURE
			case 16 : {
				listarFields(arquivo_aberto, unid);
				break;
			}
			
			//CREATE
			case 19 : {
				
				novoArquivo(unid, valor);
				rightFooterMsg("Incluir Fields ? (Y/N)");
				gotoxy(2, posY++); printf(". ");
				opc = toupper(getche());
				clearFooterMsg();
				
				if(opc == 'Y')
				{
					arquivo_aberto = abrirArquivo(unid, valor);
					insertFields(arquivo_aberto);
					
					molduraPrincipal();
					sprintf(valor, "Diretorio atual: [%c:]", unid->letter);
					leftFooterMsg(valor);
					
					rightFooterMsg("Input data records now? (Y/N)");
					posY = 5;
					gotoxy(2, posY++); printf(". ");
					opc = toupper(getche());
					clearFooterMsg();
					
					while(opc == 'Y')
					{
						//Chamada
						append(arquivo_aberto);
						rightFooterMsg("Continue including? (Y/N)");
						//gotoxy(2, posY++); printf(". ");
						opc = toupper(getch());
						clearFooterMsg();
						clearInserts();
					}
				}
				break;
			}
			
			//USE
			case 20 : {
				arquivo_aberto = abrirArquivo(unid, valor);
				
				//GOTO
				if(arquivo_aberto != NULL)
					printf("Aberto: [%s]\n", arquivo_aberto->nomeDBF);
				else
					printf("Not found\n");
					
				break;
			}
			
			//GOTO
			case 21 : {
				Goto(arquivo_aberto, atoi(valor));
				break;
			}
			
			//SET DEFAULT TO
			case 22 : {
				arquivo_aberto = NULL;
				trocaUnidade(&unid, toupper(valor[0]));
				sprintf(valor, "Diretorio atual: [%c:]", unid->letter);
				leftFooterMsg(valor);
				break;
			}
			
			//LIST FOR
			case 23 : {
				listFor(arquivo_aberto, comando_field, valor);
				break;
			}
			
			//LOCATE FOR 
			case 24 : {
				printf("\n%s", comando_field);
				printf("\n%s", valor);
				printf("Record = %d", locate_for(arquivo_aberto, comando_field, valor));
				break;
			}
			
			//SET DELETED
			case 25 : {
				set_delete(valor);
				break;
			}
			default :
				rightFooterPopUpMsg("Comando Invalido");
		}
		gotoxy(2, posY++); printf(". ");
		fflush(stdin);
		gets(comando_field);
		opc = Compara_String(comando_field, valor);
	}
	
	return 0;
}
