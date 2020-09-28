#pragma once
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <iostream>
using namespace std;

class GuiElement : public sf::Drawable, public sf::Transformable
{
public:
	const static int button_outline_thickness = 2;
	const static int view_outline_thickness = -2;
	const static int textbox_outline_thickness = 2;
	const static int divider_limit = 15;
	const static int div_width = 15;
	const static int font_size = 12;
	const static int text_padding = 10;
	const static sf::Color button_color;
	const static sf::Color button_hover_color;
	const static sf::Color button_select_color;
	const static sf::Color button_outline_color;
	const static sf::Color button_hover_outline_color;
	const static sf::Color button_select_outline_color;
	const static sf::Color menu_color;
	const static sf::Color bg_color;
	const static sf::Color grid_bg_color;
	const static sf::Color border_color;
	const static sf::Color tile_border_color;
	const static sf::Color divider_color;
	const static sf::Color selector_outline_color;
	const static sf::Color selector_fill_color;
	const static sf::Color pos_outline_color;
	const static sf::Color pos_fill_color;
	const static sf::Color view_outline_color;
	const static sf::Color textbox_fill_color;
	const static sf::Color textbox_outline_color;
	const static sf::Color text_color;
	const static string font_file;
	static sf::Font font;
	static bool init_font;
	
	float x, y, w, h;
	bool visible;

	GuiElement();
	GuiElement(float x, float y, float w, float h);
	virtual void resize(float w, float h) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool containsMouse(sf::Vector2f mouse);
private:
	bool initFont();
};


