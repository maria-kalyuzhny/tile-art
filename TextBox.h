#pragma once
#include "GuiElement.h"
class TextBox : public GuiElement
{
public:
	sf::RectangleShape box;
	sf::Text text;

	TextBox(float x, float  y, float w, float  h, string text);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void resize(float w, float h);
	void show();
	void hide();
};

