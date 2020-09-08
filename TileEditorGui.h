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


class TileEditorGui
{
public:
	float w, h;
	//vector<GuiElement*> elements;
	sf::RenderWindow* window;
	sf::View window_view;
	ButtonMenu* menu;
	ViewLayout* layout;
	TileGrid* picker;
	TileGrid* map;
	//sf::Vector2f picker_scroll;
	//sf::Vector2f map_scroll;
	string curr_button;

	TileEditorGui(sf::RenderWindow* window, ButtonMenu* menu, ViewLayout* layout, TileGrid* picker, TileGrid* map);
	void handleInput();
	//void resize();
	void draw();
	//void centerView(sf::View* view, )
private:
	const static int num_buttons = 8;
	float menu_height;
};

