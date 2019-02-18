#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
int score;

//map size (including borders)
const int width = 20;
const int height = 20;

//snake head position
int x, y;

//snake tail arrays
int tx[100], ty[100];
int tail;

//fruit position
int fx, fy;

//directions
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
	gameOver = false;
	score = 0;

	//makes snake static at the beginning
	dir = STOP;
	//positions snake in middle of the map
	x = width / 2;
	y = height / 2;

	//places one fruit at random location within map borders
	fx = rand() % width;
	fy = rand() % height;

}

void Draw()
{
	//clears console window
	system("cls");

	//creates borders
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fy && j == fx)
				cout << "f";
			else
			{
				bool print = false;
				for (int k = 0; k < tail; k++)
				{
					if (tx[k] == j && ty[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input()
{
	//detects keyboard input, wasd for movement, x for quit
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	//assigns previous snake head positions to the tail
	int prevX = tx[0];
	int prevY = ty[0];
	int prev2X, prev2Y;
	tx[0] = x;
	ty[0] = y;

	for (int i = 1; i < tail; i++)
	{
		prev2X = tx[i];
		prev2Y = ty[i];
		tx[i] = prevX;
		ty[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	//snake movement
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	//game over when snake hits any border or itself
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	for (int i = 0; i < tail; i++)
		if (tx[i] == x && ty[i] == y)
			gameOver = true;



	//gives score when eating fruit and places new fruit
	if (x == fx && y == fy)
	{
		score += 10;
		fx = rand() % width;
		fy = rand() % height;
		tail++;
	}
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		//slow down the game
		//Sleep(10);
	}
	cout << "Uh oh, you are dead!" << endl;
	system("pause");

}