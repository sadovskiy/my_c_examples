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

int SELECTOUTPOINT[2]={0,0};
int SKIPMENU=0;
int WHATFILEISOPEN=0;
int FILEWASSAVE=1;
int STROKAVIDELENA=1;
unsigned KOLYCHELEMENTOW[2]={0,0};

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

char BdFile[20]="MYPRDAT.DAT";
char SpravFile[20]="MYSPR.DAT";
char Lastmessage[78];

struct sprav{
	int id;
	char name[15];
	char model[15];
	float price;
	}*sp;

struct order{
	int id;
	int spravid;
	int kolvo;
	char date[15];
	char date2[15];
	}*or;

void *Lwindowbuf;
void *Mwindowbuf;
void *Swindowbuf;

main()
{
 int point;
 char c;
 do{
 printf("ALT+ENTER for fulscreen mode, press ESC\n");
 c=getch();
 }while(c!=27);
 READBD();
 READSPR();
 CONTROLPRINT();
 SetCursorOff();
 while(1){
 editramka();
 dhw();
 dmw();
 if(!SKIPMENU) mainmenu();
 point=SELECTOUTPOINT[0]*10+SELECTOUTPOINT[1];
 switch(point){
 case 11: savecurrentdata(); break;
 case 12: saveas(); break;
 case 13: exitfunction();
 case 21: break;
 case 22: break;
 case 23: break;
 case 31: break;
 case 32: break;
 case 41: authors(); break;
 case 42: about(); break;
 }
 SELECTOUTPOINT[1]=0;
 SELECTOUTPOINT[0]=0;
 SKIPMENU=0;
 }
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
 cprintf("That program was written for real   estate company. It allows to operatewith database.");
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
    fscanf(inone,"%d",&or[i].kolvo);
    fscanf(inone,"%s",or[i].date);
    fscanf(inone,"%s",or[i].date2);
  }
  fclose(inone);
}

READSPR(){
FILE *intwo;
int i;
if ((intwo=fopen(SpravFile,"r"))==NULL)
  {printf("FILE CRASH! CAN'T OPEN '%s'.\nExit in 3 sec.",SpravFile); sleep(3); exit(1);}
  fscanf(intwo,"%d",&KOLYCHELEMENTOW[1]);
  sp=(struct sprav*)malloc(KOLYCHELEMENTOW[1]*sizeof(struct sprav));
  for(i=0;i<KOLYCHELEMENTOW[1];i++){
    fscanf(intwo,"%d",&sp[i].id);
    fscanf(intwo,"%s",sp[i].name);
    fscanf(intwo,"%s",sp[i].model);
    fscanf(intwo,"%f",&sp[i].price);
  }
  fclose(intwo);
}

CONTROLPRINT(){
int i;
printf("\n\n");
printf("BD-%d; SPR-%d\n",KOLYCHELEMENTOW[0],KOLYCHELEMENTOW[1]);
for(i=0;i<KOLYCHELEMENTOW[0];i++){
    printf("%d ",or[i].id);
    printf("%d ",or[i].spravid);
    printf("%d ",or[i].kolvo);
    printf("%s ",or[i].date);
    printf("%s\n",or[i].date2);
  }
printf("\n");
for(i=0;i<KOLYCHELEMENTOW[1];i++){
    printf("%d ",sp[i].id);
    printf("%s ",sp[i].name);
    printf("%s ",sp[i].model);
    printf("%f\n",sp[i].price);
  }
printf("\nDatabase sucsessfully readed.");
delay(4000);
sprintf(Lastmessage,"Database loaded.");
}

savecurrentdata(){
  FILE *in;
  int i;
  if(WHATFILEISOPEN==2){
    in=fopen(SpravFile,"w");
    fprintf(in,"%d \n",KOLYCHELEMENTOW[1]);
    for(i=0;i<KOLYCHELEMENTOW[1];i++)
    fprintf(in,"%d %s %s %f \n",sp[i].id, sp[i].name, sp[i].model, sp[i].price);
    fclose(in);
    free(sp);
    SELECTOUTPOINT[1]=2;
    SELECTOUTPOINT[0]=3;
    SKIPMENU=1;
    sprintf(Lastmessage,"%s was saved.",SpravFile);
    }
  else if(WHATFILEISOPEN==1){
    in=fopen(BdFile,"w");
    fprintf(in,"%d \n",KOLYCHELEMENTOW[0]);
    for(i=0;i<KOLYCHELEMENTOW[0];i++)
    fprintf(in,"%d %d %d %s %s \n",or[i].id, or[i].spravid, or[i].kolvo, or[i].date, or[i].date2);
    fclose(in);
    free(or);
    SELECTOUTPOINT[1]=1;
    SELECTOUTPOINT[0]=3;
    SKIPMENU=1;
    sprintf(Lastmessage,"%s was saved.",BdFile);
    }
  else if(WHATFILEISOPEN==0){
  window(1,1,80,25);
  textattr(7);
  clrscr();
  printf("Impoosble, you must open and change file before savig.\nYou return in menu after 3 sec.");
  sleep(3);
  SELECTOUTPOINT[1]=0;
  SELECTOUTPOINT[0]=0;
  SKIPMENU=0;
  }
  FILEWASSAVE=1;
}

saveas(){
 FILE *in;
 char c[40]="",d=1;
 int sm=0,i;
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
 cprintf("Don't print '.dat'in the end.");
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
    strcat(c,".DAT");
    if(strcmp(c,".DAT")!=0)
    {
    in=fopen(c,"w");
    fprintf(in,"%d \n",KOLYCHELEMENTOW[0]);
    for(i=0;i<KOLYCHELEMENTOW[0];i++)
    fprintf(in,"%d %d %d %s %s \n",or[i].id, or[i].spravid, or[i].kolvo, or[i].date, or[i].date2);
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
  else{
  window(1,1,80,25);
  textattr(7);
  clrscr();
  printf("Imposble, you must open datafile before savig.\nYou return in menu after 3 sec.");
  sleep(3);
  SELECTOUTPOINT[1]=0;
  SELECTOUTPOINT[0]=0;
  SKIPMENU=0;
  }
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
window(1,1,80,25);
textattr(7);
clrscr();
if(!FILEWASSAVE)
savecurrentdata();
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
else
cprintf("bufferfile");
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
