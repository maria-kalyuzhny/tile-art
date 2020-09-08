#include "TileGrid.h"

TileGrid::TileGrid(int t, int w_tiles, int h_tiles, sf::Texture* texture) : GuiElement(0,0,w_tiles*t,h_tiles*t) {
	this->t = t;
	this->w_tiles = w_tiles;
	this->h_tiles = h_tiles;
	this->texture = texture;
	this->bg_rect = sf::RectangleShape(sf::Vector2f(this->w, this->h));
	this->bg_rect.setFillColor(grid_bg_color);
	generateVertices();
}

bool TileGrid::containsMouse(int coor_x, int coor_y) {
	if (coor_x >= 0 && coor_y >= 0 && coor_x < t * w_tiles && coor_y < t * h_tiles) {
		return true;
	}
	return false;
}

void TileGrid::setTextureCoors(int coor_x, int coor_y, int texture_x, int texture_y) {
	int v = getVertexFromCoors(coor_x, coor_y);
	if (vertices[v].color == sf::Color::Transparent) {
		for (int i = v; i < v + 4; i++) {
			vertices[i].color = sf::Color::White;
		}
	}
	vertices[v].texCoords = sf::Vector2f(texture_x, texture_y);
	vertices[v + 1].texCoords = sf::Vector2f(texture_x + t, texture_y);
	vertices[v + 2].texCoords = sf::Vector2f(texture_x + t, texture_y + t);
	vertices[v + 3].texCoords = sf::Vector2f(texture_x, texture_y + t);
}

void TileGrid::setTextureRect(int coor_x1, int coor_y1, int coor_x2, int coor_y2,
	int texture_x1, int texture_y1, int texture_x2, int texture_y2) {
	//throws exception if texture coors don't define an rectangle containing a whole number of tiles
	if ((texture_x2 - texture_x1) % t != 0 || (texture_y2 - texture_y1) % t != 0) {
		cout << "setTextureRect: texture coors don't contain whole number of tiles" << endl;
		return;
	}
	cout << "setting textureRect" << endl;
	int v1 = getVertexFromCoors(coor_x1, coor_y1);
	int v2 = getVertexFromCoors(coor_x2, coor_y2);
	int row1 = getRowFromVertex(v1); int col1 = getColFromVertex(v1);
	int row2 = getRowFromVertex(v2); int col2 = getColFromVertex(v2);
	int v = 0; //curr upper-left vertex index
	float tx, ty = 0; //texture coordinates 
	for (int i = row1; i <= row2; i++) {
		for (int j = col1; j <= col2; j++) {
			v = getVertexFromRowCol(i, j);
			tx = static_cast<float>((texture_x1 + j * t) % (texture_x2 - texture_x1));
			ty = static_cast<float>((texture_y1 + i * t) % (texture_y2 - texture_y1));
			if (vertices[v].color == sf::Color::Transparent) {
				for (int k = v; k < v + 4; k++) {
					vertices[k].color = sf::Color::White;
				}
			}
			vertices[v].texCoords = sf::Vector2f(tx, ty);
			cout << "vertex0 " << v << " tex coords " << tx << ", " << ty << endl;
			vertices[v + 1].texCoords = sf::Vector2f(tx + t, ty);
			cout << "vertex1 " << v << " tex coords " << tx+t << ", " << ty << endl;
			vertices[v + 2].texCoords = sf::Vector2f(tx + t, ty + t);
			cout << "vertex2 " << v << " tex coords " << tx+t << ", " << ty+t << endl;
			vertices[v + 3].texCoords = sf::Vector2f(tx, ty + t);
			cout << "vertex3 " << v << " tex coords " << tx << ", " << ty+t << endl;
		}
	}
}

sf::Vector2f TileGrid::getTextureCoors(int coor_x, int coor_y) {
	int v = getVertexFromCoors(coor_x, coor_y);
	return vertices[v].texCoords;
}

void TileGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//cout << "drawing vertices" << endl;
	target.draw(bg_rect);
	states.texture = texture;
	target.draw(vertices, states);
}

void TileGrid::resize(float w, float h) {
	//do nothing lol
	return;
}

int TileGrid::getVertexFromCoors(int coor_x, int coor_y) {
	if (coor_x < 0 || coor_y < 0 || coor_x >= t * w_tiles|| coor_y >= t * h_tiles) {
		return -1;
	}
	int x = floor(coor_x / t);
	int y = floor(coor_y / t);
	return 4*(y * w_tiles + x);
}

void TileGrid::generateVertices() {
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(w_tiles * h_tiles * 4);
	int v = 0;
	for (int j = 0; j < h_tiles; ++j) {
		for (int i = 0; i < w_tiles; ++i) {
			vertices[v].position = sf::Vector2f(i * t, j * t);
			vertices[v + 1].position = sf::Vector2f(i * t + t, j * t);
			vertices[v + 2].position = sf::Vector2f(i * t + t, j * t + t);
			vertices[v + 3].position = sf::Vector2f(i * t, j * t + t);
			for (int k = v; k < v+4; k++) {
				vertices[k].color = sf::Color::Transparent;
			}
			v = v + 4;
		}
	}
}

int TileGrid::getVertexFromRowCol(int row, int col) {
	return 4 * (w_tiles * row + col);
}

int TileGrid::getRowFromVertex(int v) {
	return (v / 4) / w_tiles;
}

int TileGrid::getColFromVertex(int v) {
	return (v / 4) % w_tiles;
}
//void TileGrid::setTextureRect(int coor_x1, int coor_y1, int coor_x2, int coor_y2, 
//						int texture_x1, int texture_y1, int texture_x2, int texture_x3));
//
//void TileGrid::fillTextureRect(int coor_x1, int coor_y1, int coor_x2, int coor_y2, 
//						int texture_x, int texture_y); //REDUNDANT. JUST FOR 'BASE CASE' where texture rect covers 2 tile
//LIMIT RECT SELECTION SO WE CAN ONLY GO FROM LEFT UP TO BOTTOM RIGHT FOR NOW?