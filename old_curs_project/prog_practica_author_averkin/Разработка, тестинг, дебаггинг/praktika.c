#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

#define ENTER 13
#define ESC 27
#define UP 72
#define INS 82
#define DEL 83
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define F1 59

#define N_of_pads 3
int N_of_types;

int menu(int);
void menu1();
void menu2();
void menu3();
int kurs(int,int,char[][25]);
int kurs1(int);
int kurs1s(int);
void select_list();
void select_voc();
int deleting(int,int);
int inserting(int);
int insert_voc(int);
void Edit(int);
void Edit_One(char*,int, int, int);
void open_bd();
void save_bd();
void save_spr();
void SetCursorOn();
void SetCursorOff();
void border(int,int,int,int);
void ErrorMsg(char*);
void About1();
void About2();
int select_type(int);

struct z {
	char model[15];
	char data[10];
	int Type;
	int Price;
	};

struct zz{
	char Name[16];
	 }*mtype;


char mpad[N_of_pads][16]={
	"    Файл       ",
	"    Правка     ",
	"    Помощь     "
};

int Sdvig=0, Sdvig_S=0,CurPos=0, CurPos_S=0, CurPad=0, IsOpenBd=0;

struct z *units,*MenuPad;

struct zz *MenuPad_S;

char BdFile[80]="Data.dat";

char str[]="нажмите любую клавишу...";
int NC;


main()
{
int n,next=1,i;

SetCursorOff();
open_bd();

while (next)
	{
	next=1;
	textattr(LIGHTGRAY);
	window(1,1,80,25);
	clrscr();

	n=menu(N_of_pads);
	switch(n){
		case 1: menu1(); break;
		case 2: menu2(); break;
		case 3: menu3(); break;
		}

	}

textattr(LIGHTGRAY);
window(1,1,80,25);
clrscr();

SetCursorOn();
}

int kurs(int n, int from, char dan[][25])
{
int i,y1=0,y2=n-1;
char c=3;


window(1,1,80,1);
textbackground(RED);
clrscr();
textcolor(BLACK);
cprintf("\n");
for(i=0; i<N_of_pads; i++)
		cprintf("%s",mpad[i]);

window(from+1,3,from+30,4+n);
textattr(16*BLACK);
clrscr();

window(from,2,from+29,3+n);
textattr(16*RED+BLACK);
clrscr();


gotoxy(1,2);
for(i=0; i<n; i++)
		cprintf("   %s\n\r",dan[i]);

border(2,1,29,n+2);


while (c!=ESC) {
		switch(c) {
			case DOWN: y2=y1; y1++; break;
			case UP: y2=y1; y1--; break;
			case ENTER: return y1+1;
			  }
		if(y1>n-1){y2=n-1;y1=0;}
		if(y1<0) {y2=0;y1=n-1;}

		textattr(16*RED+WHITE);
			gotoxy(4,y1+2);
			cprintf(dan[y1]);
		textattr(16*RED+BLACK);
			gotoxy(4,y2+2);
			cprintf(dan[y2]);

		c=getch();

		}
return 0;
}


int kurs1(int n)
{
int i,ii,y1,y2;
char c=3;
char s[80];
y1=CurPos;
MenuPad=units+Sdvig;
while (c!=ESC) {
		switch(c) {
			case DOWN: y2=y1; y1++; break;
			case UP: y2=y1; y1--; break;
			case DEL: n=deleting(n,y1+Sdvig);
				  CurPos=0; return -1;
			case INS: n=inserting(n);
				  y1=n-1;
			case ENTER: CurPos=y1; return y1+1+Sdvig;
		          }
		if(y1>n-1){
			   y1=n-1;y2=y1-1;
			   if(y1+1+Sdvig<NC)
				   {
				   MenuPad++;
				   Sdvig++;
				   }
			  }

		if(y1<0) {y2=1;y1=0;
			  if(y1+Sdvig>0)
				  {
				  MenuPad--;
				  Sdvig--;
				  }
			 }


		textattr(16*RED+BLACK);
		clrscr();

		for(i=0; i<(NC<16?NC:16); i++)
			{
			gotoxy(4,i+2);
			sprintf(s,"%-15s│%-15s│%-10s│%8d",
				mtype[MenuPad[i].Type].Name,
				MenuPad[i].model,
				MenuPad[i].data,
				MenuPad[i].Price);
			cprintf(s);
			}

		for(ii=i; ii<16; ii++)
			{
			gotoxy(4,ii+2);
			sprintf(s,"%-15s│%-15s│%-10s│%8s",
				"","","","");
			cprintf(s);
			}

		textattr(16*RED+WHITE);
			gotoxy(4,y1+2);
			sprintf(s,"%-15s│%-15s│%-10s│%8d",
				mtype[MenuPad[y1].Type].Name,
				MenuPad[y1].model,
				MenuPad[y1].data,
				MenuPad[y1].Price);
			cprintf(s);

		textattr(16*RED+BLACK);
		border(2,1,56,18);
		gotoxy(2,1);
		cprintf("╠");
		gotoxy(19,1);
		cprintf("╪");
		gotoxy(35,1);
		cprintf("╪");
		gotoxy(46,1);
		cprintf("╪");
		gotoxy(56,1);
		cprintf("╣");
		c=getch();
		}
return 0;
}



void select_list()
{
int n,i,next=1;

while (next)
	{
	next=1;
	textattr(16*BLACK+WHITE);
	window(1,1,80,25);
	clrscr();


	gotoxy(15,22);
	cprintf("Enter-Редактировать запись");
	gotoxy(15,23);
	cprintf("Delete-Удалить запись");
	gotoxy(15,24);
	cprintf("Insert-Добавить запись");
	gotoxy(15,25);
	cprintf("Esc- в главное меню");

	textattr(LIGHTCYAN);
	gotoxy(15,21);
	cprintf("Имя файла БД: %s",BdFile);

	window(4,2,60,21);
	textattr(16*BLACK);
	clrscr();

	window(3,1,59,20);
	textattr(16*RED+BLACK);
	clrscr();
	border(2,1,56,3);
	gotoxy(3,2);
	cprintf("%-16s│%-15s│%-10s│%-8s"," Производитель","   Модель","Дата","  Цена");
	window(3,3,59,20);
	textbackground(RED);
	clrscr();
	textcolor(LIGHTGRAY);
	cprintf("\n");

	n=kurs1((NC<16?NC:16));
	switch(n){
		case 0: next=0; break;
		case -1: break;
		default: Edit(n-1); break;
		}
	}


}

int deleting(int n,int y1)
{
int ii;

struct z* units1=(struct z*)malloc((--NC)*sizeof(struct z));
for(ii=0; ii<y1; ii++)
	{
	strcpy(units1[ii].model,units[ii].model);
	strcpy(units1[ii].data,units[ii].data);
	units1[ii].Price=units[ii].Price;
	units1[ii].Type=units[ii].Type;
	}

for(ii=y1; ii<NC; ii++)
	{
	strcpy(units1[ii].model,units[ii+1].model);
	strcpy(units1[ii].data,units[ii+1].data);
	units1[ii].Price=units[ii+1].Price;
	units1[ii].Type=units[ii+1].Type;
	}

free(units);
units=units1;
Sdvig=0;
MenuPad=units;

return --n;
}

int inserting(int n)
{
int ii;
struct z* units1=(struct z*)malloc((++NC)*sizeof(struct z));
for(ii=0;ii<NC-1;ii++)
	{
	strcpy(units1[ii].model,units[ii].model);
	strcpy(units1[ii].data,units[ii].data);
	units1[ii].Price=units[ii].Price;
	units1[ii].Type=units[ii].Type;
	}
strcpy(units1[NC-1].model,"?");
strcpy(units1[NC-1].data,"?");
units1[NC-1].Price=0;
units1[NC-1].Type=0;

free(units);
units=units1;

Sdvig=NC-16-1;
if(Sdvig<0) Sdvig=0;

MenuPad=units+Sdvig;
return ++n;

}


void Edit(int n)
{
struct z Old;
char xPrice[10];
int Price;

Old.Price=units[n].Price;
strcpy(Old.model,units[n].model);
strcpy(Old.data,units[n].data);
Old.Type=units[n].Type;

window(2,4,41,18);
textattr(16*BLACK);
clrscr();


window(1,3,40,17);
textattr(16*RED+BLACK);
clrscr();
border(2,1,39,15);

window(3,4,38,16);
textattr(16*RED+BLACK);
clrscr();


gotoxy(2,1);
cprintf("Производитель ");
gotoxy(2,4);
cprintf("Модель : %s",units[n].model);
gotoxy(2,7);
cprintf("Дата: %s",units[n].data);
gotoxy(2,10);
cprintf("Цена : %d",units[n].Price);

textattr(16*BLACK+LIGHTGREEN);
gotoxy(9,2);
cprintf("                ");
gotoxy(9,2);
cprintf(mtype[Old.Type].Name);


textattr(16*BLACK+LIGHTGREEN);
gotoxy(9,5);
cprintf("                ");
gotoxy(9,8);
cprintf("                ");
gotoxy(9,11);
cprintf("           ");
textattr(16*RED+BLACK);
gotoxy(15,13);
cprintf(" Ввод ");

window(11,5,31,5);
textattr(16*RED+WHITE);
units[n].Type=select_type(Old.Type);

Edit_One(units[n].model,8,11,15);
window(3,4,38,16);
textattr(16*RED+BLACK);
gotoxy(2,4);
clreol();
cprintf("Модель : %s",units[n].model);


Edit_One(units[n].data,11,11,10);
window(3,4,38,16);
textattr(16*RED+BLACK);
gotoxy(2,7);
clreol();
cprintf("дата: %s",units[n].data);



sprintf(xPrice,"%d",units[n].Price);
Edit_One(xPrice,14,11,10);
if(strlen(xPrice)>0)
	{
	sscanf(xPrice,"%d",&Price);
	units[n].Price=Price;
	}
window(3,4,38,16);
textattr(16*RED+BLACK);
gotoxy(2,10);
clreol();
cprintf("Цена : %-d",units[n].Price);

textattr(16*LIGHTGRAY+RED);
gotoxy(15,13);
cprintf("  Ok  ");
textattr(16*RED+RED);
clreol();

window(1,3,40,17);
textattr(16*RED+BLACK);
gotoxy(3,14);
cprintf("  ESC-отмена  ");

if(getch()==ESC)
	{
	units[n].Price=Old.Price;
	units[n].Type=Old.Type;
	strcpy(units[n].model,Old.model);
	strcpy(units[n].data,Old.data);
	}
}



void Edit_One(char *s,int Row, int Col, int Len)
{
char s1[22];
window(Col,Row,Col+Len,Row);
textattr(16*RED+WHITE);
strcpy(s1+2,s);
s1[0]=Len;
gotoxy(1,1);
clreol();
SetCursorOn();
cgets(s1);
SetCursorOff();
if(s1[1]>0)
	strcpy(s,s1+2);
}

void open_bd()
{
FILE *in;
int i;
char NChar;
in=fopen(BdFile,"rb");

if(!in)
        {
	ErrorMsg("       no file!");
        return;
        }


fread(&NChar,sizeof(char),1,in);
NC=NChar;

units=(struct z*)malloc(NC*sizeof(struct z));

for(i=0;i<NC;i++)
	fread(units[i].model,sizeof(struct z),1,in);

fclose(in);

in=fopen("Voc.dat","r");
if(!in)
        {
	ErrorMsg("       no file!");
        return;
        }

fscanf(in,"%d",&N_of_types);
mtype=(struct zz*)malloc(N_of_types*sizeof(struct zz));
for(i=0;i<N_of_types;i++)
	fscanf(in,"%s",mtype[i].Name);

IsOpenBd=1;
fclose(in);
}

void save_bd()
{
FILE *in;
int ii;
char NChar=NC;

in=fopen(BdFile,"wb");

fwrite(&NChar,sizeof(char),1,in);

for(ii=0;ii<NC;ii++)
	fwrite(units[ii].model,sizeof(struct z),1,in);

fclose(in);
}

void save_spr()
{
FILE *in;
int ii;

in=fopen("Voc.dat","w");
fprintf(in,"%d\n",N_of_types);
for(ii=0;ii<N_of_types;ii++)
	fprintf(in,"%s\n",mtype[ii].Name);
fclose(in);
}

int menu(int n)
{
int i,y1=CurPad,y2=n-1;
char c=3;

window(1,1,80,25);
textbackground(BLACK);
clrscr();
window(1,1,80,1);
textbackground(RED);
clrscr();
textcolor(BLACK);
cprintf("\n");
for(i=0; i<n; i++)
		cprintf("%s",mpad[i]);

while (c!=ESC) {
		switch(c) {
			case RIGHT: y2=y1; y1++; break;
			case LEFT: y2=y1; y1--; break;
			case ENTER: CurPad=y1; return y1+1;
		          }
		if(y1>n-1){y2=n-1;y1=0;}
		if(y1<0) {y2=0;y1=n-1;}


		textattr(16*RED+BLACK);
			gotoxy(y2*15+1,1);
			cprintf(mpad[y2]);

		textattr(16*RED+WHITE);
			gotoxy(y1*15+1,1);
			cprintf(mpad[y1]);

		textattr(16*WHITE+WHITE);

		c=getch();
		}

textattr(WHITE);
window(1,1,80,25);
clrscr();
SetCursorOn();
exit(0);

}

void menu1()
{
int n,next=1,i;

char dan[3][25]={
	"Сохранить базу данных   ",
	"Сохранить cправочник    ",
	"Выход из программы      "
};

while (next)
	{
	next=1;
	n=kurs(3,1,dan);
	switch(n){
		case 0: next=0;  break;
                case 1:
                        if(IsOpenBd)
                                   save_bd();
                        else
			   ErrorMsg(" база не открыта!");
                        break;
                case 2:
                         if(IsOpenBd)
                                   save_spr();
                        else
			   ErrorMsg(" база не открыта!");
                        break;
                case 3:
			textattr(LIGHTGRAY);
			window(1,1,80,25);
			SetCursorOn();
			clrscr();
			exit(0);

		}

	}


}


void menu2()
{
int n,next=1,i;

char dan[2][25]={
	"база данных ",
	"cправочник  "
};

while (next)
	{
	next=1;
	n=kurs(2,15,dan);
	switch(n){
		case 0: next=0;  break;
                case 1:
                        if(IsOpenBd)
                                 select_list();
                        else
			    ErrorMsg(" база не открыта!");
                         break;
                case 2:
                        if(IsOpenBd)
                                 select_voc();
                        else
			    ErrorMsg("     база не открыта!");
                         break;
		}

	}


}

void menu3()
{
int n,next=1,i;

char dan[2][25]={
	"О программе             ",
	"Автор                   "
};

while (next)
	{
	next=1;
	n=kurs(2,30,dan);
	switch(n){
		case 0: next=0;  break;
                case 1:
			About1(); break;
                case 2:
                        About2(); break;
		}

	}


}

int kurs1s(int n)
{
int i,y1,y2;
char c=3;
char s[80];
y1=CurPos_S;
MenuPad_S=mtype+Sdvig_S;
while (c!=ESC) {
		switch(c) {
			case DOWN: y2=y1; y1++; break;
			case UP: y2=y1; y1--; break;
			case INS: n=insert_voc(n);
				  y1=n-1;
			case ENTER: CurPos_S=y1; return y1+1+Sdvig_S;
		          }

		if(y1>n-1){
			   y1=n-1;y2=y1-1;
			   if(y1+1+Sdvig_S<N_of_types)
				   {
				   MenuPad_S++;
				   Sdvig_S++;
				   }
			  }

		if(y1<0) {y2=1;y1=0;
			  if(y1+Sdvig_S>0)
				  {
				  MenuPad_S--;
				  Sdvig_S--;
				  }
			 }


		textattr(16*RED+BLACK);
		clrscr();

		for(i=0; i<(N_of_types<16?N_of_types:16); i++)
			{
			gotoxy(4,i+2);
			cprintf(MenuPad_S[i].Name);
			}

		textattr(16*RED+WHITE);
			gotoxy(4,y1+2);
			cprintf(MenuPad_S[y1].Name);

		textattr(16*RED+BLACK);
		border(2,1,20,18);
		gotoxy(2,1);
		cprintf("╠");
		gotoxy(20,1);
		cprintf("╣");
		c=getch();
		}
return 0;
}



void select_voc()
{
int n,i,next=1;

while (next)
	{
	next=1;
	textattr(16*BLACK+WHITE);
	window(1,1,80,25);
	clrscr();

	gotoxy(15,22);
	cprintf("Enter-Редактировать ");
	gotoxy(15,23);
	cprintf("Введите значение:");
	gotoxy(15,24);
	cprintf("Insert-Добавить ");
	gotoxy(15,25);
	cprintf("Esc- в главное меню");

	window(21,2,41,21);
	textbackground(BLACK);
	clrscr();

	window(20,1,40,3);
	textattr(16*RED+BLACK);
	clrscr();
	border(2,1,20,3);

	gotoxy(3,2);
	cprintf("%s"," Производитель");

	window(20,3,40,20);
	textbackground(RED);
	clrscr();


	textcolor(BLACK);
	cprintf("\n");

	n=kurs1s((N_of_types<16?N_of_types:16));
	switch(n){
		case 0: next=0; break;
		case -1: break;
		default:
			window(1,1,80,25);
			Edit_One(mtype[n-1].Name,23,40,15);
			break;
		}
	}


}

int insert_voc(int n)
{

int ii;
struct zz* mtype1=(struct zz*)malloc((++N_of_types)*sizeof(struct zz));
for(ii=0;ii<N_of_types-1;ii++)
	{
	strcpy(mtype1[ii].Name,mtype[ii].Name);
	}
strcpy(mtype1[N_of_types-1].Name," ");

free(mtype);
mtype=mtype1;

Sdvig_S=N_of_types-16-1;
if(Sdvig_S<0) Sdvig_S=0;

MenuPad_S=mtype+Sdvig_S;
return ++n;


}



void SetCursorOff()
{
union REGS regs;
regs.h.ah=1;
regs.h.ch=-1;
regs.h.cl=-1;
int86(0x10,&regs,&regs);
}

void SetCursorOn()
{
union REGS regs;
regs.h.ah=1;
regs.h.ch=6;
regs.h.cl=7;
int86(0x10,&regs,&regs);
}

void border(int x1, int y1, int x2, int y2)
{
int i;

gotoxy(x1,y1);
putch('╔');

for(i=x1+1; i<x2; i++) putch('═');
putch('╗');

gotoxy(x1,y2);
putch('╚');

for(i=x1+1; i<x2; i++) putch('═');
putch('╝');

for(i=y1+1; i<y2; i++)
	{
	 gotoxy(x1,i);
	 putch('║');
	}
for(i=y1+1; i<y2; i++)
	{
	 gotoxy(x2,i);
	 putch('║');
	}

}




void ErrorMsg(char* s)
{
char buf[41*5*2];
window(20,20,60,24);
gettext(20,20,60,24,buf);
textattr(16*RED+BLACK);
clrscr();
border(2,1,40,5);
gotoxy(17,1);
textattr(16*BLACK+LIGHTGRAY);
cprintf(" Ошибка! ");
textattr(16*BLACK+GREEN);
gotoxy(3,3);
cprintf(s);
getch();
puttext(20,20,60,24,buf);
}

void About1()
{
char buf[42*6*2];

gettext(20,20,61,25,buf);

window(21,21,61,25);
textattr(16*BLACK);
clrscr();
window(20,20,60,24);

textattr(16*RED+BLACK);
clrscr();
border(2,1,40,5);
gotoxy(10,2);
cprintf("   программа написанна");
gotoxy(14,3);
cprintf("  для компании ");
gotoxy(10,4);
cprintf("     ЗАО \"СотСвязь\"");
getch();
puttext(20,20,61,25,buf);
}

void About2()
{
char buf[42*7*2];

gettext(20,19,61,25,buf);

window(21,20,61,25);
textattr(16*BLACK);
clrscr();

window(20,19,60,24);
textattr(16*RED+BLACK);
clrscr();
border(2,1,40,6);
gotoxy(14,2);
cprintf("    автор");
gotoxy(9,4);
cprintf("Севостьянов И.А. ИСТАС 1-2");

getch();
puttext(20,19,61,25,buf);
}


int select_type(int ii)
{
int c=1;
while(c!=ENTER && c!=ESC)
	{
	switch(c)
		{
		case UP: if(--ii<0) ii=0; break;
		case DOWN: if(++ii>=N_of_types) ii=N_of_types-1;
		}
	clrscr();
	cprintf(mtype[ii].Name);
	c=getch();
	}
return ii;
}
