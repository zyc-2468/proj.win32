#ifndef _WALL_H_
#define _WALL_H_

#include"library.h"

class point{
public:
	int i;
	int j;
	point(int i, int j) :i(i), j(j) {}
	point() {}
	bool operator==(const point& p) {
		return this->i == p.i && this->j == p.j;
	}
};

class Mybutton {
public:
	int hasbutton;
	int color;
	point doorpos;
	Mybutton() :hasbutton(0), color(0), doorpos(0,0) {}
	Mybutton(int hasbutton, int color, int i, int j) :hasbutton(hasbutton), color(color), doorpos(i,j) {}
};

class Mycandle {
public:
	int hascandle;
	point doorpos;
	int state = 0;
	Mycandle() :hascandle(0), doorpos(0, 0) {}
	Mycandle(int hascandle, int i, int j) :hascandle(hascandle), doorpos(i,j) {}
	int notlight() {
		return hascandle == 1 && state == 0;
	}
	int light() {
		return hascandle == 1 && state == 1;
	}
};

class Myboard {
public :
	int hasboard;
	int state = 0;
	int needbutton = 1;
	int nowbutton = 0;
	int toi = 0;
	int toj = 0;
	Myboard() :hasboard(0), needbutton(1), nowbutton(0), state(0) {}
	Myboard(int hasboard, int needbutton, int toi, int toj) :hasboard(hasboard), needbutton(needbutton), nowbutton(0), state(0),toi(toi),toj(toj) {}
	int cango() {
		return hasboard == 1 && state == 1;
	}
};

class Mydoor {
public:
	int hasdoor;
	int color;  //0-4: red, yellow, pink, blue,green
	int needbutton = 1;
	int nowbutton = 0;
	int status = 0;
	Mydoor() :hasdoor(0), color(0), needbutton(1),nowbutton(0),status(0) {}
	Mydoor(int hasdoor, int color,int needbutton) :hasdoor(hasdoor), color(color), needbutton(needbutton),nowbutton(0),status(0) {}
	int dooropen() { return hasdoor == 1 && status == 1; }
	int doorclose() { return hasdoor == 1 && status == 0; }
};

class Mysquare {
public:
	int type = 0;
	Mycandle candle;
	Mydoor door1;
	Mydoor door2;
	Mybutton button;
	int hasbox;
	string word = "";
	Myboard board;
};

class Mygraph {
public:
	Mysquare squares[20][43];
	vector<point> inibox;
	vector<point> inibox2;
	vector<point> monsters;
	vector<point>iniarrow;
	vector<point>inifirearrow;
	vector<point>inibomb;
	vector<point>iniblood;
	int boxnum = 0;
	int bombnum = 0;
	int arrownum = 0;
	int firearrownum = 0;
	point win;
	int blood = 10;

	Mygraph(int id);
	Mygraph() {}
};

#endif

