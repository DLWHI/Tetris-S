#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
//unused trash class, its just text with a frame
class TextBox
{
public:
	TextBox(std::string, Vector2f, int);
	void setPos(Vector2f);
	void setString(std::string);
	void Draw(RenderWindow&);
private:
	Text text;
	RectangleShape frame;
	Font font;
	int getLineCount(std::string);
	int getLineWidht(std::string);
};

