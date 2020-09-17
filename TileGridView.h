#pragma once
#include "GuiElement.h"
#include "TileGrid.h"
#include <SFML/Graphics.hpp>>

//Contains an sf::View which displays one TileGrid.
//TileGridView's view rectangle and Viewport are maintained to be the same size to avoid skewing/changing scale.
//Its centering and scrolling are dependent on the size of the TileGrid.

class TileGridView : public GuiElement
{
public:
	TileGrid* grid;
	sf::View view;
	sf::Vector2f w_size;
	sf::Vector2f s;
	float z;

	TileGridView(const sf::FloatRect& rect, sf::Vector2f w_size, TileGrid* grid);
	void zoom(int delta);
	void scroll(sf::Keyboard::Key key);
	void resize(float w, float h);
	void reset(const sf::FloatRect& rect);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void centerOnGrid();
	//void scroll(char direction, int delta = 10);
	void updateWindow(sf::Vector2f w_size);
private:
	float max_scroll_x;
	float max_scroll_y;
	//float init_s;
	float s_delta;
	const float min_zoom = 0.1;
	const float max_zoom = 4.0;
};

