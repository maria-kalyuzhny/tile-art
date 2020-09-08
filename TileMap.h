#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	void generateVertices();
	int getTileIndex(int coor_x, int coor_y);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	int t;

	sf::Texture* texture;
	int texture_w;
	int texture_h;
	int map_w;
	int map_h;
	sf::VertexArray vertices;
	TileMap(int t, int map_w, int map_h, sf::Texture* texture);
	std::tuple<int, int> getTextureCoordinates(int tile_index);
	bool inTileMap(int coor_x, int coor_y);
	void setTileTexture(int coor_x, int coor_y, int texture_x, int texture_y);
	void draw(sf::RenderTarget& target, sf::RenderStates states);
	void move(int xo, int yo);
};

