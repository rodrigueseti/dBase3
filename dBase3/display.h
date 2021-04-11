#define MSG_TIME 1500

int posX = 3;
int posY = 5;

void show()
{
	system("cls");
	//CABECALHO
	{
		cputsxy(6, 1, "Field Name	Type	Width	Dec");
		
		gotoxy(6, 2); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,
		205,205,205,205,205,205,205,205,205,205);
	}
}

void leftFooterMsg(char string[])
{
	gotoxy(2, 24); printf("%s", string);
}

void rightFooterMsg(char string[])
{
	gotoxy(55, 24); printf("%s", string);
}

void clearFooterMsg()
{
	gotoxy(40, 24); printf("                                             ");
}

void titleMsg(char string[])
{
	int startPos = 43 - strlen(string) / 2;
	gotoxy(startPos, 3); printf("%s", string);
}

void rightFooterPopUpMsg (char string[])
{
	gotoxy(60, 24); printf("%s", string);
	Sleep(MSG_TIME);
	gotoxy(60, 24); printf("                   ");
	clearkeybuf();
}
void clearInserts()
{
	posY = 5;
	while(posY < 15)
	{
		gotoxy(17, posY++); printf("                                    ");	
	}
	
}
void rodape()
{
	int i;
	gotoxy(1, 23); printf("%c", 204);
	gotoxy(85, 23); printf("%c", 185);
	for(i = 2; i < 85; i++)
	{
		gotoxy(i, 23); printf("%c", 205);
	}
}

void molduraTitulo()
{
	int i;
	gotoxy(2, 2); printf("%c", 201); //canto esquerdo superior
	gotoxy(84, 2); printf("%c", 187); //canto direito superior
	gotoxy(2, 4); printf("%c", 200); //canto esquerdo inferior
	gotoxy(84, 4); printf("%c", 188); //canto direito inferior
	
	gotoxy(2, 3); printf("%c", 186); //canto direito inferior
	gotoxy(84, 3); printf("%c", 186); //canto direito inferior
	
	for(i = 3; i < 84; i++) //linhas horizontais
	{
		gotoxy(i, 2); printf("%c", 205);
		gotoxy(i, 4); printf("%c", 205);
	}
}

void molduraPrincipal()
{
	int i;
	int y;
	
	gotoxy(1, 1); printf("%c", 201); //canto esquerdo superior
	gotoxy(85, 1); printf("%c", 187); //canto direito superior
	gotoxy(1, 25); printf("%c", 200); //canto esquerdo inferior
	gotoxy(85, 25); printf("%c", 188); //canto direito inferior
	
	for(i = 2; i < 85; i++) //linhas horizontais
	{
		gotoxy(i, 1); printf("%c", 205);
		gotoxy(i, 25); printf("%c", 205);
	}
	
	for(i = 2; i < 25; i++) //linhas verticais
	{
		gotoxy(1, i); printf("%c", 186);
		gotoxy(85, i); printf("%c", 186);
	}
	
	molduraTitulo();
	rodape();
	titleMsg("dBase III PLUS.");
}

