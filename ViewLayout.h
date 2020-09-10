#pragma once
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include "TileGridView.h"

class ViewLayout : public GuiElement
{
public:
	//sf::View picker_view;
	//sf::View map_view;
	TileGridView* map_view;
	TileGridView* picker_view;
	sf::RectangleShape divider;
	float div_x; //x pos of divider line between tile picker and map
	bool moving_divider;
	//float window_w;
	//float window_h;
	sf::Vector2f w_size;
	int map_w;
	int map_h;
	int picker_w;
	int picker_h;
	/*sf::Vector2f map_scroll;
	sf::Vector2f picker_scroll;*/

	ViewLayout(sf::FloatRect rect, sf::Vector2f w_size, TileGridView* picker_view, TileGridView* map_view, float div_pos);
	void updateWindow(sf::Vector2f w_size);
	void resize(float w, float h);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void moveDivider(float mouse_x);
	//void scrollView(string view, sf::Vector2f scroll);
	//void centerView(string view);
private:
	const float div_width = 15;
};

