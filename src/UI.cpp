#include "UI.h"
#include <algorithm>
namespace UI {
void init() {
 initscr(); cbreak(); noecho(); keypad(stdscr, TRUE); curs_set(0);
 if (has_colors()) { start_color(); use_default_colors();
  init_pair(1,COLOR_CYAN,-1); init_pair(2,COLOR_MAGENTA,-1); init_pair(3,COLOR_GREEN,-1);
  init_pair(4,COLOR_YELLOW,-1); init_pair(5,COLOR_RED,-1); init_pair(6,COLOR_WHITE,-1); init_pair(7,COLOR_BLUE,-1);
 }
 timeout(-1);
}
void shutdown(){ endwin(); }
void drawCentered(int y,const std::string& text,int pair,int attrs){
 int x=std::max(0,(COLS-static_cast<int>(text.size()))/2);
 attron(COLOR_PAIR(pair)|attrs); mvaddnstr(y,x,text.c_str(),std::max(0,COLS-x-1)); attroff(COLOR_PAIR(pair)|attrs);
}
void drawHeader(const std::string& title,const std::string& subtitle){
 erase(); drawCentered(1,"================================================",1,A_BOLD);
 drawCentered(2,"N E O N   A R C A D E",2,A_BOLD); drawCentered(3,title,1,A_BOLD);
 if(!subtitle.empty()) drawCentered(4,subtitle,6,A_DIM);
 drawCentered(5,"================================================",1,A_BOLD);
}
void drawPanel(int y,int x,int h,int w,const std::string& title,int pair){
 if(h<3||w<8)return; attron(COLOR_PAIR(pair)|A_BOLD);
 mvaddch(y,x,ACS_ULCORNER); mvhline(y,x+1,ACS_HLINE,w-2); mvaddch(y,x+w-1,ACS_URCORNER);
 for(int r=1;r<h-1;++r){mvaddch(y+r,x,ACS_VLINE);mvaddch(y+r,x+w-1,ACS_VLINE);}
 mvaddch(y+h-1,x,ACS_LLCORNER);mvhline(y+h-1,x+1,ACS_HLINE,w-2);mvaddch(y+h-1,x+w-1,ACS_LRCORNER);
 if(!title.empty())mvaddnstr(y,x+2,(" "+title+" ").c_str(),w-4);attroff(COLOR_PAIR(pair)|A_BOLD);
}
void waitForKey(const std::string& message){drawCentered(LINES-2,message,4,A_BOLD);refresh();timeout(-1);getch();}
}
