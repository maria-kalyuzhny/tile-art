#include "Button.h"

Button::Button() {
	this->icon_ratio = 1.0;
	this->texture = nullptr;
	this->button_rect = sf::RectangleShape(sf::Vector2f(w, h));
	this->icon_rect = sf::RectangleShape(sf::Vector2f(w, h));
}

Button::Button(float x, float y, float w, float h, string name, sf::Texture* texture) : GuiElement(x, y, w, h) {
	//cout << "Running Button constructor" << endl;
	if (!name.empty()) {
		this->name = name;
	}
	this->icon_ratio = 1.0;
	this->texture = texture;
	this->button_rect = sf::RectangleShape(sf::Vector2f(w, h));
	this->button_rect.setPosition(x, y);
	this->button_rect.setFillColor(button_color);
	this->icon_rect = sf::RectangleShape(sf::Vector2f(w, h));
	this->icon_rect.setFillColor(sf::Color::White);
	//this->texture_rect = sf::IntRect(0, 0, static_cast<int>(w), static_cast<int>(h));
	this->icon_rect.setTexture(this->texture);
	//this->icon_rect.setTextureRect(this->texture_rect);
}

//bool Button::mouseInButton(int coor_x, int coor_y) {
//	if (coor_x >= this->x && coor_x <= this->x + this->w &&
//		coor_y >= this->y && coor_y <= this->y + this->h) {
//		return true;
//	}
//	return false;
//}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//states.texture = this->texture;
	//cout << "Button: drawing button " << endl; // this->name << endl;
	target.draw(this->button_rect);
	target.draw(this->icon_rect);
}

void Button::resize(float w, float h) {
	this->w = w;
	this->h = h;
	this->button_rect.setSize(sf::Vector2f(w, h));
	this->icon_rect.setSize(sf::Vector2f(w * icon_ratio, h * icon_ratio));
	cout << "button resize called" << endl;
}

void Button::setPosition(float x, float y) {
	this->x = x; 
	this->y = y;
	this->button_rect.setPosition(sf::Vector2f(x, y));
	this->icon_rect.setPosition(sf::Vector2f(x, y));
}

void Button::setColor(sf::Color color) {
	this->button_rect.setFillColor(color);
}
//void Button::setTextureRect(int x, int y, int w, int h) {
//	cout << "setting text rect size ";
//	this->texture_rect.left = x; // = sf::IntRect(x, y, w, h);
//	this->texture_rect.top = y;
//	this->texture_rect.width = w;
//	this->texture_rect.height = h;
//	cout << this->texture_rect.width << endl;
//	this->icon_rect.setTextureRect(this->texture_rect);
//}