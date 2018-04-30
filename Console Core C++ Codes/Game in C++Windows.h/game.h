#pragma once
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
#include "plane_main.h"
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_SPACE 32
#define KEY_PLUS 43
using namespace std;
extern const int col;
extern const int row;
extern run_fire fire_st = CEASE;

enum game_status { START, END };
//game_status game_st = START;
extern enum dir;
int alien::number_players;

class game{
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbinfo;
	vector<alien> foreigners;
	figure A;
	Timer tmr;
	game_header header;
	//game_status status;
	game_status game_st;
public:
	game(HANDLE hStdOut,CONSOLE_SCREEN_BUFFER_INFO csbinfo);
	void initialize();
	~game();
	void play();
	
};
game::~game(){}
game::game(HANDLE hStdOut, CONSOLE_SCREEN_BUFFER_INFO csbinfo){
	game_status status = START;
	this->hStdOut = hStdOut;
	this->csbinfo = csbinfo;
	
	foreigners.push_back(alien({ rand() % 50 + 0, 0 }, (16 * 1 + (rand() % 8 + 3))));
	foreigners.push_back(alien({ rand() % 50 + 0, 0 }, 16 * 1 + (rand() % 8 + 3)));
	foreigners.push_back(alien({ rand() % 50 + 0, 0 }, 16 * 1 + (rand() % 8 + 3)));
	foreigners.push_back(alien({ rand() % 50 + 0, 0 }, 16 * 1 + (rand() % 8 + 3)));
	foreigners.push_back(alien({ rand() % 50 + 0, 0 }, 16 * 1 + (rand() % 8 + 3)));
	foreigners.push_back(alien({ rand() % 50 + 0, 0 }, 16 * 1 + (rand() % 8 + 3)));
	foreigners.push_back(alien({ rand() % 50 + 0, 0 }, 16 * 1 + (rand() % 8 + 3)));
	foreigners.push_back(alien({ rand() % 50 + 0, 0 }, 16 * 1 + (rand() % 8 + 3)));
	foreigners[0].set_count(8);
	game_status game_st = START;
	}
void game::initialize(){
		}
void game::play(){
	header.clear_screen(hStdOut, csbinfo);
	header.header_draw(hStdOut, csbinfo);
	getch();
	header.clear_screen(hStdOut, csbinfo);
	A.draw(hStdOut, csbinfo);
	int iKey = 50;

	do
	{
		if (kbhit()){
			iKey = getch();
			switch (iKey)
			{
			case KEY_ARROW_RIGHT:
			{if (A.get_right() > csbinfo.srWindow.Right)
			{
				cout << "\a";
			}
			else {
				A.move(hStdOut, RIGHT, csbinfo, fire_st);

			}
			}
				break;
			case KEY_ARROW_LEFT:
			{ if (A.get_left() == csbinfo.srWindow.Left)
			{
				cout << "\a";
			}

			else {
				A.move(hStdOut, LEFT, csbinfo, fire_st);
			}
			break;
			case KEY_PLUS:
				foreigners[0].move(hStdOut, csbinfo, A);
				break;
			case KEY_SPACE:
			{
							  fire_st = FIRE;
			}
				break;

			default:
				break;
			}

			}
		}

		foreigners[0].move(hStdOut, csbinfo, A);
		foreigners[1].move(hStdOut, csbinfo, A);

		double t = tmr.elapsed();

		if (t > 10)
		{
			foreigners[2].move(hStdOut, csbinfo, A);
			foreigners[3].move(hStdOut, csbinfo, A);
		}
		if (t> 20){
			foreigners[4].move(hStdOut, csbinfo, A);
			foreigners[5].move(hStdOut, csbinfo, A);

		}
		if (t> 30){
			foreigners[6].move(hStdOut, csbinfo, A);
			foreigners[7].move(hStdOut, csbinfo, A);

		}
		if (fire_st == FIRE){
			A.fire_gun(hStdOut, csbinfo, fire_st);

		}
		for (int i = 0; i < foreigners.size(); i++){
			if (check_coor(foreigners[i].get_fcoord(), A.get_collide())){
				foreigners[i].set_flag(false); foreigners[i].set_destroy(true); foreigners[i].less_count();
				fire_st = CEASE; A.reset_fire();
			}
			if (foreigners[i].get_fcoord()[0].Y == (csbinfo.srWindow.Bottom - 2))
			{
				game_st = END;
			}
		}
		if (foreigners[0].get_count() == 0)
		{
			break;
		}
		if (game_st == END)
		{
			break;
		}

	} while (iKey != 27);
	SetConsoleCursorPosition(hStdOut, { 0, 38 }); cout << csbinfo.srWindow.Bottom;
	if (foreigners[0].get_count() == 0)
	{
		header.clear_screen(hStdOut, csbinfo);
		header.won_footer(hStdOut, csbinfo);
	}
	else {
		header.clear_screen(hStdOut, csbinfo);
		header.lost_footer(hStdOut, csbinfo);
	}
	getch();

}