#ifndef _WALL_H_
#define _WALL_H_

#include"library.h"


class Mywall {
public:
	int type = 0;
};


class Mygraph {
public:
	Mywall walls[16][24];
	Mygraph();
};



#endif

