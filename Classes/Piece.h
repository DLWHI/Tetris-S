#pragma once
#include "SFML/Graphics.hpp"
#include "Block.h" 
#include "Piece.h" 
using namespace sf;
//piece class holds info about piece
class Piece
{
public:
	Piece(Vector2f, Color, int, const Vector2f*);
	Piece();
	Block getBlock(int);//get special numered block from blocks array
	int getBlockCount();//get all block count
	//move shit
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void setPos(Vector2f);//set pos of piece
	void Rotate();//rotation around its center
	void Draw(RenderWindow&);//drawing all blocks so we have less headache
	void Reset();//reset piece if something goes wrong
private:
	int blockCount = 0;//default block count is zero so no piece treat would go
	double blockSize = 22;	//def block size
	Block* blocks;//all the blocks we have
	//usually default tetris pieces have 4 blocks but if sick af and want to make one more piece we could do it with no problem by using dynamic array
	const Vector2f* posMatrix;//this vector array shows all blocks positions from point(sometimes it's origin, sometimes block check PosMatrix class)
	Vector2f pivot;//the rotation pivot of piece
};