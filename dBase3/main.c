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
	system("title dBase III - Estruturas de Dados II - Fipp - By @github.com/taveira @rafa");
	
	Dir *unid;
	Arq *arquivo_aberto = NULL;
	Entradas en;
	initDir(&unid); //Initializing
	
	buildUnit(&unid); //Build Unit C:
	buildUnit(&unid); //Build Unit D:
	buildUnit(&unid); //Build Unit E:
		
	int opc;
	char comando_field[50];
	char valor[50];
	valor[0] = '\0';
	
	//show();
	
	printf("Diretorio atual: [%c:]\n", unid->letter);
	printf(". ");
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
			//APPEND
			case 11 : { //*******************T*******************estar
				append(arquivo_aberto);
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
				printf("Incluir Fields ? (Y/N): ");
				opc = toupper(getche());
				
				if(opc == 'Y')
				{
					arquivo_aberto = abrirArquivo(unid, valor);
					insertFields(arquivo_aberto);
					
					printf("Input data records now? (Y/N)");
					opc = toupper(getch());
					while(opc == 'Y')
					{
						//Chamada
						append(arquivo_aberto);
						printf("Continue including? (Y/N)");
						opc = toupper(getch());
					}
				}
				printf("\n");
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
			
			//SET DEFAULT TO
			case 22 : {
				arquivo_aberto = NULL;
				trocaUnidade(&unid, toupper(valor[0]));
				printf("Diretorio atual: [%c:]\n", unid->letter);
				break;
			}
			
			//LIST FOR
			case 23 : {
				//FUNCOES
				/*printf("\n%s", comando_field);
				printf("\n%s", valor);
				getch()	;*/
				break;
			}
			default :
				printf("Comando Invalido\n");
		}
		
		printf(". ");
		fflush(stdin);
		gets(comando_field);
		opc = Compara_String(comando_field, valor);
	}
	
	return 0;
}
