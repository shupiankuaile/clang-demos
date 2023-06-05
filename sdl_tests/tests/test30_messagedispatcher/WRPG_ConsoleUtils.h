#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>
#include <conio.h>
#include <stdio.h>

//default text colors can be found in wincon.h
static inline void WRPG_SetTextColor(WORD colors) {
  HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
  
  SetConsoleTextAttribute(hConsole, colors);
}

static inline void WRPG_PressAnyKeyToContinue() {
  //change text color to white
  WRPG_SetTextColor(FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN);

  printf("\n\nPress any key to continue \n");

  while (!kbhit()){}

  return;
}


#endif