#include "ButtonMenu.h"

ButtonMenu::ButtonMenu() {
	this->rect = sf::RectangleShape(sf::Vector2f(w, h));
	this->rect.setPosition(x, y);
	this->rect.setFillColor(menu_color);
	this->buttons = {};
	this->button_size = h - 2 * this->padding;
	this->num_buttons = 0;
}

ButtonMenu::ButtonMenu(float x, float y, float w, float h) : GuiElement(x, y, w, h) {
	this->rect = sf::RectangleShape(sf::Vector2f(w, h));
	this->rect.setPosition(x, y);
	this->rect.setFillColor(menu_color);
	this->buttons = {};
	this->button_size = h - 2 * this->padding;
	this->num_buttons = 0;
}

void ButtonMenu::addButton(Button* button, bool fit_to_menu) {
	if (fit_to_menu) {
		float x = this->x + padding + num_buttons * (button_size + padding);
		float y = this->y + padding;
		button->setPosition(x, y);
		button->resize(button_size, button_size);
	}
	this->buttons.push_back(button);
	num_buttons += 1;
}

void ButtonMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->rect);
	for (Button* button : this->buttons) {
		if (button->visible) {
			target.draw(*button);
		}

	}
}

void ButtonMenu::resize(float w, float h) {
	this->w = w;
	this->h = h;
	this->rect.setSize(sf::Vector2f(w, h));
	for (auto button : this->buttons) {
		if (button->x + button->w > this->x + this->w) {
			button->visible = false;
		}
		else {
			button->visible = true;
		}
	}
}

Button* ButtonMenu::getButton(string name) {
	for (auto button : this->buttons) {
		if (button->name == name) {
			return button;
		}
	}
	return nullptr;
}