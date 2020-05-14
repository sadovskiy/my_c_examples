#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include <dos.h>

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

main()
{
 int point;
 char c;
 do{
 printf("ALT+ENTER for fulscreen mode, press ESC\n");
 c=getch();
 }while(c!=27);
 READALL();
 SetCursorOff();
 bluescreen();
 dhw();
 dmw();
 while(1){
 if(!SKIPMENU)
 mainmenu();
 point=SELECTOUTPOINT[0]*10+SELECTOUTPOINT[1];
 switch(point){
 case 11: break;
 case 12: break;
 case 13: exitfunction();
 case 21: break;
 case 22: break;
 case 23: break;
 case 31: break;
 case 32: break;
 case 41: break;
 case 42: break;
 }
 SELECTOUTPOINT[1]=0;
 SELECTOUTPOINT[0]=0;
 }
}

READALL(){}

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
 window(1,24,80,25);
 textattr(16*7+0);
 clrscr();
 gotoxy(1,1);
 for(i=0;i<2;i++)
 cprintf("%s",Menu1[i]);
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

savecurrentdata(){}


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
 case 1: k=submenu(1,3,Menu1,3,2,15,6); bluescreen(); dmw(); break;
 case 2: k=submenu(2,3,Menu2,10,2,21,6); bluescreen(); dmw(); break;
 case 3: k=submenu(3,2,Menu3,17,2,30,5); bluescreen(); dmw(); break;
 case 4: k=submenu(4,2,Menu4,24,2,35,5); bluescreen(); dmw(); break;
}
if(k!=0&&k!=22) break;
else if(k==22) SELECTOUTPOINT[1]=1;
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

bluescreen()
{
 window(1,1,80,23);
 textattr(16*1+1);
 clrscr();
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
