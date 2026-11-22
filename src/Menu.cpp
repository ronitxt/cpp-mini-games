#include "Menu.h"
#include "TicTacToe.h"
#include "SnakeGame.h"
#include "UI.h"
#include <string>
namespace {
void menuScreen(int selected,int played){
 UI::drawHeader("THE MINI GAME COLLECTION","Choose your arcade challenge");
 int cx=COLS/2; UI::drawPanel(7,cx-25,13,50," GAME SELECT ",1);
 const std::string options[]={"[ 1 ]  TIC TAC TOE","[ 2 ]  SNAKE GAME","[ 3 ]  HOW TO PLAY","[ Q ]  EXIT ARCADE"};
 for(int i=0;i<4;++i){int y=10+i*2,pair=(i==selected)?3:6;
  attron(COLOR_PAIR(pair)|(i==selected?A_BOLD:A_NORMAL));mvaddstr(y,cx-13,options[i].c_str());attroff(COLOR_PAIR(pair)|(i==selected?A_BOLD:A_NORMAL));}
 UI::drawCentered(22,"UP/DOWN or 1-4: navigate | ENTER: select | Q: quit",2);
 UI::drawCentered(24,"GAMES LAUNCHED THIS SESSION: "+std::to_string(played),4);
 UI::drawCentered(27,"C++17  •  NCURSES  •  NEON ARCADE",7,A_DIM);refresh();
}
void helpScreen(){
 UI::drawHeader("HOW TO PLAY");UI::drawPanel(7,COLS/2-31,17,62," ARCADE GUIDE ",2);
 mvaddstr(10,COLS/2-27,"TIC TAC TOE");
 mvaddstr(11,COLS/2-27,"Two players take turns placing X and O.");
 mvaddstr(12,COLS/2-27,"Use arrow keys to select a square, then press ENTER.");
 mvaddstr(14,COLS/2-27,"SNAKE GAME");
 mvaddstr(15,COLS/2-27,"Move using arrow keys or WASD.");
 mvaddstr(16,COLS/2-27,"Eat food, grow longer, avoid walls and yourself.");
 mvaddstr(18,COLS/2-27,"P: pause/resume    Q: return to menu");UI::waitForKey();
}
}
void runMainMenu(){
 int selected=0,played=0;bool done=false;
 while(!done){menuScreen(selected,played);int key=getch();
  if(key==KEY_UP||key=='w'||key=='W')selected=(selected+3)%4;
  else if(key==KEY_DOWN||key=='s'||key=='S')selected=(selected+1)%4;
  else if(key>='1'&&key<='4')selected=key-'1';
  else if(key=='q'||key=='Q')done=true;
  else if(key=='\n'||key==KEY_ENTER||key==' '){
   if(selected==0){++played;runTicTacToe();}
   else if(selected==1){++played;runSnakeGame();}
   else if(selected==2)helpScreen();else done=true;
  }
 }
}
