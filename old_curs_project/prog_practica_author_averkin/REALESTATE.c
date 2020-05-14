#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>

#define ENTER 13
#define ESC 27
#define DEL 83
#define BACKSPACE 8
#define INS 82
#define END 79

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define F6 64
#define F7 65
#define F8 66
#define F10 68

int BUFFER=0;
int SELECTOUTPOINT[2]={0,0};
int SKIPMENU=0;
int WHATFILEISOPEN=0;
int FILEWASSAVE=1;
int CHANGEMESSAGE=1;
int STROKAVIDELENA[2]={1,1};
int NOMERVIDELENNOGO[2]={0,0};
int CHANGEDIAP=1;
unsigned KOLYCHELEMENTOW[2]={0,0};
int diap1=0,diap2=12;
int diap3=0,diap4=14;

char MainMenu[][20] = {"File" ,
		 "Edit",
		 "Data",
		 "Help",
		 };

char Menu1[][20] = {"Save     F2",
                     "Save As  F3",
			         "Exit       ",};

char Menu2[][20] = { "Add     F4",
			          "Delete  F5",
			          "Edit    F6"};
char Menu3[][20] = { "Datafile  F7",
                     "Helpfile  F8",};


char Menu4[][20] = { "Autors    ",
			          "About   F1",};

char BdFile[20]="BDD.DAT";
char SpravFile[20]="BDS#.DAT";
char Lastmessage[78];

struct sprav{
	int id;
	char poselok[20];
	char clas[20];
	int price;
	}*sp;

struct order{
	int id;
	int spravid;
	float skidka;
	char otdelka[15];
	int plosh;
    char status[15];
    unsigned cena;
	}*or;

void *Lwindowbuf;
void *Mwindowbuf;

FILE *inter;

main()
{
 int point;
 char c;
 do{
 printf("ALT+ENTER for fulscreen mode, press ESC\n");
 c=getch();
 }while(c!=27);
 Lwindowbuf=(void*)malloc(78*18*2);
 Mwindowbuf=(void*)malloc(63*17*2);
 readflags();
 READBD();
 READSPR();
 nullcena();
 CONTROLPRINT();
 SetCursorOff();
 while(1){
 editramka();
 dhw();
 dmw();
 CHANGEDIAP=1;
 if(!SKIPMENU) mainmenu();
 point=SELECTOUTPOINT[0]*10+SELECTOUTPOINT[1];
 switch(point){
 case 11: savecurrentdata(); break;
 case 12: saveas(); break;
 case 13: exitfunction();
 case 21: adddata(); break;
 case 22: deletedata(); break;
 case 23: editdata(); break;
 case 31: opendatafile(); break;
 case 32: openhelpfile(); break;
 case 41: authors(); break;
 case 42: about(); break;
 }
 }
}

saveflags(){
  FILE *in;
    in=fopen("flags.ini","w");
    if(WHATFILEISOPEN==0)
    fprintf(in,"0 0\n");
    else if(WHATFILEISOPEN==1)
    fprintf(in,"3 1\n");
    else if(WHATFILEISOPEN==2)
    fprintf(in,"3 2\n");
    if(WHATFILEISOPEN)
    fprintf(in,"1\n");
    else
    fprintf(in,"0\n");
    fprintf(in,"%d\n",WHATFILEISOPEN);
    fprintf(in,"%d\n",1);
    fprintf(in,"%d\n",CHANGEMESSAGE);
    fprintf(in,"%d %d\n",STROKAVIDELENA[0],STROKAVIDELENA[1]);
    fprintf(in,"%d %d\n",NOMERVIDELENNOGO[0],NOMERVIDELENNOGO[1]);
    fprintf(in,"%d %d\n",diap1,diap2);
    fprintf(in,"%d %d\n",diap3,diap4);
    fclose(in);
}

readflags()
{
FILE *inone;
int i;
  clrscr();
  if((inone=fopen("flags.ini","r"))==NULL) return;
    fscanf(inone,"%d%d",&SELECTOUTPOINT[0],&SELECTOUTPOINT[1]);
    fscanf(inone,"%d",&SKIPMENU);
    fscanf(inone,"%d",&WHATFILEISOPEN);
    fscanf(inone,"%d",&FILEWASSAVE);
    fscanf(inone,"%d",&CHANGEMESSAGE);
    fscanf(inone,"%d%d",&STROKAVIDELENA[0],&STROKAVIDELENA[1]);
    fscanf(inone,"%d%d",&NOMERVIDELENNOGO[0],&NOMERVIDELENNOGO[1]);
    fscanf(inone,"%d%d",&diap1,&diap2);
    fscanf(inone,"%d%d",&diap3,&diap4);
  fclose(inone);
}

doyouwannasave()
{
 int d;
 window(21,10,56,15);
 textattr(0);
 clrscr();
 window(20,9,55,14);
 textattr(16*4+14);
 clrscr();
 ramka(36,6);
 window(21,10,54,13);
 gotoxy(3,1); cprintf("Do you want save current file?");
 d=yesno(12);
 if(d==1) savecurrentdata();
}

yesno(int Y)
{
char c;
char podmenu[][20] = {"YES",
			          "NO",};
int y=1,j=8,i;
window(21,Y,59,Y);
textattr(16*4+14);
for(i=0;i<2;i++)
{
gotoxy(j,1);
cprintf("%s",podmenu[i]);
j+=10;
}
j=8;
textattr(16*0+9);
gotoxy(j,1);
cprintf("%s",podmenu[y-1]);
do{
	c=getch();
	textattr(16*4+14);
	gotoxy(j,1);
	cprintf("%s",podmenu[y-1]);
	switch(c){
	 case RIGHT: y++; j+=10; break;
	 case LEFT: y--; j-=10; break;
	 case ENTER: return y;
     case END: exit(0);
	 }
	 if(y<1){ y=2; j=18; }
	 if(y>2){ y=1; j=8; }
	 textattr(16*0+9);
     gotoxy(j,1);
	 cprintf("%s",podmenu[y-1]);
	 }while(1);
}

opendatafile()
{
int i;
char c;
for(i=0;i<KOLYCHELEMENTOW[0];i++)
or[i].cena=(or[i].plosh/10)*(sp[or[i].spravid-1].price/100);
if(FILEWASSAVE&&CHANGEMESSAGE) sprintf(Lastmessage,"Enable DATA edit mode.");
CHANGEMESSAGE=1;
dmw();
editramka();
WHATFILEISOPEN=1;
drawdatatable();
justprintdata();
selectdatelem(NOMERVIDELENNOGO[0]);
	 do{
     gettext(2,3,79,20,Lwindowbuf);
     BUFFER=1;
	 c=getch();
     unselectdatelem(NOMERVIDELENNOGO[0]);
	 switch(c){


     case UP:
     if(NOMERVIDELENNOGO[0]>0) NOMERVIDELENNOGO[0]--;
     if(diap3>NOMERVIDELENNOGO[0]){ diap3--; diap4--; justprintdata(); STROKAVIDELENA[0]=1;}
     else if(STROKAVIDELENA[0]>1)
     STROKAVIDELENA[0]--;
     break;
	 case DOWN:
     if(NOMERVIDELENNOGO[0]<KOLYCHELEMENTOW[0]-1) NOMERVIDELENNOGO[0]++;
     if(diap4-1<NOMERVIDELENNOGO[0]){ diap3++; diap4++; justprintdata(); if(STROKAVIDELENA[0]>diap4) STROKAVIDELENA[0]=diap4; else STROKAVIDELENA[0]=14;}
     else if(STROKAVIDELENA[0]<14&&STROKAVIDELENA[0]<diap4)
     STROKAVIDELENA[0]++;
     break;

	 case ENTER: SELECTOUTPOINT[1]=3; SELECTOUTPOINT[0]=2; SKIPMENU=1; return;
     case F1: SELECTOUTPOINT[1]=2; SELECTOUTPOINT[0]=4; SKIPMENU=1; return;
     case F2: SELECTOUTPOINT[1]=1; SELECTOUTPOINT[0]=1; SKIPMENU=1; return;
     case F3: SELECTOUTPOINT[1]=2; SELECTOUTPOINT[0]=1; SKIPMENU=1; return;
     case F4: SELECTOUTPOINT[1]=1; SELECTOUTPOINT[0]=2; SKIPMENU=1; return;
     case F5: SELECTOUTPOINT[1]=2; SELECTOUTPOINT[0]=2; SKIPMENU=1; return;
     case DEL: SELECTOUTPOINT[1]=2; SELECTOUTPOINT[0]=2; SKIPMENU=1; return;
     case F6: SELECTOUTPOINT[1]=3; SELECTOUTPOINT[0]=2; SKIPMENU=1; return;
     case F8: SELECTOUTPOINT[1]=2; SELECTOUTPOINT[0]=3; SKIPMENU=1; return;
     case F10: SELECTOUTPOINT[1]=0; SELECTOUTPOINT[0]=0; SKIPMENU=0; return;
     case ESC: SELECTOUTPOINT[1]=0; SELECTOUTPOINT[0]=0; SKIPMENU=0; WHATFILEISOPEN=0; return;
     case END: exitfunction();
	 }
     selectdatelem(NOMERVIDELENNOGO[0]);
	 }while(1);

}

selectdatelem(int number){
int proz=0, trueidnumber;
for(trueidnumber=0;trueidnumber<KOLYCHELEMENTOW[1];trueidnumber++)
if(or[number].spravid==sp[trueidnumber].id) break;
proz=or[number].skidka*100;
textattr(16*1+11);
gotoxy(2,STROKAVIDELENA[0]+3);
cprintf("%4.d",number+1);
gotoxy(7,STROKAVIDELENA[0]+3);
cprintf("%-10s",sp[trueidnumber].poselok);
gotoxy(18,STROKAVIDELENA[0]+3);
cprintf("%-8s",sp[trueidnumber].clas);
gotoxy(27,STROKAVIDELENA[0]+3);
cprintf("%2.d%% ",proz);
gotoxy(35,STROKAVIDELENA[0]+3);
cprintf("%-4s",or[number].otdelka);
gotoxy(44,STROKAVIDELENA[0]+3);
cprintf("%4.dM^2",or[number].plosh);
gotoxy(53,STROKAVIDELENA[0]+3);
cprintf("%-5s",or[number].status);
gotoxy(61,STROKAVIDELENA[0]+3);
cprintf("%5.u000$",or[number].cena);
}

unselectdatelem(int number){
int proz=0, trueidnumber;
for(trueidnumber=0;trueidnumber<KOLYCHELEMENTOW[1];trueidnumber++)
if(or[number].spravid==sp[trueidnumber].id) break;
proz=or[number].skidka*100;
textattr(16*1+7);
gotoxy(2,STROKAVIDELENA[0]+3);
cprintf("%4.d",number+1);
gotoxy(7,STROKAVIDELENA[0]+3);
cprintf("%-10s",sp[trueidnumber].poselok);
gotoxy(18,STROKAVIDELENA[0]+3);
cprintf("%-8s",sp[trueidnumber].clas);
gotoxy(27,STROKAVIDELENA[0]+3);
cprintf("%2.d%% ",proz);
gotoxy(35,STROKAVIDELENA[0]+3);
cprintf("%-4s",or[number].otdelka);
gotoxy(44,STROKAVIDELENA[0]+3);
cprintf("%4.dM^2",or[number].plosh);
gotoxy(53,STROKAVIDELENA[0]+3);
cprintf("%-5s",or[number].status);
gotoxy(61,STROKAVIDELENA[0]+3);
cprintf("%5.u000$",or[number].cena);
}

justprintdata(){
int i, y=0, proz=0, trueidnumber;
for(i=diap3;i<diap4;i++)
{
for(trueidnumber=0;trueidnumber<KOLYCHELEMENTOW[1];trueidnumber++)
if(or[i].spravid==sp[trueidnumber].id) break;
proz=or[i].skidka*100;
gotoxy(2,y+4);
cprintf("%4.d",i+1);
gotoxy(7,y+4);
cprintf("%-10s",sp[trueidnumber].poselok);
gotoxy(18,y+4);
cprintf("%-8s",sp[trueidnumber].clas);
gotoxy(27,y+4);
cprintf("%2.d%% ",proz);
gotoxy(35,y+4);
cprintf("%-4s",or[i].otdelka);
gotoxy(44,y+4);
cprintf("%4.dM^2",or[i].plosh);
gotoxy(53,y+4);
cprintf("%-5s",or[i].status);
gotoxy(61,y+4);
cprintf("%5.u000$",or[i].cena);
y++;
}

}

drawdatatable(){
window(5,3,76,20);
textattr(16*1+7);
clrscr();
ramka(71,18); ramka(6,18); ramka(17,18); ramka(26,18); ramka(34,18);
ramka(43,18); ramka(52,18); ramka(60,18); ramka(71,3);
gotoxy(1,3); putchar(195); gotoxy(71,3); putchar(180);
gotoxy(6,1); putchar(194); gotoxy(17,1); putchar(194);
gotoxy(26,1); putchar(194); gotoxy(34,1); putchar(194);
gotoxy(43,1); putchar(194); gotoxy(52,1); putchar(194);
gotoxy(60,1); putchar(194); gotoxy(6,3); putchar(197);
gotoxy(17,3); putchar(197); gotoxy(26,3); putchar(197);
gotoxy(34,3); putchar(197); gotoxy(43,3); putchar(197);
gotoxy(52,3); putchar(197); gotoxy(60,3); putchar(197);
gotoxy(6,18); putchar(193); gotoxy(17,18); putchar(193);
gotoxy(26,18); putchar(193); gotoxy(34,18); putchar(193);
gotoxy(43,18); putchar(193); gotoxy(52,18); putchar(193);
gotoxy(60,18); putchar(193);
videlupdat(2,2);
}

videlupdat(int x, int y)
{
textattr(16*1+3);
gotoxy(x,y); cprintf("Num");
gotoxy(x+5,y); cprintf("Poselok");
gotoxy(x+16,y); cprintf("Class");
gotoxy(x+25,y); cprintf("Skidka");
gotoxy(x+33,y); cprintf("Otdelka");
gotoxy(x+42,y); cprintf("Ploshad");
gotoxy(x+51,y); cprintf("Status");
gotoxy(x+59,y); cprintf("Cena $");
textattr(16*1+7);
}

adddata()
{
struct sprav buf;
struct order buf2;
int d=1, goodid=1, i, trueidnumber, proz=0;
char c;
char pmenu[][20] = {"YES",
			          "NO",};
char pmenu2[][20] = {"SELL",
			          "SOLD",};
int y=0;

if(WHATFILEISOPEN==0)
{
window(1,1,80,25);
  textattr(7);
  clrscr();
  printf("Impossible, you must open file before changing.\nYou return in menu after 3 sec.");
  sleep(3);
  SELECTOUTPOINT[1]=0;
  SELECTOUTPOINT[0]=0;
  SKIPMENU=0;
}
else if(WHATFILEISOPEN==2)
{
 window(21,10,61,17);
 textattr(0);
 clrscr();
 window(20,9,60,16);
 textattr(16*4+14);
 clrscr();
 ramka(41,8);
 window(21,10,59,15);
 gotoxy(4,1); cprintf("You add now num%d in spravochnik.",KOLYCHELEMENTOW[1]+1);
 textattr(16*4+0);
 gotoxy(7,2); cprintf("Poselok");
 gotoxy(21,2); cprintf("Class");
 gotoxy(33,2); cprintf("Cena");
 textattr(16*4+15);
 gotoxy(1,4); cprintf("Add:");
 while(1){
textattr(16*4+15);
window(27,13,58,15);
clrscr();
SetCursorOn();
window(27,13,39,13);
clrscr();
gotoxy(1,1);
scanf("%s",buf.poselok);

window(41,13,51,13);
clrscr();
gotoxy(1,1);
scanf("%s",buf.clas);

window(53,13,58,13);
clrscr();
gotoxy(1,1);
scanf("%d",&buf.price);
SetCursorOff();
d=vproceed(15);
if(d==2) break;
else if(d==3){
SELECTOUTPOINT[1]=2;
SELECTOUTPOINT[0]=3;
SKIPMENU=1;
return;}
}
for(i=0;i<KOLYCHELEMENTOW[1];i++)
if(goodid==sp[i].id) {goodid++; i=0;}
sp=addspritem(sp, goodid, buf.poselok, buf.clas, buf.price);
if(diap2<12){
diap2++;
STROKAVIDELENA[1]=diap2;
NOMERVIDELENNOGO[1]=KOLYCHELEMENTOW[1]-1;
}
else{
diap1=KOLYCHELEMENTOW[1]-12;
diap2=KOLYCHELEMENTOW[1];
STROKAVIDELENA[1]=12;
NOMERVIDELENNOGO[1]=KOLYCHELEMENTOW[1]-1;
}
FILEWASSAVE=0;
SELECTOUTPOINT[1]=2;
SELECTOUTPOINT[0]=3;
SKIPMENU=1;
sprintf(Lastmessage,"Element number %d in SPRVOCHNIK was added, but not saved.",KOLYCHELEMENTOW[1]);
}
else if(WHATFILEISOPEN==1)
{
window(10,5,71,12);
 textattr(0);
 clrscr();
 window(9,4,70,11);
 textattr(16*4+14);
 clrscr();
 ramka(62,8);
 window(10,5,69,10);
 gotoxy(16,1); cprintf("You add now num%d in DATA.",KOLYCHELEMENTOW[0]+1);
 textattr(16*4+0);
 gotoxy(7,2); cprintf("Poselok");
 gotoxy(18,2); cprintf("Class");
 gotoxy(27,2); cprintf("Skidka");
 gotoxy(35,2); cprintf("Otdelka");
 gotoxy(44,2); cprintf("Ploshad");
 gotoxy(53,2); cprintf("Status");
 textattr(16*4+15);
 gotoxy(1,4); cprintf("Make:");
while(1){
textattr(16*4+15);
window(15,8,69,10);
clrscr();
y=0;
gettext(9,4,71,20,Mwindowbuf);
window(16,9,36,20);
textattr(0);
clrscr();
window(15,8,35,19);
textattr(16*5+0);
clrscr();
ramka(21,12);
buf2.spravid=getid();
puttext(9,4,71,20,Mwindowbuf);

for(trueidnumber=0;trueidnumber<KOLYCHELEMENTOW[1];trueidnumber++)
if(buf2.spravid==sp[trueidnumber].id) break;
window(16,8,39,8);
textattr(16*4+15);
clrscr();
gotoxy(1,1);
cprintf("%-10s",sp[trueidnumber].poselok);
gotoxy(12,1);
cprintf("%-8s",sp[trueidnumber].clas);

SetCursorOn();
window(36,8,41,8);
clrscr();
gotoxy(1,1);
scanf("%d",&proz);
window(36,8,41,8);
buf2.skidka=(float)proz/100+0.0001;
proz=buf2.skidka*100;
gotoxy(1,1);
cprintf("%2.d%%",proz);
SetCursorOff();

textattr(16*4+0);
window(25,10,69,10);
clrscr();
gotoxy(1,1);
cprintf("Use UP/DOWN keys to change value.");
textattr(16*4+15);

window(44,8,49,8);
do{
gotoxy(1,1);
cprintf("%-4s",pmenu[y]);
c=getch();
switch(c){
case ENTER: break;
case END: exitfunction();
case DOWN: if(y==1) y=0; else y=1; break;
case UP: if(y==1) y=0; else y=1; break;
}
}while(c!=ENTER);
strcpy(buf2.otdelka,pmenu[y]);
y=0;

window(25,10,69,10);
clrscr();

SetCursorOn();
window(53,8,60,8);
clrscr();
gotoxy(1,1);
scanf("%d",&buf2.plosh);
gotoxy(1,1);
cprintf("%4.dM^2",buf2.plosh);
SetCursorOff();

textattr(16*4+0);
window(25,10,69,10);
clrscr();
gotoxy(1,1);
cprintf("Use UP/DOWN keys to change value.");
textattr(16*4+15);

window(62,8,67,8);
do{
gotoxy(1,1);
cprintf("%-4s",pmenu2[y]);
c=getch();
switch(c){
case ENTER: break;
case END: exitfunction();
case DOWN: if(y==1) y=0; else y=1; break;
case UP: if(y==1) y=0; else y=1; break;
}
}while(c!=ENTER);
strcpy(buf2.status,pmenu2[y]);

window(25,10,69,10);
clrscr();

d=vproceed(10);
if(d==2) break;
else if(d==3){
SELECTOUTPOINT[1]=1;
SELECTOUTPOINT[0]=3;
SKIPMENU=1;
return;}
}
for(i=0;i<KOLYCHELEMENTOW[0];i++)
if(goodid==or[i].id){goodid++; i=0;}
if(diap4<14){
diap4++;
STROKAVIDELENA[0]=diap4;
NOMERVIDELENNOGO[0]=KOLYCHELEMENTOW[0];
}
else{
diap3=KOLYCHELEMENTOW[0]-14;
diap4=KOLYCHELEMENTOW[0];
STROKAVIDELENA[0]=14;
NOMERVIDELENNOGO[0]=KOLYCHELEMENTOW[0];
}
or=adddatitem(or, goodid, buf2.spravid, proz, buf2.otdelka, buf2.plosh, buf2.status);
FILEWASSAVE=0;
SELECTOUTPOINT[1]=1;
SELECTOUTPOINT[0]=3;
SKIPMENU=1;
sprintf(Lastmessage,"Element number %d in DATA was added, but not saved.",KOLYCHELEMENTOW[0]);
}
}

adddatitem(struct order *MyData ,int id, int spravid, int proz, char *otdelka, int plosh, char *status){
 struct order *Data;
 int i;
 float skidka=0;
 Data=(struct order *)malloc(sizeof(struct order)*(KOLYCHELEMENTOW[0]+1));
 for(i=0;i<KOLYCHELEMENTOW[0];i++)
 {
Data[i].id=MyData[i].id;
Data[i].spravid=MyData[i].spravid;
Data[i].skidka=MyData[i].skidka;
strcpy(Data[i].otdelka,MyData[i].otdelka);
Data[i].plosh=MyData[i].plosh;
strcpy(Data[i].status,MyData[i].status);
 }
skidka=(float)proz/100+0.0001;
 Data[i].id=id;
 Data[i].spravid=spravid;
Data[i].skidka=skidka;
strcpy(Data[i].otdelka,otdelka);
Data[i].plosh=plosh;
strcpy(Data[i].status,status);
 KOLYCHELEMENTOW[0]++;
return Data;
}

addspritem(struct sprav *MyData ,int id, char *posel, char *clas, int cena){
 struct sprav *Data;
 int i;
 Data=(struct sprav *)malloc(sizeof(struct sprav)*(KOLYCHELEMENTOW[1]+1));
 for(i=0;i<KOLYCHELEMENTOW[1];i++)
 {
Data[i].id=MyData[i].id;
strcpy(Data[i].poselok,MyData[i].poselok);
strcpy(Data[i].clas,MyData[i].clas);
Data[i].price=MyData[i].price;
 }
 Data[i].id=id;
 strcpy(Data[i].poselok,posel);
 strcpy(Data[i].clas,clas);
 Data[i].price=cena;
 KOLYCHELEMENTOW[1]++;
return Data;
}

deletedata()
{
int i, b, delid, d;
if(KOLYCHELEMENTOW[0]==1||KOLYCHELEMENTOW[1]==1&&WHATFILEISOPEN)
{
if(WHATFILEISOPEN==2) {SELECTOUTPOINT[1]=2; SELECTOUTPOINT[0]=3; SKIPMENU=1;}
if(WHATFILEISOPEN==1) {SELECTOUTPOINT[1]=1; SELECTOUTPOINT[0]=3; SKIPMENU=1;}
return;
}
if(WHATFILEISOPEN==0)
{
window(1,1,80,25);
  textattr(7);
  clrscr();
  printf("Impossible, you must open file before changing.\nYou return in menu after 3 sec.");
  sleep(3);
  SELECTOUTPOINT[1]=0;
  SELECTOUTPOINT[0]=0;
  SKIPMENU=0;
  return;
}
else if(WHATFILEISOPEN==2){
b=NOMERVIDELENNOGO[1]+1;
delid=sp[NOMERVIDELENNOGO[1]].id;
window(10,8,69,12);
 textattr(0);
 clrscr();
 window(9,7,68,11);
 textattr(16*4+14);
 clrscr();
 ramka(60,5);
 window(10,8,67,10);
 gotoxy(3,1); cprintf("Warning, all connected data will also delete! Proceed?");
 d=yesno(10);
 if(d==2) {SELECTOUTPOINT[1]=2; SELECTOUTPOINT[0]=3; SKIPMENU=1; return;}
for(i=0;i<KOLYCHELEMENTOW[0];i++)
if(delid==or[i].spravid)
{
WHATFILEISOPEN=1;
NOMERVIDELENNOGO[0]=i;
CHANGEDIAP=0;
deletedata();
CHANGEDIAP=1;
WHATFILEISOPEN=2;
NOMERVIDELENNOGO[0]=0;
STROKAVIDELENA[0]=1;
diap3=0;
if(diap4>14) diap4=14;
if(KOLYCHELEMENTOW[0]<14) diap4=KOLYCHELEMENTOW[0];
i--;
}
for(i=NOMERVIDELENNOGO[1];i<KOLYCHELEMENTOW[1]-1;i++)
{
sp[i].id=sp[i+1].id;
strcpy(sp[i].poselok,sp[i+1].poselok);
strcpy(sp[i].clas,sp[i+1].clas);
sp[i].price=sp[i+1].price;
}
if(diap2==KOLYCHELEMENTOW[1]){NOMERVIDELENNOGO[1]--; if(diap1>0) diap1--; diap2--; }
if(NOMERVIDELENNOGO[1]==KOLYCHELEMENTOW[1]-1){ NOMERVIDELENNOGO[1]--; if(diap1>0) diap1--; diap2--;}
if(diap2<KOLYCHELEMENTOW[1]&&STROKAVIDELENA[1]==diap2+1) STROKAVIDELENA[1]--;
if(diap2<12&&STROKAVIDELENA[1]<diap2+1) NOMERVIDELENNOGO[1]++;
if(diap2<12&&STROKAVIDELENA[1]==KOLYCHELEMENTOW[1]) STROKAVIDELENA[1]--;
if(diap2<12&&NOMERVIDELENNOGO[1]!=STROKAVIDELENA[1]-1) NOMERVIDELENNOGO[1]--;
KOLYCHELEMENTOW[1]--;
FILEWASSAVE=0;
SELECTOUTPOINT[1]=2;
SELECTOUTPOINT[0]=3;
SKIPMENU=1;
sprintf(Lastmessage,"Element number %d in SPRVOCHNIK was deleted, SPRAVOCHNIK not saved.",b);
}
else if(WHATFILEISOPEN==1)
{
b=NOMERVIDELENNOGO[0]+1;
for(i=NOMERVIDELENNOGO[0];i<KOLYCHELEMENTOW[0]-1;i++)
{
or[i].id=or[i+1].id;
or[i].spravid=or[i+1].spravid;
or[i].skidka=or[i+1].skidka;
strcpy(or[i].otdelka,or[i+1].otdelka);
or[i].plosh=or[i+1].plosh;
strcpy(or[i].status,or[i+1].status);
}
if(CHANGEDIAP){
if(diap4==KOLYCHELEMENTOW[0]){NOMERVIDELENNOGO[0]--; if(diap3>0) diap3--; diap4--; }
if(NOMERVIDELENNOGO[0]==KOLYCHELEMENTOW[0]-1){ NOMERVIDELENNOGO[0]--; if(diap3>0) diap3--; diap4--;}
if(diap4<KOLYCHELEMENTOW[0]&&STROKAVIDELENA[0]==diap4+1) STROKAVIDELENA[0]--;
if(diap4<14&&STROKAVIDELENA[0]<diap4+1) NOMERVIDELENNOGO[0]++;
if(diap4<14&&STROKAVIDELENA[0]==KOLYCHELEMENTOW[0]) STROKAVIDELENA[0]--;
if(diap4<14&&NOMERVIDELENNOGO[0]!=STROKAVIDELENA[0]-1) NOMERVIDELENNOGO[0]--;
}
KOLYCHELEMENTOW[0]--;
FILEWASSAVE=0;
SELECTOUTPOINT[1]=1;
SELECTOUTPOINT[0]=3;
SKIPMENU=1;
sprintf(Lastmessage,"Element number %d in DATA was deleted, DATA not saved.",b);
}
}

editdata()
{
struct sprav buf;
struct order buf2;
int d=1,proz=0,trueidnumber;
char c;
char pmenu[][20] = {"YES",
			          "NO",};
char pmenu2[][20] = {"SELL",
			          "SOLD",};
int y=0;
if(WHATFILEISOPEN==0)
{
window(1,1,80,25);
  textattr(7);
  clrscr();
  printf("Impossible, you must open file before changing.\nYou return in menu after 3 sec.");
  sleep(3);
  SELECTOUTPOINT[1]=0;
  SELECTOUTPOINT[0]=0;
  SKIPMENU=0;
}
else if(WHATFILEISOPEN==2)
{
 window(21,10,61,17);
 textattr(0);
 clrscr();
 window(20,9,60,16);
 textattr(16*4+14);
 clrscr();
 ramka(41,8);
 window(21,10,59,15);
 gotoxy(4,1); cprintf("You edit now num%d in spravochnik.",NOMERVIDELENNOGO[1]+1);
 textattr(16*4+0);
 gotoxy(7,2); cprintf("Poselok");
 gotoxy(21,2); cprintf("Class");
 gotoxy(33,2); cprintf("Cena");
 textattr(16*4+9);
 gotoxy(1,3); cprintf("Was:");
 gotoxy(7,3); cprintf("%s",sp[NOMERVIDELENNOGO[1]].poselok);
 gotoxy(21,3); cprintf("%s",sp[NOMERVIDELENNOGO[1]].clas);
 gotoxy(33,3); cprintf("%d",sp[NOMERVIDELENNOGO[1]].price);
 textattr(16*4+15);
 gotoxy(1,4); cprintf("Make:");
while(1){
textattr(16*4+15);
window(27,13,58,15);
clrscr();
SetCursorOn();
window(27,13,39,13);
clrscr();
gotoxy(1,1);
scanf("%s",buf.poselok);

window(41,13,51,13);
clrscr();
gotoxy(1,1);
scanf("%s",buf.clas);

window(53,13,58,13);
clrscr();
gotoxy(1,1);
scanf("%d",&buf.price);
SetCursorOff();
d=vproceed(15);
if(d==2) break;
else if(d==3){
SELECTOUTPOINT[1]=2;
SELECTOUTPOINT[0]=3;
SKIPMENU=1;
return;}
}
strcpy(sp[NOMERVIDELENNOGO[1]].poselok,buf.poselok);
strcpy(sp[NOMERVIDELENNOGO[1]].clas,buf.clas);
sp[NOMERVIDELENNOGO[1]].price=buf.price;
FILEWASSAVE=0;
SELECTOUTPOINT[1]=2;
SELECTOUTPOINT[0]=3;
SKIPMENU=1;
sprintf(Lastmessage,"Element number %d in SPRVOCHNIK was changed, but not saved.",NOMERVIDELENNOGO[1]+1);
}
else if(WHATFILEISOPEN==1)
{
window(10,5,71,12);
 textattr(0);
 clrscr();
 window(9,4,70,11);
 textattr(16*4+14);
 clrscr();
 ramka(62,8);
 window(10,5,69,10);
 gotoxy(16,1); cprintf("You edit now num%d in DATA.",NOMERVIDELENNOGO[0]+1);
 textattr(16*4+0);
 gotoxy(7,2); cprintf("Poselok");
 gotoxy(18,2); cprintf("Class");
 gotoxy(27,2); cprintf("Skidka");
 gotoxy(35,2); cprintf("Otdelka");
 gotoxy(44,2); cprintf("Ploshad");
 gotoxy(53,2); cprintf("Status");
 proz=or[NOMERVIDELENNOGO[0]].skidka*100;
 for(trueidnumber=0;trueidnumber<KOLYCHELEMENTOW[1];trueidnumber++)
 if(or[NOMERVIDELENNOGO[0]].spravid==sp[trueidnumber].id) break;
 textattr(16*4+9);
 gotoxy(1,3); cprintf("Was:");
 gotoxy(7,3); cprintf("%-10s",sp[trueidnumber].poselok);
 gotoxy(18,3); cprintf("%-8s",sp[trueidnumber].clas);
 gotoxy(27,3); cprintf("%2.d%% ",proz);
 gotoxy(35,3); cprintf("%-4s",or[NOMERVIDELENNOGO[0]].otdelka);
 gotoxy(44,3); cprintf("%4.dM^2",or[NOMERVIDELENNOGO[0]].plosh);
 gotoxy(53,3); cprintf("%-5s",or[NOMERVIDELENNOGO[0]].status);
 textattr(16*4+15);
 gotoxy(1,4); cprintf("Make:");
while(1){
textattr(16*4+15);
window(15,8,69,10);
clrscr();
y=0;
gettext(9,4,71,20,Mwindowbuf);
window(16,9,36,20);
textattr(0);
clrscr();
window(15,8,35,19);
textattr(16*5+0);
clrscr();
ramka(21,12);
buf2.spravid=getid();
puttext(9,4,71,20,Mwindowbuf);

for(trueidnumber=0;trueidnumber<KOLYCHELEMENTOW[1];trueidnumber++)
if(buf2.spravid==sp[trueidnumber].id) break;
window(16,8,39,8);
textattr(16*4+15);
clrscr();
gotoxy(1,1);
cprintf("%-10s",sp[trueidnumber].poselok);
gotoxy(12,1);
cprintf("%-8s",sp[trueidnumber].clas);

SetCursorOn();
window(36,8,41,8);
clrscr();
gotoxy(1,1);
scanf("%d",&proz);
window(36,8,41,8);
buf2.skidka=(float)proz/100+0.0001;
proz=buf2.skidka*100;
gotoxy(1,1);
cprintf("%2.d%%",proz);
SetCursorOff();

textattr(16*4+0);
window(25,10,69,10);
clrscr();
gotoxy(1,1);
cprintf("Use UP/DOWN keys to change value.");
textattr(16*4+15);

window(44,8,49,8);
do{
gotoxy(1,1);
cprintf("%-4s",pmenu[y]);
c=getch();
switch(c){
case ENTER: break;
case END: exitfunction();
case DOWN: if(y==1) y=0; else y=1; break;
case UP: if(y==1) y=0; else y=1; break;
}
}while(c!=ENTER);
strcpy(buf2.otdelka,pmenu[y]);
y=0;

window(25,10,69,10);
clrscr();

SetCursorOn();
window(53,8,60,8);
clrscr();
gotoxy(1,1);
scanf("%d",&buf2.plosh);
gotoxy(1,1);
cprintf("%4.dM^2",buf2.plosh);
SetCursorOff();

textattr(16*4+0);
window(25,10,69,10);
clrscr();
gotoxy(1,1);
cprintf("Use UP/DOWN keys to change value.");
textattr(16*4+15);

window(62,8,67,8);
do{
gotoxy(1,1);
cprintf("%-4s",pmenu2[y]);
c=getch();
switch(c){
case ENTER: break;
case END: exitfunction();
case DOWN: if(y==1) y=0; else y=1; break;
case UP: if(y==1) y=0; else y=1; break;
}
}while(c!=ENTER);
strcpy(buf2.status,pmenu2[y]);

window(25,10,69,10);
clrscr();

d=vproceed(10);
if(d==2) break;
else if(d==3){
SELECTOUTPOINT[1]=1;
SELECTOUTPOINT[0]=3;
SKIPMENU=1;
return;}
}
or[NOMERVIDELENNOGO[0]].spravid=buf2.spravid;
or[NOMERVIDELENNOGO[0]].skidka=buf2.skidka;
strcpy(or[NOMERVIDELENNOGO[0]].otdelka,buf2.otdelka);
or[NOMERVIDELENNOGO[0]].plosh=buf2.plosh;
strcpy(or[NOMERVIDELENNOGO[0]].status,buf2.status);
sprintf(Lastmessage,"Element number %d in DATA was changed, but not saved.",NOMERVIDELENNOGO[0]+1);
FILEWASSAVE=0;
SELECTOUTPOINT[1]=1;
SELECTOUTPOINT[0]=3;
SKIPMENU=1;
}
}

getid()
{
char c;
int y=0, bdiap=0, ediap=10, stringnum=1;
justprintvip(bdiap, ediap);
selectvipelem(y,stringnum);
	 do{
	 c=getch();
     unselectvipelem(y,stringnum);
	 switch(c){
	 case UP:
     if(y>0) y--;
     if(bdiap>y){ bdiap--; ediap--; justprintvip(bdiap, ediap); stringnum=1;}
     else if(stringnum>1)
     stringnum--;
     break;
	 case DOWN:
     if(y<KOLYCHELEMENTOW[1]-1) y++;
     if(ediap-1<y){ bdiap++; ediap++; justprintvip(bdiap, ediap); stringnum=10;}
     else if(stringnum<10)
     stringnum++;
     break;
	 case ENTER: return (sp[y].id);
     case END: exitfunction();
	 }
     selectvipelem(y,stringnum);
	 }while(1);
}

selectvipelem(int number, int num){
textattr(16*5+15);
gotoxy(2,num+1);
cprintf("%-10s",sp[number].poselok);
gotoxy(13,num+1);
cprintf("%-8s",sp[number].clas);
}

unselectvipelem(int number, int num){
textattr(16*5+0);
gotoxy(2,num+1);
cprintf("%-10s",sp[number].poselok);
gotoxy(13,num+1);
cprintf("%-8s",sp[number].clas);
}

justprintvip(int ndiap, int ldiap){
int i,y=0;
for(i=ndiap;i<ldiap;i++)
{
gotoxy(2,y+2);
cprintf("%-10s",sp[i].poselok);
gotoxy(13,y+2);
cprintf("%-8s",sp[i].clas);
y++;
}
}

vproceed(int Y)
{
char c;
char podmenu[][20] = {"Again",
			          "Proceed",
                      "Cancel",};
int y=2,j=8,i;
window(21,Y,59,Y);
textattr(16*4+0);
for(i=0;i<3;i++)
{
gotoxy(j,1);
cprintf("%s",podmenu[i]);
j+=10;
}
j=18;
textattr(16*0+9);
gotoxy(j,1);
cprintf("%s",podmenu[y-1]);
do{
	c=getch();
	textattr(16*4+0);
	gotoxy(j,1);
	cprintf("%s",podmenu[y-1]);
	switch(c){
	 case RIGHT: y++; j+=10; break;
	 case LEFT: y--; j-=10; break;
	 case ENTER: return y;
     case END: exitfunction();
	 }
	 if(y<1){ y=3; j=28; }
	 if(y>3){ y=1; j=8; }
	 textattr(16*0+9);
     gotoxy(j,1);
	 cprintf("%s",podmenu[y-1]);
	 }while(1);
}

openhelpfile()
{
int i;
char c;
if(FILEWASSAVE&&CHANGEMESSAGE) sprintf(Lastmessage,"Enable SPRAVOCHNIK edit mode.");
CHANGEMESSAGE=1;
dmw();
editramka();
window(5,3,76,20);
textattr(16*1+1);
clrscr();
textattr(16*1+3);
WHATFILEISOPEN=2;
drawhelptable();
if(KOLYCHELEMENTOW[1]<diap2-diap1) diap2--;
justprintsprav(diap1,diap2);
selectelem(NOMERVIDELENNOGO[1]);
	 do{
     gettext(2,3,79,20,Lwindowbuf);
     BUFFER=1;
	 c=getch();
     unselectelem(NOMERVIDELENNOGO[1]);
	 switch(c){
	 case UP:
     if(NOMERVIDELENNOGO[1]>0) NOMERVIDELENNOGO[1]--;
     if(diap1>NOMERVIDELENNOGO[1]){ diap1--; diap2--; justprintsprav(diap1,diap2); STROKAVIDELENA[1]=1;}
     else if(STROKAVIDELENA[1]>1)
     STROKAVIDELENA[1]--;
     break;
	 case DOWN:
     if(NOMERVIDELENNOGO[1]<KOLYCHELEMENTOW[1]-1) NOMERVIDELENNOGO[1]++;
     if(diap2-1<NOMERVIDELENNOGO[1]){ diap1++; diap2++; justprintsprav(diap1,diap2); if(STROKAVIDELENA[1]>diap2) STROKAVIDELENA[1]=diap2; else STROKAVIDELENA[1]=12;}
     else if(STROKAVIDELENA[1]<12&&STROKAVIDELENA[1]<diap2)
     STROKAVIDELENA[1]++;
     break;
	 case ENTER: SELECTOUTPOINT[1]=3; SELECTOUTPOINT[0]=2; SKIPMENU=1; return;
     case F1: SELECTOUTPOINT[1]=2; SELECTOUTPOINT[0]=4; SKIPMENU=1; return;
     case F2: SELECTOUTPOINT[1]=1; SELECTOUTPOINT[0]=1; SKIPMENU=1; return;
     case F3: SELECTOUTPOINT[1]=2; SELECTOUTPOINT[0]=1; SKIPMENU=1; return;
     case F4: SELECTOUTPOINT[1]=1; SELECTOUTPOINT[0]=2; SKIPMENU=1; return;
     case F5: SELECTOUTPOINT[1]=2; SELECTOUTPOINT[0]=2; SKIPMENU=1; return;
     case DEL: SELECTOUTPOINT[1]=2; SELECTOUTPOINT[0]=2; SKIPMENU=1; return;
     case F6: SELECTOUTPOINT[1]=3; SELECTOUTPOINT[0]=2; SKIPMENU=1; return;
     case F7: SELECTOUTPOINT[1]=1; SELECTOUTPOINT[0]=3; SKIPMENU=1; return;
     case F10: SELECTOUTPOINT[1]=0; SELECTOUTPOINT[0]=0; SKIPMENU=0; return;
     case ESC: SELECTOUTPOINT[1]=0; SELECTOUTPOINT[0]=0; SKIPMENU=0; WHATFILEISOPEN=0; return;
     case END: exitfunction();
	 }
     selectelem(NOMERVIDELENNOGO[1]);
	 }while(1);

}

selectelem(int number){
textattr(16*1+11);
gotoxy(2,STROKAVIDELENA[1]+3);
cprintf("%4.d",number+1);
gotoxy(7,STROKAVIDELENA[1]+3);
cprintf("%-10s",sp[number].poselok);
gotoxy(18,STROKAVIDELENA[1]+3);
cprintf("%-8s",sp[number].clas);
gotoxy(27,STROKAVIDELENA[1]+3);
cprintf("%d$  ",sp[number].price);
}

unselectelem(int number){
textattr(16*1+7);
gotoxy(2,STROKAVIDELENA[1]+3);
cprintf("%4.d",number+1);
gotoxy(7,STROKAVIDELENA[1]+3);
cprintf("%-10s",sp[number].poselok);
gotoxy(18,STROKAVIDELENA[1]+3);
cprintf("%-8s",sp[number].clas);
gotoxy(27,STROKAVIDELENA[1]+3);
cprintf("%d$  ",sp[number].price);
}

justprintsprav(int diap1, int diap2){
int i,y=0;
for(i=diap1;i<diap2;i++)
{
gotoxy(2,y+4);
cprintf("%4.d",i+1);
gotoxy(7,y+4);
cprintf("%-10s",sp[i].poselok);
gotoxy(18,y+4);
cprintf("%-8s",sp[i].clas);
gotoxy(27,y+4);
cprintf("%d$  ",sp[i].price);
y++;
}

}

drawhelptable(){
window(22,4,59,19);
textattr(16*1+7);
clrscr();
ramka(38,16); ramka(6,16); ramka(17,16); ramka(26,16); ramka(38,3);
gotoxy(1,3); putchar(195);
gotoxy(38,3); putchar(180);
gotoxy(6,1); putchar(194);
gotoxy(17,1); putchar(194);
gotoxy(26,1); putchar(194);
gotoxy(6,3); putchar(197);
gotoxy(17,3); putchar(197);
gotoxy(26,3); putchar(197);
gotoxy(6,16); putchar(193);
gotoxy(17,16); putchar(193);
gotoxy(26,16); putchar(193);
videlup(2,2);
}

videlup(int x, int y)
{
textattr(16*1+3);
gotoxy(x,y); cprintf("Num");
gotoxy(x+5,y); cprintf("Poselok");
gotoxy(x+16,y); cprintf("Class");
gotoxy(x+25,y); cprintf("Cena $/M^2");
textattr(16*1+7);
}

about()
{
 char c;
 window(21,6,58,11);
 textattr(0);
 clrscr();
 window(20,5,57,10);
 textattr(16*4+14);
 clrscr();
 ramka(38,6);
 window(21,6,56,9);
 gotoxy(1,1);
 cprintf("This program was written for real   estate company. It allows to operatewith database.");
 c=getch();
 switch(c){
 case END: exitfunction();
 default: break;
 }
 if(WHATFILEISOPEN==1)
 {
 SELECTOUTPOINT[1]=1;
 SELECTOUTPOINT[0]=3;
 SKIPMENU=1;
 }
 else if(WHATFILEISOPEN==2)
 {
 SELECTOUTPOINT[1]=2;
 SELECTOUTPOINT[0]=3;
 SKIPMENU=1;
 }
 else
 {
 SELECTOUTPOINT[1]=0;
 SELECTOUTPOINT[0]=0;
 SKIPMENU=0;
 }
}

authors()
{
 char c;
 window(21,6,58,19);
 textattr(0);
 clrscr();
 window(20,5,57,18);
 textattr(16*4+14);
 clrscr();
 ramka(38,14);
 gotoxy(9,2);
 cprintf(">> MGSU ISTAS 1-1 <<");
 gotoxy(6,4);
 cprintf("Source:  Awerkin Grygory");
 gotoxy(6,5);
 cprintf("Testing: Awerkin Grygory");
 gotoxy(6,6);
 cprintf("Fixing:  Awerkin Grygory");
 gotoxy(8,8);
 textattr(16*4+3);
 cprintf(" SuperSoftware 2008");
 gotoxy(8,9);
 cprintf("All rights confirmed");
 gotoxy(2,11);
 cprintf("Special thanks to ManOwaR,");
 gotoxy(19,12);
 cprintf("this music help me.");
 c=getch();
 switch(c){
 case END: exitfunction();
 default: break;
 }
 if(WHATFILEISOPEN==1)
 {
 SELECTOUTPOINT[1]=1;
 SELECTOUTPOINT[0]=3;
 SKIPMENU=1;
 }
 else if(WHATFILEISOPEN==2)
 {
 SELECTOUTPOINT[1]=2;
 SELECTOUTPOINT[0]=3;
 SKIPMENU=1;
 }
 else
 {
 SELECTOUTPOINT[1]=0;
 SELECTOUTPOINT[0]=0;
 SKIPMENU=0;
 }
}

READBD()
{
FILE *inone;
int i;
  clrscr();
  if ((inone=fopen(BdFile,"r"))==NULL)
  {printf("FILE CRASH! CAN'T OPEN '%s'.\nExit in 3 sec.",BdFile); sleep(3); exit(1);}
  fscanf(inone,"%d",&KOLYCHELEMENTOW[0]);
  or=(struct order*)malloc(KOLYCHELEMENTOW[0]*sizeof(struct order));
  for(i=0;i<KOLYCHELEMENTOW[0];i++){
    fscanf(inone,"%d",&or[i].id);
    fscanf(inone,"%d",&or[i].spravid);
    fscanf(inone,"%f",&or[i].skidka);
    fscanf(inone,"%s",or[i].otdelka);
    fscanf(inone,"%d",&or[i].plosh);
    fscanf(inone,"%s",or[i].status);
  }
  fclose(inone);
}


howmanyelements()
{
FILE *in;
int N=0;
char ch;
if ((in=fopen(SpravFile,"r"))==NULL)
  {printf("FILE CRASH! CAN'T OPEN '%s'.\nExit in 3 sec.",SpravFile); sleep(3); exit(1);}
   while(!feof(in))
  {
    ch=getc(in);
    if(ch==35) N++;
  };
fclose(in);
return N;
}


READSPR(){
int i;
char ch;
KOLYCHELEMENTOW[1]=howmanyelements();
KOLYCHELEMENTOW[1]/=4;
sp=(struct sprav *)malloc(KOLYCHELEMENTOW[1]*sizeof(struct sprav));
inter=fopen(SpravFile,"r");
for(i=0;i<KOLYCHELEMENTOW[1];i++)
{
  sp[i].id=atoi(fileread());
  strcpy(sp[i].poselok,fileread());
  strcpy(sp[i].clas,fileread());
  sp[i].price=atoi(fileread());
};
  fclose(inter);
}


fileread(){
  char ch;
  int i=0;
  char b[30];
  ch=getc(inter);
    while((ch!=35)==1)
    {
      b[i]=ch;
      i++;
      ch=getc(inter);
    }
  b[i]='\0';
  return b;
}

CONTROLPRINT(){
int i;
printf("\n\n");
printf("BD-%d; SPR-%d\n",KOLYCHELEMENTOW[0],KOLYCHELEMENTOW[1]);
for(i=0;i<KOLYCHELEMENTOW[0];i++){
    printf("%d ",or[i].id);
    printf("%d ",or[i].spravid);
    printf("%.2f ",or[i].skidka);
    printf("%s ",or[i].otdelka);
    printf("%d ",or[i].plosh);
    printf("%s\n",or[i].status);
  }
printf("\n");
for(i=0;i<KOLYCHELEMENTOW[1];i++){
    printf("%d ",sp[i].id);
    printf("%s ",sp[i].poselok);
    printf("%s ",sp[i].clas);
    printf("%d\n",sp[i].price);
  }
printf("\nDatabase sucsessfully readed.");
delay(4000);
getch();
sprintf(Lastmessage,"Database loaded.");
}

savecurrentdata(){
  FILE *in;
  int i;
  if(WHATFILEISOPEN==2||WHATFILEISOPEN==1){
    in=fopen(SpravFile,"w");
    for(i=0;i<KOLYCHELEMENTOW[1];i++)
    fprintf(in,"%d#%s#%s#%d#",sp[i].id, sp[i].poselok, sp[i].clas, sp[i].price);
    fclose(in);

    in=fopen(BdFile,"w");
    fprintf(in,"%d \n",KOLYCHELEMENTOW[0]);
    for(i=0;i<KOLYCHELEMENTOW[0];i++)
    fprintf(in,"%d %d %.4f %s %d %s\n",or[i].id, or[i].spravid, or[i].skidka, or[i].otdelka, or[i].plosh, or[i].status);
    fclose(in);

    if(WHATFILEISOPEN==2){
    SELECTOUTPOINT[1]=2;
    SELECTOUTPOINT[0]=3;
    SKIPMENU=1;
    }
    else if(WHATFILEISOPEN==1){
    SELECTOUTPOINT[1]=1;
    SELECTOUTPOINT[0]=3;
    SKIPMENU=1;
    }
    sprintf(Lastmessage,"All was saved.");
    }
  else if(WHATFILEISOPEN==0){
  window(1,1,80,25);
  textattr(7);
  clrscr();
  printf("Impossible, you must open and change file before savig.\nYou return in menu after 3 sec.");
  sleep(3);
  SELECTOUTPOINT[1]=0;
  SELECTOUTPOINT[0]=0;
  SKIPMENU=0;
  }
  FILEWASSAVE=1;
  saveflags();
  CHANGEMESSAGE=0;
}

saveas(){
 FILE *in;
 char c[40]="",d=1;
 int sm=0,i,proz=0,trueidnumber;
 if(WHATFILEISOPEN==1){
 textattr(0);
 window(21,11,61,15);
 clrscr();
 window(20,10,60,14);
 textattr(16*4+0);
 clrscr();
 ramka(41,5);
 window(21,11,59,13);
 gotoxy(5,1);
 SetCursorOn();
 cprintf("Insert name of new datafile.");
 gotoxy(5,2);
 cprintf("Don't print [.\"something\"] in the end.");
 while(d!=123){
   gotoxy(5,3);
   cprintf("%s ",c);
   gotoxy(sm+5,3);
   d=getch();
   if(d!='\x0') {
   switch(d){
     case ESC: SetCursorOff(); SELECTOUTPOINT[1]=1; SELECTOUTPOINT[0]=3; SKIPMENU=1; editramka(); dmw(); return;
     case ENTER: d=123; break;
     case BACKSPACE: if(sm>0){c[sm-1]='\0'; sm--;} break;
     case END: exitfunction();
     default: if(sm<10) if(((d>47)&&(d<58))||((d>96)&&(d<123))||((d>64)&&(d<91))||(d==46)){ c[sm]=d; sm++;c[sm]='\0';}
     }
     }
     }
    SetCursorOff();
    strcat(c,".txt");
    if(strcmp(c,".txt")!=0)
    {
    in=fopen(c,"w");
    fprintf(in,"%d \n",KOLYCHELEMENTOW[0]);
    for(i=0;i<KOLYCHELEMENTOW[0];i++)
    {
    proz=or[i].skidka*100;
    for(trueidnumber=0;trueidnumber<KOLYCHELEMENTOW[1];trueidnumber++)
    if(or[i].spravid==sp[trueidnumber].id) break;
    fprintf(in,"|%3.d |poselok-%-10s|class-%-8s|maxskidka-%2.d%% |otdelka-%-4s|ploshad-%4.dM^2 |status-%-5s|%5.u000$ |\n",i+1, sp[trueidnumber].poselok, sp[trueidnumber].clas, proz, or[i].otdelka, or[i].plosh, or[i].status, or[i].cena);
    }
    fclose(in);
    sprintf(Lastmessage,"%s was saved.",c);
    }
    else{
    clrscr();
    gotoxy(5,1);
    printf("INVALID FILE NAME.");
    gotoxy(5,2);
    printf("PRESS ANY KEY FOR EXIT.");
    d=getch();
    }
    SELECTOUTPOINT[1]=1;
    SELECTOUTPOINT[0]=3;
    SKIPMENU=1;
    WHATFILEISOPEN=1;
    }
  else if(WHATFILEISOPEN==2){
  window(1,1,80,25);
  textattr(7);
  clrscr();
  printf("Impossible, you must open datafile before savig.\nYou return in SPRAVFILE after 3 sec.");
  sleep(3);
  SELECTOUTPOINT[1]=2;
  SELECTOUTPOINT[0]=3;
  SKIPMENU=1;
  }
  else{
  window(1,1,80,25);
  textattr(7);
  clrscr();
  printf("Impossible, you must open datafile before savig.\nYou return in menu after 3 sec.");
  sleep(3);
  SELECTOUTPOINT[1]=0;
  SELECTOUTPOINT[0]=0;
  SKIPMENU=0;
  }
  CHANGEMESSAGE=0;
}

nullcena()
{
int i;
for(i=0;i<KOLYCHELEMENTOW[0];i++)
or[i].cena=0;
}

dmw()
 {
 int i=0,j=0;
 window(1,1,80,1);
 textattr(16*7+0);
 clrscr();
 while(i<4)
{
 gotoxy(j+4,1);
 cprintf("%s",MainMenu[i]);
 i++;
 j+=7;
}
}

dhw()
 {
 int i;
 window(1,24,80,24);
 textattr(16*7+0);
 clrscr();
 gotoxy(1,1);
 cprintf(" Save-F2 Save As-F3 Add-F4 Delete-F5 Change-F6 Datafile-F7 Helpfile-F8 About-F1");
 window(1,25,80,25);
 textattr(16*4+14);
 clrscr();
 gotoxy(1,1);
 cprintf(" Hotkeys work only in edit mode.                    Menu-F10 Emergency exit-END");
}

exitfunction()
{
if(!FILEWASSAVE)
doyouwannasave();
exit(0);
}

upmenu()
 {
    int i=1,j=0,y;
	char c;
	textattr(16*0+15);
    if(!SELECTOUTPOINT[0]) SELECTOUTPOINT[0]=1;
    while(i<SELECTOUTPOINT[0])
    {
    i++;
    j+=7;
    }
	gotoxy(j+4,1);
	cprintf("%s",MainMenu[SELECTOUTPOINT[0]-1]);
	do{
	c=getch();
	textattr(16*7+0);
	gotoxy(j+4,1);
	cprintf("%s",MainMenu[SELECTOUTPOINT[0]-1]);
	switch(c){
	 case RIGHT: SELECTOUTPOINT[0]++; j+=7; break;
	 case LEFT: SELECTOUTPOINT[0]--; j-=7; break;
	 case ENTER: return SELECTOUTPOINT[0];
     case DOWN: return SELECTOUTPOINT[0];
     case END: exitfunction();
	 }
	 if(SELECTOUTPOINT[0]<1){ SELECTOUTPOINT[0]=4; j=21; }
	 if(SELECTOUTPOINT[0]>4){ SELECTOUTPOINT[0]=1; j=0; }
	 textattr(16*0+15);
     gotoxy(j+4,1);
	 cprintf("%s",MainMenu[SELECTOUTPOINT[0]-1]);
	 }while(1);
 }

int submenu(int positionnumber,int kolychstrok,char subdan[][20],int x1, int y1, int x2, int y2)
	 {
	 int i=1,t,j=0;
     textattr(16*0+15);
     while(i<positionnumber)
     {
     i++;
     j+=7;
     }
	 gotoxy(j+4,1);
	 cprintf("%s",MainMenu[positionnumber-1]);
     textattr(0);
     window(x1+1,y1+1,x2+1,y2+1);
     clrscr();
	 window(x1,y1,x2,y2);
	 textattr(16*7+0);
	 clrscr();
     ramka(x2-x1+1,y2-y1+1);
	 for(i=0;i<kolychstrok;i++)
     {
	 gotoxy(2,i+2);
     cprintf("%s",subdan[i]);
     }
	 SELECTOUTPOINT[1]=menu(kolychstrok,subdan);
     if(SELECTOUTPOINT[1]!=0&&SELECTOUTPOINT[1]!=22) return 1;
     else if(SELECTOUTPOINT[1]==22) return 22;
     else return 0;
	 }
	 
 menu(int kolychstrok,char subdan[][20])
 {
	 int y=1;
	 char c;
	 textattr(16*0+15);
     gotoxy(2,2);
	 cprintf("%s",subdan[y-1]);
	 do{
	 c=getch();
	 textattr(16*7+0);
	 gotoxy(2,y+1);
	 cprintf("%s",subdan[y-1]);
	 switch(c){
	 case UP: y--; break;
	 case DOWN: y++; break;
     case LEFT: if(SELECTOUTPOINT[0]==1) SELECTOUTPOINT[0]=4; else SELECTOUTPOINT[0]--; return 22;
     case RIGHT: if(SELECTOUTPOINT[0]==4) SELECTOUTPOINT[0]=1; else SELECTOUTPOINT[0]++; return 22;
	 case ENTER: return y;
     case ESC: SELECTOUTPOINT[0]=0; return 0;
     case END: exitfunction();
	 }
	 if(y<1) y=kolychstrok;
	 if(y>kolychstrok) y=1;
	 textattr(16*0+15);
	 gotoxy(2,y+1);
	 cprintf("%s",subdan[y-1]);
	 }while(1);
 }

 
int mainmenu()
{
 int t,k=0;
 while(1)
 {
 if(!SELECTOUTPOINT[0])
 t=upmenu();
 else
 t=SELECTOUTPOINT[0];
 switch(t){
 case 1: k=submenu(1,3,Menu1,3,2,15,6); editramka(); dmw(); break;
 case 2: k=submenu(2,3,Menu2,10,2,21,6); editramka(); dmw(); break;
 case 3: k=submenu(3,2,Menu3,17,2,30,5); editramka(); dmw(); break;
 case 4: k=submenu(4,2,Menu4,24,2,35,5); editramka(); dmw(); break;
}
if(k!=0&&k!=22) break;
else if(k==22) SELECTOUTPOINT[1]=1;
}
}

editramka()
{
textattr(16*1+3);
window(1,2,80,21);
clrscr();
ramka(80,20);
window(1,21,80,23);
clrscr();
ramka(80,3);
window(1,2,80,23);
gotoxy(1,20);
putchar(195);
gotoxy(80,20);
putchar(180);
gotoxy(38,1);
cprintf(" EDIT ");
gotoxy(36,20);
cprintf(" MESSAGES ");
gotoxy(2,21);
textattr(16*1+14);
cprintf("%-78s",Lastmessage);
textattr(16*1+3);
gotoxy(32,10);
if(WHATFILEISOPEN==0)
cprintf("No edit file loaded.");
else{
window(2,3,79,20);
textattr(16*1+7);
clrscr();
if(BUFFER) puttext(2,3,79,20,Lwindowbuf);
}
}

ramka(int endx, int endy)
{
 int i;
 putchar(218);
 for(i=2;i<endx;i++)
 {gotoxy(i,1); putchar(196); }
 putchar(191);
 for(i=2;i<endy;i++)
 {gotoxy(endx,i); putchar(179); }
 gotoxy(1,endy);
 putchar(192);
 for(i=2;i<endx;i++)
 {gotoxy(i,endy); putchar(196);}
 putchar(217);
 for(i=2;i<endy;i++)
 {gotoxy(1,i); putchar(179); }
 gotoxy(1,1);
}

SetCursorOff()
{
union REGS regs;
regs.h.ah=1;
regs.h.ch=-1;
regs.h.cl=-1;
int86(0x10,&regs,&regs);
}

SetCursorOn()
{
union REGS regs;
regs.h.ah=1;
regs.h.ch=6;
regs.h.cl=7;
int86(0x10,&regs,&regs);
}

