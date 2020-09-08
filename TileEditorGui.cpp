#include "TileEditorGui.h"
#include <iostream>

TileEditorGui::TileEditorGui(sf::RenderWindow* window, ButtonMenu* menu, ViewLayout* layout,
	TileGrid* picker, TileGrid* map) {
	this->window = window;
	this->w = static_cast<float>(window->getSize().x);
	this->h = static_cast<float>(window->getSize().y);
	this->menu_height = 0.08 * h;
	this->menu = menu;
	this->layout = layout;
	this->picker = picker;
	this->map = map;
	//picker_scroll, map_scroll = sf::Vector2f(0, 0);
	//this->picker_scroll = sf::Vector2f(picker->w / 2,picker->h/2);
	//this->map_scroll = sf::Vector2f(picker->w / 2, picker->h / 2);
	//layout->scrollView("picker", sf::Vector2f(0-layout->picker_view.getSize().x+picker->w, 0-layout->picker_view.getSize().y+picker->y));
	//layout->scrollView("picker", sf::Vector2f(20, 40));
	//layout->scrollView("picker", sf::Vector2f(0 - layout->div_x/2 + picker->w/2,
	//	0 - layout->h / 2 + picker->h / 2 + menu_height/2));
	//layout->scrollView("map", sf::Vector2f(0 - layout->map_view.getSize().x/2 + map->w / 2,
	//	0 - layout->h / 2 + map->h / 2 + menu_height / 2));
	//layout->centerView("map");
	//layout->centerView("picker");
	//layout->map_view.setCenter(map->w / 2, map->h / 2);
	//layout->picker_view.setCenter(picker->w / 2, picker->h / 2);
	this->window_view = sf::View(sf::FloatRect(0, 0, w, h));
	this->window->setView(this->window_view);
}

void TileEditorGui::draw() {
	//window->draw(*menu);
	//window->draw(*layout);
	//window->setView(window_view);
	window->setView(layout->picker_view);
	//window->draw(rect2);
	//window->clear(sf::Color(255,0,255,255));
	window->draw(*picker);
	window->setView(layout->map_view);
	//window->draw(rect3);
	//window->clear(sf::Color(0,0,255, 255));
	window->draw(*map);
	window->setView(window_view);
	window->draw(*menu);
	window->draw(*layout);
}

void TileEditorGui::handleInput() {
	sf::Cursor cursor;
	
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view, mouse_pos_map, mouse_pos_picker;
	sf::Vector2f texture_coors;
	sf::RectangleShape rect1 = sf::RectangleShape(sf::Vector2f(200, 200));
	sf::RectangleShape rect2 = sf::RectangleShape(sf::Vector2f(500, 500));
	sf::RectangleShape rect3 = sf::RectangleShape(sf::Vector2f(98,98));
	rect1.setFillColor(sf::Color::Red);
	rect2.setFillColor(sf::Color::Green);
	rect3.setFillColor(sf::Color::Blue);
	float x_ratio, y_ratio;


	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Resized:
					w = static_cast<float>(event.size.width);
					h = static_cast<float>(event.size.height);
					window_view.reset(sf::FloatRect(0, 0, w, h));
					menu->resize(w, menu->h);
					layout->updateWindow(w, h);
					layout->resize(w, h - menu->h);
					//layout->map_view->scrollView("picker", picker_scroll);
					//layout->map_view.move(map_scroll);
					//layout->picker_view.move(picker_scroll);
					break;
				case sf::Event::Closed:
					window->close();
					break;
				case sf::Event::MouseButtonPressed:
					mouse_pos_window = sf::Vector2i(sf::Mouse::getPosition(*window));
					mouse_pos_view = (*window).mapPixelToCoords(mouse_pos_window);
					if (menu->containsMouse(mouse_pos_view.x, mouse_pos_view.y)) {
						//cout << "mouse in menu" << endl;
						for (auto button : menu->buttons) {
							if (button->containsMouse(mouse_pos_view.x, mouse_pos_view.y)) {
								//cout << button->name << " contains mouse" << endl;
								if (button->visible) {button->visible = false;}
								else {button->visible = true;}
							}
							else {
								button->setColor(button->button_color);
							}
						}
					}
					if (layout->containsMouse(mouse_pos_view.x, mouse_pos_view.y)) {
						if (layout->divider.getGlobalBounds().contains(mouse_pos_view.x, mouse_pos_view.y)) {
							layout->moving_divider = true;
							if (cursor.loadFromSystem(sf::Cursor::SizeHorizontal)) {
								window->setMouseCursor(cursor);
							}
						}
						else if (mouse_pos_view.x < layout->div_x) {
							window->setView(layout->picker_view);
							mouse_pos_picker=(*window).mapPixelToCoords(mouse_pos_window);
							cout << mouse_pos_picker.x << ", "<<  mouse_pos_picker.y << endl;
							if (picker->containsMouse(mouse_pos_picker.x, mouse_pos_picker.y)) {
								texture_coors = picker->getTextureCoors(mouse_pos_picker.x, mouse_pos_picker.y);
							}
						}
						else if (mouse_pos_view.x > layout->div_x) {
							window->setView(layout->map_view);
							mouse_pos_map = (*window).mapPixelToCoords(mouse_pos_window);
							if (map->containsMouse(mouse_pos_map.x, mouse_pos_map.y)) {
								map->setTextureCoors(mouse_pos_map.x, mouse_pos_map.y,
									texture_coors.x, texture_coors.y);
							}
						}
					}
					break;
				case sf::Event::MouseMoved:
					mouse_pos_window = sf::Vector2i(sf::Mouse::getPosition(*window));
					mouse_pos_view = (*window).mapPixelToCoords(mouse_pos_window);
					if (layout->moving_divider) {
						if (cursor.loadFromSystem(sf::Cursor::SizeHorizontal)) {
							window->setMouseCursor(cursor);
						}
						layout->moveDivider(mouse_pos_view.x);
					}
					else if (layout->containsMouse(mouse_pos_view.x, mouse_pos_view.y)) {
						if (layout->divider.getGlobalBounds().contains(mouse_pos_view.x, mouse_pos_view.y)) {
							if (cursor.loadFromSystem(sf::Cursor::SizeHorizontal)) {
								window->setMouseCursor(cursor);
							}
						}
						else {
							if (cursor.loadFromSystem(sf::Cursor::Arrow)) {
								window->setMouseCursor(cursor);
							}
						}
					}
					break;
				case sf::Event::MouseButtonReleased:
					if (layout->moving_divider){
						layout->moving_divider = false;
					}
					break;
			}


		}
		mouse_pos_window = sf::Vector2i(sf::Mouse::getPosition(*window));
		mouse_pos_view = (*window).mapPixelToCoords(mouse_pos_window);
		if (menu->containsMouse(mouse_pos_view.x, mouse_pos_view.y)) {
			//cout << "mouse in menu" << endl;
			for (auto button : menu->buttons) {
				if (button->containsMouse(mouse_pos_view.x, mouse_pos_view.y)) {
					//cout << button->name << " contains mouse" << endl;
					button->setColor(button->button_select_color);
				}
				else {
					button->setColor(button->button_color);
				}
			}
		}
		else {
			for (auto button : menu->buttons) {
				button->setColor(button->button_color);
			}
		}
		window->clear(layout->bg_color);
		draw();
		window->display();
	}
}

