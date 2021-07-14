#include"wall.h"

Mygraph::Mygraph() {
	for (int i = 0; i < 16; i++)walls[i][0].type = 1;
	for (int i = 0; i < 16; i++)walls[i][23].type = 1;
	for (int j = 0; j < 24; j++)walls[0][j].type = 1;
	for (int j = 0; j < 24; j++)walls[15][j].type = 1;
	for (int i = 3; i < 10; i++)walls[i][5].type = 1;
	for (int i = 7; i < 13; i++)walls[i][7].type = 1;
	for (int i = 6; i < 12; i++)walls[i][10].type = 1;
	for (int i = 4; i < 9; i++)walls[i][15].type = 1;
	for (int i = 9; i < 10; i++)walls[i][18].type = 1;
	for (int i = 3; i < 11; i++)walls[i][26].type = 1;
	for (int j = 10; j < 19; j++)walls[2][j].type = 1;
	for (int j = 8; j < 22; j++)walls[5][j].type = 1;
	for (int j = 4; j < 11; j++)walls[7][j].type = 1;
	for (int j = 5; j < 9; j++)walls[10][j].type = 1;
	for (int j = 9; j < 16; j++)walls[13][j].type = 1;
	/*
	walls[6][2].type = 0;
	walls[7][6].type = 0;
	walls[9][7].type = 0;
	walls[8][10].type = 0;
	walls[5][9].type = 0;
	walls[2][17].type = 0;
	walls[5][13].type = 0;
	walls[5][20].type = 0;
	walls[11][16].type = 0;
	*/
	
}