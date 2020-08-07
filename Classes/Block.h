#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
//unit piece in this game, field and pieces are built with block with info
//it inherits SFML.RectangleShape class to be a little bit convinient to draw and move it 
class Block: public RectangleShape
{
public:
	Block(Color);
	Block() = default;
	//to show myself a coolass mf a wrote a little bit useless function of moving to sides
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ShapeInit(Vector2f);//this sets the parameters of shape in some place that this methods asks for
	void RotateAround(Vector2f);//this func rotates the position of block around some pivot
	void operator= (Block);//logic of block assignment
private:
	const double size = 22;//size of block+outline, its convinient
};

