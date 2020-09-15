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
	//float w, h;
	sf::Vector2f w_size;
	sf::RenderWindow* window;
	sf::View window_view;
	ButtonMenu* menu;
	ViewLayout* layout;
	bool drawing_mode;
	bool rectangle_mode;
	bool erase_mode;
	bool drawing_now;
	bool selecting_now;
	//sf::Cursor cursor;
	sf::Vector2f mouse_pos_picker;
	sf::Vector2f mouse_pos_map;
	sf::Vector2f t_coor, t_coor2;
	sf::Vector2f m_coor, m_coor2;

	TileArtGui(sf::RenderWindow* window, ButtonMenu* menu, ViewLayout* layout);
	void handleInput();
	void onButtonClick(string button);
	void onResize(sf::Vector2f w_size);
	void onMouseButtonPressed(sf::Vector2i mouse_pos_window, sf::Vector2f mouse_pos_view);
	void onMouseMoved(sf::Vector2i mouse_pos_window, sf::Vector2f mouse_pos_view);
	void onMouseButtonReleased(sf::Vector2i mouse_pos_window, sf::Vector2f mouse_pos_view);
	//void onResize(sf::Vector2f )
	//void resize();
	void draw();
	//void centerView(sf::View* view, )
private:
	const static int num_buttons = 8;
	float menu_height;
};


