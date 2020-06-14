#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES	1
#include <stdio.h>
#include <stdlib.h>
#include<bangtal.h>
#include<time.h>
#include <conio.h>
#include <windows.h>
#pragma comment(lib, "Bangtal.lib")



#define MAX_X 20
#define MAX_Y 20


SceneID scene1, scene2, scene3, scene4, scene5;
TimerID timer1,timer2,  timer3;
ObjectID startButton, restartButton, restartButton2, highButton, lowButton, endButton, endButton2, endButton3, block[MAX_X][MAX_Y], bomb, adv1, adv2, adv3, flag;
int linex[MAX_X];
int liney[MAX_Y];
clock_t start, end;
int gameLevel,finish=0;
int mineCntSet, mineCntSet2;
struct Node
{
	BOOL mine;
	BOOL strip;
	BOOL flag;
	BOOL wall;
	int mineCnt;
}gameMap[MAX_X][MAX_Y];

void initMap(struct Node(*gameMap)[MAX_Y], int gameLevel);
void randMine(struct Node(*gameMap)[MAX_Y], int gameLevel);
void displayMap(struct Node(*gameMap)[MAX_Y], int gameLevel);
void mineRecursive(struct Node(*gameMap)[MAX_Y], int tmpX, int tmpY);
int resultFunc(struct Node(*gameMap)[MAX_Y], int gameLevel);
//int levelSelect(struct Node(*gameMap)[MAX_Y]);
int randx(int x, int y);

void initMap(struct Node(*gameMap)[MAX_Y], int gameLevel)
{
	int i, j;
	int cx, cy;

	for (i = 0; i < MAX_X - gameLevel; i++)
	{
		for (j = 0; j < MAX_Y - gameLevel; j++)
		{
			gameMap[i][j].mine = 0;
			gameMap[i][j].strip = 0;
			gameMap[i][j].mineCnt = 0;
		}
	}

	for (i = 0; i < MAX_X - gameLevel; i++)
	{
		for (j = 0; j < MAX_Y - gameLevel; j++)
		{
			gameMap[i][j].strip = 0;
		}
	}
	randMine(gameMap, gameLevel);

	for (i = 0; i < MAX_X - gameLevel; i++)
	{
		for (j = 0; j < MAX_Y - gameLevel; j++)
		{
			for (cx = i - 1; cx < i + 2; cx++)
			{
				for (cy = j - 1; cy < j + 2; cy++)
				{
					if (gameMap[cx][cy].mine == 1)
					{
						gameMap[i][j].mineCnt++;
					}
				}
			}
		}
	}
	//printf("\n");
	/*for (i = 0; i < MAX_X - gameLevel; i++)
	{
		for (j = 0; j < MAX_Y - gameLevel; j++)
		{
			printf("%d ", gameMap[i][j].mineCnt);
		}
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < MAX_X - gameLevel; i++)
	{
		for (j = 0; j < MAX_Y - gameLevel; j++)
		{
			printf("%d ", gameMap[i][j].mine);
		}
		printf("\n");
	}*/
}

void randMine(struct Node(*gameMap)[MAX_Y], int gameLevel)
{
	int i, j;


	if (gameLevel == 10)  mineCntSet = 10;
	else if (gameLevel == 5) mineCntSet = 30;
	mineCntSet2 = mineCntSet;
	do
	{
		i = randx(1, MAX_X - gameLevel - 2);
		j = randx(1, MAX_Y - gameLevel - 2);
		if (gameMap[i][j].mine == 0)
		{
			gameMap[i][j].mine = 1;
			mineCntSet--;
		}
	} while (mineCntSet);
}

void displayMap(struct Node(*gameMap)[MAX_Y], int gameLevel)
{
	int i, j;
	for (i = 0; i < MAX_X - gameLevel; i++)
	{
		for (j = 0; j < MAX_Y - gameLevel; j++)
		{
			if (gameLevel == 10)
			{
				if (gameMap[i][j].strip == 1)
				{
					if (gameMap[i][j].mine == 1)
					{
						setObjectImage(block[i][j], "images/폭탄.jpg");

					}
					else
					{
						if (gameMap[i][j].mineCnt == 0) { setObjectImage(block[i][j], "images/누름.png"); }
						else if (gameMap[i][j].mineCnt == 1) { setObjectImage(block[i][j], "images/누름1.png"); }
						else if (gameMap[i][j].mineCnt == 2) { setObjectImage(block[i][j], "images/누름2.png"); }
						else if (gameMap[i][j].mineCnt == 3) { setObjectImage(block[i][j], "images/누름3.png"); }
						else if (gameMap[i][j].mineCnt == 4) { setObjectImage(block[i][j], "images/누름4.png"); }
						else if (gameMap[i][j].mineCnt == 5) { setObjectImage(block[i][j], "images/누름5.png"); }
						else if (gameMap[i][j].mineCnt == 6) { setObjectImage(block[i][j], "images/누름6.png"); }
						else if (gameMap[i][j].mineCnt == 7) { setObjectImage(block[i][j], "images/누름7.png"); }
						else if (gameMap[i][j].mineCnt == 8) { setObjectImage(block[i][j], "images/누름8.png"); }
					}
				}
			}
			else if (gameLevel == 5)
			{
				if (gameMap[i][j].strip == 1)
				{
					if (gameMap[i][j].mine == 1)
					{
						setObjectImage(block[i][j], "images/작은폭탄.jpg");
						showObject(block[i][j]);
					}
					else
					{
						if (gameMap[i][j].mineCnt == 0) { setObjectImage(block[i][j], "images/0.png"); }
						else if (gameMap[i][j].mineCnt == 1) { setObjectImage(block[i][j], "images/1.png"); }
						else if (gameMap[i][j].mineCnt == 2) { setObjectImage(block[i][j], "images/2.png"); }
						else if (gameMap[i][j].mineCnt == 3) { setObjectImage(block[i][j], "images/3.png"); }
						else if (gameMap[i][j].mineCnt == 4) { setObjectImage(block[i][j], "images/4.png"); }
						else if (gameMap[i][j].mineCnt == 5) { setObjectImage(block[i][j], "images/5.png"); }
						else if (gameMap[i][j].mineCnt == 6) { setObjectImage(block[i][j], "images/6.png"); }
						else if (gameMap[i][j].mineCnt == 7) { setObjectImage(block[i][j], "images/7.png"); }
						else if (gameMap[i][j].mineCnt == 8) { setObjectImage(block[i][j], "images/8.png"); }
					}

				}
			}

		}
	}
}

void mineRecursive(struct Node(*gameMap)[MAX_Y], int tmpX, int tmpY)
{
	int i, j;

	if (gameMap[tmpX][tmpY].strip == 1) return;
	if (gameMap[tmpX][tmpY].mineCnt)
	{
		gameMap[tmpX][tmpY].strip = 1;
		return;
	}
	//printf("%d %d\n", tmpX, tmpY);

	gameMap[tmpX][tmpY].strip = 1;
	displayMap(gameMap, gameLevel);

	for (i = tmpX - 1; i < tmpX + 2; i++)
	{
		for (j = tmpY - 1; j < tmpY + 2; j++)
		{
			if (i >= 0 && i < MAX_X - gameLevel && j >= 0 && j < MAX_X - gameLevel)
				mineRecursive(gameMap, i, j);
		}
	}
}

int resultFunc(struct Node(*gameMap)[MAX_Y], int gameLevel)
{
	int i, j, a;
	int stripCnt = 0;

	for (i = 0; i < MAX_X - gameLevel; i++)
	{
		for (j = 0; j < MAX_Y - gameLevel; j++)
		{
			if (gameMap[i][j].mine == 0 && gameMap[i][j].strip == 1) stripCnt++;
		}
	}
	a = (MAX_X - gameLevel) * (MAX_Y - gameLevel);
	if (stripCnt == a - mineCntSet2)
	{
		return 1;
	}
	return 0;
}

int randx(int x, int y)
{
	int retVal;
	retVal = rand() % (y - x + 1) + x;
	return retVal;
}

void Game_ready(int a) {
	if (a == 1)
	{
		//setObjectImage(bomb, "images/폭탄이요_.JPG");
		//showObject(bomb);
		for (int k = 0; k < 10; k++) {
			linex[k] = 890 - (60 * k);
			liney[k] = 590 - (60 * k);
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				block[j][i] = createObject("images/블럭3.PNG");
				locateObject(block[j][i], scene3, linex[9 - i], liney[j]);
				showObject(block[j][i]);
			}
		}
	}
	else
	{
		setObjectImage(bomb, "images/하드모드.JPG");
		showObject(bomb);
		for (int k = 0; k < 15; k++) {

			linex[k] = 870 - (35 * k);

			liney[k] = 570 - (35 * k);

		}

		for (int i = 0; i < 15; i++) {

			for (int j = 0; j < 15; j++) {
				block[j][i] = createObject("images/작은블럭.PNG");
				locateObject(block[j][i], scene3, linex[14 - i], liney[j]);
				showObject(block[j][i]);
			}
		}
	}

}

void Game_start() {
	hideObject(startButton);
	hideObject(endButton);
	enterScene(scene3);
	timer1 = createTimer(3000.0f);
	startTimer(timer1);
	showTimer(timer1);
	start = clock();
	//pickObject(flag);  //flag 할지말지
}

void ending() {
	end = clock();
	char time[100];
	sprintf(time, "걸린 시간은 %0.1lf 초 입니다.", (double)(end - start) / CLOCKS_PER_SEC);
	showMessage(time);

}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	for (int i = 0; i < MAX_X - gameLevel; i++)
	{
		for (int j = 0; j < MAX_Y - gameLevel; j++)
		{
			if (object == block[i][j])
			{
				if (gameMap[i][j].mine != 1)
				{

					mineRecursive(gameMap, i, j);
					if (resultFunc(gameMap, gameLevel) == 1)
					{
						displayMap(gameMap, gameLevel);
						ending();
						enterScene(scene4);
					}
				}
				else
				{
					for (i = 0; i < MAX_X - gameLevel; i++)
					{
						for (j = 0; j < MAX_Y - gameLevel; j++)
						{
							if (gameMap[i][j].mine == 1)
							{
								gameMap[i][j].strip = 1;
							}
						}
					}
					startTimer(timer3);
					enterScene(scene5);
					ending();

				}
				displayMap(gameMap, gameLevel);

			}
		}
	}
	if (object == startButton) {
		enterScene(scene2);
	}
	else if (object == restartButton) 
	{
		finish = 0;
		enterScene(scene2);
		for (int i = 0; i < MAX_X; i++)
		{
			for (int j = 0; j < MAX_Y; j++)
			{
				hideObject(block[i][j]);
			}
		}
	}
	else if (object == restartButton2) 
	{
		finish = 0;
		enterScene(scene2);
		for (int i = 0; i < MAX_X; i++)
		{
			for (int j = 0; j < MAX_Y; j++)
			{
				hideObject(block[i][j]);
			}
		}
	}
	else if (object == endButton) {
		endGame();
	}
	else if (object == endButton2) {
		endGame();
	}
	else if (object == endButton3) {
		endGame();
	}
	else if (object == highButton) {
		gameLevel = 5;
		Game_ready(2);
		Game_start();
		initMap(gameMap, gameLevel);
		int a = (MAX_X - gameLevel) * (MAX_Y - gameLevel);
		//printf("%d\n", a - mineCntSet2);
	}
	else if (object == lowButton) {
		gameLevel = 10;
		Game_ready(1);
		Game_start();
		initMap(gameMap, gameLevel);
		int a = (MAX_X - gameLevel) * (MAX_Y - gameLevel);
		//printf("%d\n", a - mineCntSet2);
	}

}


void timerCallback(TimerID timer) {
	if (timer == timer1) {
		enterScene(scene3);
		locateObject(startButton, scene3, 500, 250);
		locateObject(endButton, scene3, 650, 250);
		ending();
	}
	if (timer == timer3) {
		setTimer(timer3, 1.00f);
		displayMap(gameMap, gameLevel);
		stopTimer(timer3);
	}
}



ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown)
{
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown) {
		showObject(object);
	}
	return object;
}



int main() {
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	scene1 = createScene("지뢰 찾기!", "images/지뢰찾기1.PNG");
	scene2 = createScene("게임화면", "images/게임화면1.JPG");
	scene3 = createScene("게임화면", "images/게임화면1.JPG");
	scene4 = createScene("성공..", "images/성공.JPG");
	scene5 = createScene("실패..", "images/실패.JPG");
	startButton = createObject("images/start.PNG", scene1, 600, 100, true);
	restartButton = createObject("images/restart.PNG", scene4, 600, 100, true);
	restartButton2 = createObject("images/restart.PNG", scene5, 600, 100, true);
	endButton = createObject("images/end.PNG", scene1, 600, 50, true);
	endButton2 = createObject("images/end.PNG", scene4, 600, 50, true);
	endButton3 = createObject("images/end.PNG", scene5, 600, 50, true);
	highButton = createObject("images/상.PNG", scene2, 500, 180, true);
	lowButton = createObject("images/하.PNG", scene2, 500, 50, true);
	bomb = createObject("images/폭탄이요.JPG", scene3, 80, 530, true);
	adv2 = createObject("images/로고2.JPG", scene2, 1050, 520, true);
	adv3 = createObject("images/문구.PNG", scene2, 1020, 350, true);
	//flag = createObject("images/깃발1.PNG", scene2, 1020, 350, true); //flag


	startGame(scene1);

}