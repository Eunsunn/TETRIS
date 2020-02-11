#pragma once
#include <iostream>
#include "Color.h"
#include "Cursor.h"
using namespace std;

class STAGE
{
private:
	int	speed;
	int stick_rate;
	char** stair;
	bool** stair_check;
	int clear_line;
public:
	STAGE();
	~STAGE();
	STAGE(const int& level);
	int getSpeed() const;
	void setSpeed(const int& speed);
	int getStick_rate() const;
	void setStick_rate(const int& stick_rate);
	int getClear_line() const;
	char** getStair() const;
	bool** getStair_check() const;
	void show_mission() const;
	void show_road(const int& level) const;
};