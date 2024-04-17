#define _CRT_NONSTDC_NO_WARNINGS
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#include <stdio.h>
#include <conio.h> //キー入力の受け付け
#include <windows.h> //sleep関数用
#include <time.h>

//マップデータの定義
#define MAP_W 22
#define MAP_H 11
char _map[MAP_H][MAP_W] = {
	"#####################",
	"#                   #",
	"# ###           ### #",
	"# #               ###",
	"#    # ## ## #      #",
	"#    # #   # #      #",
	"#    # ## ## #      #",
	"# #                ##",
	"# ###            ## #",
	"#                   #",
	"#####################",
};

//ゲームで使う変数の定義
int _playerPosX = 1, _playerPosY = 1;
int _score = 0;
int _timer = 300;

//カーソル位置を指定する関数
void cursor(int x, int y)
{
	printf("\x1b[%d;%dH", y + 1, x + 1);
}

//文字や文字列の色を指定する関数
enum ColorType{BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
void allocateColor(int col)
{
	printf("\x1b[3%dm", col);
}

//ゲーム画面を描く関数
void drawMap(void)
{
	for (int y = 0; y < MAP_H; y++)
	{
		for (int x = 0; x < MAP_W - 1; x++)
		{
			if (_map[y][x] == '#') allocateColor(GREEN);
			else if (_map[y][x] == 'G') allocateColor(YELLOW);
			cursor(x, y);
			printf("%c", _map[y][x]);
		}
	}
}

//main関数
int main(void)
{
	srand((unsigned int)time(NULL));

	while (1)
	{
		int key = 0;
		if (kbhit()) key = getch();
		if (key == KEY_UP && _map[_playerPosY - 1][_playerPosX] != '#') _playerPosY--;
		else if (key == KEY_DOWN && _map[_playerPosY + 1][_playerPosX] != '#') _playerPosY++;
		else if (key == KEY_LEFT && _map[_playerPosY][_playerPosX - 1] != '#') _playerPosX--;
		else if (key == KEY_RIGHT && _map[_playerPosY][_playerPosX + 1] != '#') _playerPosX++;
		drawMap(); //常に更新しておかないと宝を拾った時などに反映されなくなる+位置も更新されない
		allocateColor(MAGENTA);
		cursor(_playerPosX, _playerPosY);
		printf("P");
		if (_map[_playerPosY][_playerPosX] == 'G')
		{
			_score++;
			_timer += 20;
			_map[_playerPosY][_playerPosX] = ' ';
		}
		_timer--;
		if (_timer % 20 == 0)
		{
			int x = 1 + rand() % (MAP_W - 3);
			int y = 1 + rand() % (MAP_H - 2);
			if (_map[y][x] == ' ') _map[y][x] = 'G';
		}
		allocateColor(WHITE);
		cursor(0, MAP_H);
		printf("SCORE %d", _score);
		cursor(12, MAP_H);
		printf("TIME %d", _timer);
		Sleep(50);
		if (_timer <= 0)
		{
			allocateColor(RED);
			cursor(MAP_W / 2 - 6, MAP_H / 2);
			printf("GAME OVER");
			Sleep(5000);
			printf("\x1b[2J");
			return 0;
		}
	}
}