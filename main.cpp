#define _CRT_NONSTDC_NO_WARNINGS
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#include <stdio.h>
#include <conio.h> //�L�[���͂̎󂯕t��
#include <windows.h> //sleep�֐��p
#include <time.h>

//�}�b�v�f�[�^�̒�`
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

//�Q�[���Ŏg���ϐ��̒�`
int _playerPosX = 1, _playerPosY = 1;
int _score = 0;
int _timer = 300;

//�J�[�\���ʒu���w�肷��֐�
void cursor(int x, int y)
{
	printf("\x1b[%d;%dH", y + 1, x + 1);
}

//�����╶����̐F���w�肷��֐�
enum ColorType{BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
void allocateColor(int col)
{
	printf("\x1b[3%dm", col);
}

//�Q�[����ʂ�`���֐�
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

//main�֐�
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
		drawMap(); //��ɍX�V���Ă����Ȃ��ƕ���E�������Ȃǂɔ��f����Ȃ��Ȃ�+�ʒu���X�V����Ȃ�
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