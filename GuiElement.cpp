#include "GuiElement.h"

const sf::Color GuiElement::button_color = sf::Color(60,60,60);
const sf::Color GuiElement::button_hover_color = sf::Color(40,40,40);
const sf::Color GuiElement::button_select_color = sf::Color(20,20,20);
const sf::Color GuiElement::button_outline_color = sf::Color::Transparent;
const sf::Color GuiElement::button_hover_outline_color = sf::Color(90, 90, 90);
const sf::Color GuiElement::button_select_outline_color = sf::Color(110,110,110);
const sf::Color GuiElement::menu_color = sf::Color(60,60,60);
const sf::Color GuiElement::bg_color = sf::Color(40,40,40);
const sf::Color GuiElement::divider_color = sf::Color(60,60,60);
const sf::Color GuiElement::grid_bg_color = sf::Color(10,10,10);
const sf::Color GuiElement::border_color = sf::Color(80,80,80);
const sf::Color GuiElement::tile_border_color = sf::Color::White;
const sf::Color GuiElement::selector_outline_color = sf::Color(255, 200, 0, 100);
const sf::Color GuiElement::selector_fill_color = sf::Color(80,70,0,90);
const sf::Color GuiElement::pos_outline_color = sf::Color(255, 255, 255, 100);
const sf::Color GuiElement::pos_fill_color = sf::Color(0, 0, 0, 50);
const sf::Color GuiElement::view_outline_color = sf::Color(100,100,100,255);
const sf::Color GuiElement::textbox_fill_color = sf::Color(255,239,181);
const sf::Color GuiElement::textbox_outline_color = sf::Color(255,200,0);
const sf::Color GuiElement::text_color = sf::Color::Black;
const string GuiElement::font_file = "./img/DejaVuSansMono.ttf";
bool GuiElement::init_font = false;
sf::Font GuiElement::font = sf::Font();

GuiElement::GuiElement() {
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->visible = true;
	if (!init_font) {
		initFont();
	}
}

GuiElement::GuiElement(float x, float y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->visible = true;
	if (!init_font) {
		initFont();
	}
}

void GuiElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
}

bool GuiElement::containsMouse(sf::Vector2f mouse) {
	if (mouse.x >= this->x && mouse.x <= this->x + this->w \
		&& mouse.y >= this->y && mouse.y <= this->y + this->h) {
		return true;
	}
	return false;
}

bool GuiElement::initFont() {
	if (!font.loadFromFile(font_file)) {
		std::cerr << "Unable to load font " << font_file << endl;
		return false;
	}
	init_font=true;
	return true;
}