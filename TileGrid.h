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
	/*sf::RectangleShapes showing tiles based on user's selection and mouse movement,
	handled from external gui class. */
	sf::RectangleShape selector_rect; //shows current selection
	sf::RectangleShape pos_rect; //shows current tile position

	TileGrid(int t, int map_w, int map_h, sf::Texture* texture);
	void clear(sf::Vector2f coor);
	void clearRect(sf::Vector2f coor1, sf::Vector2f coor2);
	void setTextureCoors(sf::Vector2f coor, sf::Vector2f t_coor);
	void setTextureRect(sf::Vector2f coor1, sf::Vector2f coor2,
		sf::Vector2f t_coor1, sf::Vector2f t_coor2);//sf::FloatRect t_rect);
	sf::Vector2f getTextureCoors(sf::Vector2f coor);
	sf::FloatRect getTextureRect(sf::Vector2f coor1, sf::Vector2f coor2);
	void setSelectorRect(sf::Vector2f coor1, sf::Vector2f coor2);
	void showSelectorRect();
	void hideSelectorRect();
	void setPosRect(sf::Vector2f coor1, sf::Vector2f coor2);
	void showPosRect();
	void hidePosRect();
	void resize(float w, float h);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Image getImage();

private:
	int getOutlineWidth(); //determines outline with of selector rects based on tile size
	int getVertexFromCoors(sf::Vector2f coors);
	void generateVertices();
	int getVertexFromRowCol(int row, int col);
	int getRowFromVertex(int v);
	int getColFromVertex(int v);
	sf::Vector2f getTileCoors(sf::Vector2f coor);
	sf::FloatRect getTileRect(sf::Vector2f coor1, sf::Vector2f coor2);
};

