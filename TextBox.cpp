#include "TextBox.h"

TextBox::TextBox() : GuiElement() {
	box = sf::RectangleShape(sf::Vector2f(w,h));
	box.setPosition(x,y);
	box.setFillColor(textbox_fill_color);
	box.setOutlineThickness(textbox_outline_thickness);
	box.setOutlineColor(textbox_outline_color);
	text.setString("");
	text.setCharacterSize(font_size);
	text.setFillColor(text_color);
	text.setPosition(x + text_padding, y + text_padding);
	hide();
}

TextBox::TextBox(float x, float y, float w, float h, string desc) : GuiElement(x, y, w, h) {
	box = sf::RectangleShape(sf::Vector2f(w,h));
	box.setPosition(x,y);
	box.setFillColor(textbox_fill_color);
	box.setOutlineThickness(textbox_outline_thickness);
	box.setOutlineColor(textbox_outline_color);
	text.setString(desc);
	text.setFont(font);
	text.setCharacterSize(font_size);
	text.setFillColor(text_color);
	text.setPosition(x+text_padding,y+text_padding);
	hide();
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(box);
	target.draw(text);
}

void TextBox::resize(float w, float h) {
	this->w = w;
	this->h = h;
	box.setSize(sf::Vector2f(w,h));
}

void TextBox::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
	box.setPosition(x,y);
	text.setPosition(x+text_padding, y+text_padding);
}

void TextBox::show() {
	cout << "showing textbox" << endl;
	cout << "textbox size" << box.getSize().x << box.getSize().y << endl;
	if (!visible) {
		box.setFillColor(textbox_fill_color);
		box.setOutlineColor(textbox_outline_color);
		text.setFillColor(text_color);
		visible = true;
	}
}

void TextBox::hide() {
	if (visible) {
		box.setFillColor(sf::Color::Transparent);
		box.setOutlineColor(sf::Color::Transparent);
		text.setFillColor(sf::Color::Transparent);
		visible = false;
	}
}



