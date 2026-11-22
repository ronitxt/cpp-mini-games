#include "Menu.h"
#include "UI.h"
#include <exception>
#include <iostream>
int main(){
 try{UI::init();runMainMenu();UI::shutdown();}
 catch(const std::exception& e){UI::shutdown();std::cerr<<"Application error: "<<e.what()<<'\n';return 1;}
 return 0;
}
