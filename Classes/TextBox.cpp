#include "TextBox.h"
TextBox::TextBox(std::string txt, Vector2f pos, int outlineTh) 
{
	font.loadFromFile("font.ttf");

	text = Text();
	text.setString(txt);
	text.setCharacterSize(33);
	text.setFillColor(Color::White);
	text.setPosition(pos);
	text.setFont(font);

	frame.setFillColor(Color::Black);
	frame.setOutlineColor(Color::White);
	frame.setOutlineThickness(outlineTh);
	frame.setPosition(Vector2f(pos.x - 1, pos.y + 6));
	frame.setSize(Vector2f(getLineWidht(txt) * 25 + 6, getLineCount(txt)*33 + 6));
}

void TextBox::setPos(Vector2f pos) 
{
	text.setPosition(pos);
	frame.setPosition(pos + Vector2f(2, 0));
}

void TextBox::setString(std::string str)
{
	text.setString(str);
}

void TextBox::Draw(RenderWindow& window)
{
	window.draw(frame);
	window.draw(text);
}

int TextBox::getLineCount(std::string str) 
{
	int ret = 1;
	for (int i = 0; i < str.length(); i++)
		if (str[i] == '\n')
			ret++;
	return ret;
}

int TextBox::getLineWidht(std::string str)
{
	int ret  = 0, max = INT_MIN;
	for (int i = 0; i < str.length(); i++, ret++) 
	{
		if (ret > max)
			max = ret;
		if(str[i] == '\n')
			ret = 0;
	}
	return max;
}