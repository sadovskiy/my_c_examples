#include <stdio.h>
#include <conio.h>

#define BEGIN_LV 5 /* 1 Stage in ListView  */
#define MAX_LV 9

struct hWnd
{
  int wx;
  int wy;
  int ww;
  int wh;
  int wndattr;
  void *wndbuf;
};

struct DataStruct
{
   int Num;
   float Coast;
   char CompName[20];
   char ProcType[20];
   char Motherboard[20];

};

int all = 0;
int begin = 0;
int offset = MAX_LV;
struct hWnd win;
int dirbuf =0;

DrawWindow(int x, int y, int w, int h, int wndattr, struct hWnd *wnd)
{
  window(x,y,w,h);
  textattr(wndattr);
  clrscr();
  wnd->wx = x;
  wnd->wy = y;
  wnd->ww = w;
  wnd->wh = h;
  wnd->wndattr = wndattr;
}

MakeSpace(int count)
{
  int i;
  for(i=0;i<count;i++)
  {
    cprintf(" ");
  }
}

WriteWindowBuffer(struct hWnd *wnd)
{
  wnd->wndbuf = (void*)malloc(wnd->ww*wnd->wh*2);
  gettext(wnd->wx,wnd->wy,wnd->ww,wnd->wh,wnd->wndbuf);
}

DrawHoroLine(int Length)
{
 struct text_info tf;
 int i;
 gettextinfo(&tf);
 for(i=0;i<Length;i++)
 {
   gotoxy(tf.curx+i,tf.cury);  putchar(196);
 }

}

DrawVerticalLine(int Length)
{
  struct text_info tf;
  int i;
  gettextinfo(&tf);
  for(i=0;i<Length;i++)
  {
    gotoxy(tf.curx,tf.cury+i); putchar(179);
  }
}

DrawSpecialHoro(int x)
{
  gotoxy(2,x);
  putchar(195);
  DrawHoroLine(76);
  putchar(180);
  gotoxy(7,x);
  putchar(197);
  gotoxy(20,x);
  putchar(197);
  gotoxy(38,x);
  putchar(197);
  gotoxy(60,x);
  putchar(197);
}

ReadWindowBuffer(struct hWnd *wnd)
{
  puttext(wnd->wx,wnd->wy,wnd->ww,wnd->wh,wnd->wndbuf);
  window(wnd->wx,wnd->wy,wnd->ww,wnd->wh);
  textattr(wnd->wndattr);
}

WriteTableData(struct DataStruct *MyData,int count)
{
  int Writer = BEGIN_LV;
  int i;
  int Val = 0;
  char num[4];
  char coast[18];

  for(i=begin;i<offset+begin,i<count;i++,Val++)
  {
    sprintf(num,"%d",MyData[i].Num);
    sprintf(coast,"%.2f",MyData[i].Coast);
    PrintDataToTable(num,MyData[i].CompName,coast,MyData[i].ProcType,MyData[i].Motherboard, Writer,YELLOW+BLUE*16);
    Writer++;
    if(Val != MAX_LV-1){  DrawSpecialHoro(Writer);  Writer++;  }else{ break; }
  }
}


PrintDataToTable(char *Nun, char *CompName, char *Coast, char *ProcType, char* Motherboard, int Writer, int attr)
{
 int cdata;
 textattr(attr);
 gotoxy(3,Writer);
 cdata = strlen(Nun);
 if(cdata < 4 || cdata == 4)
 { cprintf("%s",Nun); MakeSpace(4-cdata); }
   cprintf("%c",179);  /* putchar(179);  */
 cdata = strlen(Coast);
 if(cdata < 12 || cdata == 12)
{ cprintf("%s",Coast); MakeSpace(12-cdata); }
  cprintf("%c",179);
 cdata = strlen(CompName);
 if(cdata < 17 || cdata == 17)
{ cprintf("%s",CompName); MakeSpace(17-cdata); }
  cprintf("%c",179);

 cdata = strlen(ProcType);
 if(cdata < 21 || cdata == 21)
{ cprintf("%s",ProcType); MakeSpace(21-cdata); }
  cprintf("%c",179);
 cdata = strlen(Motherboard);
 if(cdata < 18 || cdata == 18)
{ cprintf("%s",Motherboard); MakeSpace(18-cdata); }

}

PrintDataByIndex(struct DataStruct *MyData,int i,int Writer ,int attr)
{

  char num[4];
  char coast[18];
  sprintf(num,"%d",MyData[i].Num);
  sprintf(coast,"%.2f",MyData[i].Coast);
  PrintDataToTable(num,MyData[i].CompName,coast,MyData[i].ProcType,MyData[i].Motherboard, Writer,attr);

}

struct DataStruct * MListView(int n, struct DataStruct *MyData)
{
  int curRd = begin;
  int y=BEGIN_LV;
  int right = 8;
  struct DataStruct *tmp = NULL;
  char c;
  char res;
  if(all>0) PrintDataByIndex(MyData,begin,y,BLUE+LIGHTGRAY*16);
  do
    {  c=getch();
       if(all>0)PrintDataByIndex(MyData,curRd,y,YELLOW+BLUE*16);
       if(all==0) ReadWindowBuffer(&win);
       switch(c){
case 'P': y=y+2; curRd++; break;
	case 'H': y=y-2; curRd--; break;
	case 83 :
	   break;
        case 15:
           break;
	case 68:
           break;
        case '\r':return MyData;
         case 59:
	   break;
        case 60:
           break;
     }
  if(curRd > right || curRd > n)
   if(begin+offset < all)
    {
       begin++;
       right++;
       window(win.wx,win.wy,win.ww,win.wh);
       textattr(win.wndattr);
       WriteTableData(MyData,all);
       curRd=right; y=y-2;
    }
    else
    {
     y = BEGIN_LV; curRd=begin;
    }
  if(curRd<begin){
    if(begin>0)
    {
      right--;
      begin--;
       window(win.wx,win.wy,win.ww,win.wh);
       textattr(win.wndattr);
      WriteTableData(MyData,all);
      curRd = begin; y = BEGIN_LV;
    }else{

    y = BEGIN_LV; curRd=begin;
    }
  }

 if(all>0){  PrintDataByIndex(MyData,curRd,y,BLUE+LIGHTGRAY*16);    }
  }while(c!=27);
  exit(0); }



main()
{

   int i;
   FILE *in;
   struct DataStruct *MyData;
   begin = 0;
   offset = MAX_LV;

  window(1,1,80,25);
  textattr(7);
  clrscr();
   
if((in = fopen("SPRMAT.dat","r"))==NULL){
   printf("Fatal Error! File SPRAMAT.dat is not open!"); getch(); exit(1);}
   fscanf(in,"%d",&all);
   MyData = (struct DataStruct*)malloc(all*sizeof(struct DataStruct));
   for(i=0; i<all; i++)
   fscanf(in,"%d%f%s%s%s",&MyData[i].Num,&MyData[i].Coast,MyData[i].CompName,MyData[i].ProcType,MyData[i].Motherboard);
   fclose(in);



  DrawWindow(1,2,80,24,YELLOW+BLUE*16,&win);
  gotoxy(2,2);
  putchar(218);
  DrawHoroLine(76);
  putchar(191);
  gotoxy(2,3);
  DrawVerticalLine(19);
  gotoxy(2,22);
  putchar(192);
  DrawHoroLine(76);
  gotoxy(79,3);
  DrawVerticalLine(19);
  gotoxy(79,22);
  putchar(217);
  gotoxy(7,2);
  putchar(194);
  gotoxy(7,3);
  DrawVerticalLine(19);
  gotoxy(7,22);
  putchar(193);

  gotoxy(20,2);
  putchar(194);
  gotoxy(20,3);
  DrawVerticalLine(19);
  gotoxy(20,22);
  putchar(193);

  gotoxy(38,2);
  putchar(194);
  gotoxy(38,3);
  DrawVerticalLine(19);
  gotoxy(38,22);
  putchar(193);

  gotoxy(60,2);
  putchar(194);
  gotoxy(60,3);
  DrawVerticalLine(19);
  gotoxy(60,22);
  putchar(193);


  textattr(WHITE+BLUE*16);
  gotoxy(3,3);
  cprintf("Num");
  gotoxy(8,3);
  cprintf("Coast");
  gotoxy(21,3);
  cprintf("Comp. Name");

gotoxy(39,3);
  cprintf("Processor");
  gotoxy(61,3);
  cprintf("Motherboard");
  DrawSpecialHoro(4);

 while(1)
 {
  if(dirbuf!=1) /*≈сли dirbuf не равен 0, то окно еще не буферизировалось.*/
  WriteWindowBuffer(&win); /*сохран€ем окно */
  dirbuf=1; /*теперь окно сохранено. */
  if (all > 0) 
   WriteTableData(MyData,all); 
   MyData = MListView(all-1,MyData); 
 }
 getch();

}
