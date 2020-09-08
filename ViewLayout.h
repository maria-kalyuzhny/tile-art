#pragma once
#include <SFML/Graphics.hpp>
#include "GuiElement.h"

class ViewLayout : public GuiElement
{
public:
	sf::View picker_view;
	sf::View map_view;
	sf::RectangleShape divider;
	sf::RectangleShape picker_bg;
	sf::RectangleShape map_bg;
	float div_x; //x pos of divider line between tile picker and map
	bool moving_divider;
	float window_w;
	float window_h;
	int map_w;
	int map_h;
	int picker_w;
	int picker_h;
	sf::Vector2f map_scroll;
	sf::Vector2f picker_scroll;

	ViewLayout(float x, float y, float w, float h, float div_pos, float window_w, float window_h);
	void updateWindow(float window_w, float window_h);
	void resize(float w, float h);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void moveDivider(float mouse_x);
	void scrollView(string view, sf::Vector2f scroll);
	//void centerView(string view);
private:
	const float div_width = 15;
};

