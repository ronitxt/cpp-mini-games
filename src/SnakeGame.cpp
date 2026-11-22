#include "SnakeGame.h"
#include "UI.h"
#include <algorithm>
#include <deque>
#include <random>
#include <string>
namespace {
struct Point{int x,y;};
bool same(Point a,Point b){return a.x==b.x&&a.y==b.y;}
enum class Dir{Up,Down,Left,Right};
void foodAt(Point& food,const std::deque<Point>& snake,int w,int h,std::mt19937& rng){
 std::uniform_int_distribution<int> dx(1,w-2),dy(1,h-2);
 do{food={dx(rng),dy(rng)};}while(std::any_of(snake.begin(),snake.end(),[&](Point p){return same(p,food);}));
}
void drawGame(const std::deque<Point>& snake,Point food,int score,int best,int level,bool paused,int w,int h){
 UI::drawHeader("SNAKE GAME","Eat • Grow • Survive");int left=(COLS-w)/2,top=7;
 UI::drawPanel(top-1,left-1,h+2,w+2," ARENA ",3);
 for(int x=0;x<w;++x){mvaddch(top,left+x,ACS_CKBOARD);mvaddch(top+h-1,left+x,ACS_CKBOARD);}
 for(int y=1;y<h-1;++y){mvaddch(top+y,left,ACS_CKBOARD);mvaddch(top+y,left+w-1,ACS_CKBOARD);}
 attron(COLOR_PAIR(5)|A_BOLD);mvaddch(top+food.y,left+food.x,'@');attroff(COLOR_PAIR(5)|A_BOLD);
 for(std::size_t i=0;i<snake.size();++i){int pair=i==0?4:3;attron(COLOR_PAIR(pair)|A_BOLD);mvaddch(top+snake[i].y,left+snake[i].x,i==0?'O':'o');attroff(COLOR_PAIR(pair)|A_BOLD);}
 mvprintw(top+h+1,left,"SCORE %d   BEST %d   LEVEL %d",score,best,level);
 UI::drawCentered(LINES-2,paused?"PAUSED - P to resume | Q: menu":"Arrows/WASD: move   P: pause   Q: menu",4);refresh();
}
}
void runSnakeGame(){
 int best=0;bool leave=false;
 while(!leave){
  int w=std::min(52,COLS-8),h=std::min(18,LINES-12);
  if(w<20||h<10){UI::drawHeader("WINDOW TOO SMALL");UI::drawCentered(12,"Please enlarge terminal to at least 70 x 24.",5,A_BOLD);UI::waitForKey();return;}
  std::deque<Point> snake={{w/2,h/2},{w/2-1,h/2},{w/2-2,h/2}};
  Dir dir=Dir::Right;Point food{};std::mt19937 rng(std::random_device{}());foodAt(food,snake,w,h,rng);
  int score=0;bool over=false,paused=false;
  while(!over&&!leave){
   drawGame(snake,food,score,best,1+score/50,paused,w,h);
   timeout(paused?-1:std::max(55,145-score),0);int k=getch();
   if(k=='q'||k=='Q'){leave=true;break;}if(k=='p'||k=='P'){paused=!paused;continue;}if(paused)continue;
   Dir next=dir;
   if(k==KEY_UP||k=='w'||k=='W')next=Dir::Up;else if(k==KEY_DOWN||k=='s'||k=='S')next=Dir::Down;
   else if(k==KEY_LEFT||k=='a'||k=='A')next=Dir::Left;else if(k==KEY_RIGHT||k=='d'||k=='D')next=Dir::Right;
   if(!((dir==Dir::Up&&next==Dir::Down)||(dir==Dir::Down&&next==Dir::Up)||(dir==Dir::Left&&next==Dir::Right)||(dir==Dir::Right&&next==Dir::Left)))dir=next;
   if(k!=ERR&&k!=KEY_UP&&k!=KEY_DOWN&&k!=KEY_LEFT&&k!=KEY_RIGHT&&k!='w'&&k!='W'&&k!='a'&&k!='A'&&k!='s'&&k!='S'&&k!='d'&&k!='D')continue;
   Point head=snake.front();if(dir==Dir::Up)--head.y;else if(dir==Dir::Down)++head.y;else if(dir==Dir::Left)--head.x;else ++head.x;
   if(head.x<=0||head.x>=w-1||head.y<=0||head.y>=h-1){over=true;break;}
   bool eating=same(head,food);std::size_t limit=snake.size()-(eating?0:1);
   for(std::size_t i=0;i<limit;++i)if(same(head,snake[i]))over=true;
   if(over)break;snake.push_front(head);
   if(eating){score+=10;best=std::max(best,score);foodAt(food,snake,w,h,rng);}else snake.pop_back();
  }
  timeout(-1);
  if(!leave){UI::drawHeader("GAME OVER");UI::drawCentered(11,"YOUR SCORE: "+std::to_string(score),3,A_BOLD);
   UI::drawCentered(13,"SESSION BEST: "+std::to_string(best),4,A_BOLD);UI::drawCentered(16,"ENTER: play again     Q: return to menu",6);refresh();
   int k=getch();if(k=='q'||k=='Q')leave=true;
  }
 }
}
