#include"square.h"

Mygraph::Mygraph() {
	for (int i = 0; i < 16; i++)squares[i][0].type = 2;
	for (int i = 0; i < 16; i++)squares[i][23].type = 2;
	for (int j = 0; j < 24; j++)squares[0][j].type = 2;
	for (int j = 0; j < 24; j++)squares[15][j].type = 2;
	for (int i = 3; i < 10; i++)squares[i][5].type = 1;
	for (int i = 7; i < 13; i++)squares[i][7].type = 1;
	for (int i = 6; i < 12; i++)squares[i][10].type = 1;
	for (int i = 4; i < 9; i++)squares[i][15].type = 1;
	for (int i = 9; i < 10; i++)squares[i][18].type = 1;
	for (int i = 3; i < 11; i++)squares[i][26].type = 1;
	for (int j = 10; j < 19; j++)squares[2][j].type = 1;
	for (int j = 8; j < 22; j++)squares[5][j].type = 1;
	for (int j = 4; j < 11; j++)squares[7][j].type = 1;
	for (int j = 5; j < 9; j++)squares[10][j].type = 1;
	for (int j = 9; j < 16; j++)squares[13][j].type = 1;
	squares[7][3].door1 = Mydoor(1, 0, 3, 1);
	squares[7][17].button = Mybutton(1, 3, 7, 3);
	squares[11][20].candle = Mycandle(1, 0, 0);
	squares[13][21].type = 4;
	squares[13][19].type = 3;
	squares[12][19].type = 3;
	squares[11][19].type = 3;
	squares[10][19].type = 3;

}