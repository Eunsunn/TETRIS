#pragma once
#include "Block.h"
#include <conio.h>
#include <iomanip> 
#include "STAGE.h"
using namespace std;

class Game
{
private:
	STAGE* stage_data;

	int level;
	const int ab_x = 5;
	const int ab_y = 1;
	int score;
	int lines;
	int need_lines;

	Block* total_block;
	Block* now_block;
	Block* next_block;

public:
	Game();
	~Game();

	int show_gameover() const;
	int show_gamestat() const;
	int show_logo() const;
	int show_disciption() const;
	int show_stage_info();
	int set_stage_info(char (*stage_info)[53]);
	int show_bye() const;

	int check_full_line(); 
	int check_mission_line(const int& num);
	int strike_check() const;
	int merge_block();
	int block_start();
	int move_block();
	int make_new_block() const;
	int play();

	int show_total_block() const;
	int show_next_block() const;
	int erase_cur_block() const;
	int show_cur_block(Block* block) const;

	int show_home() const; //집을 보여주는 함수
};

