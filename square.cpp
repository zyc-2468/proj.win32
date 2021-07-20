#include"square.h"

Mygraph::Mygraph(int id) {
	if (id == 0) {
		//squares type: 0 none 1: wall 2:strong wall 3: water 4: on campfire 5: off campfire
		for (int i = 0; i < 20; i++)squares[i][0].type = 2;
		for (int i = 0; i < 20; i++)squares[i][42].type = 2;
		for (int j = 0; j < 43; j++)squares[0][j].type = 2;
		for (int j = 0; j < 43; j++)squares[19][j].type = 2;
		for (int i = 3; i < 10; i++)squares[i][5].type = 1;
		for (int i = 7; i < 13; i++)squares[i][7].type = 1;
		for (int i = 6; i < 12; i++)squares[i][10].type = 1;
		for (int i = 4; i < 9; i++)squares[i][15].type = 1;
		for (int i = 9; i < 10; i++)squares[i][18].type = 1;
		for (int i = 4; i < 12; i++)squares[i][2].type = 1;
		for (int j = 10; j < 19; j++)squares[2][j].type = 1;
		for (int j = 8; j < 22; j++)squares[5][j].type = 1;
		for (int j = 4; j < 11; j++)squares[7][j].type = 1;
		for (int j = 5; j < 9; j++)squares[10][j].type = 1;
		for (int j = 9; j < 16; j++)squares[13][j].type = 1;
		//0:red 1:yellow 2:pink 3:blue 4:green
		squares[7][3].door1 = Mydoor(1, 3, 1);
		squares[5][3].door1 = Mydoor(1, 0, 1);
		squares[9][3].door1 = Mydoor(1, 4, 2);
		squares[7][17].button = Mybutton(1, 3, 7, 3);
		squares[7][27].button = Mybutton(1, 4, 9, 3);
		squares[7][29].button = Mybutton(1, 4, 9, 3);
		squares[11][20].candle = Mycandle(1, 5, 3);
		squares[6][20].type = 4;
		squares[13][19].type = 3;
		squares[12][19].type = 3;
		squares[11][19].type = 3;
		squares[10][19].type = 3;
		squares[5][20].type = 0;
		squares[13][1].type = 6;
		squares[3][8].word = "This is a note.";
		iniarrow.push_back(point(2, 2));
		inibomb.push_back(point(2, 3));
		inibox.push_back(point(2, 4));
		iniblood.push_back(point(2, 5));
		inifirearrow.push_back(point(2, 6));
		boxnum = 10;
		bombnum = 10;
		arrownum = 10;
		firearrownum = 10;
		win = point(10, 30);
	}
	else if (id == 1) {

	}
	else {

	}
}