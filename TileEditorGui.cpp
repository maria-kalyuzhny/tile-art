#include "TileEditorGui.h"
#include <iostream>

TileEditorGui::TileEditorGui(sf::RenderWindow* window, ButtonMenu* menu, ViewLayout* layout) {
	this->window = window;
	this->w_size = sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));
	this->menu_height = 0.08 * w_size.y;
	this->menu = menu;
	this->layout = layout;
	this->window_view = sf::View(sf::FloatRect(0, 0, w_size.x, w_size.y));
	this->window->setView(this->window_view);
}

void TileEditorGui::draw() {
	window->setView(window_view);
	window->draw(*menu);
	window->draw(*layout);
	window->setView(window_view);
}

void TileEditorGui::handleInput() {
	bool drawing_mode = true;
	bool drawing_now = false;
	bool rectangle_mode = false;
	bool erase_mode = false;
	bool selection_mode = false;
	int t_size = layout->map_view->grid->t;
	sf::Cursor cursor;
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view, mouse_pos_map, mouse_pos_picker;
	sf::Vector2f t_coor = sf::Vector2f(0,0);
	sf::Vector2f t_coor2 = sf::Vector2f(t_size, t_size);
	sf::FloatRect t_rect = sf::FloatRect(t_coor, t_coor2-t_coor);

	/*sf::RectangleShape rect1 = sf::RectangleShape(sf::Vector2f(200, 200));
	sf::RectangleShape rect2 = sf::RectangleShape(sf::Vector2f(500, 500));
	sf::RectangleShape rect3 = sf::RectangleShape(sf::Vector2f(98,98));
	rect1.setFillColor(sf::Color::Red);
	rect2.setFillColor(sf::Color::Green);
	rect3.setFillColor(sf::Color::Blue);*/
	//sf::RectangleShape p_rect = sf::RectangleShape(sf::Vector2f(t_size, t_size));
	//sf::RectangleShape m_rect = sf::RectangleShape(sf::Vector2f(t_size, t_size));
	//p_rect.setFillColor(sf::Color::Transparent);
	//m_rect.setFillColor(sf::Color::Transparent);
	//p_rect.setPosition(0, 0);
	//m_rect.setPosition(0, 0);
	//p_rect.set

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Resized:
					w_size = sf::Vector2f(event.size.width, event.size.height);
					window_view.reset(sf::FloatRect(0,0,w_size.x, w_size.y));
					menu->resize(w_size.x, menu->h);
					layout->updateWindow(w_size);
					layout->resize(w_size.x, w_size.y - menu->h);
					break;
				case sf::Event::Closed:
					window->close();
					break;
				case sf::Event::MouseButtonPressed:
					mouse_pos_window = sf::Vector2i(sf::Mouse::getPosition(*window));
					mouse_pos_view = (*window).mapPixelToCoords(mouse_pos_window);
					if (menu->containsMouse(mouse_pos_view)) {
						//cout << "mouse in menu" << endl;
						for (auto button : menu->buttons) {
							if (button->containsMouse(mouse_pos_view)) {
								//cout << button->name << " contains mouse" << endl;
								if (button->visible) { button->visible = false; }
								else { button->visible = true; }
							}
							else {
								button->setColor(button->button_color);
							}
						}
						if (menu->getButton("draw")->containsMouse(mouse_pos_view)){
							drawing_mode = true;
							rectangle_mode = false;
							erase_mode = false;
						}
						if (menu->getButton("rect")->containsMouse(mouse_pos_view)) {
							rectangle_mode = true;
							drawing_mode = false;
							erase_mode = false;
						}
						if (menu->getButton("del")->containsMouse(mouse_pos_view)) {
							erase_mode = true;
						}
					}
					if (layout->containsMouse(mouse_pos_view)) {
						if (layout->divider.getGlobalBounds().contains(mouse_pos_view.x, mouse_pos_view.y)) {
							layout->moving_divider = true;
							if (cursor.loadFromSystem(sf::Cursor::SizeHorizontal)) {
								window->setMouseCursor(cursor);
							}
						}
						else if (mouse_pos_view.x < layout->div_x) {
							window->setView(layout->picker_view->view);
							mouse_pos_picker=(*window).mapPixelToCoords(mouse_pos_window);
							cout << mouse_pos_picker.x << ", "<<  mouse_pos_picker.y << endl;
							if (layout->picker_view->grid->containsMouse(mouse_pos_picker)) {
								t_coor = layout->picker_view->grid->getTextureCoors(sf::Vector2i(mouse_pos_picker));
								t_coor2 = t_coor + sf::Vector2f(t_size, t_size);
								t_rect = sf::FloatRect(t_coor, t_coor2 - t_coor);
								selection_mode = true;
							}
						}
						else if (mouse_pos_view.x > layout->div_x) {
							window->setView(layout->map_view->view);
							mouse_pos_map = (*window).mapPixelToCoords(mouse_pos_window);
							cout << mouse_pos_map.x << ", " << mouse_pos_map.y << endl;
							if (layout->map_view->grid->containsMouse(mouse_pos_map)) {
								layout->map_view->grid->setTextureCoors(sf::Vector2i(mouse_pos_map),t_coor);
								drawing_now = true;
							}
						}
					}
					window->setView(window_view);
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
					else if (menu->containsMouse(mouse_pos_view)) {
						//cout << "mouse in menu" << endl;
						for (auto button : menu->buttons) {
							if (button->containsMouse(mouse_pos_view)) {
								//cout << button->name << " contains mouse" << endl;
								button->setColor(button->button_select_color);
							}
							else {
								button->setColor(button->button_color);
							}
						}
					}
					else if (layout->containsMouse(mouse_pos_view)) {
						if (layout->divider.getGlobalBounds().contains(mouse_pos_view.x, mouse_pos_view.y)) {
							if (cursor.loadFromSystem(sf::Cursor::SizeHorizontal)) {
								window->setMouseCursor(cursor);
							}
						}
						else {
							if (cursor.loadFromSystem(sf::Cursor::Arrow)) {
								window->setMouseCursor(cursor);
							}
							if (mouse_pos_view.x < layout->div_x) {
								window->setView(layout->picker_view->view);
								mouse_pos_picker = (*window).mapPixelToCoords(mouse_pos_window);
								if (layout->picker_view->grid->containsMouse(mouse_pos_picker)) {
									if (selection_mode) {
										t_coor2 = layout->picker_view->grid->getTextureCoors(sf::Vector2i(mouse_pos_picker))
											+ sf::Vector2f(t_size, t_size);
										t_rect = sf::FloatRect(t_coor, t_coor2 - t_coor);
									}
								}
							}
							else if (mouse_pos_view.x > layout->div_x) {
								window->setView(layout->map_view->view);
								mouse_pos_map = (*window).mapPixelToCoords(mouse_pos_window);
								if (layout->map_view->grid->containsMouse(mouse_pos_map)) {
									if (drawing_now) {
										if (drawing_mode) {
											layout->map_view->grid->setTextureCoors(sf::Vector2i(mouse_pos_map), t_coor);
										}
									}
								}
							}
						}
					}
					break;
				case sf::Event::MouseButtonReleased:
					if (layout->moving_divider){
						layout->moving_divider = false;
					}
					if (drawing_now) {
						drawing_now = false;
					}
					break;
			}


		}
		mouse_pos_window = sf::Vector2i(sf::Mouse::getPosition(*window));
		mouse_pos_view = (*window).mapPixelToCoords(mouse_pos_window);
		//if (menu->containsMouse(mouse_pos_view)) {
		//	//cout << "mouse in menu" << endl;
		//	for (auto button : menu->buttons) {
		//		if (button->containsMouse(mouse_pos_view)) {
		//			//cout << button->name << " contains mouse" << endl;
		//			button->setColor(button->button_select_color);
		//		}
		//		else {
		//			button->setColor(button->button_color);
		//		}
		//	}
		//}
		if (!menu->containsMouse(mouse_pos_view)) {
			for (auto button : menu->buttons) {
				button->setColor(button->button_color);
			}
		}
		window->clear(layout->bg_color);
		draw();
		//window->setView(layout->picker_view->view);
		//window->draw(rect1);
		//window->setView(window_view);
		window->display();
	}
}

