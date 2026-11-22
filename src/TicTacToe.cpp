#include "TicTacToe.h"
#include "UI.h"
#include <array>
#include <string>
namespace {
using Board=std::array<char,9>;
int winner(const Board& b){
 static const int lines[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
 for(const auto& l:lines)if(b[l[0]]!=' '&&b[l[0]]==b[l[1]]&&b[l[1]]==b[l[2]])return b[l[0]]=='X'?1:2;
 return 0;
}
void draw(const Board& b,int selected,char p,int xw,int ow,int draws){
 UI::drawHeader("TIC TAC TOE","Two players • Make three in a row");int cx=COLS/2;
 UI::drawPanel(7,cx-27,15,54," PLAYING FIELD ",1);
 int sx=cx-9,sy=10;
 for(int r=0;r<3;++r){
  for(int c=0;c<3;++c){int i=r*3+c,pair=b[i]=='X'?1:(b[i]=='O'?2:6);
   if(i==selected)attron(A_REVERSE|A_BOLD);attron(COLOR_PAIR(pair)|A_BOLD);
   mvprintw(sy+r*3,sx+c*7,"  %c  ",b[i]==' '?'1'+i:b[i]);
   attroff(COLOR_PAIR(pair)|A_BOLD);if(i==selected)attroff(A_REVERSE|A_BOLD);
  }
  if(r<2){mvhline(sy+r*3+1,sx,ACS_HLINE,23);mvhline(sy+r*3+2,sx,ACS_HLINE,23);}
 }
 mvprintw(21,cx-18,"PLAYER X: %d     PLAYER O: %d     DRAWS: %d",xw,ow,draws);
 UI::drawCentered(23,std::string("CURRENT TURN: PLAYER ")+p,p=='X'?1:2,A_BOLD);
 UI::drawCentered(25,"Arrows: move   ENTER: place   R: restart   Q: menu",4);refresh();
}
}
void runTicTacToe(){
 int selected=4,xw=0,ow=0,draws=0;bool leave=false;
 while(!leave){Board b;b.fill(' ');char player='X';bool finished=false;
  while(!finished&&!leave){draw(b,selected,player,xw,ow,draws);int k=getch();
   if(k=='q'||k=='Q'){leave=true;break;}
   if(k=='r'||k=='R'){b.fill(' ');player='X';selected=4;continue;}
   if(k==KEY_LEFT&&selected%3>0)--selected;
   else if(k==KEY_RIGHT&&selected%3<2)++selected;
   else if(k==KEY_UP&&selected/3>0)selected-=3;
   else if(k==KEY_DOWN&&selected/3<2)selected+=3;
   else if(k=='\n'||k==KEY_ENTER||k==' '){
    if(b[selected]!=' ')continue;b[selected]=player;int win=winner(b);
    if(win){if(win==1)++xw;else ++ow;finished=true;}
    else{bool full=true;for(char cell:b)if(cell==' ')full=false;
     if(full){++draws;finished=true;}else player=player=='X'?'O':'X';}
   }
  }
  if(finished&&!leave){UI::drawHeader("ROUND COMPLETE");int w=winner(b);
   UI::drawCentered(11,w==1?"PLAYER X WINS!":w==2?"PLAYER O WINS!":"IT'S A DRAW!",w==1?1:w==2?2:4,A_BOLD);
   UI::drawCentered(14,"ENTER: another round     Q: return to menu",6);refresh();int k=getch();if(k=='q'||k=='Q')leave=true;
  }
 }
}
