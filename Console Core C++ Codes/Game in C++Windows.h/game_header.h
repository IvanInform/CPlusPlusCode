#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <vector>
#include <ctime>
#include <string.h>
#include <string>
#include <chrono>
using namespace std;

const int col = 60;
const int row = 40;
class game_header{
	WORD header_text;
	vector<string> letterA;
	vector<string> letterL;
	vector<string> letterI;
	vector<string> letterE;
	vector<string> letterN;
	vector<string> letterS;
	vector<string>letterW;
	vector<string>letterO;
	vector<string>letterT;
	vector<string>exclaim;
	COORD let_pos;
	public:
	game_header();
	void header_draw(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbiInfo);
	void clear_screen(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo);
	void won_footer(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbiInfo);
	void lost_footer(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbiInfo);
};
game_header::game_header(){
	header_text = FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE /*| BACKGROUND_INTENSITY*/;
	letterA.push_back(string("    #     "));
	letterA.push_back(string("   # #   "));
	letterA.push_back(string("  #####   "));
	letterA.push_back(string(" #     #  "));
	letterA.push_back(string("#       # "));
	letterL.push_back(string(" #        "));
	letterL.push_back(string(" #        "));
	letterL.push_back(string(" #        "));
	letterL.push_back(string(" #        "));
	letterL.push_back(string(" ######## "));
	letterI.push_back(string("   ###    "));
	letterI.push_back(string("    #     "));
	letterI.push_back(string("    #     "));
	letterI.push_back(string("    #     "));
	letterI.push_back(string("   ###    "));
	letterE.push_back(string("#######   "));
	letterE.push_back(string("#         "));
	letterE.push_back(string("#######   "));
	letterE.push_back(string("#         "));
	letterE.push_back(string("#######   "));
	letterN.push_back(string("#       # "));
	letterN.push_back(string("# #     # "));
	letterN.push_back(string("#   #   # "));
	letterN.push_back(string("#      ## "));
	letterN.push_back(string("#       #"));
	letterS.push_back(string("   ###### "));
	letterS.push_back(string("  #       "));
	letterS.push_back(string("	#  ## # "));
	letterS.push_back(string("        # "));
	letterS.push_back(string("  ######  "));
	letterW.push_back(string("#   #   # "));
	letterW.push_back(string("#   #   # "));
	letterW.push_back(string("#   #   # "));
	letterW.push_back(string("#   #   # "));
	letterW.push_back(string("  #   #   "));
	letterO.push_back(string("  #####   "));
	letterO.push_back(string("#       # "));
	letterO.push_back(string("#       # "));
	letterO.push_back(string("#       # "));
	letterO.push_back(string("  #####   "));
	letterT.push_back(string(" ######## "));
	letterT.push_back(string("    #     "));
	letterT.push_back(string("    #     "));
	letterT.push_back(string("    #     "));
	letterT.push_back(string("    #     "));
	exclaim.push_back(string("    #     "));
	exclaim.push_back(string("    #     "));
	exclaim.push_back(string("    #     "));
	exclaim.push_back(string("          "));
	exclaim.push_back(string("    #     "));
	let_pos = {0,0};
}
void game_header::clear_screen(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo)
{
	CHAR_INFO consbuffer[col*row];
	for (int i = 0; i < col*row; i++)
	{
		consbuffer[i].Char.UnicodeChar = ' ';
		consbuffer[i].Attributes = csbinfo.wAttributes;
	}
	COORD charPosition = { 0, 0 };
	SMALL_RECT writeArea = { 0, 0, col - 1, row - 1 };
	COORD bufferSize = { col, row };
	WriteConsoleOutput(whnd, consbuffer, bufferSize, charPosition, &writeArea);

}
void game_header::header_draw(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo) {
	DWORD previous_text = csbinfo.wAttributes;
	SetConsoleTextAttribute(whnd, header_text);
	let_pos = {1,10};
			//draw letter A;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterA)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 9;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterL)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 9;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterI)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 9;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterE)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 9;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterN)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 9;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterS)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}

		SetConsoleCursorPosition(whnd, { 1, 30 });
		cout << "Your spaceship defends planet from aggressive aliens. You\n have to destroy them before\
 they get to the planet. You \n can  make one shot until it destroys alien or reaches\n screen  top.\
To move your ship press arrows <UP>, <DOWN>,\n <LEFT>, <RIGHT>. To fire press <SPACE>. To QUIT press<ESC>.";
		SetConsoleTextAttribute(whnd, previous_text);
}
void game_header::won_footer(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo){
DWORD previous_text = csbinfo.wAttributes;
	SetConsoleTextAttribute(whnd, header_text);
	let_pos = {10,15};
			//draw letter A;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterW)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 10;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterO)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 10;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterN)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 10;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : exclaim)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		
		SetConsoleTextAttribute(whnd, previous_text);
}
void game_header::lost_footer(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo){

DWORD previous_text = csbinfo.wAttributes;
	SetConsoleTextAttribute(whnd, header_text);
	let_pos = {10,15};
			//draw letter A;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterL)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 10;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterO)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 10;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterS)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 10;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : letterT)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		let_pos.X += 10;
		let_pos.Y -= 5;
		//draw letter L;
		SetConsoleCursorPosition(whnd, let_pos);
		for (auto x : exclaim)
		{
			cout << x;
			let_pos.Y += 1;
			SetConsoleCursorPosition(whnd, let_pos);
		}
		
		SetConsoleTextAttribute(whnd, previous_text);

}




