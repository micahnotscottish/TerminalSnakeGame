#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <Windows.h>
using namespace std;
const int height = 20;
const int width = 20;
bool gameOver, exitGame;
int snakeX, snakeY, fruitX, fruitY, score, highScore;
int tailX[100], tailY[100];
int nTail =0;
int scoreNum = 0;
int scoreArray[50];
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
ofstream outScore;
ifstream inScore;
ofstream outAllScore;
ifstream inAllScore;


void draw();
void setup();
void input();
void logic();
void menu();
void playgame();
void viewscores();
void clearstats();

int main()
{
	setup();
	
	while (exitGame == false)
	{
		menu();

	}
	
	outScore.close();
	inScore.close();
	
	return 0;
}


void draw()
{
	system("cls");

	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == snakeY && j == snakeX)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "@";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					
					if (tailX[k] == j && tailY[k] == i)
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

	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
	cout << "Highscore: " << highScore << endl;
}


void setup()
{
	gameOver = false;
	exitGame = false;
	dir = STOP;
	snakeX = width / 2;
	snakeY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	nTail = 0;
	inScore.open("Highscore.txt");
	inScore >> highScore;
	inScore.close();
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case'a':
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
		}
	}
}

void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = snakeX;
	tailY[0] = snakeY;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}

	switch (dir)
	{
	case LEFT:
		snakeX--;
		break;
	case RIGHT:
		snakeX++;
		break;
	case UP:
		snakeY--;
		break;
	case DOWN:
		snakeY++;
		break;
	default:
		break;
	}

	if (snakeX > width-1 || snakeX < 0 || snakeY > height-1 || snakeY < 0)
		gameOver = true;
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == snakeX && tailY[i] == snakeY)
			gameOver = true;
	}

	if (snakeX == fruitX && snakeY == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}


}

void menu()
{
	system("cls");
	cout << "1. Play Game" << endl;
	cout << "2. View Scores" << endl;
	cout << "3. Clear Stats" << endl;
	cout << "0. Exit" << endl;
	cout << "Select an option: " << endl;

	int input;
	cin >> input;

	switch (input)
	{
	case 0:
		exitGame = true;
		break;
	case 1:
		playgame();
		break;
	case 2:
		viewscores();
		break;
	case 3:
		clearstats();
		break;
	default:
		break;

	}
}

void playgame()
{
	setup();

	while (gameOver == false)
	{
		draw();
		input();
		logic();
		Sleep(50);

	}
	system("cls");
	cout << "GAME OVER" << endl;

	if (score > highScore)
	{
		outScore.open("HighScore.txt");
		outScore << score;
		outScore.close();
		cout << "New High Score!: " << score << endl << endl;;
	}
	if (score <= highScore)
	{
		cout << "Score: " << score << endl << endl;
	}
	outAllScore.open("AllScores.txt", ofstream::app);
	outAllScore << score << endl;
	outAllScore.close();
	cout << "Press Any Key to Return to Menu";
	
	_getch();
}

void viewscores()
{
	system("cls");
	inAllScore.open("AllScores.txt");
	if (!inAllScore)
	{
		cout << "bad file";
	}
	scoreNum = 0;
	int readScore = 0;
	int totalScores =0;

	for (int i = 0; 0==0; i++)
	{
		inAllScore >> scoreArray[i];
		if (!inAllScore.eof())
		{
			scoreNum++;
			totalScores += scoreArray[i];
		}
		else break;
		
	}
	inAllScore.close();

	cout << setw(17) << "Score Stats" << endl;
	cout << "===========================" << setw(0) << endl;
	cout << "High Score: " << highScore << endl;
	if (scoreNum != 0)
		cout << "Average Score: " << totalScores / scoreNum << endl;

	cout << "Previous Scores:" << endl;
	
	for (int j = 0; j <= scoreNum; j++)
	{
		cout << j+1 << ". " << scoreArray[j] << endl;
	}

	cout << endl << "Press Any Key to Return to Menu";

	_getch();

}

void clearstats()
{
	system("cls");
	cout << "Are you sure you would like to clear ALL stats: " << endl;
	cout << "1 = YES" << endl << "2 = NO" << endl;
	char input;
	cin >> input;
	switch (input)
	{
	case '1':
	{
		outScore.open("HighScore.txt", ofstream::out, ofstream::trunc);
		outAllScore.open("AllScores.txt", ofstream::out, ofstream::trunc);
		outScore.close();
		outAllScore.close();

	}
	case '2':
		break;
	default:
		break;
	}

}