#ifndef _WALL_H_
#define _WALL_H_

#include"library.h"

class point{
public:
	int i;
	int j;
	point(int i, int j) :i(i), j(j) {}
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
	Mycandle() :hascandle(0), doorpos(0, 0) {}
	Mycandle(int hascandle, int i, int j) :hascandle(hascandle), doorpos(i,j) {}
};

class Mydoor {
public:
	int hasdoor;
	int color;  //0-4: red, yellow, pink, blue,green
	int needbutton = 1;
	int nowbutton = 0;
	int status = 0;
	Mydoor() :hasdoor(0), color(0), needbutton(1),nowbutton(0),status(0) {}
	Mydoor(int hasdoor, int color, int index, int needbutton) :hasdoor(hasdoor), color(color), needbutton(needbutton),nowbutton(0),status(0) {}
};

class Mysquare {
public:
	int type = 0;
	Mycandle candle;
	Mydoor door1;
	Mydoor door2;
	Mybutton button;
	int hasbox;
};


class Mygraph {
public:
	Mysquare squares[16][24];
	Mygraph();
};

#endif

