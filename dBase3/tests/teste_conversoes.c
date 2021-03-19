#include<stdio.h>
#include<stdlib.h>


int main()
{
	char array[50];
	float valor = 123.456;
	/*
	gets(array);
	float f1 = strtof(array, NULL);
	printf("\n%f", f1);
	
	float num = strtof(array, NULL);
	printf("\n%f", num);
	*/
	sprintf(array, "%f", valor);
	printf("Str: %s", array);
	return 0;
}
