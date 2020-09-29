#pragma once
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <string>
#include "GuiElement.h"
#include "TextBox.h"
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
	TextBox* description;
	bool selected;

	Button();
	Button(float x, float y, float width, float height, string name = NULL,
		sf::Texture* texture = NULL);
	void resize(float w, float h);
	void setPosition(float x, float y);
	void setColors(sf::Color fill, sf::Color outline);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void toggle();
	void select();
	void deselect();
	void hover();
	void unhover();
	void addDescription(TextBox* desc);
	//void showDescription();
	//void hideDescription();

private:


};

