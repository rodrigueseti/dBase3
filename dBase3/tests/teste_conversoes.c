#include<stdio.h>
#include<stdlib.h>


int main()
{
	char array[50]; 
	gets(array);
	/*
	float f1 = strtof(array, NULL);
	printf("\n%f", f1);*/
	
	float num = strtof(array, NULL);
	printf("\n%f", num);
	return 0;
}
