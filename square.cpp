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
		squares[7][3].door2 = Mydoor(1, 3, 1);
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
		squares[12][19].board = Myboard(1, 1, 12, 18);
		squares[10][25].button = Mybutton(1, 5, 12, 19);

	}
	else if (id == 1) {
		for (int i = 0; i < 20; i++)squares[i][0].type = 2;
		for (int i = 0; i < 20; i++)squares[i][42].type = 2;
		for (int j = 0; j < 43; j++)squares[0][j].type = 2;
		for (int j = 0; j < 43; j++)squares[19][j].type = 2;
		for (int j = 1; j <=5; j++) {
			squares[4][j].type = 6;//tree
		}
		for (int i = 1; i <= 4; i++) {
			squares[i][5].type = 6;
		}
		inifirearrow.push_back(point(3, 3));
		for (int i = 1; i <= 4; i++) {
			squares[i][6].type = 1;
		}
		for (int i = 5; i <= 14; i++) {
			squares[i][6].type = 2;
		}
		squares[15][3].door1 = Mydoor(1, 0, 1);
		for (int i = 1; i <= 2; i++) {
			squares[15][i].type = 1;
		}
		for (int i =4; i <= 6; i++) {
			squares[15][i].type = 1;
		}
		for (int j = 1; j <= 5; j++) {
			squares[10][j].type = 1;
		}
		inibomb.push_back(point(8, 2));
		inifirearrow.push_back(point(14,5));
		squares[18][3].candle = Mycandle(1, 15,3);
		inibox2.push_back(point(14,3));
		for (int i = 18; i >= 10; i--) {
			squares[i][8].type = 3;
		}
		squares[10][7].type = 3;
		inibomb.push_back(point(18, 7));
		squares[17][9].button = Mybutton(1, 3, 8,7);
		squares[8][7].door1 = Mydoor(1, 3, 1);
		for (int i = 18; i >= 8; i--) {
			squares[i][10].type = 6;
		}
		squares[8][9].type = 6;
		squares[8][8].type = 6;
		for (int i = 7; i >= 3; i--) {
			squares[i][8].type = 1;
		}
		squares[18][9].word = "Be quick!";
		//squares[18][12].button = Mybutton(1, 5, );
		squares[16][11].type = 3;
		squares[16][12].type = 3;
		squares[16][13].type = 3;
		squares[15][13].door2 = Mydoor(1, 4, 2);
		squares[16][12].board = Myboard(1, 1, 15, 12);
		squares[18][12].button = Mybutton(1, 4, 15, 13);
		squares[1][7].button = Mybutton(1, 5, 16, 12);
		squares[17][13].type = 2;
		squares[18][13].type = 2;
		for (int i = 14; i >= 1; i--) {
			squares[i][13].type = 2;
		}
		inibox.push_back(point(15, 11));
		inibomb.push_back(point(7, 9));
		inibomb.push_back(point(15, 12));
		squares[5][12].button = Mybutton(1, 4, 15, 13);
		squares[5][15].type = 4;
		iniarrow.push_back(point(7, 14));
		iniarrow.push_back(point(8, 14));
		inibomb.push_back(point(7, 15));
		squares[3][15].type = 3;
		squares[3][14].type = 3;
		squares[3][16].type = 3;
		squares[1][15].candle = Mycandle(1, 17, 15);
		squares[1][15].candle.state = 1;
		for (int i = 17; i >= 1; i--) {
			squares[i][17].type = 2;
		}
		squares[17][15].door1 = Mydoor(1, 0, 1);
		squares[17][14].type = 6;
		squares[17][16].type = 6;
		squares[16][16].button = Mybutton(1, 5, 6, 16);

		squares[6][15].type = 3;
		squares[6][14].type = 3;
		squares[6][16].type = 3;

		squares[6][16].board = Myboard(1, 1, 7, 16);
		iniblood.push_back(point(17, 18));
		iniblood.push_back(point(16, 18));
		iniblood.push_back(point(15, 18));
		inifirearrow.push_back(point(14, 19));
		squares[13][19].type = 3;
		inibomb.push_back(point(13, 18));
		squares[13][18].button = Mybutton(1, 1, 13, 21);
		squares[12][18].type = 3;
		inibomb.push_back(point(12, 19));
		squares[12][19].button = Mybutton(1, 2, 5, 21);
		squares[11][19].type = 3;
		inibomb.push_back(point(11, 18));
		squares[11][18].button = Mybutton(1, 3, 6, 25);
		squares[10][18].type = 3;
		inibomb.push_back(point(10, 19));
		squares[10][19].button = Mybutton(1, 4, 15,25);
		squares[9][19].type = 3;
		inibomb.push_back(point(9, 18));
		squares[9][18].button = Mybutton(1, 5, 16, 32);
		squares[17][20].type = 6;
		squares[18][20].type = 6;
		for (int i = 15; i >= 8; i--) {
			squares[i][20].type = 6;
		}
		squares[8][19].type = 6;
		squares[8][18].type = 6;
		squares[13][21].door1 = Mydoor(1, 1, 1);
		squares[13][22].type = 1;
		squares[5][21].door1 = Mydoor(1, 2, 1);
		squares[7][20].type = 2;
		squares[6][20].type = 2;
		squares[5][20].type = 2;
		squares[5][22].type = 2;
		squares[6][25].door1 = Mydoor(1, 3, 1);
		squares[15][24].type = 3;
		squares[15][26].type = 3;
		squares[15][25].door1 = Mydoor(1, 4, 1);
		squares[6][24].type = 1;
		squares[6][26].type = 1;
		
		

		for (int i = 18; i >= 2; i--) {
			squares[i][23].type = 1;
		}
		for (int i = 17; i >= 1; i--) {
			squares[i][27].type = 6;
		}
		for (int i = 18; i >= 1; i--) {
			squares[i][32].type = 3;
		}
		squares[16][32].board = Myboard(1, 1, 16, 31);
		for (int i = 18; i >= 10; i--) {
			squares[i][36].type = 3;
		}
		for (int i = 1; i <= 4; i++) {
			squares[i][38].type = 3;
		}
		for (int j = 38; j <= 41; j++) {
			squares[4][j].type = 3;
		}
		for (int j = 33; j <= 37; j++) {
			squares[8][j].type = 3;
		}
		for (int i = 17; i >= 6; i--) {
			squares[i][39].type = 3;
			squares[i][40].type = 3;
		}
		squares[7][41].type = 3;
		squares[8][41].type = 3;
		inibox.push_back(point(9, 41));
		win = point(1,41);
		for (int i = 8; i >= 1; i--) {
			squares[i][36].type = 3;
		}
	}
	else {

	}
}