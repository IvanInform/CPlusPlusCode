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
#include "game_header.h"

using namespace std;
static enum run_fire{ FIRE, CEASE };
run_fire fire_st;
class alien;
static enum dir{ RIGHT, LEFT }direction;

bool operator==(const COORD &left, const COORD&right)
{
	return (left.X == right.X)&& (left.Y == right.Y);
}

bool check_coor( vector< COORD>&x, COORD&y )
{
	for (vector<COORD>::iterator it = x.begin(); it != x.end(); it++)
	{
		if (*it == y)
			return true;
	}

}
class Timer
{
public:
	Timer() : beg_(clock_::now()) {}
	void reset() { beg_ = clock_::now(); }
	double elapsed() const {
		return std::chrono::duration_cast<second_>
			(clock_::now() - beg_).count();
	}

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::ratio<1> > second_;
	std::chrono::time_point<clock_> beg_;
};
void gotoXY_(HANDLE hwnd, int x, int y){
	COORD my_position; my_position.X = x;
	my_position.Y = y;
	SetConsoleCursorPosition(hwnd, my_position);
}
class figure{
	vector<string> data;
	string space;
	COORD position;
	int len;
	COORD top_gun;
	DWORD figure_text;
	DWORD gun_text;
	int fire_time;
	int fire_top;
	int fire_count;
	COORD collide;
	friend class alien;
public:
	figure();
	~figure();
	void draw(HANDLE hwnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo);
	void move(HANDLE hwnd, dir some_dir, CONSOLE_SCREEN_BUFFER_INFO csbinfo, run_fire &fire_st);
	void fire();
	int get_right(){ return position.X+len; }
	int get_left(){ return position.X; }
	COORD get_top(){ return top_gun; }
	void draw_fire(HANDLE hwnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo);
	void fire_gun(HANDLE hwnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo, run_fire& fire_st);
	int get_fire_top(){ return top_gun.Y; }
	void set_fire_top(){ top_gun.Y = -1; }
	void reset_fire(){ top_gun = { (position.X + 4), (position.Y - 1) }; collide = {top_gun.X, top_gun.Y}; }
	void destroy_fire(HANDLE hwnd, COORD dest);
	COORD get_collide(){ return collide; }
};
figure::figure(){
	string plane0 = "&   &   &";
	string plane1("&&&&&&&&&");
	string plane2("&&&&&&&&&");
	string plane3("&&&&&&&&&");
	
	data.push_back(plane0);
	data.push_back(plane1); data.push_back(plane2); data.push_back(plane3);
	 space = " "; 
	len = data[0].size();
	position = { 20,36 };
	top_gun = { (position.X + 4), (position.Y-1) };
	//int color=16*BackGroundColor+ForeGroundColor;
	int color = 16 * 1 + 7;
	figure_text = color; 
	fire_time = 500;
	fire_top = top_gun.Y;
	gun_text = FOREGROUND_GREEN | FOREGROUND_INTENSITY|BACKGROUND_BLUE;
	fire_count = 0;
	collide = {0,0};
}
figure::~figure(){}

void figure::draw(HANDLE hwnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo){
	COORD draw_pos = position;
	DWORD previous_text=csbinfo.wAttributes;
	SetConsoleTextAttribute(hwnd, figure_text);
	for (int i = 0; i < data.size(); i++)
	{		
		gotoXY_(hwnd,draw_pos.X, draw_pos.Y);
		cout << data[i];
		draw_pos.Y += 1;
	}
	SetConsoleTextAttribute(hwnd, previous_text);
}

void figure::move(HANDLE hwnd, dir direction, CONSOLE_SCREEN_BUFFER_INFO csbinfo, run_fire &fire_st){
	
	if (direction == RIGHT){
		COORD space_pos = position;
		position.X += 1; 
		draw(hwnd,csbinfo);
		if (top_gun.Y == -1 || fire_count == 0||fire_st==CEASE){
			reset_fire();
		}
		string space = " ";
		for (int i = 0; i < 4; i++)
		{
			SetConsoleCursorPosition(hwnd, space_pos);
			cout << space;
			space_pos.Y += 1;
		}
	}
	else {
		COORD space_pos = position;
		int len = data[0].size();
		space_pos.X += len - 1;
		position.X -= 1; 
		draw(hwnd, csbinfo);
		if (top_gun.Y == -1 || fire_count == 0 || fire_st == CEASE){
			reset_fire();
		}
		string space = " ";
		for (int i = 0; i < 4; i++)
		{
			SetConsoleCursorPosition(hwnd, space_pos);
			cout << space;
			space_pos.Y += 1;
		}
	}
}
void figure::draw_fire(HANDLE hwnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo){
	DWORD pr_color = csbinfo.wAttributes;
	SetConsoleTextAttribute(hwnd, gun_text);
	
		gotoXY_(hwnd, top_gun.X, top_gun.Y);
		cout << '@';

	collide = { top_gun.X, top_gun.Y };

	SetConsoleTextAttribute(hwnd, pr_color);


}
void figure::destroy_fire(HANDLE hwnd, COORD dest){
	int temp = dest.Y;
	for (int i = 0; i < 2; i++)
	{
		gotoXY_(hwnd, dest.X, temp);
		cout << " ";
		temp += 1;
	}
	
}
void figure::fire_gun(HANDLE hwnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo, run_fire &fire_st){
	
	fire_count = 1;
	if (fire_time > 0) {
		fire_time--;
		if (fire_time % 1000 != 0)return;
	}
	else {
		fire_time = rand() % 1500 + 50000;
	}
	if (fire_st == FIRE){
		draw_fire(hwnd, csbinfo); 
		if (top_gun.Y == -1){
			destroy_fire(hwnd, top_gun);
			reset_fire(); fire_st = CEASE;
		}
		
		int del = top_gun.Y;
		del += 1;
		gotoXY_(hwnd, top_gun.X, del);
		cout << " ";
		top_gun.Y -= 1;
	}
}



class alien{
	vector<string>data;
	COORD alien_pos;
	DWORD alien_text;
	int alien_top;
	int moveTime;
	vector<COORD> front_coord;
	bool flag_to_move;
	bool flag_destroy;
	static int number_players;
	public:
	alien(COORD position, DWORD text_color);
	~alien();
	void draw(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo, COORD pos);
	void move(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo, figure&obj);
	int gettop(){ return alien_top; }
	void destroy(HANDLE whnd );
	
	vector<COORD> get_fcoord(){ return front_coord; }
	COORD get_alienpos(){ return alien_pos; }
	void set_flag(bool x){ flag_to_move = x; }
	void set_destroy(bool x){ flag_destroy = x; }
	bool get_destroy(){ return flag_destroy; }
	static void less_count(){ number_players--; }
	static int get_count(){ return number_players; }
	static void set_count(int x){ number_players = x; }
	int get_any_front(){ return front_coord[0].Y; }
};

alien::alien(COORD position, DWORD text_color){
	moveTime = 500;
	alien_pos = {position.X,position.Y};
	alien_top = 0;
	alien_text = text_color;
	data.push_back(string("***+***")); data.push_back(string("*******"));
	int a = alien_pos.X;
	int b = alien_pos.Y;
	COORD arr[7]= { { a, b+1 }, {a+1, b+1  }, {a+2, b+1 }, {a+3, b+1}, {a+4, b+1}, {a+5, b+1}, {a+6, b+1} };
	front_coord.assign(arr, arr+7);
	flag_to_move = true;
}
alien::~alien(){}
void alien::draw(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo, COORD pos)
{
	DWORD previous_text = csbinfo.wAttributes;
	SetConsoleTextAttribute(whnd, alien_text);
	COORD temp = pos;
	for (int i = data.size() - 1; i >= 0; i--)
	{
		gotoXY_(whnd, temp.X, temp.Y);
		cout << data[i];
		temp.Y += 1;
	}
	int a = temp.X; int b = temp.Y;
	for (int i = 0; i < 7; i++)
	{
		front_coord[i] = {a+i, b-1};
	}
	SetConsoleTextAttribute(whnd, previous_text);
}

void alien::move(HANDLE whnd, CONSOLE_SCREEN_BUFFER_INFO csbinfo, figure&obj)
{
	if (moveTime > 0) {
		moveTime--;
		if (moveTime % 3000 != 0)return;
	}
	else {
		moveTime = rand() % 1500 + 1000000;
	}
	if (flag_to_move == false){ 
		if (flag_destroy == true) { destroy(whnd); flag_destroy = false; }
		return; }
	if (alien_top < csbinfo.srWindow.Bottom){
		draw(whnd, csbinfo, alien_pos);
	
		alien_top = alien_pos.Y + 2;

		gotoXY_(whnd, alien_pos.X, alien_pos.Y - 1);
		for (int i = 0; i < data[0].size(); i++)
		{
			cout << " ";
		}alien_pos.Y += 1; 
			
	}
}
void alien::destroy(HANDLE whnd){
	if (flag_destroy == true){
		COORD temp = alien_pos;
		string st = "              ";
		for (int i = 0; i < 3; i++)
		{
			gotoXY_(whnd, temp.X, temp.Y - 1);
			cout << st;
			temp.Y += 1;
		}
	}
}




