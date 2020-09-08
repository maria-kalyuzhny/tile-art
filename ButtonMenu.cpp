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
		cout << button->x << endl;
	}
	this->buttons.push_back(button);
	num_buttons += 1;
	cout << "added button w x,y,size " << x << " " << y << " " << button_size << " name " << button->name << " texture " << button->texture << endl;
	cout << num_buttons << endl;
}

void ButtonMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->rect);
	for (Button* button : this->buttons) {
		if (button->visible) {
			//cout << "drawing button" << endl;
			//cout << button->x << " " << button->y << " " << button->w << " " << button->h << " " << button->name << " " << button->texture << endl;
			target.draw(*button);
			//cout << "finished drawing button" << endl;
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
	cout << "button with name " << name << " not found." << endl;
	return nullptr;
}