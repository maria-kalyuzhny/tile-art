#include "GuiElement.h"

const sf::Color GuiElement::button_color = sf::Color(60,60,60);
const sf::Color GuiElement::button_select_color = sf::Color(80,80,80);
const sf::Color GuiElement::menu_color = sf::Color(45,45,45);
const sf::Color GuiElement::bg_color = sf::Color(30,30,30);
const sf::Color GuiElement::divider_color = sf::Color(60,60,60);
const sf::Color GuiElement::grid_bg_color = sf::Color(220,220,220);
const sf::Color GuiElement::border_color = sf::Color(80,80,80);
const sf::Color GuiElement::tile_border_color = sf::Color::White;

GuiElement::GuiElement() {
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->visible = true;
}

GuiElement::GuiElement(float x, float y, float w, float h) {
	//cout << "Running GuiElement constructor" << endl;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->visible = true;
}

void GuiElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
}

bool GuiElement::containsMouse(int coor_x, int coor_y) {
	//cout << "mouse coors: " << coor_x << ", " << coor_y << endl;
	//cout << "elem dims:" << this->x << " " << this->y << " " << this->w << " " << this->h << endl;
	if (coor_x >= this->x && coor_x <= this->x + this->w \
		&& coor_y >= this->y && coor_y <= this->y + this->h) {
		return true;
	}
	return false;
}