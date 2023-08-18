#ifndef snake_game
#define snake_game
#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <cstring>
#include <conio.h>
#include <chrono>
#include <Windows.h>
#include <thread>
#include <time.h>
#include <mmsystem.h>
#include <cwchar>
#include <atomic>
using namespace std;

#define MAX_SIZE_SNAKE 32
#define MAX_SIZE_FOOD 8
#define MAX_SPEED 5
#define BLUE 1
#define GREEN 2
#define CYAN    36
#define RED    37
#define MAGENTA    5
#define BROWN    6
#define DEFAULT_COLOR    7
#define DARKGRAY    8
#define LIGHTBLUE    9
#define LIGHTGREEN    38
#define LIGHTCYAN    11
#define LIGHTRED    12
#define LIGHTMAGENTA    13
#define YELLOW    14
#define BLACK    15

#define MAX_PLAYERS 100




extern POINT snake[31];
extern POINT food[8];
extern string NAME;
extern bool music;
extern int CHAR_LOCK;
extern int MOVING;
extern int SPEED;
extern int HEIGH_CONSOLE, WIDTH_CONSOLE;
extern int FOOD_INDEX;
extern int SIZE_SNAKE;
extern int STATE;

void FixConsoleWindow();
void GotoXY(int x, int y);
bool IsValid(int x, int y);
void GenerateFood();
void ResetData();
void StartGame(int key);
void DrawBoard(int x, int y, int width, int height, int curPosX, int curPosY);
void ExitGame(HANDLE t);
void PauseGame(HANDLE t);
void animation();
void Eat();
void ProcessDead();
void DrawSnakeAndFood(const char* str);
bool touchBody();
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();
void ThreadFunc();
void readFileAnimation(string filename, int x, int y, int colorCode);
void color(int color);
void resizeConsole(int width, int height);

void ShowConsoleCursor(bool showFlag);
void readFile(string fileName, int color, int& x, int& y, int sleepTime = 100);
int getKey();
string InputName();
void mainMenu(int& option);
void textbackrough();
void Sorting(string fileName);
void showLeaderboard();

void SaveGame();
string LoadGame(string fileName);
void clearSnake();
#endif // !snake_game