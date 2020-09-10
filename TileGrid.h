#pragma once
#include <SFML/Graphics.hpp>
#include "GuiElement.h"
#include <iostream>
using namespace std;

class TileGrid : public GuiElement
{
public:
	int t;
	int w_tiles;	//number of tile columns (width in tiles)
	int h_tiles;	//number of tile rows (height in tiles)
	int t_w;		//texture width in pixels
	int t_h;		//texture height in pixels
	sf::Texture* texture;
	sf::VertexArray vertices;
	sf::RectangleShape bg_rect;
	sf::RectangleShape selector;

	TileGrid(int t, int map_w, int map_h, sf::Texture* texture);
	//bool containsMouse(sf::Vector2i mouse);
	void setTextureCoors(sf::Vector2i coors, sf::Vector2f t_coors);
	/*void setTextureRect(sf::Vector2i coor1, sf::Vector2i coor2,
		sf::Vector2i t_coor1, sf::Vector2i t_coor2);*/
	void setTextureRect(sf::Vector2i coor1, sf::Vector2i coor2,
		sf::FloatRect t_rect);
	sf::Vector2f getTextureCoors(sf::Vector2i coors);
	sf::FloatRect getTextureRect(sf::Vector2i coor1, sf::Vector2i coor2);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void resize(float w, float h);
private:
	int getVertexFromCoors(sf::Vector2i coors);
	void generateVertices();
	int getVertexFromRowCol(int row, int col);
	int getRowFromVertex(int v);
	int getColFromVertex(int v);
};

