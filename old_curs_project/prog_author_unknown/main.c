/*ghj*/
/*AVTO.DAT Исходные данные
=========
15
Жигули гидро 96 2003-08-9
Альфа гидро 94 2003-01-23
Додж авто 120  2002-08-12
Субару авто 99 2008-05-19
Калдина мех 112 2016-09-15
Опель мех 112 1999-04-28
Прадо гидро 87 2006-07-15
Феррари мехавто 102 2005-03-11
Порш авто 256 2007-12-12
Мерседес мехавто 199 2006-08-15
Емобиль электро 213 2011-03-25
Лотус электроавто 156 2005-11-01
Москвич мех 85 1994-01-01
Волги мех 97 1998-12-18
Лексус авто 99 2007-07-16

MAIN.C
====== */
#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80

struct z
{
	char name[20];
	char vid[20];
	long summa;
	char data[11];
};

struct sp
{
	char fio[20];
	long summa;
	struct sp* sled;
} *spisok;

char dan[7][75] ={
	      "Какая марка имеет максимальную мощность двигателя?",
	      "Марка самого раннего выпуска ",
	      "Список автомобилей с электропередачей мощности свыше 100лс",
	      "Алфавитный список марок",
	      "Число марок с автомеханической трансмиссией",
	      "Диаграмма процентного соотношения мощностей по маркам",
	      "Выход"};

char str[]="Для окончания нажмите любую клaвишу";
int NC;

int main(void)
{
FILE *in;
struct z *clients;
int n,next=1,i;
system("chcp 1251");
if((in=fopen("avto.dat","r"))==NULL)
	{
	printf("\nФайл avto.dat не открыт!");
	getch(); exit(1);
	}
window(1,1,80,25);
textattr(YELLOW);
clrscr();
fscanf(in,"%d",&NC);
clients=(struct z*)malloc(NC*sizeof(struct z));
for(i=0;i<NC;i++)
	fscanf(in,"%s%s%ld%s",clients[i].name,
		clients[i].vid, &clients[i].summa,
		clients[i].data);
for(i=0;i<NC;i++)
	printf("\n%-20s %-20s %7ld %s",clients[i].name,

		clients[i].vid, clients[i].summa,
		clients[i].data);
press();
while (next)
	{
	textattr(YELLOW);
	window(1,1,80,25);
	clrscr();
	gotoxy(15,2);
	cprintf("Выберите вопрос и нажмите ENTER");
	window(10,7,80,15);
	textbackground(GREEN);
	clrscr();
	textcolor(BLACK);
	cprintf("\n");
	for(i=0; i<7; i++) cprintf("   %s\n\r",dan[i]);
	n=menu(7);
	switch(n){
		case 1: maxim(clients); break;
		case 2: first(clients);break;
		case 3: listing(clients);break;
		case 4: alfalist(clients);break;
		case 5: kolvo(clients); break;
		case 6: diagram(clients); break;
		case 7: next=0;
		}
	}
} /* main() */

 press()
{
window(1,1,80,25);
gotoxy(18,24);
textattr(YELLOW);
cputs(str);
getch();
}

int menu(int n)
{
int i,y=0;
char c;
while (c!='0')
	{
	gotoxy(4,2+y);
	textattr(16*GREEN+BLACK);
	cprintf(dan[y]);
	switch(c)
		{
		case DOWN :   y++; break;
		case UP   :   y--; break;
		case ENTER:   return y+1;
		}
	if(y>n-1)y=0;
	if(y<0)y=n-1;
	gotoxy(4,2+y);
	textattr(16*BLUE+WHITE);
	cprintf(dan[y]);
	c=getch();
	}
exit(0);
}



void text_data(char *s,char *sd)
{
char s0[3], month[12][9]={"января","февраля","марта","апреля","мая",
"июня","июля","августа","сентября","октября","ноября","декабря"};
strcpy(s,sd+8);
strcat(s," ");
strncpy(s0,sd+5,2);
strcat(s,month[atoi(s0)-1]);
strcat(s," ");
strncat(s,sd,4);
return;
}

 maxim(struct z* client)
{
int i=0;
struct z best;
strcpy(best.name,client[0].name);
best.summa=client[0].summa;
for(i=1;i<NC;i++)
	if (client[i].summa>best.summa)
		{
		strcpy(best.name,client[i].name);
		best.summa=client[i].summa;
		}
	window(23,17,58,22);
	textbackground(CYAN);
	clrscr();
	textcolor(MAGENTA);
	cprintf("\n\r       Максимальная мощность ");
	cprintf("\n\r         %ld  л.с.",best.summa);
	cprintf("\n\r       у марки");
	cprintf("\n\r       %s",best.name);
	press();
}

 first(struct z* client)
{
int i;
char s[17],sd[11];
struct z* best=client;
for(i=1;i<NC;i++)
	if (strcmp(client[i].data,best->data)<0) best=&client[i];
	text_data(s,best->data);
	window(23,17,58,22);
	textbackground(CYAN);
	clrscr();
	textcolor(MAGENTA);
	cprintf("\n\r Раньше всех начался выпуск машины ");
	cprintf("\n\r %s с мощностью %ld лс",best->vid,best->summa);
	cprintf("\n\r марки  %s",best->name);
	cprintf("\n\r Дата начала выпуска  %s ",s);
	press();
}



 kolvo(struct z *client)
{
int i,k=0;
for(i=0;i<NC;i++)
	if (strcmp(client[i].vid,"мехавто")==0) k++;
window(23,17,58,20);
textbackground(CYAN); clrscr();
textcolor(MAGENTA);
cprintf("\n\r  Марок с трансмиссией мехавто %d ",k);
/*cprintf("\n\r    Всего автомобилей: %d",k);*/
press();
}

 alfalist(struct z* client)
{
int i;
struct sp* nt;
char fio[20],mass[16][80];
int s[15];
spisok=0;
for(i=0;i<NC;i++)
	vstavka(client,client[i].name);
window(1,1,80,25);
textattr(LIGHTGRAY);
clrscr();
printf("\n    Алфавитный список марок от А до Я");
printf("\n    ===============================\n");
for(nt=spisok,i=0; nt!=0, i<15; nt=nt->sled, i++)
		{strcpy(mass[i],nt->fio);
		}
for (i=0;i<15; i++) {puts (mass[i] );}
getch ();
clrscr ();
printf("\n    Алфавитный список марок от Я до А");
printf("\n    ===============================\n");
for (i=14; i>=0; i--) {puts(mass[i]);}
getch();
press();
}

 vstavka(struct z* client,char* fio)
{
int i;
struct sp *nov,*nt,*z=0;
for(nt=spisok; nt!=0 && strcmp(nt->fio,fio)<0; z=nt, nt=nt->sled);
if(nt && strcmp(nt->fio,fio)==0) return;

nov=(struct sp *)malloc(sizeof(struct sp));
strcpy(nov->fio,fio);
nov->sled=nt;

nov->summa=0;
for(i=0;i<NC;i++)
	if(strcmp(client[i].name,fio)==0)
		nov->summa+=client[i].summa;

if(!z) spisok=nov;
else z->sled=nov;

return;
}


 listing(struct z* client)
{
int i;
struct z* nt;
window(1,1,80,25);
textattr(LIGHTGRAY);
clrscr();
cprintf("\n\r Список марок с электропередачей и мощностью свыше 100 лс");
cprintf("\n\r =====================================================\n\r");
for(i=0,nt=client;i<NC;nt++,i++)
   if (nt->summa>110 && strcmp(nt->vid,"электро")!=0)
     cprintf("\n\r  %-20s %ld лс.",nt->name,nt->summa);
press();
}

/* void vopr(struct z*albo)
{int i=0;s,k=0;
window(23,17,64,22);
textbackground(CYAN);
clrscr();
textcolor(BLACK);
scanf("%d",&s);
for(i=0;i<10;i++)
	if(albo[i].kol==s){k=1;break;}
	window(23,17,64,22);
	ik(k)
	cprintf("\nda \n");
	else
	cprintf("nnet \n");
getch();
} */

 diagram(struct z *client)
{
struct sp *nt;
int NSp,i=9,ii=1, gr1=0, gr2,k,xr,yr;
float t;
long x=0, l, j=0, sum=0;
char str2[20], str1[20];

for(k=0;k<NC;k++) sum = sum+client[k].summa ;
alfalist(client);
for(nt=spisok,NSp=0; nt!=0; nt=nt->sled) NSp++;

initgraph(&gr1,&gr2 ,"");
cleardevice(); setcolor(WHITE);
for(nt=spisok,k=0; nt!=0; nt=nt->sled,k++)
 {
  sprintf(str1,"%s",nt->fio);
  sprintf(str2,"%3.1f%%",(nt->summa*100./sum));
  settextstyle(0,0,1);
    if(i==16){i=9;ii++;}
  settextjustify(LEFT_TEXT,TOP_TEXT);
  setcolor(WHITE); outtextxy(470,k*15+20,str1);
  setfillstyle(ii,i);
  bar(440,k*15+18,460,k*15+28);
  x=x+nt->summa;
  l=360*x/sum;
  if(k==(NSp-1))   l=360;
  t=360.0*j/sum;
    setcolor(BLACK);
  pieslice(200,200,(int)t,(int)l,100);
  t=(t+l)/2*3.14/180;
  xr=200+125*cos(t);
  yr=200-125*sin(t);
  settextjustify(CENTER_TEXT,CENTER_TEXT);
  setcolor(WHITE); outtextxy(xr,yr,str2);
  j=x;  i++;
 }
getch();
closegraph();
return ;
}
