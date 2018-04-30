#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <iterator>
#include <algorithm>
#include <functional>
#include <vector>
#include <ctime>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "game.h"
using namespace std;

int main()
{
	srand(time(NULL));
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTitle(L"ALIENS GAME");
			SMALL_RECT mywindow = {0,0, col-1, row-1};
			SetConsoleWindowInfo(hStdOut, TRUE, &mywindow);
			COORD bufferSize = {col*row};
			SetConsoleScreenBufferSize(hStdOut, bufferSize);
			DWORD screen_color = BACKGROUND_BLUE ;
			SetConsoleTextAttribute(hStdOut, screen_color);
			
			CONSOLE_SCREEN_BUFFER_INFO csbinfo;
			GetConsoleScreenBufferInfo(hStdOut, &csbinfo);

	game mygame(hStdOut, csbinfo);
	mygame.play();
	return 0;

}