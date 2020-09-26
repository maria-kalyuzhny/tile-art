#pragma once
#include "TileGridView.h"

TileGridView::TileGridView(const sf::FloatRect& rect, sf::Vector2f w_size, TileGrid* grid) :
	GuiElement(rect.left, rect.top, rect.width, rect.height) {
	this->w_size = w_size;
	this->grid = grid;
	this->view = sf::View(sf::FloatRect(0, 0, w, h));
	this->view.setViewport(sf::FloatRect(x / w_size.x, y / w_size.y, w / w_size.x, h / w_size.y));
	s = sf::Vector2f(0, 0);
	s_delta = grid->t;
	init_zoom = false;
}

void TileGridView::initZoom(float in_zoom) {
	//set initial zoom to fit the screen and save the original zoom value for future reference
	default_zoom = in_zoom;
	z = in_zoom;
	init_zoom = true;
}

void TileGridView::reset(const sf::FloatRect& rect) {
	this->x = rect.left; this->y = rect.top;
	this->w = rect.width; this->h = rect.height;
	resize(w, h);
	full_zoom = std::max(grid->w / w, grid->h / h);
	if (!init_zoom) {
		initZoom(full_zoom);
		default_zoom = full_zoom;
		z = full_zoom;
	}
	view.setSize(w * z, h * z);
	//handleResize();
	handleZoom();
}

void TileGridView::resize(float w, float h) {
	view.reset(sf::FloatRect(0, 0, w, h));
	view.setViewport(sf::FloatRect(x / w_size.x, y / w_size.y, w / w_size.x, h / w_size.y));
}

void TileGridView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.setView(view);
	target.draw(*grid);
	//sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(500,250));
	//target.draw(rect);
}

void TileGridView::zoom(int delta) {
	float temp_z;
	if (delta < 0) {
		for (int i = 0; i >= delta; i -= 1) {
			temp_z = z + 0.01;
			if (temp_z <= max_zoom * default_zoom) {
				z = temp_z;
				view.setSize(w * z, h * z);
				handleZoom();
			}
		}
	}
	else if (delta > 0) {
		for (int i = 0; i <= delta; i += 1) {
			temp_z = z - 0.01;
			if (temp_z >= min_zoom * default_zoom) {
				z = temp_z;
				view.setSize(w * z, h * z);
				handleZoom();
			}
		}
	}
}

void TileGridView::handleZoom() {
	cout << "zoom " << z << endl;
	cout << "view width " << w << endl;
	cout << "grid width " << grid->w / z << endl;
	if (w - grid->w / z > 0) {
		view.setCenter(grid->w / 2, view.getCenter().y);
		s.x = 0;
	}
	else {
		view.setCenter(grid->w / 2, view.getCenter().y);
		view.move(s.x,0);
		//view.setCenter(grid->w/2,view.getCenter().y);
		//cout << "moving view x " << -w / 2 + (w * z) / 2 << endl;
		cout << "x center at " << view.getCenter().x << endl;
		cout << "x left limit at " << floor((w * z) / 2) << endl;
		cout << "x right limit at " << grid->w - floor((w * z) / 2) << endl;
		if (view.getCenter().x >= grid->w - floor((w * z) / 2)) {
			while (view.getCenter().x >= grid->w - floor((w * z) / 2)) {
				view.move(sf::Vector2f(-1, 0));
				cout << "moving right" << endl;
			}
			s.x = view.getCenter().x - grid->w / 2;
		}
		else if (view.getCenter().x <= floor((w * z) / 2)){
			while (view.getCenter().x <= floor((w * z) / 2)) {
				view.move(sf::Vector2f(1, 0));
				cout << "moving left" << endl;
			}
			s.x = view.getCenter().x - grid->w / 2;
		}
	}
	if (h - grid->h / z > 0) {
		view.setCenter(view.getCenter().x, grid->h / 2);
		s.y = 0;
	}
	else {
		view.setCenter(view.getCenter().x, grid->h / 2);
		view.move(0,s.y);
		if (view.getCenter().y >= grid->h - floor((h * z) / 2)) {
			while (view.getCenter().y >= grid->h - floor((h * z) / 2)) {
				view.move(sf::Vector2f(0,-1));
			}
			s.y = view.getCenter().y - grid->h / 2;
		}
		else if (view.getCenter().y <= floor((h * z) / 2)) {
			while (view.getCenter().y <= floor((h * z) / 2)) {
				view.move(sf::Vector2f(0,1));
			}
			s.y = view.getCenter().y - grid->h / 2;
		}
	}
}

void TileGridView::handleResize() {
	if (w - grid->w / z > 0) {
		view.setCenter(grid->w / 2, view.getCenter().y);
		s.x=0;
	}
	else {
		view.setCenter(w/2, view.getCenter().y);
		//view.move(-w / 2 + (w * z) / 2, 0);
		//s.x=view.getCenter().x-grid->w/2;
		view.move(s.x,0);
	}
	if (h - grid->h / z > 0) {
		view.setCenter(view.getCenter().x, grid->h / 2);
		s.y=0;
	}
	else {
		view.setCenter(view.getCenter().x, h / 2);
		//view.move(0, -h / 2 + (h * z) / 2);
		//s.y = view.getCenter().y - grid->w / 2;
		view.move(0,s.y);
	}
}

void TileGridView::scroll(sf::Keyboard::Key key){
	float new_x=0;
	float new_y=0;
	if (key == sf::Keyboard::Key::D) {
		for (int i = 0; i <= s_delta; i++) {
			if (view.getCenter().x+1 <= grid->w - floor((w * z) / 2)) {
				view.move(sf::Vector2f(1, 0));
				s.x = s.x + 1;
			}
			else {
				break;
			}
		}
	}
	else if (key == sf::Keyboard::Key::A) {
		for (int i = 0; i <= s_delta; i++) {
			if (view.getCenter().x-1 >= floor((w * z) / 2)) {
				view.move(sf::Vector2f(-1, 0));
				s.x = s.x - 1;
			}
			else {
				break;
			}
		}
	}
	else if (key == sf::Keyboard::Key::S) {
		for (int i = 0; i <= s_delta; i++) {
			if (view.getCenter().y + 1 <= grid->h - floor((h * z) / 2)) {
				view.move(sf::Vector2f(0, 1));
				s.y = s.y + 1;
			}
			else {
				break;
			}
		}
	}
	else if (key == sf::Keyboard::Key::W) {
		for (int i = 0; i <= s_delta; i++) {
			if (view.getCenter().y - 1 >= floor((h * z) / 2)) {
				view.move(sf::Vector2f(0,-1));
				s.y = s.y - 1;
			}
			else {
				break;
			}
		}
	}
	cout << "center set to" << view.getCenter().x << ", " << view.getCenter().y << endl;
}

void TileGridView::centerOnGrid() {
	if (w - grid->w/z > 0) {
		view.setCenter(grid->w/2,view.getCenter().y);
	}
	if (h - grid->h/z > 0) {
		view.setCenter(view.getCenter().x, grid->h/2);
	}
}

void TileGridView::fitToScreen() {
	float x_ratio = grid->w/w;
	float y_ratio = grid->h/h;
	z = std::max(x_ratio, y_ratio);
	view.setSize(w*z,h*z);
}

void TileGridView::updateWindow(sf::Vector2f w_size) {
	this->w_size = w_size;
}