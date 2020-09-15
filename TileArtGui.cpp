#include "TileArtGui.h"
#include <iostream>
#include "TileArtGui.h"

TileArtGui::TileArtGui(sf::RenderWindow* window, ButtonMenu* menu, ViewLayout* layout) {
	this->window = window;
	this->w_size = sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));
	this->menu_height = 0.08 * w_size.y;
	this->menu = menu;
	this->layout = layout;
	this->window_view = sf::View(sf::FloatRect(0, 0, w_size.x, w_size.y));
	this->window->setView(this->window_view);
	t_coor = sf::Vector2f(0, 0); t_coor2 = sf::Vector2f(0, 0);
	m_coor = sf::Vector2f(0, 0); m_coor2 = sf::Vector2f(0, 0);
	drawing_mode = true;
	rectangle_mode = false;
	erase_mode = false;
	drawing_now = false;
	selecting_now = false;
}

void TileArtGui::draw() {
	window->setView(window_view);
	window->draw(*menu);
	window->draw(*layout);
	window->setView(window_view);
}

void TileArtGui::onButtonClick(string button) {
	if (button == "save") {
		return;
	}
	else if (button == "draw") {
		drawing_mode = true;
		rectangle_mode = false;
	}
	else if (button == "rect") {
		rectangle_mode = true;
		drawing_mode = false;
	}
	else if (button == "del") {
		if (erase_mode) {
			erase_mode = false;
		}
		else {
			erase_mode = true;
		}
	}
}



void TileArtGui::handleInput() {
	int t_size = layout->map_view->grid->t;
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view; //, mouse_pos_map, mouse_pos_picker;
	sf::Vector2f mouse_pos_picker;
	sf::Vector2f mouse_pos_map;
	sf::Vector2f t_coor = sf::Vector2f(0, 0), t_coor2 = sf::Vector2f(0, 0);				//first coor of current texture rectangle
	//sf::Vector2f t_coor2 = sf::Vector2f(t_size, t_size);	//second coor of current texture rectangle
	//sf::FloatRect t_rect = sf::FloatRect(t_coor, t_coor2);	//texture selection rectangle
	sf::Vector2f m_coor = sf::Vector2f(0, 0), m_coor2 = sf::Vector2f(0, 0) ;				//first coor of map selection
	//sf::Vector2f m_coor2 = sf::Vector2f(t_size, t_size);	//second coor of map selection
	//sf::FloatRect m_rect = sf::FloatRect(m_coor, m_coor2);	//map selection rectangle

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			mouse_pos_window = sf::Mouse::getPosition(*window);
			mouse_pos_view = (*window).mapPixelToCoords(mouse_pos_window);
			switch (event.type)
			{
			case sf::Event::Resized:
				w_size = sf::Vector2f(event.size.width, event.size.height);
				onResize(w_size);
				break;
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseButtonPressed:
				onMouseButtonPressed(mouse_pos_window, mouse_pos_view);
				break;
			case sf::Event::MouseMoved:
				onMouseMoved(mouse_pos_window, mouse_pos_view);
				break;
			case sf::Event::MouseButtonReleased:
				onMouseButtonReleased(mouse_pos_window, mouse_pos_view);
				break;
			case sf::Event::MouseLeft:
				layout->picker_view->grid->hidePosRect();
				layout->map_view->grid->hidePosRect();
				break;
			}
			if (!menu->containsMouse(mouse_pos_view)) {
				for (auto button : menu->buttons) {
					button->setColor(button->button_color);
				}
			}
			window->clear(layout->bg_color);
			draw();
			window->display();

		}
	}
}

void TileArtGui::onResize(sf::Vector2f w_size) {
	window_view.reset(sf::FloatRect(0, 0, w_size.x, w_size.y));
	menu->resize(w_size.x, menu->h);
	layout->updateWindow(w_size);
	layout->resize(w_size.x, w_size.y - menu->h);
}

void TileArtGui::onMouseButtonPressed(sf::Vector2i mouse_pos_window, sf::Vector2f mouse_pos_view) {
	sf::Cursor cursor;
	if (menu->containsMouse(mouse_pos_view)) {
		for (auto button : menu->buttons) {
			if (button->containsMouse(mouse_pos_view)) {
				onButtonClick(button->name);
			}
			else {
				button->setColor(button->button_color);
			}
		}
	}
	if (layout->containsMouse(mouse_pos_view)) {
		/* move divider */
		if (layout->divider.getGlobalBounds().contains(mouse_pos_view.x, mouse_pos_view.y)) {
			layout->moving_divider = true;
			if (cursor.loadFromSystem(sf::Cursor::SizeHorizontal)) {
				window->setMouseCursor(cursor);
			}
		}
		/* initiate texture selection */
		else if (layout->picker_view->containsMouse(mouse_pos_view)) {
			window->setView(layout->picker_view->view);
			mouse_pos_picker = (*window).mapPixelToCoords(mouse_pos_window);
			layout->picker_view->grid->setSelectorRect(mouse_pos_picker, mouse_pos_picker);
			//cout << mouse_pos_picker.x << ", " << mouse_pos_picker.y << endl;
			if (layout->picker_view->grid->containsMouse(mouse_pos_picker)) {
				selecting_now = true;
				t_coor = mouse_pos_picker;
				layout->picker_view->grid->showSelectorRect();
				layout->picker_view->grid->hidePosRect();
			}
		}
		/* start drawing */
		else if (layout->map_view->containsMouse(mouse_pos_view)) {
			window->setView(layout->map_view->view);
			mouse_pos_map = (*window).mapPixelToCoords(mouse_pos_window);
			cout << mouse_pos_map.x << ", " << mouse_pos_map.y << endl;
			if (layout->map_view->grid->containsMouse(mouse_pos_map)) {
				drawing_now = true;
				layout->map_view->grid->setPosRect(mouse_pos_map, mouse_pos_map);
				if (drawing_mode) {
					layout->map_view->grid->showPosRect();
					if (erase_mode) {
						layout->map_view->grid->clear(mouse_pos_map);
					}
					else {
						layout->map_view->grid->setTextureCoors(mouse_pos_map, t_coor);
					}
				}
				else if (rectangle_mode) {
					m_coor = mouse_pos_map;
					layout->map_view->grid->hidePosRect();
					layout->map_view->grid->setSelectorRect(m_coor, m_coor);
					layout->map_view->grid->showSelectorRect();
				}
			}
		}
	}
	window->setView(window_view);
}

void TileArtGui::onMouseMoved(sf::Vector2i mouse_pos_window, sf::Vector2f mouse_pos_view) {
	sf::Cursor cursor;
	/* highlight buttons when hovering over them */
	if (menu->containsMouse(mouse_pos_view)) {
		for (auto button : menu->buttons) {
			if (button->containsMouse(mouse_pos_view)) {
				button->setColor(button->button_select_color);
			}
			else {
				button->setColor(button->button_color);
			}
		}
	}
	/* move divider */
	if (layout->moving_divider) {
		if (cursor.loadFromSystem(sf::Cursor::SizeHorizontal)) {
			window->setMouseCursor(cursor);
		}
		layout->moveDivider(mouse_pos_view.x);
	}
	else if (layout->containsMouse(mouse_pos_view)) {
		/* cursor set to double arrow if over divider */
		if (layout->divider.getGlobalBounds().contains(mouse_pos_view.x, mouse_pos_view.y)) {
			layout->picker_view->grid->hidePosRect();
			if (cursor.loadFromSystem(sf::Cursor::SizeHorizontal)) {
				window->setMouseCursor(cursor);
			}
		}
		else {
			if (cursor.loadFromSystem(sf::Cursor::Arrow)) {
				window->setMouseCursor(cursor);
			}
			/* update picker selection rect and pos rect */
			if (layout->picker_view->containsMouse(mouse_pos_view)) {
				window->setView(layout->picker_view->view);
				mouse_pos_picker = (*window).mapPixelToCoords(mouse_pos_window);
				layout->map_view->grid->hidePosRect();
				if (layout->picker_view->grid->containsMouse(mouse_pos_picker)) {
					if (selecting_now) {
						t_coor2 = mouse_pos_picker;
						layout->picker_view->grid->setSelectorRect(t_coor, t_coor2);
						layout->picker_view->grid->showSelectorRect();
					}
					else {
						layout->picker_view->grid->setPosRect(mouse_pos_picker, mouse_pos_picker);
						layout->picker_view->grid->showPosRect();
					}
				}
				else {
					layout->picker_view->grid->hidePosRect();
				}
			}
			/* update map pos rect and handle drawing logic */
			else if (layout->map_view->containsMouse(mouse_pos_view)) {
				window->setView(layout->map_view->view);
				layout->picker_view->grid->hidePosRect();
				mouse_pos_map = (*window).mapPixelToCoords(mouse_pos_window);
				if (layout->map_view->grid->containsMouse(mouse_pos_map)) {
					layout->map_view->grid->setPosRect(mouse_pos_map, mouse_pos_map);
					if (drawing_now) {
						if (drawing_mode) {
							layout->map_view->grid->showPosRect();
							if (erase_mode) {
								layout->map_view->grid->clear(mouse_pos_map);
							}
							else {
								layout->map_view->grid->setTextureCoors(mouse_pos_map, t_coor);
							}
						}
						else if (rectangle_mode) {
							//m_rect = layout->map_view->grid->getTileRect(m_coor, m_coor2);
							m_coor2 = mouse_pos_map;
							layout->map_view->grid->hidePosRect();
							layout->map_view->grid->setSelectorRect(m_coor, m_coor2);
							layout->map_view->grid->showSelectorRect();
						}
					}
					else layout->map_view->grid->showPosRect();
				}
				else layout->map_view->grid->hidePosRect();
			}
		}
	}
	else {
		layout->picker_view->grid->hidePosRect();
		layout->map_view->grid->hidePosRect();
	}
	window->setView(window_view);
}

void TileArtGui::onMouseButtonReleased(sf::Vector2i mouse_pos_window, sf::Vector2f mouse_pos_view) {
	if (layout->moving_divider) {
		layout->moving_divider = false;
	}
	/* finalize texture selection */
	if (layout->picker_view->containsMouse(mouse_pos_view)) {
		window->setView(layout->picker_view->view);
		mouse_pos_picker = (*window).mapPixelToCoords(mouse_pos_window);
		if (layout->picker_view->grid->containsMouse(mouse_pos_picker)) {
			if (selecting_now) {
				t_coor2 = mouse_pos_picker;
				layout->picker_view->grid->setSelectorRect(t_coor, t_coor2);
				layout->picker_view->grid->showSelectorRect();
			}
			layout->picker_view->grid->setPosRect(mouse_pos_picker, mouse_pos_picker);
			layout->picker_view->grid->showPosRect();
		}
	}
	/* stop drawing, fill map rect w/ curr texture rect */
	else if (layout->map_view->containsMouse(mouse_pos_view)) {
		window->setView(layout->map_view->view);
		mouse_pos_map = (*window).mapPixelToCoords(mouse_pos_window);
		layout->map_view->grid->hideSelectorRect();
		if (layout->map_view->grid->containsMouse(mouse_pos_map)) {
			if (drawing_now) {
				if (drawing_mode) {
					if (erase_mode) {
						layout->map_view->grid->clear(mouse_pos_map);
					}
					else {
						layout->map_view->grid->setTextureCoors(mouse_pos_map, t_coor);
					}
				}
				else if (rectangle_mode) {
					m_coor2 = mouse_pos_map;
					if (erase_mode) {
						cout << "clearing rect" << endl;
						layout->map_view->grid->clearRect(m_coor, m_coor2);
					}
					else {
						layout->map_view->grid->setTextureRect(m_coor, m_coor2, t_coor, t_coor2);
					}
				}
				layout->map_view->grid->setPosRect(mouse_pos_map, mouse_pos_map);
			}
		}
		else {
			layout->map_view->grid->hidePosRect();
		}
	}
	if (drawing_now) {
		drawing_now = false;
	}
	if (selecting_now) {
		selecting_now = false;
	}
	window->setView(window_view);
}
