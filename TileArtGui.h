#pragma once
#include <string>
#include <vector>
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include "GuiElement.h"
#include "ButtonMenu.h"
#include "Button.h"
#include "ViewLayout.h"
#include "TileGrid.h"
using namespace std;


class TileArtGui
{
public:
	sf::Vector2f w_size;
	sf::RenderWindow* window;
	sf::View window_view;
	ButtonMenu* menu;
	ViewLayout* layout;
	bool rectangle_mode;
	bool erase_mode;
	bool drawing_now;
	bool selecting_now;
	bool mouse_in_curr_button;
	sf::Vector2f mouse_pos_picker;
	sf::Vector2f mouse_pos_map;
	sf::Vector2f t_coor, t_coor2;
	sf::Vector2f m_coor, m_coor2;
	Button* curr_button;
	sf::Clock clock;
	string output_file;

	TileArtGui(sf::RenderWindow* window, ButtonMenu* menu, ViewLayout* layout, string output_file);
	void handleInput();
	void draw();

private:
	const static int num_buttons = 8;
	const float delay = 0.5;
	float menu_height;
	bool shift_down;
	void onButtonClick(string button);
	void onMouseButtonPressed(sf::Vector2i mouse_pos_window, sf::Vector2f mouse_pos_view);
	void onMouseMoved(sf::Vector2i mouse_pos_window, sf::Vector2f mouse_pos_view);
	void onMouseButtonReleased(sf::Vector2i mouse_pos_window, sf::Vector2f mouse_pos_view);
	void onMouseWheelMoved(sf::Vector2f mouse_pos_view, int delta);
	void onKeyPressed(sf::Vector2f mouse_pos_view, sf::Keyboard::Key key);
	void onResize(sf::Vector2f w_size);
};


