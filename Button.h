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
	Button();
	Button(float x, float y, float width, float height, string name = NULL, sf::Texture* texture = NULL);
	//bool mouseInButton(int x, int y);
	//void set_texture();
	//void set_color();
	//void set_texture_ratio();
	//void set_texture_rect(sf::IntRect);
	//void setTextureRect(int x, int y,int w, int h);
	//sf::IntRect texture_rect;
	float icon_ratio; //ratio of icon to button, e.g. 1.0 means icon covers entire button
	sf::Texture* texture;
	sf::RectangleShape button_rect;
	sf::RectangleShape icon_rect;
	void resize(float w, float h);
	void setPosition(float x, float y);
	void setColor(sf::Color color);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:


};

