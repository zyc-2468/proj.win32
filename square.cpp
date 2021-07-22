#include"square.h"

void Mygraph::settype(int i1, int i2, int j1, int j2, int t1)
{
	for (int i = i1; i <= i2; i++)
		for (int j = j1; j <= j2; j++)
			squares[i][j].type = t1;
}

void Mygraph::settype2(int i1, int i2, int j1, int j2, int t1)
{
	for (int i = i1; i <= i2; i++)squares[i][j1].type = t1;
	for (int i = i1; i <= i2; i++)squares[i][j2].type = t1;
	for (int j = j1; j <= j2; j++)squares[i1][j].type = t1;
	for (int j = j1; j <= j2; j++)squares[i2][j].type = t1;
}

Mygraph::Mygraph(int id) {
	if (id == 0) {
		inii = 1;
		inij = 1;
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
		squares[3][8].wordsize = 12;
		//squares[3][8].word = "This is.";
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
		squares[12][19].board = Myboard(1, 1);
		squares[10][25].button = Mybutton(1, 5, 12, 19);


	}
	else if (id==4) {
		settype2(0, 19, 0, 42,2);
		settype2(0, 10, 0, 10, 2);
		settype2(10, 19, 0, 10, 2);
		settype2(0, 10, 10, 20, 2);
		settype2(10, 19, 10, 20, 2);
		settype2(0, 10, 20, 27, 2);
		settype2(10, 19, 20, 27, 2);
		settype2(0, 10, 27, 35, 2);
		settype2(10, 19, 27, 35, 2);
		settype2(0, 10, 35, 42, 2);
		settype2(10, 19, 35, 42, 2);
		squares[10][5].type = 1;
		inibomb.push_back(point(5, 5));
		inibox.push_back(point(15, 5));
		inibox2.push_back(point(15, 8));
		squares[15][10].door2 = Mydoor(1, 3, 2);
		squares[15][10].type = 0;
		squares[17][3].button = Mybutton(1, 3, 15, 10);
		squares[17][7].button = Mybutton(1, 3, 15, 10);
		squares[10][15].door1 = Mydoor(1, 0, 1);
		squares[10][15].type = 0;
		squares[18][12].candle = Mycandle(1, 10, 15);
		inifirearrow.push_back(point(12, 18));
		inibox2.push_back(point(6, 13));
		squares[3][20].type = 3;
		squares[10][23].door1 = Mydoor(1, 4, 1);
		squares[10][23].type = 0;
		squares[8][22].button = Mybutton(1, 4, 10, 23);
		inibomb.push_back(point(7, 26));
		squares[15][27].type = 6;
		inifirearrow.push_back(point(12, 22));
		squares[10][34].door1 = Mydoor(1, 1, 1);
		squares[10][34].type = 0;
		squares[18][28].button = Mybutton(1, 1, 10, 34);
		iniarrow.push_back(point(15, 29));
		inibomb.push_back(point(16, 30));
		squares[1][41].button = Mybutton(1, 2, 5, 35);
		squares[5][35].door2 = Mydoor(1, 2, 1);
		squares[5][35].type = 0;
		squares[1][35].type = 3;
		squares[1][35].board = Myboard(1, 1);
		squares[6][28].button = Mybutton(1, 5, 1, 35);
		inibomb.push_back(point(3, 29));
		inibox.push_back(point(7, 32));
		settype(13, 17, 36, 41, 3);
		win = point(18, 39);
		squares[10][39].door1 = Mydoor(1, 0, 1);
		squares[10][39].type = 0;
		squares[5][41].type = 4;
		squares[9][41].candle = Mycandle(1, 10, 39);
		iniarrow.push_back(point(3, 38));
		inibox.push_back(point(4, 38));
		inibox.push_back(point(4, 39));
		inibox.push_back(point(5, 38));
		inibox.push_back(point(5, 39));
		inibox.push_back(point(6, 39));
		squares[5][3].word = "Put bomb near the\n breakable wall";
		squares[15][3].word = "Put boxes onto\n the buttons";
		squares[15][13].word = "Light up\n the candle";
		squares[5][13].word = "Fill the\n water";
		squares[5][23].word = "Use bomb to\n press the button.";
		squares[15][23].word = "Fire the\n tree";
		squares[15][30].word = "Use arrow to\n put off the bomb";
		squares[5][30].word = "Use bomb to\n push the box";
		squares[5][37].word = "Campfire can light\n up the arrow";
		squares[11][39].word = "See the\n victory!";
		for (int j = 35; j <= 42; j++) {
			squares[2][j].type = 2;
		}
		

	}
	else if (id == 1) {
		inii = 1;
		inij = 1;
		for (int i = 0; i < 20; i++)squares[i][0].type = 2;
		for (int i = 0; i < 20; i++)squares[i][42].type = 2;
		for (int j = 0; j < 43; j++)squares[0][j].type = 2;
		for (int j = 0; j < 43; j++)squares[19][j].type = 2;
		for (int j = 1; j <= 5; j++) {
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
		for (int i = 4; i <= 6; i++) {
			squares[15][i].type = 1;
		}
		for (int j = 1; j <= 5; j++) {
			squares[10][j].type = 1;
		}
		inibomb.push_back(point(8, 2));
		inifirearrow.push_back(point(14, 5));
		squares[18][3].candle = Mycandle(1, 15, 3);
		inibox2.push_back(point(14, 3));
		for (int i = 18; i >= 10; i--) {
			squares[i][8].type = 3;
		}
		squares[10][7].type = 3;
		inibomb.push_back(point(18, 7));
		squares[17][9].button = Mybutton(1, 3, 8, 7);
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
		squares[16][12].board = Myboard(1, 1);
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

		squares[6][16].board = Myboard(1, 1);
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
		squares[10][19].button = Mybutton(1, 4, 15, 25);
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
		squares[16][32].board = Myboard(1, 1);
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
		win = point(1, 41);
		for (int i = 8; i >= 1; i--) {
			squares[i][36].type = 3;
		}
	}
	else if (id == 3) {

		settype(0, 19, 0, 0, 2);
		settype(0, 0, 0, 42, 2);
		settype(19, 19, 0, 42, 2);
		settype(0, 19, 42, 42, 2);
		settype(1, 1, 1, 9, 2);
		settype(1, 1, 11, 19, 2);
		settype(9, 9, 1, 9, 2);
		settype(9, 9, 11, 19, 2);
		settype(11, 11, 1, 9, 2);
		settype(11, 11, 11, 19, 2);

		settype(9, 9, 22, 31, 2);
		settype(9, 9, 33, 41, 2);
		settype(11, 11, 22, 31, 2);
		settype(11, 11, 33, 41, 2);

		settype(1, 9, 1, 1, 2);
		settype(1, 9, 19, 19, 2);
		settype(1, 9, 22, 22, 2);
		settype(1, 9, 20, 20, 2);

		settype(11, 18, 22, 22, 2);
		settype(11, 18, 20, 20, 2);

		settype(13, 13, 2, 9, 2);
		settype(13, 13, 11, 18, 2);
		settype(17, 17, 2, 9, 2);
		settype(17, 17, 11, 18, 2);


		settype(15, 16, 2, 4, 2);
		settype(15, 16, 16, 18, 2);
		settype(13, 15, 6, 9, 2);
		settype(13, 15, 11, 14, 2);


		settype(3, 7, 3, 9, 2);

		settype(3, 7, 11, 17, 2);
		settype(6, 6, 8, 12, 0);

		squares[4][37].type = 2;


		settype(13, 13, 24, 34, 2);
		squares[12][34].type = 2;
		squares[14][31].type = 2;

		settype(13, 18, 38, 38, 2);
		settype(12, 17, 40, 40, 2);
		//strong wall part

		squares[12][9].type = 3;
		squares[12][11].type = 3;
		squares[18][9].type = 3;
		squares[18][11].type = 3;
		squares[13][19].type = 3;
		squares[7][10].type = 3;
		squares[1][28].type = 3;
		squares[1][31].type = 3;
		squares[5][31].type = 3;
		squares[15][34].type = 3;

		settype(3, 9, 21, 21, 3);
		settype(2, 2, 4, 4, 3);
		settype(2, 2, 16, 17, 3);

		settype(15, 18, 26, 26, 3);
		settype(14, 14, 27, 31, 3);

		settype(8, 8, 24, 31, 3);
		settype(2, 8, 24, 24, 3);
		settype(2, 2, 24, 38, 3);

		settype(4, 4, 26, 33, 3);
		settype(6, 6, 26, 33, 3);


		settype(4, 8, 33, 33, 3);

		settype(1, 5, 35, 35, 3);
		settype(1, 5, 38, 38, 3);
		settype(5, 5, 35, 38, 3);

		settype(6, 6, 38, 41, 3);

		settype(6, 8, 39, 39, 3);
		squares[5][33].type = 0;
		//water part

		squares[12][15].type = 6;
		squares[2][10].type = 6;
		squares[5][27].type = 6;
		squares[3][32].type = 6;
		//tree part

		squares[18][29].type = 1;
		squares[15][31].type = 1;
		//wall part

		squares[12][12].candle = Mycandle(1, 13, 21);
		squares[13][39].candle = Mycandle(1, 13, 21);
		squares[1][21].candle = Mycandle(1, 13, 21);
		squares[13][39].candle.state = 1;
		//candle part

		squares[9][10].door1 = Mydoor(1, 1, 1);
		squares[11][10].door1 = Mydoor(1, 2, 3);
		squares[11][32].door1 = Mydoor(1, 3, 1);
		squares[11][21].door1 = Mydoor(1, 4, 1);

		//normal door part

		settype(15, 18, 25, 25, 4);
		squares[12][10].type = 4;
		squares[5][32].type = 4;
		squares[18][5].type = 4;
		squares[2][5].type = 4;
		squares[2][15].type = 4;
		//campfire part


		squares[8][23].button = Mybutton(1, 1, 9, 10);
		squares[6][8].button = Mybutton(1, 2, 11, 10);
		squares[6][12].button = Mybutton(1, 2, 11, 10);
		squares[1][10].button = Mybutton(1, 2, 11, 10);
		squares[12][13].button = Mybutton(1, 3, 11, 32);
		squares[12][41].button = Mybutton(1, 4, 11, 21);
		//button part

		squares[7][10].board = Myboard(1, 1);
		squares[8][10].button = Mybutton(1, 5, 7, 10);

		squares[14][31].board = Myboard(1, 1);
		squares[18][37].button = Mybutton(1, 5, 14, 31);

		squares[14][29].board = Myboard(1, 1);
		squares[17][37].button = Mybutton(1, 5, 14, 29);

		squares[14][27].board = Myboard(1, 1);
		squares[18][35].button = Mybutton(1, 5, 14, 27);

		//board part


		squares[13][21].door1 = Mydoor(1, 0, 2);
		// fire door part


		inibomb.push_back(point(18, 19));
		inibomb.push_back(point(6, 10));
		inibomb.push_back(point(18, 27));
		inibomb.push_back(point(16, 28));
		inibomb.push_back(point(17, 30));
		inibomb.push_back(point(16, 32));
		inibomb.push_back(point(15, 32));
		inibomb.push_back(point(15, 35));
		inibomb.push_back(point(18, 39));
		inibomb.push_back(point(18, 40));
		inibomb.push_back(point(18, 41));


		inibomb.push_back(point(10, 10));
		//bomb part


		inibox2.push_back(point(6, 23));
		inibox2.push_back(point(6, 9));
		inibox2.push_back(point(6, 11));
		inibox2.push_back(point(6, 34));
		inibox2.push_back(point(6, 35));
		inibox2.push_back(point(6, 37));

		inibox2.push_back(point(5, 10));
		inibox2.push_back(point(5, 41));
		inibox2.push_back(point(4, 39));
		inibox2.push_back(point(3, 39));
		inibox2.push_back(point(3, 40));
		inibox2.push_back(point(2, 39));
		inibox2.push_back(point(1, 40));

		inibox2.push_back(point(7, 35));
		inibox2.push_back(point(7, 37));
		inibox2.push_back(point(7, 38));
		inibox2.push_back(point(7, 41));
		inibox2.push_back(point(8, 36));


		inibox2.push_back(point(12, 16));
		inibox2.push_back(point(17, 19));


		inibox2.push_back(point(15, 28));
		inibox2.push_back(point(18, 28));
		inibox2.push_back(point(16, 30));
		inibox2.push_back(point(17, 31));
		inibox2.push_back(point(15, 33));
		inibox2.push_back(point(16, 35));
		inibox2.push_back(point(17, 41));
		//box part

		iniblood.push_back(point(17, 10));
		iniblood.push_back(point(16, 10));
		//life part

		iniarrow.push_back(point(7, 28));
		iniarrow.push_back(point(7, 30));
		iniarrow.push_back(point(8, 16));

		iniarrow.push_back(point(14, 2));
		iniarrow.push_back(point(15, 23));
		iniarrow.push_back(point(16, 23));
		iniarrow.push_back(point(17, 23));
		iniarrow.push_back(point(18, 23));
		iniarrow.push_back(point(12, 35));
		//arrow part


		inifirearrow.push_back(point(13, 35));
		inifirearrow.push_back(point(5, 28));
		//fire arrow part


		win = point(18, 21);




		squares[10][23].word = "The Ancient Temple is \n Abandoned ";
		squares[10][24].word = "Clerics is Seeking for\n YOUR DESPAIR and\n SUFFERING";
		squares[10][25].word = "Only Way to Escape \n is Going Through --";
		squares[10][26].word = "--Throught Challenge from\n Four Elements";

		squares[9][32].word = "First Room is built\n for Spirit of Aqua";
		squares[7][26].word = "Arrows and Torch helps\nto Achieve its Head";
		squares[4][34].word = "Walk Through its Teeth Carefully";
		squares[1][27].word = "Find the Lost  \n in its Stomache";


		squares[9][10].word = "Second Room is built\n for Spirit of Tierra";
		squares[8][18].word = "Choose a Better Way \n Deep into Ground";
		squares[2][2].word = "Break the Weed on the Way";
		squares[8][10].word = "Start the Ancient Engine";

		squares[11][10].word = "Third Room is built\n for Spirit of Ignis";
		squares[13][10].word = "Sacrifice your Soul \nto  Feel His Power";
		squares[18][3].word = "The Bloody Strength \n Breaak the Blocker";
		squares[12][3].word = "Dancing in Danger,\nRewarded in Honer";

		squares[11][32].word = "Last Room is built\n for Spirit of Vento";
		squares[12][23].word = "Let the Arrows Follow the Winds";
		squares[14][35].word = "Clear the Mess \n Open the Ways";
		squares[12][39].word = "End the Elder Fire\n Future Weights";

		squares[12][21].word = "Final Thing to do is\n Light the Torch";
		squares[14][21].word = "A Brand New Future \n is Carried on";
		squares[15][21].word = "The Strang Temple then Fell to Sleep";
		squares[16][21].word = "Who Will be the Next Waken Hero?";

		inii = 10;
		inij = 21;
	}
	else if (id == 2) {
		for (int i = 0; i < 20; i++)squares[i][0].type = 2;
		for (int i = 0; i < 20; i++)squares[i][42].type = 2;
		for (int j = 0; j < 43; j++)squares[0][j].type = 2;
		for (int j = 0; j < 43; j++)squares[19][j].type = 2;
		for (int j = 2; j < 7; j++)squares[4][j].type = 1;
		for (int j = 2; j < 8; j++)squares[6][j].type = 1;
		for (int j = 5; j < 8; j++)squares[10][j].type = 1;
		for (int j = 5; j < 8; j++)squares[16][j].type = 1;
		for (int j = 6; j < 11; j++)squares[8][j].type = 1;
		for (int j = 1; j < 3; j++)squares[13][j].type = 1;
		for (int j = 10; j < 14; j++)squares[12][j].type = 1;
		for (int j = 15; j < 21; j++)squares[15][j].type = 1;
		for (int j = 16; j < 22; j++)squares[13][j].type = 1;
		for (int j = 17; j < 19; j++)squares[10][j].type = 1;
		for (int j = 17; j < 19; j++)squares[4][j].type = 1;
		for (int j = 20; j < 24; j++)squares[17][j].type = 1;
		for (int j = 27; j < 29; j++)squares[3][j].type = 1;
		for (int i = 10; i < 17; i++)squares[i][4].type = 1;
		for (int i = 6; i < 10; i++)squares[i][2].type = 1;
		for (int i = 2; i < 8; i++)squares[i][10].type = 1;
		for (int i = 1; i < 4; i++)squares[i][5].type = 2;
		for (int i = 16; i < 19; i++)squares[i][9].type = 1;
		for (int i = 10; i < 12; i++)squares[i][10].type = 1;
		for (int i = 2; i < 4; i++)squares[i][7].type = 1;
		for (int i = 1; i < 6; i++)squares[i][13].type = 1;
		for (int i = 10; i < 13; i++)squares[i][16].type = 1;
		for (int i = 7; i < 10; i++)squares[i][18].type = 1;
		for (int i = 9; i < 17; i++)squares[i][23].type = 1;
		for (int i = 15; i < 19; i++)squares[i][25].type = 1;
		for (int i = 1; i < 4; i++)squares[i][17].type = 1;
		for (int i = 7; i < 9; i++)squares[i][14].type = 1;
		for (int i = 10; i < 15; i++)squares[i][14].type = 2;
		for (int i = 1; i < 11; i++)squares[i][20].type = 2;
		for (int i = 1; i < 11; i++)squares[i][21].type = 2;
		for (int i = 10; i < 15; i++)squares[i][25].type = 2;
		for (int i = 12; i < 15; i++)squares[i][31].type = 2;
		for (int i = 11; i < 15; i++)squares[i][32].type = 2;
		for (int i = 10; i < 17; i++)squares[i][37].type = 2;
		for (int i = 13; i < 17; i++)squares[i][38].type = 2;
		for (int i = 10; i < 18; i++)squares[i][40].type = 2;
		for (int i = 10; i < 13; i++)squares[i][37].type = 2;
		for (int i = 5; i < 8; i++)squares[i][37].type = 2;
		for (int j = 23; j < 29; j++)squares[7][j].type = 2;
		for (int j = 25; j < 29; j++)squares[6][j].type = 2;
		for (int j = 26; j < 29; j++)squares[5][j].type = 2;
		for (int j = 23; j < 29; j++)squares[4][j].type = 2;
		for (int j = 23; j < 32; j++)squares[1][j].type = 2;
		for (int j = 28; j < 33; j++)squares[15][j].type = 2;
		for (int j = 28; j < 33; j++)squares[16][j].type = 2;
		for (int j = 32; j < 34; j++)squares[17][j].type = 2;
		for (int j = 23; j < 29; j++)squares[7][j].type = 2;
		for (int j = 36; j < 39; j++)squares[17][j].type = 2;
		for (int j = 37; j < 41; j++)squares[9][j].type = 2;
		for (int j = 37; j < 40; j++)squares[3][j].type = 2;
		for (int j = 15; j < 19; j++)squares[6][j].type = 2;
		for (int j = 38; j < 40; j++)squares[12][j].type = 2;

		for (int j = 5; j < 10; j++)squares[11][j].type = 3;
		for (int j = 9; j < 12; j++)squares[9][j].type = 3;
		for (int j = 11; j < 13; j++)squares[8][j].type = 3;
		for (int j = 12; j < 14; j++)squares[7][j].type = 3;
		for (int j = 13; j < 15; j++)squares[6][j].type = 3;
		for (int j = 14; j < 16; j++)squares[5][j].type = 3;
		for (int j = 14; j < 17; j++)squares[4][j].type = 3;
		for (int j = 11; j < 13; j++)squares[4][j].type = 3;
		for (int j = 6; j < 10; j++)squares[4][j].type = 3;
		for (int j = 8; j < 10; j++)squares[10][j].type = 3;
		for (int i = 1; i < 19; i++)squares[i][34].type = 3;
		for (int i = 1; i < 19; i++)squares[i][35].type = 3;
		for (int i = 1; i < 4; i++)squares[i][40].type = 3;
		for (int i = 1; i < 4; i++)squares[i][41].type = 3;
		for (int i = 4; i < 6; i++)squares[i][36].type = 3;
		for (int i = 11; i < 14; i++)squares[i][26].type = 3;
		for (int i = 11; i < 14; i++)squares[i][27].type = 3;
		for (int i = 11; i < 14; i++)squares[i][28].type = 3;
		for (int i = 10; i < 14; i++)squares[i][29].type = 3;
		for (int i = 9; i < 13; i++)squares[i][30].type = 3;
		for (int i = 8; i < 12; i++)squares[i][31].type = 3;
		for (int i = 7; i < 11; i++)squares[i][32].type = 3;
		for (int i = 6; i < 10; i++)squares[i][33].type = 3;
		for (int i = 15; i < 19; i++)squares[i][14].type = 3;


		//0:red 1:yellow 2:pink 3:blue 4:green


		squares[17][39].door1 = Mydoor(1, 1, 4);
		squares[13][3].door1 = Mydoor(1, 2, 2);
		squares[16][8].door1 = Mydoor(1, 3, 1);
		squares[9][1].door1 = Mydoor(1, 4, 1);



		squares[3][36].button = Mybutton(1, 1, 17, 39);
		squares[1][38].button = Mybutton(1, 1, 17, 39);
		squares[15][33].button = Mybutton(1, 1, 17, 39);
		squares[13][41].button = Mybutton(1, 1, 17, 39);

		squares[10][1].button = Mybutton(1, 2, 13, 3);
		squares[10][3].button = Mybutton(1, 2, 13, 3);
		squares[18][1].button = Mybutton(1, 3, 16, 8);
		squares[5][6].button = Mybutton(1, 4, 9, 1);


		squares[9][24].type = 4;
		squares[2][32].type = 4;
		squares[2][33].type = 4;
		squares[1][32].type = 4;
		squares[1][33].type = 4;


		iniarrow.push_back(point(3, 4));
		iniarrow.push_back(point(11, 2));
		iniarrow.push_back(point(6, 31));
		inibomb.push_back(point(2, 4));
		inibomb.push_back(point(14, 1));
		inibomb.push_back(point(18, 19));
		inibomb.push_back(point(5, 41));
		inibomb.push_back(point(1, 14));
		inibox.push_back(point(3, 3));
		inibox.push_back(point(17, 3));
		inibox.push_back(point(15, 3));
		inibox.push_back(point(16, 17));
		inibox.push_back(point(2, 24));
		inibox.push_back(point(2, 26));
		inibox.push_back(point(4, 31));
		inibox.push_back(point(7, 29));
		iniblood.push_back(point(2, 5));
		iniblood.push_back(point(18, 15));
		inifirearrow.push_back(point(2, 6));
		iniblood.push_back(point(5, 11));

		win = point(13, 39);
		inii = 1;
		inij = 1;
	}
}