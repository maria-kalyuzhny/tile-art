#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class TilePicker : public sf::Drawable, public sf::Transformable
{
private:
	int t;
	sf::Texture* texture;
	sf::RectangleShape tileset;
	int w;
	int h;
	sf::Vector2i size;
	//void generateVertices();
public:
	TilePicker(int t, sf::Texture* texture);
	sf::Vector2i getTextureCoors(int mouse_x, int mouse_y);
	bool inTilePicker(int coor_x, int coor_y);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

