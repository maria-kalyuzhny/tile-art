#pragma once
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "TileGridView.h"

class ViewLayout : public GuiElement
{
public:
	TileGridView* map_view;
	TileGridView* picker_view;
	sf::RectangleShape divider;
	float div_x;
	bool moving_divider;
	sf::RectangleShape map_outline;
	sf::RectangleShape picker_outline;
	sf::Vector2f w_size;

	ViewLayout(sf::FloatRect rect, sf::Vector2f w_size, TileGridView* picker_view, TileGridView* map_view, float div_pos);
	void setOutlines();
	void updateWindow(sf::Vector2f w_size);
	void resize(float w, float h);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void moveDivider(float mouse_x);

private:
};

