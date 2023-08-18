#include"snake.h"

HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
POINT snake[31];
POINT food[8];
string sort[3][2];
bool music = 1;
string NAME;
int CHAR_LOCK;
int MOVING;
int SPEED = 1;
int HEIGH_CONSOLE, WIDTH_CONSOLE;
int FOOD_INDEX;
int SIZE_SNAKE;
int STATE;

char snakeID[] = { '2', '2', '1', '2', '7', '2', '3', '6','2', '2', '1', '2', '7', '1', '6', '9','2', '2',
				   '1', '2', '7', '0', '1', '7','2', '2', '1', '2', '7', '3', '8', '5' };
int n = sizeof(snakeID) / sizeof(snakeID[0]);

void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void animation() {
	GotoXY(0, HEIGH_CONSOLE + 1);
	readFileAnimation("dead.txt", 0, 0, 200);

}

bool IsValid(int x, int y) {
	for (int i = 0; i < SIZE_SNAKE; i++) {
		if (snake[i].x + 32 == x && snake[i].y + 7 == y) {
			return false;
		}
	}
	return true;
}

void GenerateFood() {
	int x, y;
	srand(time(NULL));
	for (int i = 0; i < MAX_SIZE_FOOD; i++) {
		do {
			x = rand() % (WIDTH_CONSOLE - 2) + 1;
			y = rand() % (HEIGH_CONSOLE - 2) + 1;
		} while (IsValid(x, y) == false);
		food[i] = { x + 32,y + 7 };
	}
}

void ResetData() {
		CHAR_LOCK = 'A', MOVING = 'D', SPEED = 1; FOOD_INDEX = 0, WIDTH_CONSOLE = 70, HEIGH_CONSOLE = 20, SIZE_SNAKE = 6, STATE = 1;
		snake[0] = { 10 + 32, 5 + 7 }; snake[1] = { 11 + 32, 5 + 7 };
		snake[2] = { 12 + 32, 5 + 7 }; snake[3] = { 13 + 32, 5 + 7 };
		snake[4] = { 14 + 32, 5 + 7 }; snake[5] = { 15 + 32, 5 + 7 };


}



void StartGame(int key) {
	system("cls");
	if (key == 1)
		ResetData();
	else {
		CHAR_LOCK = 'A', MOVING = 'D'; 
		FOOD_INDEX = 0, WIDTH_CONSOLE = 70, HEIGH_CONSOLE = 20;
	}
		GenerateFood();
	// Print state
	system("cls");
	color(15);
	GotoXY(106, 12);
	cout << "ROUND: " << SPEED << "/3";

	GotoXY(106, 15);
	cout << "LENGTH: " << SIZE_SNAKE << "/32";

	
	DrawBoard(32, 7, WIDTH_CONSOLE, HEIGH_CONSOLE, 0, 0);
	STATE = 1;
}

string LoadGame(string filename) {
	system("cls");

	ifstream ifs(filename);
	if (!ifs)
		cout << "Could not opening file";
	string s;
	ifs >> s;
	ifs >> SIZE_SNAKE;
	ifs >> SPEED;
	ifs >> STATE;
	for (int i = 0; i < SIZE_SNAKE; i++) {
		ifs >> snake[i].x >> snake[i].y;
	}
	ifs.close();
	STATE = 1;
	return s;
}


void DrawBoard(int x, int y, int width, int height, int curPosX, int curPosY /*string name, int length, int level*/) {
	system("color F0"); // bg color

	color(192);
	GotoXY(x, y); cout << char(201);
	for (int i = 1; i < width; i++)
		cout << char(205);
	cout << char(187);
	GotoXY(x, height + y); cout << char(200);
	for (int i = 1; i < width; i++)cout << char(205);
	cout << char(205);


	for (int i = y + 1; i < height + y; i++) {
		GotoXY(x, i); cout << char(186);
		GotoXY(x + width, i); cout << char(186);
	}
	GotoXY(x + width, height + y);
	cout << char(188);

	// right
	color(144);
	GotoXY(x + width + 2, y);
	for (int i = 1; i <= 22; i++)
		cout << char(220);
	GotoXY(x + width + 2, y + height);
	for (int i = 1; i <= 22; i++)
		cout << char(223);

	color(144);
	for (int i = y + 1; i < height + y; i++) {
		GotoXY(x + width + 2, i); cout << char(221);
		GotoXY(x + width + 23, i); cout << char(222);
	}
	GotoXY(x + width + 3, y + height / 2 + 1);
	cout << "                    ";

	color(15);
	GotoXY(x + width + 4, y + 2);
	cout << "NAME: ";
	
	
	GotoXY(x + width + 9, y + 13);
	cout << "STATUS ";

	GotoXY(x + width + 12, y + 15);
	ProcessDead();


	// left
	color(160);
	GotoXY(x - 26, y - 1);
	for (int i = 1; i <= 25; i++)
		cout << char(220);
	GotoXY(x - 26, y + height + 2 - 1);
	for (int i = 1; i <= 25; i++)
		cout << char(223);


	for (int i = y; i < height + y + 2 - 1; i++) {
		GotoXY(x - 26, i); cout << char(221);
		GotoXY(x - 2, i); cout << char(222);
	}

	readFileAnimation("keyboard.txt", x - 25, y, 244);

	// Top
	readFileAnimation("snakeIlu.txt", 31, 6, 252);

	GotoXY(curPosX, curPosY);
}

void ExitGame(HANDLE t) {
	system("cls");
	exit(0);
}


void PauseGame(HANDLE t) {
	color(249);
	GotoXY(106, 23);
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	cout << u8"█▀█ ▄▀█ █░█ █▀ █▀▀";
	GotoXY(106, 24);
	cout << u8"█▀▀ █▀█ █▄█ ▄█ ██▄";

	GotoXY(20, 30);
	cout << u8"█▀█ █▀█ █▀▀ █▀ █▀   ▄▀█ █▄░█ █▄█   █▄▀ █▀▀ █▄█   ▀█▀ █▀█   █▀▀ █▀█ █░█ █▄░█ ▀█▀ █ █▄░█ █░█ █▀▀";
	GotoXY(20, 31);
	cout << u8"█▀▀ █▀▄ ██▄ ▄█ ▄█   █▀█ █░▀█ ░█░   █░█ ██▄ ░█░   ░█░ █▄█   █▄▄ █▄█ █▄█ █░▀█ ░█░ █ █░▀█ █▄█ ██▄";
	SetConsoleOutputCP(old_cp);
	SuspendThread(t);
}

void Eat() {

	snake[SIZE_SNAKE] = food[FOOD_INDEX];
	if (FOOD_INDEX == MAX_SIZE_FOOD - 1) { //3

		FOOD_INDEX = 0;
		SPEED++;
		if (SPEED == MAX_SPEED) { // 2
			FOOD_INDEX = 0;

			clearSnake();
			Sleep(3000);
			
			SIZE_SNAKE = -1; // 6
			SPEED = 1;

		}

		GenerateFood();
	}
	else {
		if (music == 1) {
			PlaySound(TEXT("Selectright.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		FOOD_INDEX++;
		SIZE_SNAKE++;
		color(15);
		GotoXY(106, 15);
		cout << "LENGTH: " << SIZE_SNAKE << " /32";
	}
}

void readFileAnimation(string filename, int x, int y, int colorCode) {
	if (filename == "congrat.txt" && music == 1)
		PlaySound(TEXT("youwin.wav"), NULL, SND_FILENAME | SND_ASYNC);
	else if (filename == "dead.txt" && music == 1)
		PlaySound(TEXT("youlose.wav"), NULL, SND_FILENAME | SND_ASYNC);
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	ifstream fin;
	fin.open(filename);
	string line;
	while (!fin.eof()) {

		color(colorCode);
		getline(fin, line);
		GotoXY(x, y++);
		cout <<  line << endl;
	}
	fin.close();
	SetConsoleOutputCP(old_cp);

}
void ProcessDead() {

	color(249);
	if (STATE == 1) {
		GotoXY(109, 23);
		UINT old_cp = GetConsoleOutputCP();
		SetConsoleOutputCP(CP_UTF8);
		cout << u8"█░░ █ █░█ █▀▀";
		GotoXY(109, 24);
		cout << u8"█▄▄ █ ▀▄▀ ██▄";
		SetConsoleOutputCP(old_cp);
	}
	else {
		UINT old_cp = GetConsoleOutputCP();
		SetConsoleOutputCP(CP_UTF8);

		GotoXY(108, 23);
		SetConsoleOutputCP(CP_UTF8);
		cout << u8"█▀▄ █▀▀ ▄▀█ █▀▄";
		GotoXY(108, 24);
		cout << u8"█▄▀ ██▄ █▀█ █▄▀";
		SetConsoleOutputCP(old_cp);
		
		

		readFileAnimation("snakeBoard.txt", 0, 0, 250);
		readFileAnimation("dead.txt", 18, 1, 249);
		
	
	}
}

void DrawSnakeAndFood(char* str) {
	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
	color(255);
	printf(str);
	for (int i = 0; i < SIZE_SNAKE; i++) {
		GotoXY(snake[i].x, snake[i].y);
		printf(str);
	}
}


bool touchBody() {
	for (int i = 0; i < SIZE_SNAKE - 1; i++) {
		if (snake[SIZE_SNAKE - 1].x == snake[i].x && snake[SIZE_SNAKE - 1].y == snake[i].y) {
			return true;
		}
	}
	return false;
}


void MoveRight() {
	if (snake[SIZE_SNAKE - 1].x + 1 >= WIDTH_CONSOLE + 32 || touchBody() == true) {
		
		STATE = 0;
		ProcessDead();

	}
	else {
		if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
			Eat();
			if (SIZE_SNAKE == -1)
				SIZE_SNAKE = 6;
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].x++;
	}
}

void MoveLeft() {
	if (snake[SIZE_SNAKE - 1].x - 1 <= 0 + 32 || touchBody() == true) {
		STATE = 0;
		ProcessDead();
	}
	else {
		if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
			Eat();
			if (SIZE_SNAKE == -1)
				SIZE_SNAKE = 6;
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].x--;
	}
}

void MoveDown() {
	if (snake[SIZE_SNAKE - 1].y + 1 >= HEIGH_CONSOLE + 7 || touchBody() == true) {
		STATE = 0;
		ProcessDead();
	}
	else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y) {
			Eat();
			if (SIZE_SNAKE == -1)
				SIZE_SNAKE = 6;
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].y++;
	}
}

void MoveUp() {
	if (snake[SIZE_SNAKE - 1].y - 1 <= 0 + 7 || touchBody() == true) {
		STATE = 0;
		ProcessDead();
	}
	else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y) {
			Eat();
			if (SIZE_SNAKE == -1)
				SIZE_SNAKE = 6;
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].y--;
	}
}

void clearSnake() {
	int index = 0;
	color(250);
	for (int i = 0; i < SIZE_SNAKE; i++) {
		GotoXY(snake[i].x, snake[i].y);
		if (index == n) {
			index = 0;
		}

		cout << " ";
		index++;
	}
}


void ThreadFunc() {

	char snakefood[] = "0";
	char space[] = " ";
	int index = 0;
	
	while (1) {
		
		if (STATE == 1) {
			
			DrawSnakeAndFood(space);
			switch (MOVING) {
			case 'A':
				MoveLeft();
				break;
			case 'D':
				MoveRight();
				break;
			case 'W':
				MoveUp();
				break;
			case 'S':
				MoveDown();
				break;
			}
			
			if (SPEED == MAX_SPEED - 1) {
				SaveGame();
				system("cls");
				system("color 252");
				readFileAnimation("congrat.txt", 1, 12, 252);
				STATE = 0;
				continue;
			}

			// Food
			
			GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
			color(236);
			cout << char(4); // create food
			// MSSV
			color(160);
			for (int i = 0; i < SIZE_SNAKE; i++) {
				GotoXY(snake[i].x, snake[i].y);
				if (index == n) {
					index = 0;
				}

				if (i == 0) {
					color(138);
					cout << snakeID[index];
					color(160);
				}
				else if (i < SIZE_SNAKE - 1) {
					cout << snakeID[index];
				}

				else {
					color(10);
					cout << snakeID[index];
					color(160);
				}

				index++;
			}
			index = 0;

			
			Sleep(500 / SPEED); // change speed here
		}
	}
}
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}


void textbackrough() {

	SetConsoleTextAttribute(cons, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void readFile(string fileName, int colorcode, int& x, int& y, int sleepTime) {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

	ifstream fin;
	fin.open(fileName);
	string line;
	if (!fin)
		cout << "Could not opening file";
	int cnt = 0;
	while (!fin.eof()) {

		getline(fin, line);
		GotoXY(x, y++);
		color(colorcode);
		cout << line << endl;
	/*	Sleep(sleepTime);*/
		cnt++;
	}
	fin.close();
	SetConsoleOutputCP(old_cp);
}

int getKey() {
	char c = _getch();

	if ((int)c == -32)
		c = _getch();
	Beep(300, 90);
	switch ((int)tolower(c)) {

	case 's':
		return 1; // down

	case 'w':
		return 2; // up

	case 'd':
		return 3; // right

	case 'a':
		return 4; // left

	case 27:
		return 5; // esc

	case 13: {
		if (music == 1) {
			PlaySound(TEXT("PressKey.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		
		return 6; // enter
	}

	case 104:
		return 7; // h character

	default:
		return 0;

	}

}

void SaveGame() {
	ofstream ofs;
	ofs.open("Data.txt", ios::app);
	color(15);

	int size = SIZE_SNAKE;
	int speed = SPEED;
	int state = STATE;
	int goX = snake[0].x;
	int goY = snake[0].y;
	GotoXY(0, 12);

	ofs << NAME << " " << size << " " << speed << " " << state << " ";
	for (int i = 0; i < SIZE_SNAKE; i++) {
		int goX = snake[i].x;
		ofs << goX << " ";
		int goY = snake[i].y;
		ofs << goY << " ";
	}
	ofs << endl;
	ofs.close();

}
// max number of players in the list

string InputName() {
	system("color F0");
	GotoXY(20, 10);
	resizeConsole(800,400);
	cout << "NAME: ___________________";
	string s;
	GotoXY(26, 10);
	getline(cin, s);
	system("cls");
	resizeConsole(1000, 600);
	FixConsoleWindow();
	return s;
}


void mainMenu(int& option) {
	if (music == 1) {
		PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	
	system("color F0");
	resizeConsole(1000, 600);
	ShowConsoleCursor(false);
	

	// cap nhat cach in 
	UINT init_cp = GetConsoleOutputCP();
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	color(252);
	GotoXY(16, 1);

	cout <<  u8"♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥";
	SetConsoleOutputCP(old_cp);


	// 1. print background
	int p = 6, q = 12;
	readFileAnimation("MenuBG.txt", p, q, 250);

	p = 30, q = 5;
	readFile("SnakeBG.txt", 252, p, q, 252);
	
	p = 39;
	q = 12;
	readFile("snakeIMG.txt", 252, p, q, 100);

	Sleep(300);
	p = 50;
	q += 1;


	string text[] = {
		"START",
		"SOUND",
		"LEADERBOARD",
		"EXIT"
	};
	// print menu
	int width = 25; // the width of the menu
	old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	for (int i = 0; i < 5; i++) {
		GotoXY(p + 3, q + 2 * i);

		

		textbackrough();
		color(250);
		if (i == 0) {
			cout << u8"๑━━━━━━━━━━━━━๑۩۩๑๑۩۩๑━━━━━━━━━━━━๑";
		}
		else {
			cout << u8"☆━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━☆";
		}

	}
	SetConsoleOutputCP(old_cp);

	old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	for (int i = 0; i < 4; i++) {

		color(LIGHTRED);
		GotoXY(p + 3, q + 1 + 2 * i);

		textbackrough();
		color(250);
		cout << u8"☆                                 ☆";

	}
	SetConsoleOutputCP(old_cp);



	for (int i = 0; i < 4; i++) {
		GotoXY(p + 19, q + 1 + 2 * i);
		if (i == 2) {
			GotoXY(p + 16, q + 1 + 2 * i);
		}
		color(252);
		cout << text[i];
	}

	// choose option
	option = 0;
	int oldOption = option;
	while (1) {

		int ch = getKey();

		if (ch == 6 && option != 0) {
			break;
		}
		switch (ch) {
		case 2:
			option--;
			break;
		case 1:
			option++;
		}
		if (option <= 0)
			option = 4;
		else if (option >= 5)
			option = 1;
		// old option
		if (oldOption != 0) {
			GotoXY(p + 4, q + 1 + 2 * (oldOption - 1));
			color(255);
			cout << "                                 ";

			GotoXY(p + 19, q + 1 + 2 * (oldOption - 1));
			if (oldOption == 3)
				GotoXY(p + 16, q + 1 + 2 * (oldOption - 1));
			color(244);
			cout << text[oldOption - 1];
		}

		color(255);
		GotoXY(p, q + 1 + 2 * (oldOption - 1));
		cout << "  ";
		oldOption = option;
		old_cp = GetConsoleOutputCP();
		SetConsoleOutputCP(CP_UTF8);
		color(250);
		GotoXY(p, q + 1 + 2 * (option - 1));
		cout << u8"🐍";
		SetConsoleOutputCP(old_cp);
		color(014);

		/*textbackrough();*/
		GotoXY(p + 4, q + 1 + 2 * (option - 1));
		cout << "                                 ";
		
		GotoXY(p + (width - text[option - 1].size()) / 2 + 9, q + 1 + 2 * (option - 1));
		cout << text[option - 1];
		/*color(YELLOW);*/
	}
	SetConsoleOutputCP(init_cp);


	system("cls");
}

void Sorting(string filename) {
	ifstream ifs(filename);
	if (!ifs) {
		cout << "File not open";
		return;
	}
	int count = 0;
	string temp;
	// count players
	while (!ifs.eof()) {
		getline(ifs, temp);
		count++;
	}
	count--;
	//
	//// name and length
	string** s = new string * [count];
	for (int i = 0; i < count; i++) {
		s[i] = new string[2];
	}
	ifs.close();

	//
	ifs.open(filename);
	string tmp;
	
	int jIndex = 0;
	for (int i = 0; i < count; i++) {
		getline(ifs, tmp, ' ');
		s[i][jIndex++] = tmp;

		getline(ifs, tmp, ' ');
		s[i][jIndex] = tmp;
		jIndex = 0;

		getline(ifs, tmp);
	}

	
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (s[i][1] < s[j][1]) {
				swap(s[i][1], s[j][1]);
				swap(s[i][0], s[j][0]);
			}
		}
	}

	/*for (int i = 0; i < 3; i++) {
		for (int j = 0; i < 2; j++) {
			sort[i][j] = s[i][j];
		}
	}*/
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			sort[i][j] = s[i][j];
		}
	}

	ifs.close();
	for (int i = 0; i < count; i++) {
		delete[] s[i];
	}
	delete[]s;

}

void showLeaderboard() {
	Sorting("Data.txt");
	system("color F0");
	
	UINT init_cp = GetConsoleOutputCP();
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	color(244);
	GotoXY(24, 3);
	
	cout << u8"🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇🥇";
	

	// LEADERBOARD
	GotoXY(10, 10);
	
	GotoXY(24, 5);
	color(241);
	cout << u8"██╗░░░░░███████╗░█████╗░██████╗░███████╗██████╗░██████╗░░█████╗░░█████╗░██████╗░██████╗░";
	color(242);
	GotoXY(24, 6);
	cout << u8"██║░░░░░██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗";
	color(243);
	GotoXY(24, 7);
	cout << u8"██║░░░░░█████╗░░███████║██║░░██║█████╗░░██████╔╝██████╦╝██║░░██║███████║██████╔╝██║░░██║";
	color(244);
	GotoXY(24, 8);
	cout << u8"██║░░░░░██╔══╝░░██╔══██║██║░░██║██╔══╝░░██╔══██╗██╔══██╗██║░░██║██╔══██║██╔══██╗██║░░██║";
	color(245);
	GotoXY(24, 9);
	cout << u8"███████╗███████╗██║░░██║██████╔╝███████╗██║░░██║██████╦╝╚█████╔╝██║░░██║██║░░██║██████╔╝";
	color(246);
	GotoXY(24, 10);
	cout << u8"╚══════╝╚══════╝╚═╝░░╚═╝╚═════╝░╚══════╝╚═╝░░╚═╝╚═════╝░░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═════╝░";
	

	
	for (int i = 0; i < 10; i++) {
		
		GotoXY(30, 20 + i);
		color(188);
		cout << u8"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
		
	}

	for (int i = 0; i < 15; i++) {

		GotoXY(60, 15 + i);
		color(189);
		cout << u8"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓";

	}

	for (int i = 0; i < 7; i++) {
		GotoXY(90, 23 + i);
		color(190);
		cout << u8"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓";

	}
	SetConsoleOutputCP(old_cp);
	
	// name top1
	color(189);
	GotoXY(68, 13);
	cout << sort[0][0];

	GotoXY(38, 18);
	cout << sort[1][0];

	GotoXY(97, 21);
	cout << sort[2][0];

	cin.get();
}

