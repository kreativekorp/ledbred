#ifndef DISPLAY_H
#define DISPLAY_H

void displayBegin();
void displayClear();
void displayUpdate();
void displayString(const char * str, int x, int y, int fg, int bg);
void displayStringCenter(const char * str, int x, int y, int fg, int bg);
void displayStringRight(const char * str, int x, int y, int fg, int bg);
void displayIcon(int i, int x, int y, int fg, int bg);
void displayColorSelect(int i);
void displayLevelSelect(int i);
void displayMessage(int icon, const char * str);
void displayConfirmation(const char * str, int i);
void displayMenuSelect(int n, const int * icons, const char ** items, int i);
void displayFileSelect(int i, int n, const char * name);

#endif
