#pragma once
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <iostream>
using namespace std;

class GuiElement : public sf::Drawable, public sf::Transformable
{
public:
	const static sf::Color button_color;
	const static sf::Color button_select_color;
	const static sf::Color menu_color;
	const static sf::Color bg_color;
	const static sf::Color grid_bg_color;
	const static sf::Color border_color;
	const static sf::Color tile_border_color;
	const static sf::Color divider_color;

	float x, y, w, h;
	bool visible;
	//bool scale_x;
	//bool scale_y;

	GuiElement();
	GuiElement(float x, float y, float w, float h);
	virtual void resize(float w, float h) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//virtual void scale(float x_ratio, float y_ratio);
	bool containsMouse(int coor_x, int coor_y);
private:
};


