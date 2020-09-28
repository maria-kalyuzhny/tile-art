#pragma once
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <string>
#include "GuiElement.h"
using namespace std;

class Button : public GuiElement
{
public:
	string name;
	float icon_ratio; //ratio of icon to button, e.g. 1.0 means icon covers entire button
	sf::Texture* texture;
	sf::RectangleShape button_rect;
	sf::RectangleShape icon_rect;
	sf::RectangleShape desc_rect;
	bool selected;

	Button();
	Button(float x, float y, float width, float height, string name = NULL, sf::Texture* texture = NULL);
	void resize(float w, float h);
	void setPosition(float x, float y);
	void setColors(sf::Color fill, sf::Color outline);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void toggle();
	void hover();
	void unhover();

private:


};

