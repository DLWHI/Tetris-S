#pragma once
#include "SFML/Graphics.hpp"
#include "Piece.h"
using namespace sf;
//square struct is for each block in field, it hold all info i need to process
struct Square
{
	bool occupied = false;//is block occupied?
	Block block;//block itself
	Vector2f pos;//top left corner of square
	void operator=(Square);//assignment logic
};
//field can be generated with any size
class Field
{
public:
	Field(Vector2f, int, int);
	int Occupie(Piece, int);//this places piece to field if it can no longer move
	bool MoveCheck(Piece, int, Vector2f);//checks if piece can move by some vector
	void RotateCheck(Piece&, int);//checks if piece can freely rotate in its current pos, if cannot moves it so it could rotate
	bool LoseCheck();//checks if we lost, it happens when any block occupies first line
	void Draw(RenderWindow&);//draw
private:
	void ClearLine(int);//cleares full lines
	int FieldCheck();//check for lines to clean
	double blockSize = 22;//def
	RectangleShape frame;//frame of field
	int xSize;
    int ySize;
	Square** field;//all field blocks
};