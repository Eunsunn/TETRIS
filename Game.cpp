#include "Game.h"

//////////////////////////////////
//			��� ����			//
//////////////////////////////////
const int EXT_KEY = 0xffffffe0;	//Ȯ��Ű �νİ� 
const int KEY_LEFT = 0x4b;
const int KEY_RIGHT = 0x4d;
const int KEY_UP = 0x48;
const int KEY_DOWN = 0x50;
const int KEY_ESC = 0x1b;

Game::Game()
	:level(0), score(0), lines(0), need_lines(0)
{
	stage_data = new STAGE(level);
	total_block = new Block();
	now_block = new Block(rand() % 7);
	next_block = new Block(rand() % 7);
}

Game::~Game()
{
	delete stage_data;
	delete total_block;
	delete now_block;
	delete next_block;
}

int Game::show_gameover() const
{
	Color::SetColor(Color::RED);
	Cursor::gotoxy(15, 8);
	cout << "������������������������������";
	Cursor::gotoxy(15, 9);
	cout << "��**************************��";
	Cursor::gotoxy(15, 10);
	cout << "��*        GAME OVER       *��";
	Cursor::gotoxy(15, 11);
	cout << "��**************************��";
	Cursor::gotoxy(15, 12);
	cout << "������������������������������";
	fflush(stdin);
	Sleep(2200);

	_getch();
	system("cls");

	return 0;
}

int Game::show_gamestat() const
{
	static int printed_text = 0;
	Color::SetColor(Color::GRAY);
	if (printed_text == 0)
	{
		Cursor::gotoxy(35, 7);
		cout << "STAGE";

		Cursor::gotoxy(35, 9);
		cout << "SCORE";

		Cursor::gotoxy(35, 12);
		cout << "LINES";

	}
	Cursor::gotoxy(41, 7);
	cout << level + 1;
	Cursor::gotoxy(35, 10);
	cout << setw(10) << score;
	Cursor::gotoxy(35, 13);
	cout << setw(10) << lines;
	return 0;
}

int Game::show_logo() const
{
	int i, j;
	Cursor::gotoxy(13, 3);
	Color::SetColor(Color::WHITE);
	cout << "��������������������������������������������������";
	Sleep(100);
	Cursor::gotoxy(13, 4);
	cout << "���ߡߡ�  �ߡߡ�  �ߡߡ�   �ߡ�     ��     �ߡ� ��";
	Sleep(100);
	Cursor::gotoxy(13, 5);
	cout << "��  ��    ��        ��     �� ��    ��   ��     ��";
	Sleep(100);
	Cursor::gotoxy(13, 6);
	cout << "��  ��    �ߡߡ�    ��     �ߡ�     ��     ��   ��";
	Sleep(100);
	Cursor::gotoxy(13, 7);
	cout << "��  ��    ��        ��     �� ��    ��       �� ��";
	Sleep(100);
	Cursor::gotoxy(13, 8);
	cout << "��  ��    �ߡߡ�    ��     ��  ��   ��   �ߡ�   ��";
	Sleep(100);
	Cursor::gotoxy(13, 9);
	cout << "��������������������������������������������������";

	Cursor::gotoxy(28, 25);
	cout << "Please Press Any Key~!";

	int fullBlock = 0;
	int goAll = 0;
	for (i = 0; i >= 0; i++)
	{
		if (_kbhit())
			break;
		char home[10][20] = {
		   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
		   {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		   {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		   {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		   {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0},
		   {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0},
		   {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 3, 2, 2, 2, 2, 0, 0},
		   {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 3, 2, 2, 2, 2, 0, 0},
		   {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 4, 3, 3, 2, 2, 2, 2, 0, 0},
		   {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 3, 2, 2, 2, 2, 0, 0},
		};
		char road[2][28] = {
		   {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2},
		   {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 2, 2, 2, 2},
		};
		for (int i = 0; i < 10; i++) {
			if (_kbhit())
				break;
			for (int j = 0; j < 20; j++) {
				if (_kbhit())
					break;
				Cursor::gotoxy(40 + 2 * j, 12 + i);
				if (home[i][j] == 1)
				{
					Color::SetColor(Color::DARK_RED);
					cout << "��";
				}
				else if (home[i][j] == 2)
				{
					Color::SetColor(Color::DARK_YELLOW);
					cout << "��";
				}
				else if (home[i][j] == 3)
				{
					Color::SetColor(Color::DARK_GRAY);
					cout << "��";
				}
				else if (home[i][j] == 4)
				{
					Color::SetColor(Color::WHITE);
					cout << "��";
				}
			}
			if (i < 9)
				Sleep(100);
		}
		//�� ���
		if (!fullBlock)
		{
			for (int i = 0; i < 2; i++)
			{
				if (_kbhit())
					break;
				for (int j = 0; j < 28; j++)
				{
					if (_kbhit())
						break;
					Color::SetColor(Color::DARK_YELLOW);
					Cursor::gotoxy(12 + 2 * j, 20 + i);
					if (road[i][j] == 2)
					{
						cout << "��";
					}
					else if (road[i][j] == 3)
					{
						cout << "��";
					}
					else if (road[i][j] == 5)
					{
						cout << "��";
					}
				}
				Sleep(100);
			}
		}

		if (_kbhit())
			break;
		if (!fullBlock)
		{
			if (_kbhit())
				break;
			Sleep(500);
			for (int i = 0; i < 2; i++)
			{
				if (_kbhit())
					break;
				Color::SetColor(Color::DARK_YELLOW);
				for (int j = 0; j < 30; j++)
				{
					if (_kbhit())
						break;
					if (road[1 - i][j] == 3)
					{
						if (_kbhit())
							break;
						road[1 - i][j] = 5;
						Cursor::gotoxy(12 + 2 * (j), 20 + (1 - i));
						cout << "��";
						Sleep(200);
					}
				}
			}
			fullBlock = 1;
		}

		char person[4][4] = {
		   {0, 1, 0, 0},
		   {3, 2, 4, 0},
		   {0, 2, 0, 0},
		   {3, 0, 4, 0},
		};
		if (_kbhit())
			break;
		if (fullBlock == 1 && goAll == 0)
		{
			if (_kbhit())
				break;
			for (int i = 0; i < 20; i++)
			{
				if (_kbhit())
					break;
				Color::SetColor(Color::WHITE);
				for (int j = 0; j < 4; j++)
				{
					if (_kbhit())
						break;
					for (int k = 0; k < 4; k++)
					{
						if (_kbhit())
							break;
						Cursor::gotoxy(12 + 2 * i + 2 * k, 16 + j);
						if (person[j][k] == 1)
						{
							cout << "��";
						}
						else if (person[j][k] == 2)
						{
							cout << "��";
						}
						else if (person[j][k] == 3)
						{
							cout << "/";
						}
						else if (person[j][k] == 4)
						{
							cout << "��";
						}
					}
				}
				Sleep(200);
				if (i < 19)
				{
					for (int j = 0; j < 4; j++)
					{
						Cursor::gotoxy(12 + 2 * i, 16 + j);
						cout << "     ";
					}
				}

			}
			goAll = 1;
		}
		if (_kbhit())
			break;
		Sleep(30);
	}

	_getch();
	system("cls");

	return 0;
}

int Game::show_disciption() const
{

	Cursor::gotoxy(7, 3);
	Color::SetColor(Color::WHITE);
	cout << "����������������������������������������������������";
	Sleep(10);
	Cursor::gotoxy(7, 4);
	cout << "��            ����� ������ �����մϴ�.           ��";
	Sleep(10);
	Cursor::gotoxy(7, 5);
	cout << "��    ������ ���� �濡 5�ܰ��� ������ �ֽ��ϴ�.   ��";
	Sleep(10);
	Cursor::gotoxy(7, 6);
	cout << "��                                                ��";
	Sleep(10);
	Cursor::gotoxy(7, 7);
	cout << "��  1�ܰ� : �̿ϼ��� ����� ä���ּ���!           ��";
	Sleep(10);
	Cursor::gotoxy(7, 8);
	cout << "��  2�ܰ� : ��� ���� �����̸� ä���ּ���!        ��";
	Sleep(10);
	Cursor::gotoxy(7, 9);
	cout << "��  3�ܰ� : �̿ϼ��� ����� ä���ּ���!           ��";
	Sleep(10);
	Cursor::gotoxy(7, 10);
	cout << "��  4�ܰ� : �̿ϼ��� ����� ä���ּ���!           ��";
	Sleep(10);
	Cursor::gotoxy(7, 11);
	cout << "��  5�ܰ� : ���� �ǳʷ��� �ٸ��� ������ּ���!    ��";
	Sleep(10);
	Cursor::gotoxy(7, 12);
	cout << "��                                                ��";
	Sleep(10);
	Cursor::gotoxy(7, 13);
	cout << "�� ������ ��� Ŭ������ ���� �����ϱ� �����մϴ�! ��";
	Sleep(10);
	Cursor::gotoxy(7, 14);
	cout << "����������������������������������������������������";
	Sleep(10);
	Cursor::gotoxy(7, 15);
	cout << "��*�������� �� ����� ��� ä��� ���� �ϼ��˴ϴ�*��";
	Sleep(10);
	Cursor::gotoxy(7, 16);
	cout << "����������������������������������������������������";
	Sleep(10);
	Cursor::gotoxy(7, 17);
	cout << "�� �������� �� ����� �ٰ� ���� ������ ���� ����  ��";
	Sleep(10);
	Cursor::gotoxy(7, 18);
	cout << "�� ��Ʈ�������� �� �� Ŭ�����Ҷ����� �������� ��  ��";
	Sleep(10);
	Cursor::gotoxy(7, 19);
	cout << "�� ����� �� ĭ�� ä�����ϴ�.                     ��";
	Sleep(10);
	Cursor::gotoxy(7, 20);
	cout << "����������������������������������������������������";

	Cursor::gotoxy(40, 22);
	cout << "Please Press Any Key~!";


	Color::SetColor(Color::GRAY);
	Cursor::gotoxy(60, 7);
	cout << "����������<GAME KEY>������������";
	Sleep(10);
	Cursor::gotoxy(60, 8);
	cout << "�� UP   : Rotate Block        ��";
	Sleep(10);
	Cursor::gotoxy(60, 9);
	cout << "�� DOWN : Move One-Step Down  ��";
	Sleep(10);
	Cursor::gotoxy(60, 10);
	cout << "�� SPACE: Move Bottom Down    ��";
	Sleep(10);
	Cursor::gotoxy(60, 11);
	cout << "�� LEFT : Move Left           ��";
	Sleep(10);
	Cursor::gotoxy(60, 12);
	cout << "�� RIGHT: Move Right          ��";
	Sleep(10);
	Cursor::gotoxy(60, 13);
	cout << "�� ESC: Exit Game             ��";
	Sleep(10);
	Cursor::gotoxy(60, 14);
	cout << "��������������������������������";

	fflush(stdin);
	_getch();
	system("cls");

	return 0;
}

int Game::show_stage_info()
{
	char stage_info[11][53] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4, 4, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 4, 4, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 1, 1, 1, 6, 6, 6, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 4, 4, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 2, 1, 1, 6, 6, 6, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 4, 4, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 1, 1, 1, 6, 6, 6, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 4, 4, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
	{0, 0, 1, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
	{0, 1, 1, 4, 4, 4, 4, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
	{1, 1, 1, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
	};

	if (level != 0) {
		int end;
		switch (level) {
		case 1:	end = 3; break;
		case 2: end = 11; break;
		case 3: end = 21; break;
		case 4: end = 31; break;
		case 5: end = 40; break;
		}
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j <= end; j++) {
				if (stage_info[i][j] == 1) {
					stage_info[i][j] = 3;
				}
			}
		}
	}

	system("cls");
	Cursor::gotoxy(45, 5);
	Color::SetColor(Color::WHITE);
	cout << "----STAGE INFORMATION----";
	for (int i = 0; i < 11; i++)
	{
		Cursor::gotoxy(6, 12 + i);
		for (int j = 0; j < 53; j++) {
			switch (stage_info[i][j]) {
			case 0: case 1: case 2: case 3:
				Color::SetColor(Color::WHITE);
				break;
			case 4:
				Color::SetColor(Color::DARK_YELLOW);
				break;
			case 5:
				Color::SetColor(Color::BLUE);
				break;
			case 6:
				Color::SetColor(Color::DARK_YELLOW);
				break;
			case 7:
				Color::SetColor(Color::DARK_RED);
				break;
			}
			switch (stage_info[i][j]) {
			case 0:
				cout << "  ";
				break;
			case 1:
				cout << "��";
				break;
			case 2:
				cout << "��";
				break;
			case 3: case 5: case 6: case 7:
				cout << "��";
				break;
			case 4:
				cout << "��";
				break;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (i == level) Color::SetColor((level % 6) + 1);
		else Color::SetColor(Color::WHITE);
		switch (i) {
		case 0: Cursor::gotoxy(6, 10); break;
		case 1: Cursor::gotoxy(19, 10); break;
		case 2: Cursor::gotoxy(35, 10); break;
		case 3: Cursor::gotoxy(53, 10); break;
		case 4: Cursor::gotoxy(71, 10); break;
		}
		cout << " STAGE " << (i + 1);
	}

	Sleep(2200);

	system("cls");
	return 0;
}

int Game::check_full_line()
{
	char** block = this->total_block->getBlock();
	int i, j, k;
	for (i = 0; i < 20; i++)
	{
		for (j = 1; j < 13; j++)
		{
			if (block[i][j] == 0)
				break;
		}
		if (j == 13)	//������ �� ä������
		{
			lines++;
			check_mission_line(i - 11);
			show_total_block();
			stage_data->show_mission();
			Color::SetColor(Color::BLUE);
			Cursor::gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "��";
				Sleep(10);
			}
			Cursor::gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				cout << "  ";
				Sleep(10);
			}

			for (k = i; k > 0; k--)
			{
				for (j = 1; j < 13; j++)
					block[k][j] = block[k - 1][j];
			}
			for (j = 1; j < 13; j++)
				block[0][j] = 0;
			score += 100 + (level * 10) + (rand() % 10);
			show_gamestat();
		}
	}
	return 0;
}

int Game::check_mission_line(const int& num)
{
	if (num < 0) {
		return 0;
	}
	char** stair = this->stage_data->getStair();
	bool** stair_check = this->stage_data->getStair_check();
	for (int j = 0; j < 9; j++) {
		if (stair[num][j] == 1)
			if (stair_check[num][j] == false) {
				stair_check[num][j] = !stair_check[num][j];
				this->need_lines++;
				stage_data->show_mission();
				break;
			}
	}
	return 0;
}

int Game::strike_check() const
{
	int i, j;
	int block_dat;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (((now_block->getX() + j) == 0) || ((now_block->getX() + j) == 13))
				block_dat = 1;
			else if (i + now_block->getY() < 0 || (i + now_block->getY()) > 20)
				continue;
			else
				block_dat = total_block->getBlock()[now_block->getY() + i][now_block->getX() + j];


			if ((block_dat == 1) && (now_block->getBlock()[i][j] == 1))																							//�������� ��ǥ�� ��������
			{
				return 1;
			}
			block_dat = 0;
		}
	}
	return 0;
}

int Game::merge_block()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		if ((i + now_block->getY()) < 0 || (i + now_block->getY()) > 20)
			continue;

		for (j = 0; j < 4; j++)
		{
			if ((now_block->getX() + j) > 13)
				continue;
			total_block->getBlock()[now_block->getY() + i][now_block->getX() + j] |= now_block->getBlock()[i][j];
		}
	}
	check_full_line();
	show_total_block();

	return 0;
}

int Game::block_start()
{
	now_block->setX(5);
	now_block->setY(-3);
	now_block->setAngle(0);
	return 0;
}


int Game::move_block()
{
	erase_cur_block();
	now_block->setY(now_block->getY() + 1); //���� ��ĭ �Ʒ��� ����
	if (strike_check() == 1)
	{
		if (now_block->getY() < 0)	//���ӿ���
		{
			return 1;
		}
		now_block->setY(now_block->getY() - 1);
		merge_block();
		delete now_block;
		now_block = next_block;
		next_block = new Block(make_new_block());

		block_start();	//angle,x,y�� ��������
		show_next_block();
		return 2;
	}
	return 0;
}

int Game::make_new_block() const
{
	int i = rand() % 100;
	if (i <= stage_data->getStick_rate())		//����� ����Ȯ�� ���
		return 0;							//����� ������� ����

	return (rand() % 6) + 1;
}

//���� �����ִ� �Լ�
int Game::show_home() const
{
	Color::SetColor(Color::WHITE);
	Cursor::gotoxy(30, 1);
	cout << "                            \\\\^\\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 2);
	cout << "                           \\\\   \\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 3);
	cout << "                          \\\\     \\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 4);
	cout << "                         \\\\       \\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 5);
	cout << "                 |=^|   \\\\    _    \\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 6);
	cout << "               __|= |__\\\\    (+)    \\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 7);
	cout << "              \\LLLLLLL\\\\      ~      \\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 8);
	cout << "             \\LLLLLLL\\\\               \\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 9);
	cout << "            \\LLLLLLL\\\\                 \\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 10);
	cout << "           \\LLLLLLL\\\\  |~[|]~| |~[|]~|  \\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 11);
	cout << "           ^| [|] \\\\   | [|] | | [|] |   \\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 12);
	cout << "           ^| [|] \\\\   | [|] | | [|] |   \\\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 13);
	cout << "            | [|] ^|   |_[|]_| |_[|]_|   |^" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 14);
	cout << "         ___|______|                     |" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 15);
	cout << "        \\LLLLLLLLLL|_____________________|" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 16);
	cout << "       \\LLLLLLLLLLL\\LLLLLLLLLLLLLLLLLLLLLL\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 17);
	cout << "      \\LLLLLLLLLLL\\LLLLLLLLLLLLLLLLLLLLLLLL\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 18);
	cout << "      ^||^^^^^^^^\\LLLLLLLLLLLLLLLLLLLLLLLLLL\\" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 19);
	cout << "       || |~[|]~|^^||^^^^^^^^^^||^|~[|]~|^||^^" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 20);
	cout << "       || | [|] |  ||  |~~~~|  || | [|] | ||" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 21);
	cout << "       || |_[|]_|  ||  | [] |  || |_[|]_| ||" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 22);
	cout << "       ||__________||  |   o|  ||_________||" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 23);
	cout << "     .'||][][][][][||  | [] |  ||[][][][][||.'." << endl;
	Sleep(10);
	Cursor::gotoxy(30, 24);
	cout << "    .\"'||[][][][][]||_-`----'-_||[][][][][|| \".\"" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 25);
	cout << "  .(')^(.)(').( )'^@\\-- -- - --\\@( )'( ).(( )^(.)^" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 26);
	cout << " '( )^(`)'.(').( )@\\-- -- - -- -\\@ (.)'(.),( ).(')." << endl;
	Sleep(10);
	Cursor::gotoxy(30, 27);
	cout << " \".'.'.\" .\" '.\". @\\- - --- -- - -\\@ '.\".'.\".'.\".'.\"" << endl;
	Sleep(10);
	Cursor::gotoxy(30, 28);
	cout << " \". '' \".\".\".'.'@\\ - -- -- -- -- -\\@\".'..'\".'.\"'.'.'" << endl;

	fflush(stdin);
	Sleep(1000);

	Color::SetColor(Color::DARK_YELLOW);
	Cursor::gotoxy(42, 13);
	cout << "������������������������������";
	Cursor::gotoxy(42, 14);
	cout << "��**************************��";
	Cursor::gotoxy(42, 15);
	cout << "��*        I'M HOME        *��";
	Cursor::gotoxy(42, 16);
	cout << "��**************************��";
	Cursor::gotoxy(42, 17);
	cout << "������������������������������";
	Color::SetColor(Color::WHITE);
	fflush(stdin);

	_getch();
	system("cls");

	return 0;
}

int Game::show_bye() const {
	Color::SetColor(Color::GRAY);
	Cursor::gotoxy(15, 8);
	cout << "������������������������������";
	Cursor::gotoxy(15, 9);
	cout << "��**************************��";
	Cursor::gotoxy(15, 10);
	cout << "��*           Bye          *��";
	Cursor::gotoxy(15, 11);
	cout << "��**************************��";
	Cursor::gotoxy(15, 12);
	cout << "������������������������������";
	Color::SetColor(Color::WHITE);
	fflush(stdin);
	Sleep(1000);
	system("cls");
	return 0;
}

int Game::play()
{
	int i;
	int is_gameover = 0;
	char keytemp;
	srand((unsigned)time(NULL));
	Cursor::setCursorView(false);
	show_logo();
	show_disciption();
	while (1)
	{
		show_stage_info();
		show_total_block();
		now_block->setShape(make_new_block());
		next_block->setShape(make_new_block());
		show_next_block();
		stage_data->show_road(level);
		stage_data->show_mission();
		block_start();
		show_gamestat();
		for (i = 1; 1; i++)
		{
			if (_kbhit())
			{
				keytemp = _getch();
				if (keytemp == EXT_KEY)
				{
					keytemp = _getch();
					switch (keytemp)
					{
					case KEY_UP:		//ȸ���ϱ�
						now_block->setAngle((now_block->getAngle() + 1) % 4);
						if (strike_check() == 0)
						{
							now_block->setAngle(((now_block->getAngle() - 1) % 4 < 0 ? 3 : (now_block->getAngle() - 1) % 4));
							erase_cur_block();
							now_block->setAngle((now_block->getAngle() + 1) % 4);
							show_cur_block(now_block);
						}
						else {
							int j;
							now_block->setAngle(((now_block->getAngle() - 1) % 4 < 0 ? 3 : (now_block->getAngle() - 1) % 4));
							erase_cur_block();
							now_block->setAngle((now_block->getAngle() + 1) % 4);
							bool check = false;
							for (j = 1; j <= 4; j++) {
								now_block->setX(now_block->getX() - j);
								if (now_block->getX() < 1) {
									now_block->setX(now_block->getX() + j);
									break;
								}
								if (strike_check() == 0) {
									check = true;
									break;
								}
								now_block->setX(now_block->getX() + j);
							}
							if (!check) {
								now_block->setAngle(((now_block->getAngle() - 1) % 4 < 0 ? 3 : (now_block->getAngle() - 1) % 4));
							}
							show_cur_block(now_block);
						}
						break;
					case KEY_LEFT:		//�������� �̵�
						if (now_block->getX() > 1)
						{
							erase_cur_block();
							now_block->setX(now_block->getX() - 1);
							if (strike_check() == 1) {
								now_block->setX(now_block->getX() + 1);
							}
							show_cur_block(now_block);
						}
						break;
					case KEY_RIGHT:		//���������� �̵�
						if (now_block->getX() < 13)
						{
							erase_cur_block();
							now_block->setX(now_block->getX() + 1);
							if (strike_check() == 1) {
								now_block->setX(now_block->getX() - 1);
							}
							show_cur_block(now_block);
						}
						break;
					case KEY_DOWN:		//�Ʒ��� �̵�
						is_gameover = move_block();
						show_cur_block(now_block);
						break;
					}
				}
				if (keytemp == 32)	//�����̽��ٸ� ��������
				{
					while (is_gameover == 0)
					{
						is_gameover = move_block();
					}
					show_cur_block(now_block);
				}
				if (keytemp == KEY_ESC) {
					show_bye();
					return 0;
				}

			}
			if (i % stage_data->getSpeed() == 0)
			{
				is_gameover = move_block();
				show_cur_block(now_block);
			}
			if (stage_data->getClear_line() <= need_lines)	//Ŭ���� ��������
			{
				level++;
				Sleep(500);
				if (level == 5) {
					show_stage_info();
					system("cls");
					show_home();
					return 0;
				}
				else {
					need_lines = 0;
					delete total_block;
					total_block = new Block();
					delete stage_data;
					stage_data = new STAGE(level);
					show_stage_info();
					show_total_block();
					stage_data->show_road(level);
					stage_data->show_mission();
					show_gamestat();
					show_next_block();
				}
			}
			if (is_gameover == 1)
			{
				Sleep(1000);
				is_gameover = 0;
				score = 0;
				show_gameover();
				Color::SetColor(Color::GRAY);
				break;
			}
			Cursor::gotoxy(77, 23);
			Sleep(15);
			Cursor::gotoxy(77, 23);
		}
		//init() �κ�
		level = 0;
		lines = 0;
		need_lines = 0;
		//���� �� �ʱ�ȭ
		delete stage_data;
		stage_data = new STAGE(level);
		delete total_block;
		total_block = new Block();
	}
	return 0;
}

int Game::show_total_block() const
{
	char** block = total_block->getBlock();
	Color::SetColor(Color::DARK_GRAY);
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (j == 0 || j == 13 || i == 20)		//������ ���� �ܺ� ���� ����
			{
				Color::SetColor((level % 6) + 1);
			}
			else {
				Color::SetColor(Color::DARK_GRAY);
			}
			Cursor::gotoxy((j * 2) + ab_x, i + ab_y);
			if (block[i][j] == 1)
			{
				cout << "��";
			}
			else {
				cout << "  ";
			}

		}
	}
	Color::SetColor(Color::BLACK);
	Cursor::gotoxy(77, 23);
	return 0;
}
int Game::show_next_block() const
{
	Color::SetColor((level + 1) % 6 + 1);
	for (int i = 1; i < 7; i++)
	{
		Cursor::gotoxy(33, i);
		for (int j = 0; j < 6; j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				cout << "��";
			}
			else {
				cout << "  ";
			}
		}
	}
	show_cur_block(next_block);
	return 0;
}
int Game::erase_cur_block() const
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((j + now_block->getY()) < 0)
				continue;

			if (now_block->getBlock()[j][i] == 1)
			{
				Cursor::gotoxy((i + now_block->getX()) * 2 + ab_x, j + now_block->getY() + ab_y);
				cout << "  ";
			}
		}
	}
	return 0;
}
int Game::show_cur_block(Block* block) const
{
	int i, j;

	switch (block->getShape())
	{
	case 0:
		Color::SetColor(Color::RED);
		break;
	case 1:
		Color::SetColor(Color::BLUE);
		break;
	case 2:
		Color::SetColor(Color::SKY_BLUE);
		break;
	case 3:
		Color::SetColor(Color::WHITE);
		break;
	case 4:
		Color::SetColor(Color::YELLOW);
		break;
	case 5:
		Color::SetColor(Color::VOILET);
		break;
	case 6:
		Color::SetColor(Color::GREEN);
		break;
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((j + block->getY()) < 0)
				continue;

			if (block->getBlock()[j][i] == 1)
			{
				Cursor::gotoxy((i + block->getX()) * 2 + ab_x, j + block->getY() + ab_y);
				cout << "��";

			}
		}
	}
	Color::SetColor(Color::BLACK);
	Cursor::gotoxy(77, 23);
	return 0;
}
