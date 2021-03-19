#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int indexOf(char str[], char subs[])
{
	unsigned short int flag = 0;
	char auxStr[50];
	char auxSubs[50];
	
	strcpy(auxStr, str);
	strcpy(auxSubs, subs);
	
	int pos = -1;
	int i = 0;
	int x;
	int y;
	
	if (str[0] == '\0' || subs[0] == '\0' || strlen(subs) > strlen(str))
		return -1;
	
	while (str[i] != '\0' && !flag)
	{
		if(subs[0] == str[i])
		{
			flag = 1;
			x = i; 
			y = 0; 
			
			while (auxStr[x] != '\0' && auxSubs[y] != '\0' && flag)
			{
				flag = auxStr[x] != auxSubs[y] ? 0 : 1;
			
				x++; 
				y++; 
			}
		}
		pos++;
		i++;
	}
	if(auxSubs[y] == '\0' && flag == 1)
		return pos;
	return -1;
}

int main()
{
	char vet[] = "VICTOR TAVEIRA RODRIGUES";
	char in[50];
	int i;
	printf("%s\n", vet);
	
	gets(in);
	printf("Pos: %d\n", indexOf(vet, in));
	
	while(in[0] != '\0')
	{
		fflush(stdin);
		gets(in);
		printf("Pos: %d\n", indexOf(vet, in));
	}
	
	return 0;
}
