#include "TilePicker.h"

TilePicker::TilePicker(int tile_size, sf::Texture *texture) {
	this->t = tile_size;
	this->texture = texture;
	//cout << texture->getSize().x << endl;
	sf::Vector2u size = texture->getSize();
	w = static_cast<int>(size.x / t);
	h = static_cast<int>(size.y / t);
	//cout << "picker is " << w << " by " << h << endl;
	tileset = sf::RectangleShape(sf::Vector2f(w,h));
	tileset.setPosition(sf::Vector2f(0, 0));
	tileset.setTexture(texture);
}

sf::Vector2i TilePicker::getTextureCoors(int coor_x, int coor_y) {
	//cout << "get texture coors" << endl;
	int x = t * (coor_x / t);
	int y = t * (coor_y / t);
	//cout << x << "," << y << endl;
	return sf::Vector2i(x, y);
}

bool TilePicker::inTilePicker(int coor_x, int coor_y) {
	cout << "in tile picker, coors are " << coor_x << "," << coor_y << endl;
	cout << "picker bottom right is " << w << "," << h << endl;
	if (coor_x >= 0 && coor_y >= 0 && coor_x < w && coor_y < h) {
		cout << "true" << endl;
		return true;
	}
	cout << "false" << endl;
	return false;
}

void TilePicker::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//cout << "drawing picker" << endl;
	states.transform *= sf::Transformable::getTransform();

	// apply the tileset texture
	states.texture = texture;

	// draw the vertex array
	target.draw(tileset, states);
	//target.draw(vertices, texture);
}
