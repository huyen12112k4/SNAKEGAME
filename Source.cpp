#include"snake.h"

HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
POINT snake[32];
POINT food[8];

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
	GenerateFood();
}



void StartGame() {
	system("cls");
	
	ResetData();
	DrawBoard(32, 7, WIDTH_CONSOLE, HEIGH_CONSOLE, 0, 0);
	STATE = 1;
}

void DrawBoard(int x, int y, int width, int height, int curPosX, int curPosY /*string name, int length, int level*/) {
	system("color 70"); // bg color

	

	color(192);
	GotoXY(x, y); cout << char(4);
	for (int i = 1; i < width; i++)
		cout << char(31);
	cout << char(4);
	GotoXY(x, height + y); cout << char(4);
	for (int i = 1; i < width; i++)cout << char(30);
	cout << char(4);

	for (int i = y + 1; i < height + y; i++) {
		GotoXY(x, i); cout << char(16);
		GotoXY(x + width, i); cout << char(17);
	}

	// right
	color(144);
	GotoXY(x + width + 2, y);
	for (int i = 1; i < 22; i++)
		cout << char(220);
	GotoXY(x + width + 2, y + height);
	for (int i = 1; i < 22; i++)
		cout << char(223);

	color(144);
	for (int i = y + 1; i < height + y; i++) {
		GotoXY(x + width + 2, i); cout << char(221);
		GotoXY(x + width + 22, i); cout << char(222);
	}

	GotoXY(x + width + 3, y + height / 2 + 2);
	cout << "-------------------";

	color(15);
	GotoXY(x + width + 4, y + 2);
	cout << "NAME:";


	GotoXY(x + width + 4, y + 5);
	cout << "ROUND: " << SPEED << "/3";

	GotoXY(x + width + 4, y + 8);
	cout << "LENGTH: " << SIZE_SNAKE << " /33";

	GotoXY(x + width + 9, y + 14);
	cout << "STATUS ";

	GotoXY(x + width + 10, y + 16);
	ProcessDead();


	// left
	color(224);
	GotoXY(x - 22, y);
	for (int i = 1; i <= 21; i++)
		cout << char(220);
	GotoXY(x - 22, y + height);
	for (int i = 1; i <= 21; i++)
		cout << char(223);

	color(224);
	for (int i = y + 1; i < height + y; i++) {
		GotoXY(x - 22, i); cout << char(221);
		GotoXY(x - 2, i); cout << char(222);
	}

	readFileAnimation("keyboard.txt", x - 21, y + 1, 240);

	// Top
	readFileAnimation("snakeIlu.txt", 31, 6, 242);

	GotoXY(curPosX, curPosY);
}

void ExitGame(HANDLE t) {
	system("cls");
	exit(0);
}


void PauseGame(HANDLE t) {
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
		FOOD_INDEX++;
		SIZE_SNAKE++;
	}
}

void readFileAnimation(string filename, int x, int y, int colorCode) {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	ifstream fin;
	fin.open(filename);
	string line;
	while (!fin.eof()) {

		color(colorCode);
		getline(fin, line);
		GotoXY(x, y++);
		cout << line << endl;
	}
	fin.close();
	SetConsoleOutputCP(old_cp);

}
void ProcessDead() {
	color(249);
	if (STATE == 1) {
		GotoXY(108, 23);
		UINT old_cp = GetConsoleOutputCP();
		SetConsoleOutputCP(CP_UTF8);
		cout << u8"█░░ █ █░█ █▀▀";
		GotoXY(108, 24);
		cout << u8"█▄▄ █ ▀▄▀ ██▄";
		SetConsoleOutputCP(old_cp);
	}
	else {
		GotoXY(107, 23);
		UINT old_cp = GetConsoleOutputCP();
		SetConsoleOutputCP(CP_UTF8);
		cout << u8"█▀▄ █▀▀ ▄▀█ █▀▄";
		GotoXY(107, 24);
		cout << u8"█▄▀ ██▄ █▀█ █▄▀";
		SetConsoleOutputCP(old_cp);
			
		readFileAnimation("snakeBoard.txt", 0, 0, 122);
		readFileAnimation("dead.txt", 18, 1, 121);
		
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
			if (SPEED == MAX_SPEED) {
				system("cls");
				system("color 74");
				readFileAnimation("congrat.txt", 1, 12, 124);
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
			Sleep(250 / SPEED); // change speed here
		}
	}

	//GotoXY(snake[0].x, snake[0].y);
}
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// set color of text
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
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
void readFile(string fileName, int color, int& x, int& y, int sleepTime) {
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
		textbackrough();
		cout << line << endl;
		Sleep(sleepTime);
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

	case 13:
		return 6; // enter

	case 104:
		return 7; // h character

	default:
		return 0;

	}

}


void SaveGame(string playerName, int round, int score, POINT snake[], int sizeSnake, bool isGameEnded) {
	ofstream file;
	file.open("Data.txt", ios::app);

	if (file.is_open()) {
		// Get the current time
		time_t currentTime = time(0);
		tm* now = localtime(&currentTime);

		// Format the time as HH:mm:ss dd-MM-yyyy
		char timeStr[20];
		strftime(timeStr, sizeof(timeStr), "%H:%M:%S %d-%m-%Y", now);

		// Write player's data to the file
		file << playerName << "/" << round << "/" << score << "/" << sizeSnake << "/" << timeStr << "/" << isGameEnded << endl;

		file.close();
	}
	else {
		cout << "Error: Unable to open file for saving data!" << endl;
	}
}


// max number of players in the list

PlayerData LoadGame(string playerName) {
	ifstream file;
	file.open("Data.txt");

	PlayerData playerData;

	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string playerName, timeStr;
			int round, score, sizeSnake;
			bool isGameEnded;
			POINT snake[MAX_SIZE_SNAKE];

			getline(ss, playerName, '/');
			ss >> round;
			ss.ignore();
			ss >> score;
			ss.ignore();
			ss >> sizeSnake;
			ss.ignore();

			for (int i = 0; i < sizeSnake; i++) {
				ss >> snake[i].x;
				ss.ignore();
				ss >> snake[i].y;
				ss.ignore();
			}

			getline(ss, timeStr, '/');
			ss >> isGameEnded;

			if (playerName == playerName) {
				memcpy(playerData.snake, snake, sizeof(POINT) * sizeSnake);
				return playerData;
			}
		}

		file.close();
	}
	else {
		cout << "Error: Unable to open file for loading data!" << endl;
	}

	return playerData;
}
string InputName() {
	GotoXY(20, 10);
	cout << "NAME: ___________________";
	string s;
	GotoXY(26, 10);
	cin >> s;
	system("cls");
	return s;
}


void mainMenu(int& option) {
	system("color 70");
	resizeConsole(1000, 600);
	ShowConsoleCursor(false);
	

	// cap nhat cach in 
	UINT init_cp = GetConsoleOutputCP();
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	textcolor(LIGHTRED);
	GotoXY(16, 1);
	textbackrough();
	cout << u8"♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥";
	SetConsoleOutputCP(old_cp);


	// 1. print background
	int p = 6, q = 12;
	readFileAnimation("MenuBG.txt", p, q, 122);

	p = 30, q = 5;
	readFile("SnakeBG.txt", LIGHTRED, p, q, 50);
	
	p = 39;
	q = 12;
	readFile("snakeIMG.txt", GREEN, p, q, 100);

	Sleep(300);
	p = 50;
	q += 1;


	string text[] = {
		"START",
		"LOAD",
		"LEADERBOARD",
		"EXIT"
	};
	// print menu
	int width = 25; // the width of the menu
	old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	for (int i = 0; i < 5; i++) {
		GotoXY(p + 3, q + 2 * i);

		color(LIGHTRED);

		textbackrough();
		cout << u8"☆━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━☆";

	}
	SetConsoleOutputCP(old_cp);

	old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	for (int i = 0; i < 4; i++) {

		color(LIGHTRED);
		GotoXY(p + 3, q + 1 + 2 * i);

		textbackrough();
		cout << u8"☆                                 ☆";

	}
	SetConsoleOutputCP(old_cp);
	color(YELLOW);


	for (int i = 0; i < 4; i++) {
		GotoXY(p + 19, q + 1 + 2 * i);
		if (i == 2) {
			GotoXY(p + 16, q + 1 + 2 * i);
		}
		textbackrough();
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

			color(119);

			cout << "                                 ";

			GotoXY(p + 19, q + 1 + 2 * (oldOption - 1));
			if (oldOption == 3)
				GotoXY(p + 16, q + 1 + 2 * (oldOption - 1));
			color(116);
			cout << text[oldOption - 1];
		}

		oldOption = option;

		GotoXY(p + 4, q + 1 + 2 * (option - 1));

		color(LIGHTRED);

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


void colorKeyBoard(int arrow) {
	if (char(arrow) == 'D') {
		GotoXY(25, 15);
		color(192);
		cout << " D ";
		GotoXY(25, 15);
		Sleep(10);
		color(240);
		cout << " D ";
		return;
	}
	if (char(arrow) == 'S') {
		GotoXY(19, 15);
		color(192);
		cout << " S ";
		Sleep(10);
		GotoXY(19, 15);
		color(240);
		cout << " S ";
		return;
	}
	if (char(arrow) == 'A') {
		GotoXY(13, 15);
		color(192);
		cout << " A ";
		Sleep(10);
		GotoXY(13, 15);
		color(240);
		cout << " A ";
		return;
	}
	if (char(arrow) == 'W') {
		GotoXY(19, 12);
		color(192);
		cout << " W ";
		Sleep(10);
		GotoXY(19, 12);
		color(240);
		cout << " W ";
		return;
	}
}