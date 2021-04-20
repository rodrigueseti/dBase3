#include <conio2.h>

void main()
{
	struct text_info info;
	int i;
	//inittextinfo();
	gettextinfo(&info);
	system("title CONIO 2.1 TESTE");
	
	putchar(201); //canto esquerdo superior
	gotoxy(2, 1);
	for (i = 2; i < info.screenwidth; i++)
		putchar(205);
	putchar(187); //canto direito superior
	
	
	gotoxy(1, info.screenheight); putchar(200); //canto esquerdo superior
	for (i = 2; i < info.screenwidth; i++)
		putchar(205);
	putchar(188); //canto direito inferior
	
	for (i = 2; i < info.screenheight; i++) {
		gotoxy(1, i); putchar(186);
		gotoxy(info.screenwidth, i); putchar(186);
	}
	getch();
}
