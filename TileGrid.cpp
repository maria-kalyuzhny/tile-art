#include "TileGrid.h"

TileGrid::TileGrid(int t, int w_tiles, int h_tiles, sf::Texture* texture) : GuiElement(0,0,w_tiles*t,h_tiles*t) {
	this->t = t;
	this->w_tiles = w_tiles;
	this->h_tiles = h_tiles;
	this->texture = texture;
	this->bg_rect = sf::RectangleShape(sf::Vector2f(this->w, this->h));
	this->bg_rect.setFillColor(grid_bg_color);
	this->selector_rect = sf::RectangleShape(sf::Vector2f(t,t));
	this->selector_rect = sf::RectangleShape(sf::Vector2f(t, t));
	this->selector_rect.setOutlineThickness(getOutlineWidth());
	this->pos_rect.setOutlineThickness(getOutlineWidth());
	hideSelectorRect();
	hidePosRect();
	generateVertices();
}


void TileGrid::clear(sf::Vector2f coors) {
	int v = getVertexFromCoors(coors);
	for (int i = v; i < v + 4; i++) {
		vertices[i].color = sf::Color::Transparent;
	}
}

void TileGrid::clearRect(sf::Vector2f coor1, sf::Vector2f coor2) {
	sf::FloatRect c_rect = getTileRect(coor1, coor2);
	sf::Vector2f upper_left = sf::Vector2f(c_rect.left, c_rect.top);
	sf::Vector2f lower_right = sf::Vector2f(c_rect.left + c_rect.width - t,
		c_rect.top + c_rect.height - t);
	int v1 = getVertexFromCoors(upper_left);
	int v2 = getVertexFromCoors(lower_right);
	int row1 = getRowFromVertex(v1); int col1 = getColFromVertex(v1);
	int row2 = getRowFromVertex(v2); int col2 = getColFromVertex(v2);
	int v = 0;
	for (int i = row1; i <= row2; i++) {
		for (int j = col1; j <= col2; j++) {
			v = getVertexFromRowCol(i, j);
			for (int k = v; k < v + 4; k++) {
				vertices[k].color = sf::Color::Transparent;
			}
		}
	}
}

void TileGrid::setTextureCoors(sf::Vector2f coors, sf::Vector2f t_coors) {
	int v = getVertexFromCoors(coors);
	if (coors.x < 0 || coors.x >= w || coors.y < 0 || coors.y >= h) {
		return;
	}
	t_coors = getTileCoors(t_coors);
	if (vertices[v].color == sf::Color::Transparent) {
		for (int i = v; i < v + 4; i++) {
			vertices[i].color = sf::Color::White;
		}
	}
	vertices[v].texCoords = t_coors;
	vertices[v + 1].texCoords = sf::Vector2f(t_coors.x + t, t_coors.y);
	vertices[v + 2].texCoords = sf::Vector2f(t_coors.x + t, t_coors.y + t);
	vertices[v + 3].texCoords = sf::Vector2f(t_coors.x, t_coors.y + t);
}

void TileGrid::setTextureRect(sf::Vector2f coor1, sf::Vector2f coor2,
	sf::Vector2f t_coor1, sf::Vector2f t_coor2){//sf::FloatRect t_rect) {
	//throws exception if texture coors don't define an rectangle containing a whole number of tiles
	sf::FloatRect c_rect = getTileRect(coor1, coor2);
	sf::FloatRect t_rect = getTileRect(t_coor1, t_coor2);
	sf::Vector2f upper_left = sf::Vector2f(c_rect.left, c_rect.top);
	sf::Vector2f lower_right = sf::Vector2f(c_rect.left + c_rect.width - t,
											c_rect.top + c_rect.height - t);
	int v1 = getVertexFromCoors(upper_left);
	int v2 = getVertexFromCoors(lower_right);
	int row1 = getRowFromVertex(v1); int col1 = getColFromVertex(v1);
	int row2 = getRowFromVertex(v2); int col2 = getColFromVertex(v2);
	int v = 0; //curr upper-left vertex index
	float tx, ty = 0; //texture coordinates 
	for (int i = row1; i <= row2; i++) {
		for (int j = col1; j <= col2; j++) {
			v = getVertexFromRowCol(i, j);
			//tx = getTileCoors(t_coor1);
			tx = t_rect.left + t * (j-col1) % static_cast<int>(t_rect.width);
			ty = t_rect.top  + static_cast<int>((i-row1) * t) % static_cast<int>(t_rect.height);
			if (vertices[v].color == sf::Color::Transparent) {
				for (int k = v; k < v + 4; k++) {
					vertices[k].color = sf::Color::White;
				}
			}
			vertices[v].texCoords = sf::Vector2f(tx, ty);
			vertices[v + 1].texCoords = sf::Vector2f(tx + t, ty);
			vertices[v + 2].texCoords = sf::Vector2f(tx + t, ty + t);
			vertices[v + 3].texCoords = sf::Vector2f(tx, ty + t);
		}
	}
}

sf::Vector2f TileGrid::getTextureCoors(sf::Vector2f coors) {
	int v = getVertexFromCoors(coors);
	return vertices[v].texCoords;
}

sf::FloatRect TileGrid::getTextureRect(sf::Vector2f coor1, sf::Vector2f coor2) {
	sf::Vector2f t1 = getTextureCoors(coor1);
	sf::Vector2f t2 = getTextureCoors(coor2);
	sf::Vector2f upper_left = t1; //by default, first coor is upper left
	sf::Vector2f lower_right = t2;
	if (t2.x < t1.x) {
		upper_left.x = t2.x;
		lower_right.x = t1.x;
	}
	if (t2.y < t1.y) {
		upper_left.y = t2.y;
		lower_right.y = t1.y;
	}
	sf::Vector2f pos = upper_left;
	sf::Vector2f size = lower_right - upper_left + sf::Vector2f(t, t);
	return sf::FloatRect(pos, size);
}

void TileGrid::setSelectorRect(sf::Vector2f coor1, sf::Vector2f coor2) {
	sf::FloatRect rect = getTileRect(coor1, coor2);
	selector_rect.setPosition(sf::Vector2f(rect.left, rect.top));
	selector_rect.setSize(sf::Vector2f(rect.width, rect.height));
}

void TileGrid::showSelectorRect() {
	selector_rect.setOutlineColor(selector_outline_color);
	selector_rect.setFillColor(selector_fill_color);
}

void TileGrid::hideSelectorRect() {
	selector_rect.setOutlineColor(sf::Color::Transparent);
	selector_rect.setFillColor(sf::Color::Transparent);
}

void TileGrid::setPosRect(sf::Vector2f coor1, sf::Vector2f coor2) {
	sf::FloatRect rect = getTileRect(coor1, coor2);
	pos_rect.setPosition(sf::Vector2f(rect.left, rect.top));
	pos_rect.setSize(sf::Vector2f(rect.width, rect.height));
}

void TileGrid::showPosRect() {
	pos_rect.setOutlineColor(pos_outline_color);
	pos_rect.setFillColor(pos_fill_color);
}

void TileGrid::hidePosRect() {
	pos_rect.setOutlineColor(sf::Color::Transparent);
	pos_rect.setFillColor(sf::Color::Transparent);
}

void TileGrid::resize(float w, float h) {
	//do nothing lol
	return;
}

void TileGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(bg_rect);
	states.texture = texture;
	target.draw(vertices, states);
	target.draw(selector_rect);
	target.draw(pos_rect);
}

sf::Image TileGrid::getImage() {
	sf::RenderTexture r_texture;
	r_texture.create(w, h);
	r_texture.display();
	r_texture.draw(vertices, texture);
	sf::Image img = r_texture.getTexture().copyToImage();
	return img;
}

/* private methods */


int TileGrid::getOutlineWidth() {
	return -((0.1*t)+1);
}

int TileGrid::getVertexFromCoors(sf::Vector2f coors) {
	//if (coors.x < 0 || coors.y < 0 || coors.x >= t * w_tiles|| coors.y >= t * h_tiles) {
	//	cout << "vertex coors out of range. Returning vertex 0" << endl;
	//	return 0;
	//}
	int x = coors.x / t;
	int y = coors.y / t;
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

sf::Vector2f TileGrid::getTileCoors(sf::Vector2f coor) {
	return sf::Vector2f((static_cast<int>(coor.x) / t) * t,
		(static_cast<int>(coor.y) / t) * t);
}

sf::FloatRect TileGrid::getTileRect(sf::Vector2f coor1, sf::Vector2f coor2) {
	sf::Vector2f t1 = getTileCoors(coor1);
	sf::Vector2f t2 = getTileCoors(coor2);
	sf::Vector2f upper_left = t1; //by default, first coor is upper left
	sf::Vector2f lower_right = t2;
	if (t2.x < t1.x) {
		upper_left.x = t2.x;
		lower_right.x = t1.x;
	}
	if (t2.y < t1.y) {
		upper_left.y = t2.y;
		lower_right.y = t1.y;
	}
	sf::Vector2f pos = upper_left;
	sf::Vector2f size = lower_right - upper_left + sf::Vector2f(t, t);
	return sf::FloatRect(pos, size);
}