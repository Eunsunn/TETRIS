#pragma once
#include <Windows.h>
class Cursor
{
public:
	static int gotoxy(int x, int y);	//커서옮기기
	static void setCursorView(bool visible);
};

