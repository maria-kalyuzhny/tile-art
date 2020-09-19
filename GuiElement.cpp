#include "GuiElement.h"

const sf::Color GuiElement::button_color = sf::Color(60,60,60);
const sf::Color GuiElement::button_hover_color = sf::Color(40,40,40);
const sf::Color GuiElement::button_select_color = sf::Color(20,20,20);
const sf::Color GuiElement::button_outline_color = sf::Color::Transparent;
const sf::Color GuiElement::button_hover_outline_color = sf::Color(80, 80, 80);
const sf::Color GuiElement::button_select_outline_color = sf::Color(100,100,100);
const sf::Color GuiElement::menu_color = sf::Color(60,60,60);
const sf::Color GuiElement::bg_color = sf::Color(30,30,30);
const sf::Color GuiElement::divider_color = sf::Color(60,60,60);
const sf::Color GuiElement::grid_bg_color = sf::Color(220,220,220);
const sf::Color GuiElement::border_color = sf::Color(80,80,80);
const sf::Color GuiElement::tile_border_color = sf::Color::White;
const sf::Color GuiElement::selector_outline_color = sf::Color::Red;
const sf::Color GuiElement::selector_fill_color = sf::Color(255,0,0,80);
const sf::Color GuiElement::pos_outline_color = sf::Color::Green;
const sf::Color GuiElement::pos_fill_color = sf::Color::Transparent;

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

bool GuiElement::containsMouse(sf::Vector2f mouse) {
	//cout << "mouse coors: " << coor_x << ", " << coor_y << endl;
	//cout << "elem dims:" << this->x << " " << this->y << " " << this->w << " " << this->h << endl;
	if (mouse.x >= this->x && mouse.x <= this->x + this->w \
		&& mouse.y >= this->y && mouse.y <= this->y + this->h) {
		return true;
	}
	return false;
}