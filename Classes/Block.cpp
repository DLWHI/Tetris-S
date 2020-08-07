#include "Block.h"
Block::Block(Color color)
{
	//all blocks a pretty same so we just need to know which color to generate
	setFillColor(color);
}

void Block::ShapeInit(Vector2f pos)
{
	//inheritance form RectangleShape lets as easily set paremeters of the block where we need
	setSize(Vector2f(size - 2, size - 2));
	setOutlineColor(Color::Black);
	setOutlineThickness(2);
	setPosition(pos);
}
//movin shit
void Block::MoveUp()
{
	Vector2f oldPos = getPosition();
	Vector2f move(0, -this->size);
	setPosition(oldPos + move);
}
void Block::MoveDown() 
{
	Vector2f oldPos = getPosition();
	Vector2f move(0, this->size);
	setPosition(oldPos + move);
}
void Block::MoveLeft()
{
	Vector2f oldPos = getPosition();
	Vector2f move(-this->size, 0);
	setPosition(oldPos + move);
}
void Block::MoveRight()
{
	Vector2f oldPos = getPosition();
	Vector2f move(this->size, 0);
	setPosition(oldPos + move);
}

void Block::RotateAround(Vector2f pivot)
{
	//rotation alghorithm is stupid as it can be
	Vector2f oldPos = getPosition();
	move(-pivot);//moving block to coordinate system where pivot is origin
	Vector2f rot = getPosition() + Vector2f(this->size/2, this->size/2);//using simple rotation around origin transform, gotta subtract vector that points to center of block so
	//it would rotate center and not the top left corner(sfml has all rect shape origin at top left corner)
	setPosition(Vector2f(-rot.y, rot.x));//applying transform
	move(pivot - Vector2f(this->size / 2, this->size / 2));//and moving it back and shifting by same origin vector
	//dumb but workie
}

void Block::operator= (Block other) 
{
	//in fact, to assign one block to other we need just to know color, they're all the same pog
	setFillColor(other.getFillColor());
}
