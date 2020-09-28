#include "TileArtGui.h"
#include <iostream>
#include "TileArtGui.h"

TileArtGui::TileArtGui(sf::RenderWindow* window, ButtonMenu* menu, ViewLayout* layout, string output_file) {
	this->window = window;
	this->w_size = sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));
	this->menu_height = 0.08 * w_size.y;
	this->menu = menu;
	this->layout = layout;
	this->window_view = sf::View(sf::FloatRect(0, 0, w_size.x, w_size.y));
	this->window->setView(this->window_view);
	this->output_file = output_file;
	t_coor = sf::Vector2f(0, 0); t_coor2 = sf::Vector2f(0, 0);
	m_coor = sf::Vector2f(0, 0); m_coor2 = sf::Vector2f(0, 0);
	pencil_mode = true;
	rectangle_mode = false;
	erase_mode = false;
	fill_mode = false;
	drawing_now = false;
	selecting_now = false;
	shift_down = false;
	mouse_in_curr_button = false;
}

void TileArtGui::draw() {
	window->setView(window_view);
	window->draw(*menu);
	window->draw(*layout);
	window->setView(window_view);
}

void TileArtGui::handleInput() {
	int t_size = layout->map_view->grid->t;
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view;
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
			case sf::Event::MouseWheelMoved:
				onMouseWheelMoved(mouse_pos_view, event.mouseWheel.delta);
				break;
			case sf::Event::KeyPressed:
				onKeyPressed(mouse_pos_view, event.key.code);
				break;
			}
			window->clear(layout->bg_color);
			draw();
			window->display();

		}
		if (clock.getElapsedTime().asSeconds() >= delay &&
			mouse_in_curr_button && curr_button) {
			cout << "showing description" << endl;
			curr_button->description->show();
			window->clear(layout->bg_color);
			draw();
			window->display();
		}
	}
}

void TileArtGui::onButtonClick(string button) {
	if (button == "save") {
		sf::Image img = layout->map_view->grid->getImage();
		if (img.saveToFile(output_file)) {
			cout << "Saved tile grid to file " << output_file << endl;
		}
	}

	else if (button == "pencil") {
		if (!pencil_mode) {
			pencil_mode = true;
			rectangle_mode = false;
			fill_mode = false;
		}
	}
	else if (button == "rectangle") {
		if (!rectangle_mode) {
			pencil_mode=false;
			rectangle_mode = true;
			fill_mode=false;
		}
	}
	else if (button == "fill") {
		if (!rectangle_mode) {
			rectangle_mode = false;
			pencil_mode = false;
			fill_mode = true;
		}
	}
	else if (button == "erase") {
		menu->getButton(button)->toggle();
		if (erase_mode) {
			erase_mode = false;
		}
		else {
			erase_mode = true;
		}
	}

}

void TileArtGui::onMouseButtonPressed(sf::Vector2i mouse_pos_window, sf::Vector2f mouse_pos_view) {
	sf::Cursor cursor;
	if (menu->containsMouse(mouse_pos_view)) {
		for (auto button : menu->buttons) {
			if (button->containsMouse(mouse_pos_view)) {
				onButtonClick(button->name);
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
			cout << mouse_pos_picker.x << ", " << mouse_pos_picker.y << endl;
			if (layout->picker_view->grid->containsMouse(mouse_pos_picker)) {
				layout->picker_view->grid->setSelectorRect(mouse_pos_picker, mouse_pos_picker);
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
				if (rectangle_mode) {
					m_coor = mouse_pos_map;
					layout->map_view->grid->hidePosRect();
					layout->map_view->grid->setSelectorRect(m_coor, m_coor);
					layout->map_view->grid->showSelectorRect();
				}
				else {
					layout->map_view->grid->showPosRect();
					if (erase_mode) {
						layout->map_view->grid->clear(mouse_pos_map);
					}
					else {
						layout->map_view->grid->setTextureCoors(mouse_pos_map, t_coor);
					}
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
		mouse_in_curr_button=false;
		for (auto button : menu->buttons) {
			//button->description->hide();
			if (button->containsMouse(mouse_pos_view)) {
				button->hover();
				curr_button = button;
				mouse_in_curr_button=true;
			}
			else {
				button->unhover();
				button->description->hide();
			}
		}
	}
	else {
		mouse_in_curr_button = false;
		for (auto button : menu->buttons) {
			button->unhover();
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
			layout->map_view->grid->hidePosRect();
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
						if (rectangle_mode) {
							t_coor2 = mouse_pos_picker;
							layout->picker_view->grid->setSelectorRect(t_coor, t_coor2);
						}
						else {
							t_coor = mouse_pos_picker;
							layout->picker_view->grid->setSelectorRect(t_coor, t_coor);
						}
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
						if (rectangle_mode) {
							//m_rect = layout->map_view->grid->getTileRect(m_coor, m_coor2);
							m_coor2 = mouse_pos_map;
							layout->map_view->grid->hidePosRect();
							layout->map_view->grid->setSelectorRect(m_coor, m_coor2);
							layout->map_view->grid->showSelectorRect();
						}
						else {
							layout->map_view->grid->showPosRect();
							if (erase_mode) {
								layout->map_view->grid->clear(mouse_pos_map);
							}
							else {
								layout->map_view->grid->setTextureCoors(mouse_pos_map, t_coor);
							}
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
	clock.restart();
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
				if (rectangle_mode) {
					t_coor2 = mouse_pos_picker;
					layout->picker_view->grid->setSelectorRect(t_coor, t_coor2);
				}
				else {
					t_coor = mouse_pos_picker;
					layout->picker_view->grid->setSelectorRect(t_coor, t_coor);
				}
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
				if (rectangle_mode) {
					m_coor2 = mouse_pos_map;
					if (erase_mode) {
						layout->map_view->grid->clearRect(m_coor, m_coor2);
					}
					else {
						layout->map_view->grid->setTextureRect(m_coor, m_coor2, t_coor, t_coor2);
					}
				}
				else {
					if (erase_mode) {
						layout->map_view->grid->clear(mouse_pos_map);
					}
					else {
						layout->map_view->grid->setTextureCoors(mouse_pos_map, t_coor);
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

void TileArtGui::onMouseWheelMoved(sf::Vector2f mouse_pos_view, int delta) {
	std::cout << "delta" << delta << endl;
	if (layout->picker_view->containsMouse(mouse_pos_view)) {
		layout->picker_view->zoom(delta);
	}
	else if (layout->map_view->containsMouse(mouse_pos_view)) {
		layout->map_view->zoom(delta);
	}
}

void TileArtGui::onKeyPressed(sf::Vector2f mouse_pos_view, sf::Keyboard::Key key) {
	if (layout->picker_view->containsMouse(mouse_pos_view)) {
		layout->picker_view->scroll(key);
		return;
	}
	else if (layout->map_view->containsMouse(mouse_pos_view)) {
		layout->map_view->scroll(key); 
		return;
	}
}

void TileArtGui::onResize(sf::Vector2f w_size) {
	window_view.reset(sf::FloatRect(0, 0, w_size.x, w_size.y));
	menu->resize(w_size.x, menu->h);
	layout->updateWindow(w_size);
	layout->resize(w_size.x, w_size.y - menu->h);
}