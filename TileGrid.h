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

	TileGrid(int t, int map_w, int map_h, sf::Texture* texture);
	bool containsMouse(int coor_x, int coor_y);
	void setTextureCoors(int coor_x, int coor_y, int texture_x, int texture_y);
	void setTextureRect(int coor_x1, int coor_y1, int coor_x2, int coor_y2,
		int texture_x1, int texture_y1, int texture_x2, int texture_y2);
	sf::Vector2f getTextureCoors(int coor_x, int coor_y);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void resize(float w, float h);
private:
	int getVertexFromCoors(int coor_x, int coor_y);
	void generateVertices();
	int getVertexFromRowCol(int row, int col);
	int getRowFromVertex(int v);
	int getColFromVertex(int v);
};

