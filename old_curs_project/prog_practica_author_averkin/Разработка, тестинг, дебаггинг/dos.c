#include <stdio.h>
#include <conio.h>
#include <alloc.h>

/*Main Menu Position */
#define xScr 1
#define yScr 0
#define TextColor 112
#define Col LIGHTGRAY+BLACK*16
/*Sub Menu Position */
#define qxScr 1
#define qyScr 1
#define qTextColor BLACK+LIGHTGRAY*16
#define qCol LIGHTGRAY+BLACK*16
int CurSelected = 0;
int cur = 1;

char MainMenu[][20] = {"| File " ,
		 " Edit ",
		 " Data ",
		 " Help ",
		 };

char Menu1[][20] = { "| Save Data ",
			"| Save As.. ",
			"| Exit ",
			"| Languages "};

char Menu2[][20] = { "| Add Record F1",
			"| Dell Record ",
			"| Edit Record F2",
			"| Search ",
		 };
char Menu3[][20] = { "| Data Directory",
			"| Data in Doc ",
		 };


char Menu4[][20] = { "| Autors ",
			"| About "
		 };

main()
{
 BlackScreen();
 DrawMenuWindow(); /*Рисуем окно муляж для меню */
 ShowMainMenu(1); /* Вызываем функцию объединяющую в себе все функции по работе с меню */
 getch();
}

 DrawMenuWindow()
 {
 int i;
 window(1,1,80,1);
 textattr(112);
 clrscr();
 for(i=0;i<4;i++)
{
 gotoxy(1,0);
 cprintf("%s",MainMenu[i]); 
}

}
 Mainmenu(int n,int z,char dan[][20])
 {
	int y=1;
	int zdvig=0;
	char c;
	if(z>1)
	{
	 while(z!=y)
	 {
	 zdvig+=strlen(dan[y-1]); y++;
	 }
	}
	textattr(Col);
	gotoxy(xScr+zdvig,yScr+1);
	cprintf("%s",dan[y-1]);
	do{
	c=getch();
	textattr(TextColor);
	gotoxy(xScr+zdvig,1+yScr);
	cprintf("%s",dan[y-1]);
	switch(c){
	 case 'M' : zdvig+=strlen(dan[y-1]); y++; break;
	 case 'K' : y--; zdvig-=strlen(dan[y-1]); break;
	 case 'P' : CurSelected = zdvig; return y;
	 }
	 if(y<1){ y=n; zdvig=19; }
	 if(y>n){ y=1; zdvig=0; }
	 textattr(Col);
	 gotoxy(xScr+zdvig,1+yScr);
	 cprintf("%s",dan[y-1]);
	 }while(c!=27);
	 return c;
 }

int DrawSubMenu(int y,int n,char dan[][20],char subDan[][20],int xScreen, int yScreen, int wScreen, int zScreen)
	 {
	 int i,t;


 textattr(Col);
	 gotoxy(xScr+CurSelected,yScr+1);
	 cprintf("%s",dan[y-1]);


 
	 /* Draw shadow under menu item */
	 window(xScreen+1,yScreen+1,wScreen+1,zScreen+1);
	 textattr(0);
	 clrscr();

	 window(xScreen,yScreen,wScreen,zScreen);
	 textattr(qTextColor);
	 clrscr();
	 DrawBorders(17,6);
	for(i=0;i<n;i++)
 {
	gotoxy(qxScr,i+qyScr+1);
 cprintf("%s",subDan[i]); }
	t = menu(n,subDan);
	 return t;
	 }
	 
 menu(int n,char subDan[][20])
 {
	 int y=1;
	 char c;
	 textattr(qCol);
	 gotoxy(qxScr,y+qyScr);
	 cprintf("%s",subDan[y-1]);
	 do{
	 c=getch();
	 textattr(qTextColor);
	 gotoxy(qxScr,y+qyScr);
	 cprintf("%s",subDan[y-1]);
	 switch(c){
	 case 'P' : y++; break;
	 case 'H' : y--; break;
	 case '\r' : return y;
	 }
	 if(y<1) y=n;
	 if(y>n) y=1;
	 textattr(qCol);
	 gotoxy(qxScr,y+qyScr);
	 cprintf("%s",subDan[y-1]);
	 }while(c!=27);
	 return c;
 }

 
/*Функция контроля работы меню, в качестве параметра принимает номер элемента горизонтального меню, который должен быть автоматически выделен при создании меню. */
int ShowMainMenu(int curRd)
{
 int t;
 int k,i;
 int tr=1;
 char p[20];
 char res;
 char bf[18]="";

 DrawMenuWindow();
 
 while(tr)
 {
 t = Mainmenu(4,cur,MainMenu); /*Вызываем функцию работы горизонтального меню */
 switch(t){ /*То что она возвращает фильтруем через switch … case */
 case 1: /*Если пользователь выбрал первый элемент меню, то… */
 k=DrawSubMenu(1,4,MainMenu,Menu1,3,2,19,7); /*Рисуем выпадающее меню, результат выбора возвращается в переменную k */
 BlackScreen(); /*Как только отработали делаем очистку экрана и удаляем выпадающее меню с экрана */
	 DrawMenuWindow(); /*Обновляем муляж */
 break;
 case 2:
 k=DrawSubMenu(2,2,MainMenu,Menu2,21,2,37,7);
 BlackScreen();
 DrawMenuWindow();
 break; /*Если пользователь выбрал 2 или 3 элемент, то ничего не делаем. */
 case 3:
 k=DrawSubMenu(3,2,MainMenu,Menu3,21,2,37,7);
 BlackScreen();
 DrawMenuWindow();
 break;
 case 4: /*Если пользователь выбрал 4 пункт меню то… */
 k=DrawSubMenu(4,2,MainMenu,Menu4,21,2,37,7); /* Рисуем выпадающее меню*/
 if(k==1) /*Смотрим если пользователь выбрал первый пункт выпадающего меню, то рисуем окно авторов. */
 {
 window(21,6,58,19);
 textattr(0);
 clrscr();
 window(20,5,57,18);
 textattr(63);
 clrscr();
 DrawBorders(38,14);
 gotoxy(11,2);
 cprintf("<< MGSU ISTAS >>");
 gotoxy(2,4);
 cprintf("Developers: Harin Sergey");
 gotoxy(12,5);
 cprintf(": Korotkov Petr");
 gotoxy(12,6);
 cprintf(": Gamburger Alex");
 gotoxy(8,8);
 textattr(57);
 cprintf("LordSprint Software 2007");
 gotoxy(14,10);

 getch();
 }

 if(k==2)
 {
 /*Если пользователь выбрал второй пункт меню то ничего не делаем. */
 }
 BlackScreen();
	 DrawMenuWindow();
 CurSelected=0;
	 
 
 break;
 case 27: /*Если пользователь нажал ESC, то делаем следующее… */
	 tr=0; /*Выходим из бесконечного цикла */
 BlackScreen(); /*Очищаем экран */
	 DrawMenuWindow(); /*Рисуем муляж меню.*/
 break;
}
 
}
}

DrawBorders(int ByX, int ByY)
{
 int i;
 putchar(218);
 for(i=2;i<ByX;i++)
 {gotoxy(i,1); putchar(196); }
 putchar(191);
 for(i=2;i<ByY;i++)
 {gotoxy(ByX,i); putchar(179); }
 gotoxy(1,ByY);
 putchar(192);
 for(i=2;i<ByX;i++)
 {gotoxy(i,ByY); putchar(196);}
 putchar(217);
 for(i=2;i<ByY;i++)
 {gotoxy(1,i); putchar(179); }
 gotoxy(1,1);
}

BlackScreen()
{
 window(1,1,80,25);
 textattr(16*1+1);
 clrscr();
}
