#include "Block.h"

Block::Block()			//total_block
	:block_shape(0), block_angle(0)
{				
	block_x = 0;
	block_y = 0;
	row = 21;
	col = 14;
	block = new char* [21];
	for (int i = 0; i < 21; i++) {
		block[i] = new char[14];
		for (int j = 0; j < 14; j++) {
			if ((j == 0) || (j == 13))
				block[i][j] = 1;
			else
				block[i][j] = 0;
		}
	}
	for (int j = 0; j < col; j++)
		block[20][j] = 1;
}

Block::~Block()
{
	for (int i = 0; i < row; i++) {
		delete[] block[i];
	}
	delete[] block;
}

Block::Block(const int& shape)
	:block_shape(shape), block_angle(0), row(4), col(4)
{
	block_x = 15;
	block_y = 1;
	block = new char* [4];
	for (int i = 0; i < 4; i++) {
		block[i] = new char[4];
	}
	setBlock();
}

Block::Block(const int& shape, const int& angle, const int& x, const int& y) 
	:block_shape(shape), block_angle(angle), block_x(x), block_y(y), row(4), col(4) //임시블록
{
	block = new char* [4];
	for (int i = 0; i < 4; i++) {
		block[i] = new char[4];
	}
	setBlock();
}

void Block::setShape(const int& shape) {
	block_shape = shape;
	setBlock();
}
int Block::getShape() const {
	return block_shape;
}
void Block::setAngle(const int& angle) {
	block_angle = angle;
	setBlock();
}
int Block::getAngle() const {
	return block_angle;
}
void Block::setX(const int& x) {
	block_x = x;
}
int Block::getX() const {
	return block_x;
}
void Block::setY(const int& y) {
	block_y = y;
}
int Block::getY() const {
	return block_y;
}
int Block::getRow() const {
	return row;
}
int Block::getCol() const {
	return col;
}

void Block::setBlock() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			block[i][j] = block_design[block_shape][block_angle][i][j];
		}
	}
}

char** Block::getBlock()
{
	return block;
}



