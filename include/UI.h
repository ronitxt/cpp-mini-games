#pragma once
#include <ncurses.h>
#include <string>
namespace UI {
void init();
void shutdown();
void drawCentered(int y, const std::string& text, int colorPair = 0, int attrs = A_NORMAL);
void drawHeader(const std::string& title, const std::string& subtitle = "");
void drawPanel(int y, int x, int height, int width, const std::string& title, int colorPair = 1);
void waitForKey(const std::string& message = "Press any key to continue");
}
