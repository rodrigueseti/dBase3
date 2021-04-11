#include <stdio.h>
#include <conio.h>

int posMaior(char mat[3][50], int tl)
{
	int i;
	int pos_maior;
	char maior[50];
	
	strcpy(maior, mat[0]);
	pos_maior = 0;
	
	for(i = 1; i < tl; i++)
	{
		if(stricmp(maior, mat[i]) < 0)
		{
			strcpy(maior, mat[i]);
			pos_maior = i;
		}
	}
	return pos_maior;
}

void show(char mat[3][50], int tl)
{
	int i;
	for(i = 0; i < tl; i++)
		printf("%s\n", mat[i]);
}

int main()
{
	char mat[3][50];
	int tl;
	int pos_maior;
	char maior[50];
	
	for(tl = 0; tl < 3; tl++)
	{
		printf("%d: ", tl + 1);
		fflush(stdin);
		gets(mat[tl]);
	}
	show(mat, 3);
	printf("\n");
	while(tl > 0)
	{
		pos_maior = posMaior(mat, tl);
		
		if(pos_maior < tl - 1)
		{
			strcpy(maior, mat[pos_maior]);
			strcpy(mat[pos_maior], mat[tl - 1]);
			strcpy(mat[tl - 1], maior);
		}
		tl--;
	}
	show(mat, 3);
	
	return 0;	
}


