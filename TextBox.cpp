#include "TextBox.h"

TextBox::TextBox(float x, float y, float w, float h, string desc) : GuiElement(x, y, w, h) {
	box = sf::RectangleShape(sf::Vector2f(w,h));
	box.setPosition(x,y);
	box.setFillColor(textbox_fill_color);
	box.setOutlineThickness(textbox_outline_thickness);
	box.setOutlineColor(textbox_outline_color);
	text.setFont(font);
	text.setString(desc);
	text.setCharacterSize(font_size); // in pixels, not points!
	text.setFillColor(text_color);
	text.setPosition(x+text_padding,y+text_padding);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	return;
}

void TextBox::resize(float w, float h) {
	return;
}

void TextBox::show() {
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



