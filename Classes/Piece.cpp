#include "Piece.h"
Piece::Piece(Vector2f startPos, Color color, int blockCount, const Vector2f *blockPos)
{
	//the constructor recieves position of piece, blocks color, their count and block position array to build piece
	this->blockCount = blockCount;
	this ->posMatrix = blockPos;
	this->pivot = startPos + blockPos[0];
	blocks = new Block[blockCount];//we give some space to block array
	for (int i = 0; i < blockCount; i++) 
	{
		blocks[i] = Block(color);
		blocks[i].ShapeInit(startPos + blockPos[i + 1]);//and setting each colored block at pos plus its shift that we get from matrix
	}
}

Piece::Piece()
{
	//default constructor generates empty piece with pivot at (0, 0)
	pivot = Vector2f(0, 0);
	blockCount = 0;
	posMatrix = {new Vector2f(0, 0)};
	blocks = nullptr;
}

Block Piece::getBlock(int n)
{
	//returns empty block if there's no such block in array
	if (n >= blockCount || n < 0)
		return Block();
	return blocks[n];
}

int Piece::getBlockCount()
{
	return blockCount;
}
//move shit
void Piece::MoveUp()
{
	for (int i = 0; i < blockCount; i++)
		blocks[i].MoveUp();
	pivot += Vector2f(0, -blockSize);
}
void Piece::MoveDown()
{
	for (int i = 0; i < blockCount; i++)
		blocks[i].MoveDown();
	pivot += Vector2f(0, blockSize);
}
void Piece::MoveLeft()
{
	for (int i = 0; i < blockCount; i++)
		blocks[i].MoveLeft();
	pivot += Vector2f(-blockSize, 0);
}
void Piece::MoveRight()
{
	for (int i = 0; i < blockCount; i++)
		blocks[i].MoveRight();
	pivot += Vector2f(blockSize, 0);
}
void Piece::setPos(Vector2f pos)
{
	//we move all block to pos and then resetting piece beacuse everything goes to shit
	//i could just move piece to pos + posMatrix but then i wouldn't use Reset() so i want to do it this way
	for (int i = 0; i < blockCount; i++)
		blocks[i].setPosition(pos);
	pivot = pos + posMatrix[0];//setting pivot
	Reset();
}

void Piece::Rotate()
{
	//we just rotate all the pieces around pivot so ez
	for (int i = 0; i < blockCount; i++)
		blocks[i].RotateAround(pivot);
}

void Piece::Draw(RenderWindow& window) 
{
	for (int i = 0; i < blockCount; i++)
		window.draw(blocks[i]);
}

void Piece::Reset() 
{
	for (int i = 0; i < blockCount; i++)
		blocks[i].ShapeInit(pivot + posMatrix[i + 1] - posMatrix[0]);
}