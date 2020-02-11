#include "STAGE.h"

STAGE::STAGE() :STAGE(0) {}
STAGE::~STAGE(){}
STAGE::STAGE(const int& level)
{
	stair = new char*[9];
	stair_check = new bool* [9];
	for (int i = 0; i < 9; i++) {
		stair[i] = new char[9];
		stair_check[i] = new bool[9];
		for (int j = 0; j < 9; j++) {
			stair_check[i][j] = false;
		}
	}
	switch(level)
	{
	case 0:
		speed = 40;
		stick_rate = 20;
		clear_line = 6;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (i == 6) {
					if (j == 2)
						stair[i][j] = 1;
					else if (j > 2)
						stair[i][j] = 2;
				}
				else if (i == 7) {
					if (j >= 1 && j <= 2)
						stair[i][j] = 1;
					else if (j > 2)
						stair[i][j] = 2;
				}
				else if (i == 8) {
					if (j >= 0 && j <= 2)
						stair[i][j] = 1;
					else if (j > 2)
						stair[i][j] = 2;
				}
				else {
					stair[i][j] = 0;
				}
			}
		}
		break;
	case 1:
		speed = 38;
		stick_rate = 18;
		clear_line = 9;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (i == 6) {
					if (j >= 2 && j <= 6)
						stair[i][j] = 1;
					else
						stair[i][j] = 2;
				}
				else if (i == 7) {
					if (j >= 3 && j <= 5)
						stair[i][j] = 1;
					else
						stair[i][j] = 2;
				}
				else if (i == 8) {
					if (j == 4)
						stair[i][j] = 1;
					else
						stair[i][j] = 2;
				}
				else {
					stair[i][j] = 0;
				}
			}
		}
		break;
	case 2:
		speed = 35;
		stick_rate = 18;
		clear_line = 10;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (i == 3) {
					if (j == 6)
						stair[i][j] = 1;
					else if (j > 6)
						stair[i][j] = 2;
				}
				else if (i == 4 && j == 5) {
					stair[i][j] = 1;
				}
				else if (i == 5 && (j == 3 || j == 4)) {
					stair[i][j] = 1;
				}
				else if (i == 6 && (j == 4 || j == 2)) {
					stair[i][j] = 1;
				}
				else if (i == 7 && (j == 4 || j == 1)) {
					stair[i][j] = 1;
				}
				else if (i == 8 && (j == 4 || j == 0)) {
					stair[i][j] = 1;
				}
				else {
					stair[i][j] = 0;
				}
			}
		}
		break;
	case 3:
		speed = 30;
		stick_rate = 17;
		clear_line = 18;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (i == 4 && j >= 1 && j <= 4) {
					stair[i][j] = 1;
				}
				else if (i == 5 && j >= 4 && j <= 5) {
					stair[i][j] = 1;
				}
				else if (i == 6 && j >= 4 && j <= 6) {
					stair[i][j] = 1;
				}
				else if (i == 7 && j >= 4 && j <= 7) {
					stair[i][j] = 1;
				}
				else if (i == 8 && j >= 4 && j <= 8) {
					stair[i][j] = 1;
				}
				else if (i >= 4 && j == 0) {
					stair[i][j] = 2;
				}
				else {
					stair[i][j] = 0;
				}
			}
		}
		break;
	case 4:
		speed = 25;
		stick_rate = 16;
		clear_line = 39;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if ((i >= 2 && i <= 6) && (j >= 3 && j <= 5)) {
					stair[i][j] = 1;
				}
				else if ((i == 1 || i == 7) && j >= 2 && j <= 6) {
					stair[i][j] = 1;
				}
				else if ((i == 0 || i == 8) && j >= 1 && j <= 7) {
					stair[i][j] = 1;
				}
				else {
					stair[i][j] = 2;
				}
			}
		}
		break;
	}
}
int STAGE::getSpeed() const 
{
	return speed;
}
void STAGE::setSpeed(const int& speed) 
{
	this->speed = speed;
}
int STAGE::getStick_rate() const 
{
	return stick_rate;
}
void STAGE::setStick_rate(const int& stick_rate) 
{
	this->stick_rate = stick_rate;
}
int STAGE::getClear_line() const {
	return clear_line;
}
char** STAGE::getStair() const {
	return stair;
}
bool** STAGE::getStair_check() const {
	return stair_check;
}
void STAGE::show_mission() const {
	Color::SetColor(Color::WHITE);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			Cursor::gotoxy(50 + j*2, 12 + i);
			if (stair[i][j] == 1)
				cout << (stair_check[i][j] ? "■" : "□");
		}
	}
}
void STAGE::show_road(const int& level) const {
	Color::SetColor((level % 6) + 1);		//외벽
	for (int i = 0; i < 11; i++)
	{
		Cursor::gotoxy(48, 11 + i);
		for (int j = 0; j < 11; j++)
		{
			if (i == 0 || i == 10 || j == 0 || j == 10)
			{
				cout << "■";
			}
			else {
				cout << "  ";
			}
		}
	}
	switch (level) {						//내부
	case 0: case 1: case 2: case 3:
		Color::SetColor(Color::DARK_YELLOW);
		for (int i = 0; i < 9; i++) {
			Cursor::gotoxy(50, 12 + i);
			for (int j = 0; j < 9; j++) {
				if (stair[i][j] == 2)
					cout << "▒";
				else
					cout << "  ";
			}
		}
		break;
	case 4:
		for (int i = 0; i < 9; i++) {
			Cursor::gotoxy(50, 12 + i);
			if (i == 0 || i == 1 || i == 7 || i == 8)
				Color::SetColor(Color::DARK_YELLOW);
			else 
				Color::SetColor(Color::BLUE);
			for (int j = 0; j < 9; j++) {
				if (stair[i][j] == 2)
					cout << "▒";
				else
					cout << "  ";
			}
		}
		break;
	}
}