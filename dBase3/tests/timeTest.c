#include <stdio.h>
#include <time.h>

int main(void)
{
	char data[49];
    struct tm *p;
    time_t seconds;

    time(&seconds);
    p = localtime(&seconds);

    //printf("Dia do ano: %d\n", p->tm_yday);
    //printf("Data: %d/%d/%d\n", p->tm_mday, p->tm_mon + 1, p->tm_year + 1900);
    //printf("Hora: %d:%d:%d\n", p->tm_hour, p->tm_min, p->tm_sec);

    //sprintf(data, "0%d/0%d/%d", p->tm_mday, p->tm_mon + 1, p->tm_year + 1900);
	sprintf(data, "%d:%d:%d\0", p->tm_hour, p->tm_min, p->tm_sec);
	puts(data);
    return 0;
}
