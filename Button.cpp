#include "Button.h"

Button::Button() {
	this->icon_ratio = 1.0;
	this->texture = nullptr;
	this->button_rect = sf::RectangleShape(sf::Vector2f(w, h));
	this->icon_rect = sf::RectangleShape(sf::Vector2f(w, h));
	this->selected = false;
}

Button::Button(float x, float y, float w, float h, string name, sf::Texture* texture) : GuiElement(x, y, w, h) {
	if (!name.empty()) {
		this->name = name;
	}
	this->icon_ratio = 1.0;
	this->texture = texture;
	this->button_rect = sf::RectangleShape(sf::Vector2f(w, h));
	this->button_rect.setPosition(x, y);
	this->button_rect.setFillColor(button_color);
	this->button_rect.setOutlineColor(button_outline_color);
	this->button_rect.setOutlineThickness(button_outline_thickness);
	this->icon_rect = sf::RectangleShape(sf::Vector2f(w, h));
	this->icon_rect.setFillColor(sf::Color::White);
	this->icon_rect.setTexture(this->texture);
	this->selected = false;
	this->description = NULL;
	//description->setPosition(x,y+h+button_textbox_offset);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->button_rect);
	target.draw(this->icon_rect);
	target.draw(*this->description);
}

void Button::resize(float w, float h) {
	this->w = w;
	this->h = h;
	this->button_rect.setSize(sf::Vector2f(w, h));
	this->icon_rect.setSize(sf::Vector2f(w * icon_ratio, h * icon_ratio));
}

void Button::setPosition(float x, float y) {
	this->x = x; 
	this->y = y;
	this->button_rect.setPosition(sf::Vector2f(x, y));
	this->icon_rect.setPosition(sf::Vector2f(x, y));
}

void Button::setColors(sf::Color fill, sf::Color outline) {
	this->button_rect.setFillColor(fill);
	this->button_rect.setOutlineColor(outline);
}

void Button::toggle() {
	if (selected) {
		selected = false;
		setColors(button_color, button_outline_color);
	}
	else {
		selected = true;
		setColors(button_select_color, button_select_outline_color);
	}
}

void Button::select() {
	selected = true;
	setColors(button_select_color, button_select_outline_color);
}

void Button::deselect() {
	selected = false;
	setColors(button_color, button_outline_color);
}

void Button::hover() {
	if (!selected) {
		setColors(button_hover_color, button_hover_outline_color);
		//cout << "hovering over unselected button " << name << endl;
	}
	else {
		//cout << "hovering over selected button " << name << endl;
	}
	//description->show();
}

void Button::unhover() {
	if (!selected) {
		setColors(button_color, button_outline_color);
	}
	else {
		setColors(button_select_color, button_select_outline_color);
	}
	//description->hide();
}

void Button::addDescription(TextBox* desc) {
	description = desc;
	description->setPosition(x, y + h + button_textbox_offset);
}
